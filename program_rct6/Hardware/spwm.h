//
// Created by yue on 2024/3/18.
//

#ifndef PROGRAM_RCT6_SPWM_H
#define PROGRAM_RCT6_SPWM_H

#include <stdint.h>

void set_spwm(float spwm_freq);
void tim1_reset(uint32_t prescaler, uint32_t period);

#endif //PROGRAM_RCT6_SPWM_H
