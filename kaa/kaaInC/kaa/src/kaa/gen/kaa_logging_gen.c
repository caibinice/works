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
# include "kaa_logging_gen.h"
# include "avro_src/avro/io.h"
# include "avro_src/encoding.h"
# include "utilities/kaa_mem.h"

/*
 * AUTO-GENERATED CODE
 */



# ifndef KAA_LOGGING_UNION_INT_OR_NULL_C_
# define KAA_LOGGING_UNION_INT_OR_NULL_C_
static void kaa_logging_union_int_or_null_destroy(void *data)
{
    if (data) {
        kaa_union_t *kaa_union = (kaa_union_t *)data;

        switch (kaa_union->type) {
        case KAA_LOGGING_UNION_INT_OR_NULL_BRANCH_0:
        {
            if (kaa_union->data) {
                kaa_data_destroy(kaa_union->data);
            }
            break;
        }
        default:
            break;
        }

        kaa_data_destroy(kaa_union);
    }
}

static size_t kaa_logging_union_int_or_null_get_size(void *data)
{
    if (data) {
        kaa_union_t *kaa_union = (kaa_union_t *)data;
        size_t union_size = avro_long_get_size(kaa_union->type);

        switch (kaa_union->type) {
        case KAA_LOGGING_UNION_INT_OR_NULL_BRANCH_0:
        {
            if (kaa_union->data) {
                union_size += kaa_int_get_size(kaa_union->data);
            }
            break;
        }
        default:
            break;
        }

        return union_size;
    }

    return 0;
}

static void kaa_logging_union_int_or_null_serialize(avro_writer_t writer, void *data)
{
    if (data) {
        kaa_union_t *kaa_union = (kaa_union_t *)data;
        avro_binary_encoding.write_long(writer, kaa_union->type);

        switch (kaa_union->type) {
        case KAA_LOGGING_UNION_INT_OR_NULL_BRANCH_0:
        {
            if (kaa_union->data) {
                kaa_int_serialize(writer, kaa_union->data);
            }
            break;
        }
        default:
            break;
        }
    }
}
static kaa_union_t *kaa_logging_union_int_or_null_create(void)
{
    kaa_union_t *kaa_union = KAA_CALLOC(1, sizeof(kaa_union_t));

    if (kaa_union) {
        kaa_union->serialize = kaa_logging_union_int_or_null_serialize;
        kaa_union->get_size = kaa_logging_union_int_or_null_get_size;
        kaa_union->destroy = kaa_logging_union_int_or_null_destroy;
    }

    return kaa_union; 
}

kaa_union_t *kaa_logging_union_int_or_null_branch_0_create(void)
{
    kaa_union_t *kaa_union = kaa_logging_union_int_or_null_create();
    if (kaa_union) {
        kaa_union->type = KAA_LOGGING_UNION_INT_OR_NULL_BRANCH_0;
    }
    return kaa_union;
}

kaa_union_t *kaa_logging_union_int_or_null_branch_1_create(void)
{
    kaa_union_t *kaa_union = kaa_logging_union_int_or_null_create();
    if (kaa_union) {
        kaa_union->type = KAA_LOGGING_UNION_INT_OR_NULL_BRANCH_1;
    }
    return kaa_union;
}

kaa_union_t *kaa_logging_union_int_or_null_deserialize(avro_reader_t reader)
{
    kaa_union_t *kaa_union = kaa_logging_union_int_or_null_create();

    if (kaa_union) {
        int64_t branch;
        avro_binary_encoding.read_long(reader, &branch);
        kaa_union->type = branch;

        switch (kaa_union->type) {
        case KAA_LOGGING_UNION_INT_OR_NULL_BRANCH_0: {
            kaa_union->data = kaa_int_deserialize(reader);
            break;
        }
        default:
            break;
        }
    }

    return kaa_union;
}
# endif // KAA_LOGGING_UNION_INT_OR_NULL_C_



# ifndef KAA_LOGGING_UNION_DOUBLE_OR_NULL_C_
# define KAA_LOGGING_UNION_DOUBLE_OR_NULL_C_
static void kaa_logging_union_double_or_null_destroy(void *data)
{
    if (data) {
        kaa_union_t *kaa_union = (kaa_union_t *)data;

        switch (kaa_union->type) {
        case KAA_LOGGING_UNION_DOUBLE_OR_NULL_BRANCH_0:
        {
            if (kaa_union->data) {
                kaa_data_destroy(kaa_union->data);
            }
            break;
        }
        default:
            break;
        }

        kaa_data_destroy(kaa_union);
    }
}

static size_t kaa_logging_union_double_or_null_get_size(void *data)
{
    if (data) {
        kaa_union_t *kaa_union = (kaa_union_t *)data;
        size_t union_size = avro_long_get_size(kaa_union->type);

        switch (kaa_union->type) {
        case KAA_LOGGING_UNION_DOUBLE_OR_NULL_BRANCH_0:
        {
            if (kaa_union->data) {
                union_size += AVRO_DOUBLE_SIZE;
            }
            break;
        }
        default:
            break;
        }

        return union_size;
    }

    return 0;
}

