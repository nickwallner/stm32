#ifndef HAL_H_
#define HAL_H_

#define BIT(x) (1UL << (x)) // convenience macro

#include "common.h"

/* driver includes */
#include "exti.h"
#include "gpio.h"
#include "nvic.h"
#include "rcc.h"
#include "systick.h"
#include "usart.h"

#endif // HAL_H_