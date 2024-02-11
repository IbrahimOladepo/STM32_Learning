/*
  This is a template file that you can use to start your project on your
  stm32 developlent board. Use it with the supplied Makefile, stm32_flash.ld,
  stm32f4xx_conf.h and system_stm32f4xx.c files for your need.

  Edit Makefile to include right paths to all stlibs, arm compiler and st-link.

  Also make sure to have the right settings in system_stm32f4xx.c for input clock.
*/

#include "stm32f4xx.h"

int main(void)
{
  // Setup RCC peripheral clock for the LED pin's port
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  // Configure the GPIO pin
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_5;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;

  // Initialize the GPIO peripheral
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  while(1)
  {
    
    // Turn on LED
    GPIO_SetBits(GPIOA, GPIO_Pin_5);

    // Add some delay
    for(long i=0; i < 168000000/30; i++){__NOP();}

    // Turn off LED
    GPIO_ResetBits(GPIOA, GPIO_Pin_5);

    // Add some delay
    for(long i=0; i < 168000000/30; i++){__NOP();}

  }

  return 0;
}
