//
// Created by yue on 2023/12/11.
//

#ifndef EC11_F103_DEBUG_H
#define EC11_F103_DEBUG_H

#include <stdio.h>
#include "lcd_printf.h"

#define DEBUG_ERROR() printf("[ERROR] function is %s | line is %d\r\n", __FUNCTION__, __LINE__)
#define DEBUG_ERROR_LCD() lcd_printf("[ERROR] function is %s | line is %d\r\n", __FUNCTION__, __LINE__)

#endif //EC11_F103_DEBUG_H
