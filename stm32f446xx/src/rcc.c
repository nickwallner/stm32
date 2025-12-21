#include "rcc.h"

// make an enum for each port? or maybe a macro like stm32 hal

void GPIO_Clock_Init(void)
{
    SET_BIT(RCC->AHB1ENR, 0); // GPIOA
    SET_BIT(RCC->AHB1ENR, 1); // GPIOB
    SET_BIT(RCC->AHB1ENR, 2); // GPIOC
    SET_BIT(RCC->AHB1ENR, 7); // GPIOH
}