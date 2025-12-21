#ifndef GPIO_H_
#define GPIO_H_

#include "common.h"

/* base address for gpio peripherals */
#define GPIO_PERIPH_BASE_ADDR 0x40020000

/* STM32F446RE i/o ports */
/* each i/o port is controlled by a corresponding GPIO peripheral
and each GPIO peripheral is 0x0400 large (aka 1024 KiB or 1 MiB) */
#define GPIOA_BASE_ADDR (GPIO_PERIPH_BASE_ADDR + 0x0000UL)
#define GPIOB_BASE_ADDR (GPIO_PERIPH_BASE_ADDR + 0x0400UL)
#define GPIOC_BASE_ADDR (GPIO_PERIPH_BASE_ADDR + 0x0800UL)
#define GPIOD_BASE_ADDR (GPIO_PERIPH_BASE_ADDR + 0x0C00UL)

/* gpio peripherals */
#define GPIOA ((GPIO_Peripheral *) GPIOA_BASE_ADDR)
#define GPIOB ((GPIO_Peripheral *) GPIOB_BASE_ADDR)
#define GPIOC ((GPIO_Peripheral *) GPIOC_BASE_ADDR)
#define GPIOD ((GPIO_Peripheral *) GPIOD_BASE_ADDR)

/* gpio pins */
#define PIN0  0U
#define PIN1  1U
#define PIN2  2U
#define PIN3  3U
#define PIN4  4U
#define PIN5  5U
#define PIN6  6U
#define PIN7  7U
#define PIN8  8U
#define PIN9  9U
#define PIN10 10U
#define PIN11 11U
#define PIN12 12U
#define PIN13 13U
#define PIN14 14U
#define PIN15 15U

/* gpio alternate functions */
#define AF0  0U
#define AF1  1U
#define AF2  2U
#define AF3  3U
#define AF4  4U
#define AF5  5U
#define AF6  6U
#define AF7  7U
#define AF8  8U
#define AF9  9U
#define AF10 10U
#define AF11 11U
#define AF12 12U
#define AF13 13U
#define AF14 14U
#define AF15 15U

/* gpio peripheral struct, holds all the gpio peripheral registers */
typedef struct
{
    volatile uint32_t MODER;   // GPIO port mode register
    volatile uint32_t OTYPER;  // GPIO port output type register
    volatile uint32_t OSPEEDR; // GPIO port output speed register
    volatile uint32_t PUPDR;   // GPIO port pull-up/pull-down register
    volatile uint32_t IDR;     // GPIO port input data register
    volatile uint32_t ODR;     // GPIO port output data register
    volatile uint32_t BSRR;    // GPIO port bit set/reset register
    volatile uint32_t LCKR;    // GPIO port configuration lock register
    volatile uint32_t AFRL;    // GPIO alternate function register low
    volatile uint32_t AFRH;    // GPIO alternate function register high
} GPIO_Peripheral;

/* gpio pin mode enum, these are the 4 possible modes a
gpio pin can be set too */
typedef enum
{
    GPIO_MODE_INPUT  = 0U,
    GPIO_MODE_OUTPUT = 1U,
    GPIO_MODE_AF     = 2U,
    GPIO_MODE_ANALOG = 3U
} GPIO_Pin_Mode;

/* gpio pin state enum, a pin is either high (set) or low (reset) */
typedef enum
{
    GPIO_PIN_RESET = 0U,
    GPIO_PIN_SET   = 1U
} GPIO_Pin_State;

/**
 * @brief Set the mode of a SINGLE GPIO pin
 * 
 * @param gpiox Pointer to GPIO bank
 * @param pin Selected pin
 * @param mode Selected mode
 */
void GPIO_Set_Mode(GPIO_Peripheral *gpiox, int pin, GPIO_Pin_Mode mode);

/**
 * @brief Set the alternate function of a SINGLE GPIO pin
 * 
 * @param gpiox Pointer to GPIO bank
 * @param pin Selected pin
 * @param af Selected alternate function
 * 
 * @details This function will set the selected pin to alternate
 * function mode if it is not already in alternate function mode
 */
void GPIO_Set_AF(GPIO_Peripheral *gpiox, int pin, int af);

/**
 * @brief Write to a GPIO pin
 * 
 * @param gpiox Pointer to GPIO bank
 * @param pin Selected pin
 * @param pinstate Pin state to write
 * 
 * @details This function assumes the pin passed to it
 * is already in output mode
 */
void GPIO_Write(GPIO_Peripheral *gpiox, int pin, GPIO_Pin_State pinstate);

/**
 * @brief Read from a GPIO pin
 * 
 * @param gpiox Pointer to GPIO bank
 * @param pin Selected pin
 * @return Current state of the pin (GPIO_PIN_SET or GPIO_PIN_RESET)
 * 
 * @details This function assumes the pin passed to it
 * is already in input mode
 */
GPIO_Pin_State GPIO_Read(GPIO_Peripheral *gpiox, int pin);

/**
 * @brief Toggle a GPIO pin
 * 
 * @param gpiox Pointer to GPIO bank
 * @param pin Selected pin
 * 
 * @details This function assumes the pin passed to it
 * is already in output mode
 */
void GPIO_Toggle(GPIO_Peripheral *gpiox, int pin);

#endif // GPIO_H_