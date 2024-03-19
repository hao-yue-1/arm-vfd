//
// Created by yue on 2023/12/8.
//

#include "lcd.h"
#include "lcd_font.h"
#include "spi.h"

uint16_t lcd_color_char = LCD_WHITE;    // �ַ���ɫ
uint16_t lcd_color_back = LCD_BLACK;    // ������ɫ

/**
 * SPI - ��������
 * @param dat
 */
static void SPI_SendData(uint8_t data)
{
	LCD_CS_Clr();
    HAL_SPI_Transmit(&hspi1, &data, 1, 1000);   // HAL��Ӳ��SPI���ݷ���
	LCD_CS_Set();
}

/**
 * SPI - д������ - 8λ
 * @param dat
 */
static void LCD_WriteData8(uint8_t data)
{
	LCD_DC_Set();   // ����DC��ʾд����
    SPI_SendData(data);
}

/**
 * SPI - д������ - 16λ
 * @param dat
 */
static void LCD_WriteData16(uint16_t data)
{
	LCD_DC_Set();   // ����DC��ʾд����
	SPI_SendData(data>>8);
	SPI_SendData(data);
}

/**
 * SPI - д������ - 8λ
 * @param cmd
 */
static void LCD_WriteCmd(uint8_t cmd)
{
	LCD_DC_Clr();	//����DC��ʾд����
	SPI_SendData(cmd);
}

/**
 * LCD - ������ʼ�ͽ�����ַ
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 */
static void LCD_SetAddress(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    /* ������Ļ��ʾ�������� */
    switch (LCD_HORIZONTAL)
    {
        case 0:
        {
            LCD_WriteCmd(0x2a); // �е�ַ����
            LCD_WriteData16(x1+52);
            LCD_WriteData16(x2+52);
            LCD_WriteCmd(0x2b); // �е�ַ����
            LCD_WriteData16(y1+40);
            LCD_WriteData16(y2+40);
            LCD_WriteCmd(0x2c); // ������д
            break;
        }
        case 1:
        {
            LCD_WriteCmd(0x2a); // �е�ַ����
            LCD_WriteData16(x1+53);
            LCD_WriteData16(x2+53);
            LCD_WriteCmd(0x2b); // �е�ַ����
            LCD_WriteData16(y1+40);
            LCD_WriteData16(y2+40);
            LCD_WriteCmd(0x2c); // ������д
            break;
        }
        case 2:
        {
            LCD_WriteCmd(0x2a); // �е�ַ����
            LCD_WriteData16(x1+40);
            LCD_WriteData16(x2+40);
            LCD_WriteCmd(0x2b); // �е�ַ����
            LCD_WriteData16(y1+53);
            LCD_WriteData16(y2+53);
            LCD_WriteCmd(0x2c); // ������д
            break;
        }
        case 3:
        {
            LCD_WriteCmd(0x2a); // �е�ַ����
            LCD_WriteData16(x1+40);
            LCD_WriteData16(x2+40);
            LCD_WriteCmd(0x2b); // �е�ַ����
            LCD_WriteData16(y1+52);
            LCD_WriteData16(y2+52);
            LCD_WriteCmd(0x2c); // ������д
            break;
        }
        default: break;
    }
}

/**
 * LCD - ��ʼ��
 * @param color_pen �ַ���ɫ
 * @param color_back ������ɫ
 */
