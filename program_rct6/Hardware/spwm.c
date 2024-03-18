//
// Created by yue on 2024/3/18.
//

#include "spwm.h"
#include "tim.h"
#include <math.h>
#include <stdlib.h>

/**
 * ����SPWM����
 * @param pwm_freq PWMƵ��
 * @param pwm_duty PWM���ռ�ձ�
 * @param spwm_freq SPWMƵ��
 * @param spwm_list SPWM����
 * @param spwm_list_size SPWM���鳤��
 */
void get_spwm_list(uint32_t pwm_freq, uint16_t pwm_duty, uint16_t spwm_freq, uint16_t spwm_list[], uint16_t spwm_list_size)
{
    float omega = 2.0 * M_PI * spwm_freq / pwm_freq;
    float theta;
    for (int i = 0; i < spwm_list_size; ++i)
    {
        theta = fmod(omega * i, 2.0 * M_PI); // ����Ƕȣ�ʹ��������ʾƵ�ʵı���
        spwm_list[i] = (uint16_t)((0.5 * (1 + sin(theta))) * pwm_duty); // ����ռ�ձȣ�sin��������-1��1֮���ֵ������ӳ�䵽0��1֮��
    }
}

uint16_t *spwm_list = NULL;
uint16_t spwm_list_size = 0;

/**
 * ����SPWM
 * @param spwm_freq SPWMƵ��
 */
void set_spwm(float spwm_freq)
{
    spwm_list_size = round(100000 / spwm_freq);
    spwm_list = (uint16_t*) malloc(sizeof(uint16_t) * spwm_list_size);

    get_spwm_list(100000, 720, spwm_freq, spwm_list, spwm_list_size);
}

/**
 * ��ʱ���жϻص����� ��ʱ������: 1ms
 * @param htim
 */
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//    static uint16_t spwm_cnt;   // SPWM�����±�
//
//    /* SPWM */
//    if (htim->Instance == TIM1)
//    {
//        __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, spwm_list[spwm_cnt++]);
//        if(spwm_cnt >= spwm_list_size)
//        {
//            spwm_cnt = 0;
//        }
//    }
//}
