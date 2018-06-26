#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <kaa.h>
#include <platform/kaa_client.h>
#include <kaa_error.h>
#include <kaa_configuration_manager.h>
#include <kaa_logging.h>
#include <gen/kaa_logging_gen.h>
#include <platform/kaa_client.h>
#include <utilities/kaa_log.h>
#include <utilities/kaa_mem.h>
#include <platform-impl/common/ext_log_upload_strategies.h>

#include <extensions/notification/kaa_notification_manager.h>
#include <kaa/platform/ext_notification_receiver.h>

#define BUFF_SIZE 65536
static char buff[BUFF_SIZE];
static int g_single_proc_inst_lock_fd = -1;  

kaa_client_t *kaa_client = NULL;

static int32_t sample_period;
static int32_t latitude = 0;
static int32_t longitude = 100;
static time_t  last_sample_time;
extern int exec_sb(char *cmd, char *res_buff, size_t size);
extern kaa_error_t ext_unlimited_log_storage_create(void **log_storage_context_p, kaa_logger_t *logger);
/* Retrieves current temperature. */
static int32_t get_temperature_sample(void)
{
    /* For the sake of example, random data is used */
    return rand() % 10 + 25;
}
/* Periodically called by Kaa SDK. */
static void example_callback(void *context)
{
    time_t current_time = time(NULL);
    /* Respect sample period */
    if (difftime(current_time, last_sample_time) >= sample_period) {
        latitude++;
        longitude++;
        int32_t temperature = get_temperature_sample();
        printf("Sampled temperature: %i\n", temperature);
        printf("Sampled longitude: %i, latitude: %i\n", longitude, latitude);
        last_sample_time = current_time;
        kaa_user_log_record_t *log_record = kaa_logging_data_collection2_create();
        log_record->nodeid = kaa_string_copy_create("SB1");
        printf("Sampled SB1 ok \n");
        if (temperature % 2 == 0) {
            log_record->weaher__temperature = kaa_logging_union_int_or_null_branch_0_create();
            int32_t* temp = (int32_t *)KAA_MALLOC(sizeof(int32_t));
            *temp = temperature;
            log_record->weaher__temperature->data = temp;
        }
        else {
            log_record->weaher__temperature = kaa_logging_union_int_or_null_branch_1_create();
        }
        printf("Sampled temperature ok \n");
        log_record->coordinate__longitude = kaa_logging_union_double_or_null_branch_0_create();
        double* lon = (double *)KAA_MALLOC(sizeof(double));
        *lon = (double)longitude;
        log_record->coordinate__longitude->data = lon;
        printf("Sampled longitude ok \n");
        if (latitude % 2 == 0) {
            log_record->coordinate__latitude = kaa_logging_union_double_or_null_branch_0_create();
            double* lat = (double *)KAA_MALLOC(sizeof(double));
            *lat = (double)latitude;
            log_record->coordinate__latitude->data = lat;
        }
        else {
            log_record->coordinate__latitude = kaa_logging_union_double_or_null_branch_1_create();
        }
        printf("Sampled latitude ok \n");
        kaa_logging_add_record(kaa_client_get_context(context)->log_collector, log_record, NULL);
        printf("Sampled add_record ok \n");
        log_record->destroy(log_record);
        printf("Sampled destroy ok \n");

        if (latitude > 50) kaa_client_stop(kaa_client);
    }

}
/* Receives new configuration data. */
static kaa_error_t on_configuration_updated(void *context, const kaa_root_configuration_t *conf)
{
    (void) context;
    printf("Received configuration data. New sample period: %i seconds\n", conf->sample_period);
    sample_period = conf->sample_period;
    return KAA_ERR_NONE;
}

void on_notification(void *context, uint64_t *topic_id, kaa_notification_t *notification)
{
	(void) context;
    printf("Received notification on topic %llu: message='%s'\n", *topic_id, notification->message->data);
    char test[256];
    strncpy(test, notification->message->data, sizeof(test));
    int rv = exec_sb(test, buff, BUFF_SIZE);
    printf("exec_sb rv=%d\n", rv);
    if (rv == 0) {
        printf(buff);
    }
}
  
static void single_proc_inst_lockfile_cleanup(void)  
{  
    if (g_single_proc_inst_lock_fd != -1) {  
        close(g_single_proc_inst_lock_fd);  
        g_single_proc_inst_lock_fd = -1;  
    }  
}  
  
