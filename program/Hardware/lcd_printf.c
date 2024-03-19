//
// Created by yue on 2024/2/2.
//

#include "lcd_printf.h"
#include "lcd.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

extern uint16_t lcd_color_char; // �ַ���ɫ
extern uint16_t lcd_color_back; // ������ɫ

/* Ĭ���ַ���СΪ 8*16(w*h) �����ַ���С����Ļ����Ϊ30*8������ �������ڻ����ַ� */
static uint8_t lcd_x_arr[30] = {0, 8, 16, 24, 32, 40, 48, 56, 64,
                       72, 80, 88, 96, 104, 112, 120, 128,
                       136, 144, 152, 160, 168, 176, 184,
                       192, 200, 208, 216, 224, 232};
static uint8_t lcd_y_arr[8] = {0, 16, 32, 48, 64, 80, 96, 112};

/* ������Ļ�ַ��������� */
static uint8_t lcd_x_p = 0;
static uint8_t lcd_y_p = 0;

static uint8_t flag_point = 0;  // �ڵ�ǰ�����β������һ����� (0:��ǰΪ����,���δ���� - 1:��ǰΪ����,����ѻ���)

/**
 * ���µ�ǰ�б�� - ɾ�����л�������
 */
static void lcd_update_now_line(void)
{
    if (lcd_y_p == 0)   // ��ǰΪ��һ�� �����ײ�һ�б��
        lcd_fill(224, lcd_y_arr[7], 239, lcd_y_arr[7]+16, lcd_color_back);
    else                // �����һ�б��
        lcd_fill(224, lcd_y_arr[lcd_y_p]-16, 239, lcd_y_arr[lcd_y_p], lcd_color_back);

    // ���Ƶ�ǰ�б��
    lcd_fill(224+4, lcd_y_arr[lcd_y_p]+4, 224+11, lcd_y_arr[lcd_y_p]+11, lcd_color_char);
}

/**
 * ���һ���е��ַ�
 * @param y
 */
static void lcd_clear_line(uint8_t y)
{
    lcd_fill(0, lcd_y_arr[y], LCD_W - 1, lcd_y_arr[y] + 16, lcd_color_back);
}

/**
 * ��ʾһ���ַ�����������
 * @param val
 */
static void lcd_putchar_update_point(char val)
{
    /* ���µ�ǰ�б�� */
    if (flag_point == 0)
    {
        lcd_clear_line(lcd_y_p);
        lcd_update_now_line();
        flag_point = 1;
    }

    lcd_print_char(lcd_x_arr[lcd_x_p], lcd_y_arr[lcd_y_p], val, 0, lcd_color_char);
    /* ����׼����һ���ַ� */
    lcd_x_p++;
    /* ��β ���� */
    if (lcd_x_p > 27)   // Ԥ��β�������ַ���λ�����ڻ��Ƶ�ǰ�б��
    {
        lcd_x_p = 0;
        lcd_y_p++;
        if (lcd_y_p > 7)
            lcd_y_p = 0;

        flag_point = 0;
    }
}

/**
 * ��Ļ���������´Ӷ�����ʼ��ʾ ��ǰ��ʾ������β���б��
 * @param format
 * @param ...
 */
void lcd_printf(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    for (int i = 0; format[i] != '\0'; ++i)
    {
        if (format[i] == '%')
        {
            switch (format[++i])
            {
                case 'd':
                {
                    int d = va_arg(args, int);
                    char d_str[16] = {0};
                    sprintf(d_str, "%d", d);
                    unsigned int len = strlen(d_str);
                    for (int j = 0; j < len; ++j)
                    {
                        lcd_putchar_update_point(d_str[j]);
                    }
                    break;
                }
                case 'x':
                {
                    int x = va_arg(args, int);
                    char x_str[16] = {0};
                    sprintf(x_str, "%x", x);
                    unsigned int len = strlen(x_str);
                    for (int j = 0; j < len; ++j)
                    {
                        lcd_putchar_update_point(x_str[j]);
                    }
                    break;
                }
                case 'f':
                {
                    double f = va_arg(args, double);
                    printf("f = %f\r\n", f);
                    char f_str[16] = {0};
                    sprintf(f_str, "%f", f);
                    unsigned int len = strlen(f_str);
                    for (int j = 0; j < len; ++j)
                    {
                        lcd_putchar_update_point(f_str[j]);
                    }
                    break;
                }
                case 'c':
                {
                    int c = va_arg(args, int);
                    lcd_putchar_update_point(c);
                    break;
                }
                case 's':
                {
                    char* p = va_arg(args, char*);
                    unsigned int len = strlen(p);
                    for (int j = 0; j < len; ++j)
                    {
                        lcd_putchar_update_point(p[j]);
                    }
                    break;
                }
                default:
                {
                    lcd_putchar_update_point(format[i]);
                    break;
                }
            }
        }
        else if (format[i] == '\r') // �ص���ǰ�п�ͷλ��
        {
            lcd_x_p = 0;
        }
        else if (format[i] == '\n') // �л�����һ��
        {
            lcd_y_p++;
            if (lcd_y_p > 7)
                lcd_y_p = 0;

            flag_point = 0;
        }
        else
        {
            lcd_putchar_update_point(format[i]);
        }
    }

    va_end(args);
}

/**
 * �����ַ���ɫ
 * @param color
 */
void lcd_color_char_set(uint16_t color)
{
    lcd_color_char = color;
}

/**
 * ���ñ�����ɫ
 * @param color
 */
void lcd_color_back_set(uint16_t color)
{
    lcd_color_back = color;
}

/**
 * ����lcd_printf�������ʾ
 */
void lcd_printf_reset(void)
{
    lcd_clear(lcd_color_back);
    lcd_x_p = 0;
    lcd_y_p = 0;
    flag_point = 0;
}
