//
// Created by yue on 2024/3/14.
//

#ifndef PROGRAM_SPWM_H
#define PROGRAM_SPWM_H

#include <stdint.h>

#define SPWM_LIST_MAX_SIZE 2500
extern uint16_t *spwm_list;
extern uint16_t spwm_list_size;

void get_spwm_list(uint32_t pwm_freq, uint16_t pwm_duty, float spwm_freq);
void tim1_reset(uint32_t prescaler, uint32_t period);
uint8_t spwm_set(float spwm_freq);

#endif //PROGRAM_SPWM_H
