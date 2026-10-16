#ifndef __TFT_H
#define __TFT_H

#include "stm32f4xx_hal.h"      /* F4??stm32f4xx_hal.h,G4?? */

/* ========== ????? ========== */
#define LCD_W           240
#define LCD_H           240

#define USE_ST7789      1       /* 0=ILI9341(240x320), 1=ST7789(240x240) */
#define ST7789_YOFF     80      /* ST7789?Y??,??????0/80/-80? */
#define LCD_BGR         0       /* ?????????1 */
/* ================================ */

#define WHITE   0xFFFF
#define BLACK   0x0000
#define RED     0xF800
#define GREEN   0x07E0
#define BLUE    0x001F
#define YELLOW  0xFFE0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define GRAY    0x8410

void LCD_Init(void);
void LCD_Clear(uint16_t color);
void LCD_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color);
void LCD_ShowChar(uint16_t x, uint16_t y, char c, uint16_t color);
void LCD_ShowString(uint16_t x, uint16_t y, const char *str, uint16_t color);
void LCD_ShowNum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint16_t color);
void LCD_ShowFloat(uint16_t x, uint16_t y, float val, uint8_t len, uint16_t color);
void LCD_TestColors(void);

#endif
