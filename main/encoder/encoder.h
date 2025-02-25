#pragma once

#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ENC_CLK_GPIO    7
#define ENC_DT_GPIO     6
#define ENC_SW_GPIO     5

typedef struct {
    int32_t pos;
    int8_t dir;
    uint8_t event;
} sEncoderInfo;

typedef void (*encoder_cb_t)(sEncoderInfo event);


void encoder_init();
void encoder_deinit();
void encoder_start();
void encoder_stop();
void encoder_set_cb(encoder_cb_t cb);

#ifdef __cplusplus
}
#endif
