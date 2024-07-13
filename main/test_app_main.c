#include "esp_heap_caps.h"
#include "test_spi_board.h"

void app_main()
{
    st7789_init();

    lcd_panel_test();

    printf("turn off the panel\r\n");
    st7789_deinit();
}
