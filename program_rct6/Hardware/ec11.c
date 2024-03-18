//
// Created by yue on 2024/3/14.
//

#include "ec11.h"
#include "tim.h"
#include <stdio.h>
#include "debug.h"
#include "spwm.h"

/**
 * 外部中断回调函数 - EC11
 * @param GPIO_Pin
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    static GPIO_PinState a_state_last;    // 上一次捕获到的A引脚的电平状态
    static GPIO_PinState b_state_last;    // 上一次捕获到的B引脚的电平状态

    switch (GPIO_Pin)
    {
        case EC11_KEY_Pin:
        {
            HAL_TIM_Base_Start_IT(&htim4);  // 开启10ms定时器 按键消抖
            break;
        }
        case EC11_A_Pin:
        {
            /* 获取 A、B 信号 */
            GPIO_PinState a_state = HAL_GPIO_ReadPin(EC11_A_GPIO_Port, EC11_A_Pin);
            GPIO_PinState b_state = HAL_GPIO_ReadPin(EC11_B_GPIO_Port, EC11_B_Pin);

            switch (a_state)
            {
                case 0: // A初次捕获
                {
                    a_state_last = a_state;
                    b_state_last = b_state;
                    break;
                }
                case 1: // A二次捕获
                {
                    if (a_state_last == 0)  // 0-1 正确的A信号
                    {
                        if (b_state_last==0 && b_state==1)      // 0-1 顺时针动作
                        {
                            printf("this is +\r\n");
                        }
                        else if (b_state_last==1 && b_state==0) // 1-0 逆时针动作
                        {
                            printf("this is -\r\n");
                        }
                        else
                        {
                            DEBUG_ERROR();  // 错误的B信号
                        }
                    }
                    else
                    {
                        DEBUG_ERROR();  // 0-0 错误的A信号
                    }
                    a_state_last = a_state;
                    b_state_last = b_state;
                    break;
                }
            }
            break;
        }
        default: DEBUG_ERROR();  // 系统错误 or 没有给对应的中断引脚写回调函数
    }
}

/**
 * 定时器中断回调函数 定时器周期: 1ms
 * @param htim
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    static uint32_t tim4_1ms;   // 定时器4的计时周期为1ms

    /* EC11 - 10ms按键消抖 */
    if (htim->Instance == TIM4)
    {
        tim4_1ms++;
        if (tim4_1ms == 10)
        {
            GPIO_PinState key_state = HAL_GPIO_ReadPin(EC11_A_GPIO_Port, EC11_KEY_Pin);
            if (key_state == 0)
            {
                printf("this is KEY\r\n");
            }
            tim4_1ms = 0;
            HAL_TIM_Base_Stop(&htim4);  // 消抖完毕 关闭定时器
        }
    }
}
