#include "gpio.h"

/* check if a GPIO pinno is set to a specific mode */
#define IS_MODE(pin, mode) ((gpiox->MODER & (mode << (pin * 2))) == ((uint32_t)(mode << (pin * 2))))

void GPIO_Set_Mode(GPIO_Peripheral *gpiox, int pin, GPIO_Pin_Mode mode)
{
    gpiox->MODER &= ~(3U << (pin * 2)); // clear bits before setting them
    gpiox->MODER |= (mode << (pin * 2)); // set bits to proper mode
}

void GPIO_Set_AF(GPIO_Peripheral *gpiox, int pin, int af)
{
    /* check if pin is already in af mode */
    if (!(IS_MODE(pin, GPIO_MODE_AF)))
    {
        /* set pin to alternate function mode */
        GPIO_Set_Mode(gpiox, pin, GPIO_MODE_AF);
    }

    /* pins 0-7 are controlled by afrl, 8-15 are controlled by afrh */
    if (pin <= 7)
    {
        gpiox->AFRL &= ~(15U << (pin * 4)); // clear bits before setting them
        gpiox->AFRL |= ((long unsigned int)af << (pin * 4));
    }
    else
    {
        gpiox->AFRH &= ~(15U << (pin * 4)); // clear bits before setting them
        gpiox->AFRH |= ((long unsigned int)af << (pin * 4));
    }
}

void GPIO_Write(GPIO_Peripheral *gpiox, int pin, GPIO_Pin_State pinstate)
{
    switch (pinstate)
    {
    case GPIO_PIN_SET:
        gpiox->BSRR = BITMASK16(pin);
        break;

    case GPIO_PIN_RESET:
        gpiox->BSRR = (BITMASK32(pin) << 16);
        break;
    }
}

GPIO_Pin_State GPIO_Read(GPIO_Peripheral *gpiox, int pin)
{
    /* check if pin is set */
    if ((gpiox->IDR & BITMASK16(pin)) == BITMASK16(pin))
    {
        return GPIO_PIN_SET;
    }
    
    return GPIO_PIN_RESET;
}

void GPIO_Toggle(GPIO_Peripheral *gpiox, int pin)
{
    /* check if pin is already set */
    if ((gpiox->ODR & BITMASK16(pin)) == BITMASK16(pin))
    {
        /* reset pin */
        gpiox->BSRR = (BITMASK32(pin) << 16);
    }
    else
    {
        /* set pin */
        gpiox->BSRR = BITMASK16(pin);
    }
}