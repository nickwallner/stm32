#include "main.h"

// there should be an init function for each peripheral that handles
// enabling clocks for that peripheral AND any modes/details

// i.e. gpio_init() initialises clock signal for provided gpio port
// and sets initial pin mode and alternate function mode

// probably use an init struct like stm32 hal

int main_other(void)
{
    /* set bit 0 in the AHB1ENR register to enable 
    the system clock for the GPIOA peripheral */
    SET_BIT(RCC->AHB1ENR, 0);

    /* LD2 is connected to PA5, so set PA5 to output mode */
    GPIO_Set_Mode(GPIOA, PIN5, GPIO_MODE_OUTPUT);

    /* initialize the systick timer to milliseconds */
    SYSTICK_Init(SYS_FREQ, SYSTICK_MS);

    USART_InitStruct init = {
        .usartx = USART2,
        .baud_rate = 9600,
        .sys_freq = SYS_FREQ,
        .transmit_en = 1,
        .transmit_interrupts_en = 0,
        .receive_en = 0,
        .receive_interrupts_en = 0
    };
    USART_Init(&init);

    while (1)
    {
        GPIO_Toggle(GPIOA, PIN5); // turn led on
        USART_Transmit(USART2, "led on\r\n", 8);

        SYSTICK_Delay(80); // delay for 80ms

        GPIO_Toggle(GPIOA, PIN5); // turn led off
        USART_Transmit(USART2, "led off\r\n", 9);

        SYSTICK_Delay(1000); // delay for 1000ms
    }
}