//
// Created by yue on 2024/3/14.
//

#ifndef PROGRAM_SPWM_H
#define PROGRAM_SPWM_H

#include <stdint.h>

void get_spwm_list(uint32_t pwm_freq, uint16_t pwm_duty, float spwm_freq);
void tim1_reset(uint32_t prescaler, uint32_t period);

#endif //PROGRAM_SPWM_H
