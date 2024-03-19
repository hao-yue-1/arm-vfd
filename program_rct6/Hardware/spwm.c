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
 * �������ö�ʱ��1�Ĳ���
 * @param prescaler ��Ƶϵ��
 * @param period ��������
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

    /* ���¿���PWM����Ͷ�ʱ���ж� */
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_1);
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, period/2);
    HAL_TIM_Base_Start_IT(&htim1);
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
