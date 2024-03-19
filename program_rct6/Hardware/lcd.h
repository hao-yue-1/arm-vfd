#ifndef _LCD_H_
#define _LCD_H_

#include <stdlib.h>
#include "gpio.h"

/*
 * SPIЭ��:
 * 1. 8Bits
 * 2. MSB First
 * 3. CPOL Low
 * 4. CPHA 1 Edge
 */

/* ������Ļ��ʾ���� */
#define LCD_HORIZONTAL 2  // ����or������ʾ - 01:���� - 23:����

#if LCD_HORIZONTAL==0||LCD_HORIZONTAL==1    // ����
#define LCD_W 135
#define LCD_H 240
#else                                       // ����
#define LCD_W 240
#define LCD_H 135
#endif

/* LCD SPI - �˿ڶ��� */

/* SCK */
#define LCD_SCL_Clr() HAL_GPIO_WritePin(SPI1_SCK_GPIO_Port,SPI1_SCK_Pin,GPIO_PIN_RESET)
#define LCD_SCL_Set() HAL_GPIO_WritePin(SPI1_SCK_GPIO_Port,SPI1_SCK_Pin,GPIO_PIN_SET)
/* MOSI */
#define LCD_SDA_Clr() HAL_GPIO_WritePin(SPI1_MOSI_GPIO_Port,SPI1_MOSI_Pin,GPIO_PIN_RESET)
#define LCD_SDA_Set() HAL_GPIO_WritePin(SPI1_MOSI_GPIO_Port,SPI1_MOSI_Pin,GPIO_PIN_SET)
/* RES */
#define LCD_RST_Clr() HAL_GPIO_WritePin(SPI1_RES_GPIO_Port,SPI1_RES_Pin,GPIO_PIN_RESET)
#define LCD_RST_Set() HAL_GPIO_WritePin(SPI1_RES_GPIO_Port,SPI1_RES_Pin,GPIO_PIN_SET)
/* DC */
#define LCD_DC_Clr() HAL_GPIO_WritePin(SPI1_DC_GPIO_Port,SPI1_DC_Pin,GPIO_PIN_RESET)
#define LCD_DC_Set() HAL_GPIO_WritePin(SPI1_DC_GPIO_Port,SPI1_DC_Pin,GPIO_PIN_SET)
/* CS */
#define LCD_CS_Clr()  HAL_GPIO_WritePin(SPI1_CS_GPIO_Port,SPI1_CS_Pin,GPIO_PIN_RESET)
#define LCD_CS_Set()  HAL_GPIO_WritePin(SPI1_CS_GPIO_Port,SPI1_CS_Pin,GPIO_PIN_SET)
/* BLK */
#define LCD_BLK_Clr()  HAL_GPIO_WritePin(SPI1_BLK_GPIO_Port,SPI1_BLK_Pin,GPIO_PIN_RESET)
#define LCD_BLK_Set()  HAL_GPIO_WritePin(SPI1_BLK_GPIO_Port,SPI1_BLK_Pin,GPIO_PIN_SET)

void lcd_init(uint16_t color_pen, uint16_t color_back);
void lcd_clear(uint16_t color);
void lcd_fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

void lcd_draw_point(uint16_t x,uint16_t y,uint16_t color);
void lcd_draw_line(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);
void lcd_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);
void lcd_draw_circle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color);

void lcd_print_char(uint16_t x,uint16_t y,uint8_t num,uint8_t mode,uint16_t color);
void lcd_print_string(uint16_t x,uint16_t y,const uint8_t *p,uint16_t color);
void lcd_print_image(uint16_t x1, uint16_t y1, uint16_t len, const uint8_t* img);

/* ������ɫ */
#define LCD_WHITE         	 0xFFFF
#define LCD_BLACK         	 0x0000
#define LCD_BLUE           	 0x001F
#define LCD_BRED             0XF81F
#define LCD_GRED 			 0XFFE0
#define LCD_GBLUE			 0X07FF
#define LCD_RED           	 0xF800
#define LCD_MAGENTA       	 0xF81F
#define LCD_GREEN         	 0x07E0
#define LCD_CYAN          	 0x7FFF
#define LCD_YELLOW        	 0xFFE0
#define LCD_BROWN 			 0XBC40 //��ɫ
#define LCD_BRRED 			 0XFC07 //�غ�ɫ
#define LCD_GRAY  			 0X8430 //��ɫ

/* GUI��ɫ */
#define LCD_DARKBLUE      	 0X01CF	//����ɫ
#define LCD_LIGHTBLUE      	 0X7D7C	//ǳ��ɫ
#define LCD_GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LCD_LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LCD_LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LCD_LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LCD_LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

#endif
