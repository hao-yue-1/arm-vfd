//
// Created by yue on 2023/12/12.
//

#include "system.h"

/**
 * 将16bit的彩色图片(但图片只有黑白二色)压缩
 * @param img 压缩前的16bit彩色图片
 * @param bin 压缩后的二值图片
 * @param bin_size
 */
void ImgToBin(const uint8_t* img, uint8_t* bin, uint32_t bin_size)
{
    /* 前8字节数据为帧头 保留 */
    for (int i = 0; i < 8; ++i)
    {
        bin[i] = img[i];
    }
    /* 后面每8字节数据压缩为1字节数据 0xff->1 0x00->0 */
    for (int i_bin = 8, i_img = 8; i_bin < bin_size; ++i_bin)
    {
        for (int i = 0; i < 8; ++i, ++i_img)
        {
            if (img[i_img] == 0xff)
                SETBIT(bin[i_bin], i);
            else
                RESETBIT(bin[i_bin], i);
        }
    }
}

/**
 * 将被压缩的16位彩色图片解压
 * @param img 解压后的16bit彩色图片
 * @param bin 被压缩后的二值图片
 * @param bin_size
 */
void BinToImg(uint8_t* img, const uint8_t* bin, uint32_t bin_size)
{
    /* 前8字节数据为帧头 保留 */
    for (int i = 0; i < 8; ++i)
    {
        img[i] = bin[i];
    }
    /* 后面每1字节数据解压为8字节数据 1->0xff 0->0x00 */
    for (int i_bin = 8, i_img = 8; i_bin < bin_size; ++i_bin)
    {
        for (int i = 0; i < 8; ++i, ++i_img)
        {
            if (GETBIT(bin[i_bin], i) == 1)
                img[i_img] = 0xff;
            else
                img[i_img] = 0x00;
        }
    }
}

/**
 * 格式化缓冲区数组为固定值 替换memset函数 (memset函数时间复杂度为)
 * @param buf 缓冲区
 * @param data 格式化为该固定值
 * @param size 缓冲区大小
 */
void user_memset(void* buf, uint8_t data, uint32_t size)
{
    uint8_t* buf_p = (uint8_t*)buf;
    for (uint32_t i = 0; i < size; ++i)
    {
        buf_p[i] = data;
    }
}

void uint16_to_uint8(uint16_t data16, uint8_t* data8)
{
    data8[0] = (data16 >> 8) & 0xff;
    data8[1] = data16 & 0xff;
}

void uint8_to_uint16(const uint8_t* data8, uint16_t* data16)
{
    *data16 = (data8[0]<<8) | data8[1];
}


