/*
 *  ring_buffer.h
 */

#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#if defined __cplusplus
extern "C" {
#endif

#include <stdint.h>

enum {
    RB_ERR_NONE = 0,
    RB_ERR_NO_ENOUGH_SPACE,
    RB_ERR_NO_ENOUGH_DATA,
    RB_ERR_INVALID_PARAM,
};

typedef struct aic_ring_buffer {
    uint8_t  *storage;
    uint32_t size;
    uint32_t data_size;
    uint32_t read;
    uint32_t write;
} ring_buffer_t;

/**
 * Init ring buffer
 * @param ring_buffer object
 * @param storage
 * @param size in bytes
 * @return RB_ERR_NONE if all params valid
 */
int ring_buffer_init(ring_buffer_t *ring_buffer, uint8_t *storage, uint32_t size);

/**
 * Deinit ring buffer
 * @param ring_buffer object
 * @return RB_ERR_NONE if all params valid
 */
int ring_buffer_deinit(ring_buffer_t *ring_buffer);

/**
 * Reset ring buffer
 * @param ring_buffer object
 * @return RB_ERR_NONE if all params valid
 */
int ring_buffer_reset(ring_buffer_t *ring_buffer);

/**
 * Check if ring buffer is empty
 * @param ring_buffer object
 * @return TRUE if empty
 */
int ring_buffer_empty(ring_buffer_t *ring_buffer);

/**
 * Get number of bytes available for read
 * @param ring_buffer object
 * @return number of bytes available for read
 */
uint32_t ring_buffer_bytes_used(ring_buffer_t *ring_buffer);

/**
 * Get free space available for write
 * @param ring_buffer object
 * @return number of bytes available for write
 */
uint32_t ring_buffer_bytes_free(ring_buffer_t *ring_buffer);

/**
 * Write bytes into ring buffer
 * @param ring_buffer object
 * @param data to store
 * @param data length
 * @return RB_ERR_NONE if ok, RB_ERR_NO_ENOUGH_SPACE if not enough space in buffer
 */
int ring_buffer_write(ring_buffer_t *ring_buffer, uint8_t *data, uint32_t length);

/**
 * Read from ring buffer
 * @param ring_buffer object
 * @param buffer to store read data
 * @param length to read
 * @return RB_ERR_NONE if ok, RB_ERR_NO_ENOUGH_DATA if not enough data in buffer
 */
int ring_buffer_read(ring_buffer_t *ring_buffer, uint8_t *buffer, uint32_t length);

/**
 * Read from ring buffer
 * @param ring_buffer object
 * @param length to peek
 * @param data of 1st trunk
 * @param length of 1st trunk
 * @param data of 2nd trunk
 * @param length of 2nd trunk
 * @return RB_ERR_NONE if ok, RB_ERR_NO_ENOUGH_DATA if not enough data in buffer
 */
int ring_buffer_peek(ring_buffer_t * ring_buffer, uint32_t length, uint8_t **data1, uint32_t *length1, uint8_t **data2, uint32_t *length2);

#if defined __cplusplus
}
#endif

#endif // RING_BUFFER_H
