//
// Created by yue on 2023/12/12.
//

#include "system.h"

/**
 * ��16bit�Ĳ�ɫͼƬ(��ͼƬֻ�кڰ׶�ɫ)ѹ��
 * @param img ѹ��ǰ��16bit��ɫͼƬ
 * @param bin ѹ����Ķ�ֵͼƬ
 * @param bin_size
 */
void ImgToBin(const uint8_t* img, uint8_t* bin, uint32_t bin_size)
{
    /* ǰ8�ֽ�����Ϊ֡ͷ ���� */
    for (int i = 0; i < 8; ++i)
    {
        bin[i] = img[i];
    }
    /* ����ÿ8�ֽ�����ѹ��Ϊ1�ֽ����� 0xff->1 0x00->0 */
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
 * ����ѹ����16λ��ɫͼƬ��ѹ
 * @param img ��ѹ���16bit��ɫͼƬ
 * @param bin ��ѹ����Ķ�ֵͼƬ
 * @param bin_size
 */
void BinToImg(uint8_t* img, const uint8_t* bin, uint32_t bin_size)
{
    /* ǰ8�ֽ�����Ϊ֡ͷ ���� */
    for (int i = 0; i < 8; ++i)
    {
        img[i] = bin[i];
    }
    /* ����ÿ1�ֽ����ݽ�ѹΪ8�ֽ����� 1->0xff 0->0x00 */
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
 * ��ʽ������������Ϊ�̶�ֵ �滻memset���� (memset����ʱ�临�Ӷ�Ϊ)
 * @param buf ������
 * @param data ��ʽ��Ϊ�ù̶�ֵ
 * @param size ��������С
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


