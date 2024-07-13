#include <stdio.h>
#include <string.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "unity.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_commands.h"
#include "soc/soc_caps.h"
#include "test_spi_board.h"

#define TEST_SPI_HOST_ID  SPI2_HOST
#define TEST_IMG_SIZE (200 * 200 * sizeof(uint16_t))


static void lcd_common_init(esp_lcd_panel_io_handle_t *io_handle, esp_lcd_panel_io_color_trans_done_cb_t on_color_trans_done, void *user_data, int cmd_bits, int param_bits) {
    spi_bus_config_t buscfg = {
        .sclk_io_num = TEST_LCD_PCLK_GPIO,
        .mosi_io_num = TEST_LCD_MOSI_GPIO,
        .miso_io_num = -1,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 100 * 100 * sizeof(uint16_t),
    };
    TEST_ESP_OK(spi_bus_initialize(TEST_SPI_HOST_ID, &buscfg, SPI_DMA_CH_AUTO));

    esp_lcd_panel_io_spi_config_t io_config = {
        .dc_gpio_num = TEST_LCD_DC_GPIO,
        .cs_gpio_num = TEST_LCD_CS_GPIO,
        .pclk_hz = TEST_LCD_PIXEL_CLOCK_HZ,
        .spi_mode = 0,
        .trans_queue_depth = 10,
        .lcd_cmd_bits = cmd_bits,
        .lcd_param_bits = param_bits,
        .on_color_trans_done = on_color_trans_done,
        .user_ctx = user_data,
    };
    TEST_ESP_OK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)TEST_SPI_HOST_ID, &io_config, io_handle));
}

static esp_lcd_panel_io_handle_t io_handle = NULL;
static esp_lcd_panel_handle_t panel_handle = NULL;

void st7789_init() {
    // turn off backlight
    gpio_config_t bk_gpio_config = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = 1ULL << TEST_LCD_BK_LIGHT_GPIO
    };
    gpio_config(&bk_gpio_config);
    gpio_set_level(TEST_LCD_BK_LIGHT_GPIO, 0);

    lcd_common_init(&io_handle, NULL, NULL, 8, 8);

    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = TEST_LCD_RST_GPIO,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
        .bits_per_pixel = 16,
    };

    TEST_ESP_OK(esp_lcd_new_panel_st7789(io_handle, &panel_config, &panel_handle));

    esp_lcd_panel_reset(panel_handle);
    esp_lcd_panel_init(panel_handle);
    esp_lcd_panel_invert_color(panel_handle, true);
    // the gap is LCD panel specific, even panels with the same driver IC, can have different gap value
    esp_lcd_panel_set_gap(panel_handle, 0, 20);

    esp_lcd_panel_disp_on_off(panel_handle, true);
    gpio_set_level(TEST_LCD_BK_LIGHT_GPIO, 1);

}

void st7789_deinit() {
    gpio_set_level(TEST_LCD_BK_LIGHT_GPIO, 0);
    esp_lcd_panel_disp_on_off(panel_handle, false);
    esp_lcd_panel_del(panel_handle);
    esp_lcd_panel_io_del(io_handle);
    spi_bus_free(TEST_SPI_HOST_ID);
    //gpio_reset_pin(TEST_LCD_BK_LIGHT_GPIO);
}

void lcd_panel_test() {
    uint8_t *img = heap_caps_malloc(TEST_IMG_SIZE, MALLOC_CAP_DMA);
    TEST_ASSERT_NOT_NULL(img);

    for (int i = 0; i < 100; i++) {
        uint8_t color_byte = rand() & 0xFF;
        int x_start = rand() % (TEST_LCD_H_RES - 200);
        int y_start = rand() % (TEST_LCD_V_RES - 200);
        memset(img, color_byte, TEST_IMG_SIZE);
        esp_lcd_panel_draw_bitmap(panel_handle, x_start, y_start, x_start + 200, y_start + 200, img);
    }

    printf("go into sleep mode\r\n");
    esp_lcd_panel_disp_sleep(panel_handle, true);
    vTaskDelay(pdMS_TO_TICKS(500));
    printf("exit sleep mode\r\n");
    esp_lcd_panel_disp_sleep(panel_handle, false);

    for (int i = 0; i < 100; i++) {
        uint8_t color_byte = rand() & 0xFF;
        int x_start = rand() % (TEST_LCD_H_RES - 200);
        int y_start = rand() % (TEST_LCD_V_RES - 200);
        memset(img, color_byte, TEST_IMG_SIZE);
        esp_lcd_panel_draw_bitmap(panel_handle, x_start, y_start, x_start + 200, y_start + 200, img);
    }

    free(img);

}
