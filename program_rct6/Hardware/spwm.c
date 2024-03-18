//
// Created by yue on 2024/3/18.
//

#include "spwm.h"
#include "tim.h"
#include <math.h>
#include <stdlib.h>

/**
 * 生成SPWM数组
 * @param pwm_freq PWM频率
 * @param pwm_duty PWM最大占空比
 * @param spwm_freq SPWM频率
 * @param spwm_list SPWM数组
 * @param spwm_list_size SPWM数组长度
 */
void get_spwm_list(uint32_t pwm_freq, uint16_t pwm_duty, uint16_t spwm_freq, uint16_t spwm_list[], uint16_t spwm_list_size)
{
    float omega = 2.0 * M_PI * spwm_freq / pwm_freq;
    float theta;
    for (int i = 0; i < spwm_list_size; ++i)
    {
        theta = fmod(omega * i, 2.0 * M_PI); // 计算角度，使用整数表示频率的倍数
        spwm_list[i] = (uint16_t)((0.5 * (1 + sin(theta))) * pwm_duty); // 计算占空比，sin函数返回-1到1之间的值，将其映射到0到1之间
    }
}

uint16_t *spwm_list = NULL;
uint16_t spwm_list_size = 0;

/**
 * 设置SPWM
 * @param spwm_freq SPWM频率
 */
void set_spwm(float spwm_freq)
{
    spwm_list_size = round(100000 / spwm_freq);
    spwm_list = (uint16_t*) malloc(sizeof(uint16_t) * spwm_list_size);

    get_spwm_list(100000, 720, spwm_freq, spwm_list, spwm_list_size);
}

/**
 * 定时器中断回调函数 定时器周期: 1ms
 * @param htim
 */
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//    static uint16_t spwm_cnt;   // SPWM数组下标
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
