#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_heap_caps.h"
#include "display/dispcolor.h"
#include "display/fonts/font.h"
#include "st7789/st7789.h"
/*
void dispcolor_FillScreen(uint16_t color);
void dispcolor_DrawPixel(int16_t X, int16_t Y, uint16_t color);
void dispcolor_DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void dispcolor_DrawLine2(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color, uint8_t thick);
void dispcolor_DrawLine_Wu(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void dispcolor_DrawRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void dispcolor_FillRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t fillcolor);
void dispcolor_DrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void dispcolor_DrawTriangle_Wu(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void dispcolor_FillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void dispcolor_DrawCircle(int16_t x0, int16_t y0, int16_t radius, uint16_t color, uint8_t correction);
void dispcolor_DrawCircle_Wu(int16_t x0, int16_t y0, int16_t radius, uint16_t color);
void dispcolor_FillCircle(int16_t x0, int16_t y0, int16_t radius, uint16_t color);
void dispcolor_FillCircleWu(int16_t x0, int16_t y0, int16_t radius, uint16_t color);
void dispcolor_DrawArc(int16_t x0, int16_t y0, int16_t radius, int16_t startAngle, int16_t endAngle, uint16_t color, uint8_t correction);
int16_t dispcolor_DrawString(int16_t X, int16_t Y, uint8_t FontID, char *Str, uint16_t TextColor);
int16_t dispcolor_DrawString_Bg(int16_t X, int16_t Y, uint8_t FontID, char *Str, uint16_t TextColor, uint16_t BgColor);
int16_t dispcolor_printf(int16_t X, int16_t Y, uint8_t FontID, uint16_t TextColor, const char *args, ...);
int16_t dispcolor_printf_Bg(int16_t X, int16_t Y, uint8_t FontID, uint16_t TextColor, uint16_t BgColor, const char *args, ...);
*/

uint32_t cntr = 0;

void app_main()
{
    dispcolor_Init(170, 320);
    dispcolor_ClearScreen();
    dispcolor_SetBrightness(100);

    while (1) {
        dispcolor_ClearScreen();

        dispcolor_DrawLine(0, 0, 170, 320, RED);
        dispcolor_DrawLine(170, 0, 0, 320, RED);

        dispcolor_DrawLine(0, 0, 170, 0, GREEN);
        dispcolor_DrawLine(0, 319, 169, 319, GREEN);

        dispcolor_DrawLine(0, 0, 0, 319, BLUE);
        dispcolor_DrawLine(169, 0, 169, 319, BLUE);

        dispcolor_printf(10, 10, FONTID_10X16F, WHITE, "Counter %d", cntr++);

        dispcolor_Update();
        vTaskDelay(20);
    }




    //lcd_panel_test();

    //printf("turn off the panel\r\n");
    //st7789_deinit();
}