int is_single_proc_inst_running(const char *process_name)  
{  
    char lock_file[128];  
    snprintf(lock_file, sizeof(lock_file), "/var/tmp/%s.lock", process_name);  
  
    g_single_proc_inst_lock_fd = open(lock_file, O_CREAT|O_RDWR, 0644);  
    if (-1 == g_single_proc_inst_lock_fd) {  
        fprintf(stderr, "Fail to open lock file(%s). Error: %s\n",  
            lock_file, strerror(errno));  
        return 1;  
    }  
    if (0 == flock(g_single_proc_inst_lock_fd, LOCK_EX | LOCK_NB)) {  
        atexit(single_proc_inst_lockfile_cleanup);  
        return 0;  
    }  
    close(g_single_proc_inst_lock_fd);  
    g_single_proc_inst_lock_fd = -1;  
    return 2;  
} 

int main(void)
{
    //判断是否已经有相同进程在运行
    if (is_single_proc_inst_running("kaaClientDemo")) {
        exit(0);
    }    

    /* Init random generator used to generate temperature */
    srand(time(NULL));
    /* Prepare Kaa client. */

    kaa_error_t error = kaa_client_create(&kaa_client, NULL);
    if (error) {
        return EXIT_FAILURE;
    }
    /* Configure notification manager. */
    kaa_configuration_root_receiver_t receiver = {
        .context = NULL,
        .on_configuration_updated = on_configuration_updated
    };
    error = kaa_configuration_manager_set_root_receiver(
        kaa_client_get_context(kaa_client)->configuration_manager,
        &receiver);
    if (error) {
        return EXIT_FAILURE;
    }
    /* Obtain default configuration shipped within SDK. */
    const kaa_root_configuration_t *dflt = kaa_configuration_manager_get_configuration(
        kaa_client_get_context(kaa_client)->configuration_manager);
    printf("Default sample period: %i seconds\n", dflt->sample_period);
    sample_period = dflt->sample_period;

    /* Configure data collection. */
    void *log_storage_context         = NULL;
    void *log_upload_strategy_context = NULL;
    /* The internal memory log storage distributed with Kaa SDK. */
    error = ext_unlimited_log_storage_create(&log_storage_context,
        kaa_client_get_context(kaa_client)->logger);
    if (error) {
        return EXIT_FAILURE;
    }
    /* Create a strategy based on timeout. */
    error = ext_log_upload_strategy_create(
        kaa_client_get_context(kaa_client), &log_upload_strategy_context,
        KAA_LOG_UPLOAD_BY_TIMEOUT_STRATEGY);
    if (error) {
        return EXIT_FAILURE;
    }
    /* Strategy will upload logs every 5 seconds. */
    error = ext_log_upload_strategy_set_upload_timeout(log_upload_strategy_context, 5);
    if (error) {
        return EXIT_FAILURE;
    }
    /* Specify log bucket size constraints. */
    kaa_log_bucket_constraints_t bucket_sizes = {
         .max_bucket_size       = 32,   /* Bucket size in bytes. */
         .max_bucket_log_count  = 2,    /* Maximum log count in one bucket. */
    };
    /* Initialize the log storage and strategy (by default, they are not set). */
    error = kaa_logging_init(kaa_client_get_context(kaa_client)->log_collector,
        log_storage_context, log_upload_strategy_context, &bucket_sizes);
    if (error) {
        return EXIT_FAILURE;
    }

    kaa_notification_listener_t notification_listener = { &on_notification, NULL };
    uint32_t notification_listener_id = 0;
    // Add listener
    error = kaa_add_notification_listener(kaa_client_get_context(kaa_client)->notification_manager, &notification_listener, &notification_listener_id);
    if (error) {
        printf("Failed to listen notification: %i \n", error);
        return EXIT_FAILURE;
    }

    /* Start Kaa SDK's main loop. example_callback is called once per second. */
    error = kaa_client_start(kaa_client, example_callback, kaa_client, 1);
    if (error) {
        kaa_client_destroy(kaa_client);
        return EXIT_FAILURE;
    }

    error = kaa_remove_notification_listener(kaa_client_get_context(kaa_client)->notification_manager, &notification_listener_id);
    if (error) {
        return EXIT_FAILURE;
    }

    /* Should get here only after Kaa stops. */
    kaa_client_destroy(kaa_client);

    return EXIT_SUCCESS;
}