void lcd_init(uint16_t color_pen, uint16_t color_back)
{
	LCD_RST_Clr();
	HAL_Delay(20);
	LCD_RST_Set();
    HAL_Delay(200);
	LCD_BLK_Set();
    HAL_Delay(300);

    /*������Ļ��ʾ����*/
    LCD_WriteCmd(0x36);
    switch (LCD_HORIZONTAL)
    {
        case 0: LCD_WriteData8(0x00);   break;
        case 1: LCD_WriteData8(0xC0);   break;
        case 2: LCD_WriteData8(0x70);   break;
        case 3: LCD_WriteData8(0xA0);   break;
        default: break;
    }

    LCD_WriteCmd(0x3A);
    LCD_WriteData8(0x05);

    LCD_WriteCmd(0xB2);
    LCD_WriteData8(0x0C);
    LCD_WriteData8(0x0C);
    LCD_WriteData8(0x00);
    LCD_WriteData8(0x33);
    LCD_WriteData8(0x33);

    LCD_WriteCmd(0xB7);
    LCD_WriteData8(0x35);

    LCD_WriteCmd(0xBB);
    LCD_WriteData8(0x19);

    LCD_WriteCmd(0xC0);
    LCD_WriteData8(0x2C);

    LCD_WriteCmd(0xC2);
    LCD_WriteData8(0x01);

    LCD_WriteCmd(0xC3);
    LCD_WriteData8(0x12);

    LCD_WriteCmd(0xC4);
    LCD_WriteData8(0x20);

    LCD_WriteCmd(0xC6);
    LCD_WriteData8(0x0F);

    LCD_WriteCmd(0xD0);
    LCD_WriteData8(0xA4);
    LCD_WriteData8(0xA1);

    LCD_WriteCmd(0xE0);
    LCD_WriteData8(0xD0);
    LCD_WriteData8(0x04);
    LCD_WriteData8(0x0D);
    LCD_WriteData8(0x11);
    LCD_WriteData8(0x13);
    LCD_WriteData8(0x2B);
    LCD_WriteData8(0x3F);
    LCD_WriteData8(0x54);
    LCD_WriteData8(0x4C);
    LCD_WriteData8(0x18);
    LCD_WriteData8(0x0D);
    LCD_WriteData8(0x0B);
    LCD_WriteData8(0x1F);
    LCD_WriteData8(0x23);

    LCD_WriteCmd(0xE1);
    LCD_WriteData8(0xD0);
    LCD_WriteData8(0x04);
    LCD_WriteData8(0x0C);
    LCD_WriteData8(0x11);
    LCD_WriteData8(0x13);
    LCD_WriteData8(0x2C);
    LCD_WriteData8(0x3F);
    LCD_WriteData8(0x44);
    LCD_WriteData8(0x51);
    LCD_WriteData8(0x2F);
    LCD_WriteData8(0x1F);
    LCD_WriteData8(0x1F);
    LCD_WriteData8(0x20);
    LCD_WriteData8(0x23);

    LCD_WriteCmd(0x21);

    LCD_WriteCmd(0x11);

    LCD_WriteCmd(0x29);

    lcd_clear(color_back);
    lcd_color_char = color_pen;
}

/**
 * LCD - ���� - ͬʱ������Ļ�ı�����ɫ
 * @param color
 */
void lcd_clear(uint16_t color)
{
	LCD_SetAddress(0, 0, LCD_W-1, LCD_H-1);

    for (uint16_t i = 0; i < LCD_W; i++)
    {
        for (uint16_t j = 0; j < LCD_H; j++)
        {
            LCD_WriteData16(color);
        }
    }

    lcd_color_back = color; // ���ñ���ɫ
}

/**
 * LCD - ���������ɫ���
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @param color
 */
void lcd_fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	LCD_SetAddress(x1, y1, x2, y2); // ���ù��λ��

	for (uint16_t i = y1; i <= y2; i++)
	{
		for (uint16_t j = x1; j <= x2; j++)
        {
            LCD_WriteData16(color); // ���ù��λ��
        }
	}
}

/**
 * LCD - ����һ����
 * @param x
 * @param y
 * @param color
 */
void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color)
{
    LCD_SetAddress(x, y, x, y); // ���ù��λ��
    LCD_WriteData16(color);
}

/**
 * LCD - ����һ��ֱ��
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @param color
 */
void lcd_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	int xerr = 0, yerr = 0, delta_x, delta_y, distance;
	int incx, incy, uRow, uCol;
	delta_x = x2 - x1;  // ������������
	delta_y = y2 - y1;
	uRow = x1;  // �����������
	uCol = y1;

	if (delta_x > 0)
    {
        incx = 1;   // ���õ����ķ���
    }
	else if (delta_x == 0)  // ��ֱ��
    {
        incx = 0;
    }
	else
    {
        incx = -1;
        delta_x = -delta_x;
    }
	if (delta_y > 0)
    {
        incy = 1;
    }
	else if (delta_y == 0)  // ˮƽ��
    {
        incy = 0;
    }
	else
    {
        incy = -1;
        delta_y = -delta_x;
    }
	if (delta_x > delta_y)
    {
        distance = delta_x; // ѡȡ��������������
    }
	else
    {
        distance = delta_y;
    }
	for (uint16_t t = 0; t < distance + 1; t++)
	{
		lcd_draw_point(uRow, uCol, color);   // ����
		xerr += delta_x;
		yerr += delta_y;
		if (xerr > distance)
		{
			xerr -= distance;
			uRow += incx;
		}
		if (yerr > distance)
		{
			yerr -= distance;
			uCol += incy;
		}
	}
}

