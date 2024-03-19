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
 * 重新设置定时器1的参数
 * @param prescaler 分频系数
 * @param period 计数周期
 */
void tim1_reset(uint32_t prescaler, uint32_t period)
{
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

    htim1.Instance = TIM1;
    htim1.Init.Prescaler = prescaler-1;
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = period-1;
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.RepetitionCounter = 0;
    htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
        Error_Handler();
    }
    sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
    sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
    sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
    sBreakDeadTimeConfig.DeadTime = 0;
    sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
    sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
    sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
    if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
    {
        Error_Handler();
    }

    HAL_TIM_MspPostInit(&htim1);

    /* 重新开启PWM输出和定时器中断 */
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_1);
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, period/2);
    HAL_TIM_Base_Start_IT(&htim1);
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
