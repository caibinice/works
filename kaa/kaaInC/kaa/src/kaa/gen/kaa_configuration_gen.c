/*
 * Copyright 2014-2016 CyberVision, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

# include <inttypes.h>
# include <string.h>
# include "platform/stdio.h"
# include "kaa_configuration_gen.h"
# include "avro_src/avro/io.h"
# include "avro_src/encoding.h"
# include "utilities/kaa_mem.h"

/*
 * AUTO-GENERATED CODE
 */




static void kaa_configuration_configuration_serialize(avro_writer_t writer, void *data)
{
    if (data) {
        kaa_configuration_configuration_t *record = (kaa_configuration_configuration_t *)data;

        kaa_int_serialize(writer, &record->sample_period);
    }
}

static size_t kaa_configuration_configuration_get_size(void *data)
{
    if (data) {
        size_t record_size = 0;
        kaa_configuration_configuration_t *record = (kaa_configuration_configuration_t *)data;

        record_size += kaa_int_get_size(&record->sample_period);

        return record_size;
    }

    return 0;
}

kaa_configuration_configuration_t *kaa_configuration_configuration_create(void)
{
    kaa_configuration_configuration_t *record = 
            (kaa_configuration_configuration_t *)KAA_CALLOC(1, sizeof(kaa_configuration_configuration_t));

    if (record) {
        record->serialize = kaa_configuration_configuration_serialize;
        record->get_size = kaa_configuration_configuration_get_size;
        record->destroy = kaa_data_destroy;
    }

    return record;
}

kaa_configuration_configuration_t *kaa_configuration_configuration_deserialize(avro_reader_t reader)
{
    kaa_configuration_configuration_t *record = 
            (kaa_configuration_configuration_t *)KAA_MALLOC(sizeof(kaa_configuration_configuration_t));

    if (record) {
        record->serialize = kaa_configuration_configuration_serialize;
        record->get_size = kaa_configuration_configuration_get_size;
        record->destroy = kaa_data_destroy;

        avro_binary_encoding.read_int(reader, &record->sample_period);
    }

    return record;
}

