#pragma once

#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TEST_LCD_H_RES          170
#define TEST_LCD_V_RES          320

#define TEST_LCD_BK_LIGHT_GPIO  16
#define TEST_LCD_RST_GPIO       6
#define TEST_LCD_CS_GPIO        15
#define TEST_LCD_DC_GPIO        7
#define TEST_LCD_PCLK_GPIO      4
#define TEST_LCD_MOSI_GPIO      5

#define TEST_LCD_PIXEL_CLOCK_HZ (20 * 1000 * 1000)

void st7789_init();
void st7789_deinit();
void lcd_panel_test();

#ifdef __cplusplus
}
#endif
