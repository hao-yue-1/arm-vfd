//
// Created by yue on 2024/3/14.
//

#include "ec11.h"
#include "tim.h"
#include <stdio.h>
#include "debug.h"
#include "spwm.h"

/**
 * �ⲿ�жϻص����� - EC11
 * @param GPIO_Pin
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    static GPIO_PinState a_state_last;    // ��һ�β��񵽵�A���ŵĵ�ƽ״̬
    static GPIO_PinState b_state_last;    // ��һ�β��񵽵�B���ŵĵ�ƽ״̬

    switch (GPIO_Pin)
    {
        case EC11_KEY_Pin:
        {
            HAL_TIM_Base_Start_IT(&htim4);  // ����10ms��ʱ�� ��������
            break;
        }
        case EC11_A_Pin:
        {
            /* ��ȡ A��B �ź� */
            GPIO_PinState a_state = HAL_GPIO_ReadPin(EC11_A_GPIO_Port, EC11_A_Pin);
            GPIO_PinState b_state = HAL_GPIO_ReadPin(EC11_B_GPIO_Port, EC11_B_Pin);

            switch (a_state)
            {
                case 0: // A���β���
                {
                    a_state_last = a_state;
                    b_state_last = b_state;
                    break;
                }
                case 1: // A���β���
                {
                    if (a_state_last == 0)  // 0-1 ��ȷ��A�ź�
                    {
                        if (b_state_last==0 && b_state==1)      // 0-1 ˳ʱ�붯��
                        {
                            printf("this is +\r\n");
                        }
                        else if (b_state_last==1 && b_state==0) // 1-0 ��ʱ�붯��
                        {
                            printf("this is -\r\n");
                        }
                        else
                        {
                            DEBUG_ERROR();  // �����B�ź�
                        }
                    }
                    else
                    {
                        DEBUG_ERROR();  // 0-0 �����A�ź�
                    }
                    a_state_last = a_state;
                    b_state_last = b_state;
                    break;
                }
            }
            break;
        }
        default: DEBUG_ERROR();  // ϵͳ���� or û�и���Ӧ���ж�����д�ص�����
    }
}

/**
 * ��ʱ���жϻص����� ��ʱ������: 1ms
 * @param htim
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    static uint32_t tim4_1ms;   // ��ʱ��4�ļ�ʱ����Ϊ1ms

    /* EC11 - 10ms�������� */
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
            HAL_TIM_Base_Stop(&htim4);  // ������� �رն�ʱ��
        }
    }
}
