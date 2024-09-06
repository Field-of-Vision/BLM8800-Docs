#ifndef __APP_AUDIO_H__
#define __APP_AUDIO_H__

#include <stdint.h>
#include <stdbool.h>
#include "app_media.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    AUD_REQ_MODE mode;
    MediaControlType cmd;
    MediaCommonStruct param;
} APP_AUDIO_MSG_T;

typedef void (*APP_AUDIO_HANDLER)(void);

int app_audio_handler_register(APP_AUDIO_HANDLER handler);

void app_audio_rb_unlock(void);

void app_audio_rb_lock(void);

void app_audio_heap_init(uint32_t start_addr, uint32_t end_addr);

int app_audio_memp_init(uint32_t start_addr, uint32_t end_addr);

uint32_t app_audio_memp_free_size(void);

void *app_audio_memp_malloc(uint32_t size);

void app_audio_memcpy_16bit(int16_t *dst, int16_t *src, uint32_t n);

void app_audio_memset_16bit(int16_t *dst, int16_t val, uint32_t n);

void app_audio_track_copy_16bits(int16_t *dst, int16_t *src, uint32_t src_n);

void app_audio_track_merge_16bits(int16_t *dst, int16_t *src, uint32_t dst_n);

void app_audio_send_msg(APP_AUDIO_MSG_T* msg, bool isr);

void app_audio_open(uint32_t mem_start_addr, uint32_t mem_end_addr);

void app_audio_close(void);

int app_audio_task_notify(void);

void app_audio_send_audio_end(void);

#ifdef __cplusplus
}
#endif

#endif