/**
 * LCD - ����һ������
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @param color
 */
void lcd_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
    lcd_draw_line(x1, y1, x2,y1, color);
    lcd_draw_line(x1, y1,x1, y2, color);
    lcd_draw_line(x1, y2, x2, y2, color);
    lcd_draw_line(x2, y1, x2, y2, color);
}

/**
 * LCD - ����һ��Բ
 * @param x0
 * @param y0
 * @param r
 * @param color
 */
void lcd_draw_circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color)
{
	int a = 0, b = r;

	while (a <= b)
	{
		lcd_draw_point(x0-b, y0-a, color);   // 3
		lcd_draw_point(x0+b, y0-a, color);   // 0
		lcd_draw_point(x0-a, y0+b, color);   // 1
		lcd_draw_point(x0-a, y0-b, color);   // 2
		lcd_draw_point(x0+b, y0+a, color);   // 4
		lcd_draw_point(x0+a, y0-b, color);   // 5
		lcd_draw_point(x0+a, y0+b, color);   // 6
		lcd_draw_point(x0-b, y0+a, color);   // 7
		a++;
		if ((a*a+b*b) > (r*r))   // �ж�Ҫ���ĵ��Ƿ��Զ
		{
			b--;
		}
	}
}

/**
 * LCD - ��ʾһ���ַ� - 16*8
 * @param x
 * @param y
 * @param num
 * @param mode 0:�ǵ���ģʽ - 1:����ģʽ
 * @param color
 */
void lcd_print_char(uint16_t x, uint16_t y, uint8_t num, uint8_t mode, uint16_t color)
{
    uint8_t temp;
	uint16_t x0 = x;
    if (x>LCD_W-8 || y>LCD_H-16)    // ���ô���
    {
        return;
    }
	num = num - ' ';    // �õ�ƫ�ƺ��ֵ
	LCD_SetAddress(x, y, x+8-1, y+16-1);    // ���ù��λ��
    if (!mode) //�ǵ��ӷ�ʽ
	{
		for (uint8_t pos = 0; pos < 16; pos++)
		{
			temp = asc2_1608[(uint16_t)num*16+pos];   // ����1608������
			for (uint8_t t = 0; t < 8; t++)
		    {
                if(temp&0x01)
                {
                    LCD_WriteData16(color);
                }
                else
                {
                    LCD_WriteData16(lcd_color_back);
                }
                temp >>= 1;
                x++;
		    }
			x = x0;
			y++;
		}
	}
    else    //���ӷ�ʽ
	{
		for (uint8_t pos = 0; pos < 16; pos++)
		{
		    temp = asc2_1608[(uint16_t)num*16+pos]; // ����1608������
			for (uint8_t t = 0; t < 8; t++)
		    {
		        if (temp&0x01)
                {
                    lcd_draw_point(x+t, y+pos, color); // ��һ����
                }
		        temp >>= 1;
		    }
		}
	}
}

/**
 * LCD - ��ʾһ���ַ���
 * @param x
 * @param y
 * @param p �ַ���
 * @param color
 */
void lcd_print_string(uint16_t x, uint16_t y, const uint8_t *p, uint16_t color)
{
    while (*p != '\0')
    {
        if (x > LCD_W-8)
        {
            x = 0;
            y += 16;
        }
        if (y > LCD_H-16)
        {
            y = x = 0;
            lcd_clear(LCD_RED);
        }
        lcd_print_char(x, y, *p,0, color);
        x += 8;
        p++;
    }
}

/**
 * LCD - ��ʾһ��ͼƬ - n*n��������ͼƬ
 * @param x1
 * @param y1
 * @param len ������ͼƬ�ı߳�
 */
void lcd_print_image(uint16_t x1, uint16_t y1, uint16_t len, const uint8_t* img)
{
    uint16_t x2 = x1+len-1;
    uint16_t y2 = y1+len-1;

    LCD_SetAddress(x1, y1, x2, y2);

    uint32_t size = (x2-x1+1) * (y2-y1+1);   //����ͼ�����������

    for (uint32_t i = 0; i < size; i++)
    {
        LCD_WriteData8(img[i*2+1]);
        LCD_WriteData8(img[i*2]);
    }
}
