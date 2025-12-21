#include "interrupts.h"

/* increment system tick counter each time a systick
interrupt is generated */
void SysTick_Handler(void)
{
    SYSTICK_Inc_Ticks();
}
