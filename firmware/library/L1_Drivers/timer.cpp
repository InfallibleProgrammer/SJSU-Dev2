#include "L0_LowLevel/LPC40xx.h"
#include "L1_Drivers/timer.hpp"

LPC_TIM_TypeDef* Timer::timer_peripherals[4] = {LPC_TIM0, LPC_TIM1, LPC_TIM2, LPC_TIM3};