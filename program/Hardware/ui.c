//
// Created by yue on 2024/4/22.
//

#include "ui.h"
#include "lcd.h"
#include "lcd_font.h"

void ui_print_point(void)
{
    lcd_fill(155, 100, 165, 110, LCD_BLACK);
    lcd_fill(155, 100, 156, 101, LCD_WHITE);
    lcd_fill(155, 109, 156, 110, LCD_WHITE);
    lcd_fill(164, 100, 164, 101, LCD_WHITE);
    lcd_fill(164, 109, 165, 110, LCD_WHITE);
}

void ui_print_num(uint16_t x1, uint16_t y1, uint8_t num)
{
    /* 根据数字显示的对应的图片 */
    switch (num)
    {
        case 0: LCD_PrintPictureBin(x1, y1, 80, bin_0);  break;
        case 1: LCD_PrintPictureBin(x1, y1, 80, bin_1);  break;
        case 2: LCD_PrintPictureBin(x1, y1, 80, bin_2);  break;
        case 3: LCD_PrintPictureBin(x1, y1, 80, bin_3);  break;
        case 4: LCD_PrintPictureBin(x1, y1, 80, bin_4);  break;
        case 5: LCD_PrintPictureBin(x1, y1, 80, bin_5);  break;
        case 6: LCD_PrintPictureBin(x1, y1, 80, bin_6);  break;
        case 7: LCD_PrintPictureBin(x1, y1, 80, bin_7);  break;
        case 8: LCD_PrintPictureBin(x1, y1, 80, bin_8);  break;
        case 9: LCD_PrintPictureBin(x1, y1, 80, bin_9);  break;
        default: return;
    }
}

void ui_print_nums(uint16_t nums)
{
    if (nums == 1000)
    {
        ui_print_num(0, 25, 1);
        ui_print_num(80, 25, 0);
        ui_print_num(160, 25, 0);

        lcd_fill(155, 100, 165, 110, LCD_WHITE);    // 清除小数点

        return;
    }

    uint8_t tmp;
    tmp = nums % 10; // 提取个位数
    ui_print_num(160, 25, tmp);
    nums /= 10;
    tmp = nums %10;  // 提取十位数
    ui_print_num(80, 25, tmp);
    nums /= 10;
    tmp = nums %10;  // 提取个位数
    ui_print_num(0, 25, tmp);

    ui_print_point();
}
