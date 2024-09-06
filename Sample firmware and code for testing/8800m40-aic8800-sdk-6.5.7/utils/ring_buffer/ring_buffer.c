/*
 *  ring_buffer.c
 *
 */

#include <string.h>

#include "ring_buffer.h"


#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif /* max */

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif /* min */

int ring_buffer_init(ring_buffer_t *ring_buffer, uint8_t *storage, uint32_t size)
{
    if ((ring_buffer == NULL) || (storage == NULL) || (size == 0)) {
        return RB_ERR_INVALID_PARAM;
    }

    ring_buffer->storage = storage;
    ring_buffer->size = size;
    ring_buffer->data_size = 0;
    ring_buffer->read = 0;
    ring_buffer->write = 0;

    return RB_ERR_NONE;
}

int ring_buffer_deinit(ring_buffer_t *ring_buffer)
{
    if (ring_buffer == NULL) {
        return RB_ERR_INVALID_PARAM;
    }

    ring_buffer->storage = NULL;
    ring_buffer->size = 0;
    ring_buffer->data_size = 0;
    ring_buffer->read = 0;
    ring_buffer->write = 0;

    return RB_ERR_NONE;
}

int ring_buffer_reset(ring_buffer_t *ring_buffer)
{
    if (ring_buffer == NULL) {
        return RB_ERR_INVALID_PARAM;
    }

    ring_buffer->data_size = 0;
    ring_buffer->read = 0;
    ring_buffer->write = 0;

    return RB_ERR_NONE;
}

uint32_t ring_buffer_bytes_used(ring_buffer_t *ring_buffer)
{
    return ring_buffer->data_size;
}

int ring_buffer_empty(ring_buffer_t *ring_buffer)
{
    return (ring_buffer->data_size == 0u);
}

uint32_t ring_buffer_bytes_free(ring_buffer_t *ring_buffer)
{
    return (ring_buffer->size - ring_buffer->data_size);
}

int ring_buffer_write(ring_buffer_t *ring_buffer, uint8_t *data, uint32_t length)
{
    if ((ring_buffer == NULL) || (ring_buffer->storage == NULL)) {
        return RB_ERR_INVALID_PARAM;
    }

    if (ring_buffer_bytes_free(ring_buffer) < length) {
        return RB_ERR_NO_ENOUGH_SPACE;
    }

    unsigned int bytes_until_end = ring_buffer->size - ring_buffer->write;
    if (bytes_until_end >= length) {
        memcpy((void *)&ring_buffer->storage[ring_buffer->write], (void *)data, length);
        ring_buffer->write += length;
    } else {
        // copy first chunk
        memcpy((void *)&ring_buffer->storage[ring_buffer->write], (void *)data, bytes_until_end);
        // copy second chunk
        memcpy((void *)&ring_buffer->storage[0], (void *)(data + bytes_until_end), (length - bytes_until_end));
        ring_buffer->write = length - bytes_until_end;
    }

    if (ring_buffer->write == ring_buffer->size) {
        ring_buffer->write = 0;
    }

    ring_buffer->data_size += length;

    return RB_ERR_NONE;
}

int ring_buffer_read(ring_buffer_t *ring_buffer, uint8_t *buffer, uint32_t length)
{
    if ((ring_buffer == NULL) || (ring_buffer->storage == NULL)) {
        return RB_ERR_INVALID_PARAM;
    }

    if (ring_buffer_bytes_used(ring_buffer) < length) {
        return RB_ERR_NO_ENOUGH_DATA;
    }

    unsigned int bytes_until_end = ring_buffer->size - ring_buffer->read;

    if (buffer != NULL) {
        if (bytes_until_end >= length) {
            memcpy((void *)buffer, (void *)&ring_buffer->storage[ring_buffer->read], length);
            ring_buffer->read += length;
        } else {
            // copy first chunk
            memcpy((void *)buffer, (void *)&ring_buffer->storage[ring_buffer->read], bytes_until_end);
            // copy second chunk
            memcpy((void *)(buffer + bytes_until_end), (void *)&ring_buffer->storage[0], (length - bytes_until_end));
            ring_buffer->read = length - bytes_until_end;
        }
    } else {
        // just modify read index
        if (bytes_until_end >= length) {
            ring_buffer->read += length;
        } else {
            ring_buffer->read = length - bytes_until_end;
        }
    }

    if (ring_buffer->read == ring_buffer->size) {
        ring_buffer->read = 0;
    }

    ring_buffer->data_size -= length;

    return RB_ERR_NONE;
}

int ring_buffer_peek(ring_buffer_t *ring_buffer, uint32_t length, uint8_t **data1, uint32_t *length1, uint8_t **data2, uint32_t *length2)
{
    if (ring_buffer_bytes_used(ring_buffer) < length) {
        return RB_ERR_NO_ENOUGH_DATA;
    }

    *data1 = &(ring_buffer->storage[ring_buffer->read]);
    if((ring_buffer->write > ring_buffer->read) || ((ring_buffer->size - ring_buffer->read) >= length)) {
        *length1 = length;
        *data2   = NULL;
        *length2 = 0;
        return RB_ERR_NONE;
    } else {
        *length1 = ring_buffer->size - ring_buffer->read;
        *data2   = &(ring_buffer->storage[0]);
        *length2 = length - *length1;
        return RB_ERR_NONE;
    }
}