static void kaa_logging_union_double_or_null_serialize(avro_writer_t writer, void *data)
{
    if (data) {
        kaa_union_t *kaa_union = (kaa_union_t *)data;
        avro_binary_encoding.write_long(writer, kaa_union->type);

        switch (kaa_union->type) {
        case KAA_LOGGING_UNION_DOUBLE_OR_NULL_BRANCH_0:
        {
            if (kaa_union->data) {
                kaa_double_serialize(writer, kaa_union->data);
            }
            break;
        }
        default:
            break;
        }
    }
}
static kaa_union_t *kaa_logging_union_double_or_null_create(void)
{
    kaa_union_t *kaa_union = KAA_CALLOC(1, sizeof(kaa_union_t));

    if (kaa_union) {
        kaa_union->serialize = kaa_logging_union_double_or_null_serialize;
        kaa_union->get_size = kaa_logging_union_double_or_null_get_size;
        kaa_union->destroy = kaa_logging_union_double_or_null_destroy;
    }

    return kaa_union; 
}

kaa_union_t *kaa_logging_union_double_or_null_branch_0_create(void)
{
    kaa_union_t *kaa_union = kaa_logging_union_double_or_null_create();
    if (kaa_union) {
        kaa_union->type = KAA_LOGGING_UNION_DOUBLE_OR_NULL_BRANCH_0;
    }
    return kaa_union;
}

kaa_union_t *kaa_logging_union_double_or_null_branch_1_create(void)
{
    kaa_union_t *kaa_union = kaa_logging_union_double_or_null_create();
    if (kaa_union) {
        kaa_union->type = KAA_LOGGING_UNION_DOUBLE_OR_NULL_BRANCH_1;
    }
    return kaa_union;
}

kaa_union_t *kaa_logging_union_double_or_null_deserialize(avro_reader_t reader)
{
    kaa_union_t *kaa_union = kaa_logging_union_double_or_null_create();

    if (kaa_union) {
        int64_t branch;
        avro_binary_encoding.read_long(reader, &branch);
        kaa_union->type = branch;

        switch (kaa_union->type) {
        case KAA_LOGGING_UNION_DOUBLE_OR_NULL_BRANCH_0: {
            kaa_union->data = kaa_double_deserialize(reader);
            break;
        }
        default:
            break;
        }
    }

    return kaa_union;
}
# endif // KAA_LOGGING_UNION_DOUBLE_OR_NULL_C_



static void kaa_logging_data_collection2_destroy(void *data)
{
    if (data) {
        kaa_logging_data_collection2_t *record = (kaa_logging_data_collection2_t *)data;

        kaa_string_destroy(record->nodeid);
        if (record->weaher__temperature && record->weaher__temperature->destroy) {
            record->weaher__temperature->destroy(record->weaher__temperature);
        }
        if (record->coordinate__latitude && record->coordinate__latitude->destroy) {
            record->coordinate__latitude->destroy(record->coordinate__latitude);
        }
        if (record->coordinate__longitude && record->coordinate__longitude->destroy) {
            record->coordinate__longitude->destroy(record->coordinate__longitude);
        }
        kaa_data_destroy(record);
    }
}

static void kaa_logging_data_collection2_serialize(avro_writer_t writer, void *data)
{
    if (data) {
        kaa_logging_data_collection2_t *record = (kaa_logging_data_collection2_t *)data;

        kaa_string_serialize(writer, record->nodeid);
        record->weaher__temperature->serialize(writer, record->weaher__temperature);
        record->coordinate__latitude->serialize(writer, record->coordinate__latitude);
        record->coordinate__longitude->serialize(writer, record->coordinate__longitude);
    }
}

static size_t kaa_logging_data_collection2_get_size(void *data)
{
    if (data) {
        size_t record_size = 0;
        kaa_logging_data_collection2_t *record = (kaa_logging_data_collection2_t *)data;

        record_size += kaa_string_get_size(record->nodeid);
        record_size += record->weaher__temperature->get_size(record->weaher__temperature);
        record_size += record->coordinate__latitude->get_size(record->coordinate__latitude);
        record_size += record->coordinate__longitude->get_size(record->coordinate__longitude);

        return record_size;
    }

    return 0;
}

kaa_logging_data_collection2_t *kaa_logging_data_collection2_create(void)
{
    kaa_logging_data_collection2_t *record = 
            (kaa_logging_data_collection2_t *)KAA_CALLOC(1, sizeof(kaa_logging_data_collection2_t));

    if (record) {
        record->serialize = kaa_logging_data_collection2_serialize;
        record->get_size = kaa_logging_data_collection2_get_size;
        record->destroy = kaa_logging_data_collection2_destroy;
    }

    return record;
}

kaa_logging_data_collection2_t *kaa_logging_data_collection2_deserialize(avro_reader_t reader)
{
    kaa_logging_data_collection2_t *record = 
            (kaa_logging_data_collection2_t *)KAA_MALLOC(sizeof(kaa_logging_data_collection2_t));

    if (record) {
        record->serialize = kaa_logging_data_collection2_serialize;
        record->get_size = kaa_logging_data_collection2_get_size;
        record->destroy = kaa_logging_data_collection2_destroy;

        record->nodeid = kaa_string_deserialize(reader);
        record->weaher__temperature = kaa_logging_union_int_or_null_deserialize(reader);
        record->coordinate__latitude = kaa_logging_union_double_or_null_deserialize(reader);
        record->coordinate__longitude = kaa_logging_union_double_or_null_deserialize(reader);
    }

    return record;
}

