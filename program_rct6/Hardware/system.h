//
// Created by yue on 2023/12/12.
//

#ifndef EC11_F103_SYSTEM_H
#define EC11_F103_SYSTEM_H

#include <stdint.h>

/**
 * 将data的第i位置1
 * i: 0-7
 */
#define SETBIT(data, i)     ((data) |= (1<<(i)))
/**
 * 将data的第i位置0
 * i: 0-7
 */
#define RESETBIT(data, i)     ((data) &= (~(1<<(i))))
/**
 * 获取data的第i为的值
 * i: 0-7
 */
#define GETBIT(data, i)     (((data)&(1<<(i))) == 0) ? 0:1

void ImgToBin(const uint8_t* img, uint8_t* bin, uint32_t bin_size);
void BinToImg(uint8_t* img, const uint8_t* bin, uint32_t bin_size);

void user_memset(void* buf, uint8_t data, uint32_t size);

void uint16_to_uint8(uint16_t data16, uint8_t* data8);
void uint8_to_uint16(const uint8_t* data8, uint16_t* data16);

#endif //EC11_F103_SYSTEM_H
