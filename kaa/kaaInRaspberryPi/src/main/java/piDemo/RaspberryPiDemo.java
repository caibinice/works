package piDemo;

import org.kaaproject.kaa.client.DesktopKaaPlatformContext;
import org.kaaproject.kaa.client.Kaa;
import org.kaaproject.kaa.client.KaaClient;
import org.kaaproject.kaa.client.SimpleKaaClientStateListener;
import org.kaaproject.kaa.client.configuration.base.ConfigurationListener;
import org.kaaproject.kaa.client.configuration.base.SimpleConfigurationStorage;
import org.kaaproject.kaa.client.logging.strategies.RecordCountLogUploadStrategy;
import org.kaaproject.kaa.schema.pi.Configuration;
import org.kaaproject.kaa.schema.pi.DataCollection;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.ScheduledFuture;
import java.util.concurrent.TimeUnit;

/**
 * Class implement functionality for First Kaa application. Application send temperature data
 * from the Kaa endpoint with required configured sampling period
 */
public class RaspberryPiDemo {

    private static final long DEFAULT_START_DELAY = 1000L;

    private static final Logger LOG = LoggerFactory.getLogger(RaspberryPiDemo.class);

    private static KaaClient kaaClient;

    private static ScheduledFuture<?> scheduledFuture;
    private static ScheduledExecutorService scheduledExecutorService;

    public static void main(String[] args) {
        LOG.info(RaspberryPiDemo.class.getSimpleName() + " app starting!");

        scheduledExecutorService = Executors.newScheduledThreadPool(1);

        //Create the Kaa desktop context for the application.
        DesktopKaaPlatformContext desktopKaaPlatformContext = new DesktopKaaPlatformContext();

        /*
         * Create a Kaa client and add a listener which displays the Kaa client
         * configuration as soon as the Kaa client is started.
         */
        kaaClient = Kaa.newClient(desktopKaaPlatformContext, new FirstKaaClientStateListener(), true);

        /*
         *  Used by log collector on each adding of the new log record in order to check whether to send logs to server.
         *  Start log upload when there is at least one record in storage.
         */
        RecordCountLogUploadStrategy strategy = new RecordCountLogUploadStrategy(1);
        strategy.setMaxParallelUploads(1);
        kaaClient.setLogUploadStrategy(strategy);

        /*
         * Persist configuration in a local storage to avoid downloading it each
         * time the Kaa client is started.
         */
        kaaClient.setConfigurationStorage(new SimpleConfigurationStorage(desktopKaaPlatformContext, "saved_config.cfg"));

        kaaClient.addConfigurationListener(new ConfigurationListener() {
            @Override
            public void onConfigurationUpdate(Configuration configuration) {
                LOG.info("Received configuration data. New sample period: {}", configuration.getSamplePeriod());
                onChangedConfiguration(TimeUnit.SECONDS.toMillis(configuration.getSamplePeriod()));
            }
        });

        //Start the Kaa client and connect it to the Kaa server.
        kaaClient.start();

        LOG.info("--= Press any key to exit =--");
        try {
            System.in.read();
        } catch (IOException e) {
            LOG.error("IOException has occurred: {}", e.getMessage());
        }
        LOG.info("Stopping...");
        scheduledExecutorService.shutdown();
        kaaClient.stop();
    }

    /*
        get cpu temp
    */
    private static double getCPUTemp() {
        try {
            FileReader reader = new FileReader("/sys/class/thermal/thermal_zone0/temp");
            BufferedReader br = new BufferedReader(reader);
            String str;
            if ((str = br.readLine()) != null) {
                return new Double(str.trim()) / 1000;
            }
            return 0.0;

        } catch (Exception e) {
            e.printStackTrace();
            return 0.0;
        }
    }

    /*
        get used memory
    */
    private static int getUsedMem() {
        try {
            FileReader fr_mem_usage = new FileReader("/proc/meminfo");
            BufferedReader br_mem_usage = new BufferedReader(fr_mem_usage);
            String s_mem_total = br_mem_usage.readLine();
            String s_mem_free = br_mem_usage.readLine();
            br_mem_usage.readLine();
            String s_mem_buffers = br_mem_usage.readLine();
            String s_mem_cached = br_mem_usage.readLine();
            String[] s_mem_total_array = s_mem_total.split("\\s+");
            String[] s_mem_free_array = s_mem_free.split("\\s+");
            String[] s_mem_buffers_array = s_mem_buffers.split("\\s+");
            String[] s_mem_cached_array = s_mem_cached.split("\\s+");
            int mem_total = Integer.parseInt(s_mem_total_array[1]);
            int mem_free = Integer.parseInt(s_mem_free_array[1]);
            int mem_buffers = Integer.parseInt(s_mem_buffers_array[1]);
            int mem_cached = Integer.parseInt(s_mem_cached_array[1]);
            int memUsage = mem_total - (mem_free + mem_buffers + mem_cached);
            fr_mem_usage.close();
            br_mem_usage.close();
            return memUsage;
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private static void onKaaStarted(long time) {
        if (time <= 0) {
            LOG.error("Wrong time is used. Please, check your configuration!");
            kaaClient.stop();
            System.exit(0);
        }

        scheduledFuture = scheduledExecutorService.scheduleAtFixedRate(
                new Runnable() {
                    @Override
                    public void run() {
                        try {
                            Double cpu = getCPUTemp();
                            int memUsed = getUsedMem();
                            kaaClient.addLogRecord(new DataCollection(cpu, memUsed));
                            LOG.info("Data~~~~~~~~~~~~:CPU Temp - " + cpu + "°C,  memUsed - " + memUsed + "KB ~~~~~~~~~~~~");
                        } catch (Exception e) {
                            LOG.error("exception occur");
                        }
                    }
                }, 0, time, TimeUnit.MILLISECONDS);
    }

    private static void onChangedConfiguration(long time) {
        if (time == 0) {
            time = DEFAULT_START_DELAY;
        }
        scheduledFuture.cancel(false);

        scheduledFuture = scheduledExecutorService.scheduleAtFixedRate(
                new Runnable() {
                    @Override
                    public void run() {
                        kaaClient.addLogRecord(new DataCollection(1.0, 0));
                        LOG.info("Configuration Changed: {}", 1.0);
                    }
                }, 0, time, TimeUnit.MILLISECONDS);
    }

    private static class FirstKaaClientStateListener extends SimpleKaaClientStateListener {

        @Override
        public void onStarted() {
            super.onStarted();
            LOG.info("Kaa client started");
            Configuration configuration = kaaClient.getConfiguration();
            LOG.info("Default sample period: {}", configuration.getSamplePeriod());
            onKaaStarted(TimeUnit.SECONDS.toMillis(configuration.getSamplePeriod()));
        }

        @Override
        public void onStopped() {
            super.onStopped();
            LOG.info("Kaa client stopped");
        }
    }
}