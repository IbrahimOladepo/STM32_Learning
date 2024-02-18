/*
  This is a template file that you can use to start your project on your
  stm32 developlent board. Use it with the supplied Makefile, stm32_flash.ld,
  stm32f4xx_conf.h and system_stm32f4xx.c files for your need.

  Edit Makefile to include right paths to all stlibs, arm compiler and st-link.

  Also make sure to have the right settings in system_stm32f4xx.c for input clock.
*/

// #include "stm32f401xe.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_rcc.h"


// #define   STM32F401xE


/* Private function prototypes -----------------------------------------------*/
void     delay(void);
void     SystemClock_Config(void);
void     GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);


/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */

int main(void)
{
  /* Configure the system clock to 84 MHz */
  SystemClock_Config();

  // Configure the GPIO pin
  LL_GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin        = LL_GPIO_PIN_5;
  GPIO_InitStruct.Mode       = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed      = LL_GPIO_SPEED_FREQ_MEDIUM;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull       = LL_GPIO_PULL_NO;

  // Initialize the GPIO peripheral
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  while(1)
  {
    
    // Toggle LED
    GPIO_ToggleBits(GPIOA, LL_GPIO_PIN_5);

    // Add some delay
    delay();

  }

  return 0;
}


// Delay function
void delay(void)
{
	for(uint32_t i = 0 ; i < 500000 ; i ++);
}


/* ==============   BOARD SPECIFIC CONFIGURATION CODE BEGIN    ============== */

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 84000000
  *            HCLK(Hz)                       = 84000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 336
  *            PLL_P                          = 4
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale2 mode
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  /* Enable HSE oscillator */
  LL_RCC_HSE_EnableBypass();
  LL_RCC_HSE_Enable();
  while(LL_RCC_HSE_IsReady() != 1)
  {
  };

  /* Set FLASH latency */
  // LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);

  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_8, 336, LL_RCC_PLLP_DIV_4);
  LL_RCC_PLL_Enable();
  while(LL_RCC_PLL_IsReady() != 1)
  {
  };

  /* Sysclk activation on the main PLL */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  };

  /* Set APB1 & APB2 prescaler */
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

  /* Set systick to 1ms */
  SysTick_Config(84000000 / 1000);

  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  SystemCoreClock = 84000000;
}


/**
  * @brief  Toggles the specified GPIO pins..
  * @param  GPIOx: where x can be (A..I) to select the GPIO peripheral.
  * @param  GPIO_Pin: Specifies the pins to be toggled.
  * @retval None
  */
void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  GPIOx->ODR ^= GPIO_Pin;
}
