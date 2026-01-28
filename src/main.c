#include "main.h"

/* a simple test program that flashes the onboard led at 1 second
intervals and prints to usart2 when the led is turned on/off */
int main(void)
{
    /* init gpio clocks */
    GPIO_Clock_Init();

    /* LD2 is connected to PA5, so set PA5 to output mode */
    GPIO_Set_Mode(GPIOA, GPIO_PIN5, GPIO_MODE_OUTPUT);

    /* initialize the systick timer to milliseconds */
    SYSTICK_Init(SYS_FREQ, SYSTICK_MS);

    /* initialize usart2, usart2 is connected to the stlink
    debugger and thus can be connected to a computer via usb */
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
        GPIO_Toggle(GPIOA, GPIO_PIN5);
        USART_Transmit(USART2, "led on\r\n", 8);

        SYSTICK_Delay(80);

        GPIO_Toggle(GPIOA, GPIO_PIN5);
        USART_Transmit(USART2, "led off\r\n", 9);

        SYSTICK_Delay(1000);
    }
}