#include "stm32f0xx.h"

void delay(uint32_t ms);
void counterIncrease(void);

static uint32_t counter;

int main(void)
{
  //Initialize clock for GPIOA
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

  GPIOA->MODER |= GPIO_MODER_MODER5_0; //Set PA_5 to output
  GPIOA->OTYPER &= GPIO_OTYPER_OT_5; //Set PA_5 to push pull
  GPIOA->OSPEEDR &= GPIO_OSPEEDR_OSPEEDR5; //Set PA_5 speed to low 
  GPIOA->PUPDR &= GPIO_PUPDR_PUPDR5; //Set PA_5 to pull up 

  SysTick_Config(SystemCoreClock / 1000);
  
  while (1)
  {
    GPIOA->BSRR = GPIO_BSRR_BS_5;
    delay(1000);
    GPIOA->BSRR = GPIO_BSRR_BR_5;
    delay(1000);
  }
}

//Function for generating delay
void delay(uint32_t ms)
{
  counter =0;
  while(counter < ms);
}

//Interrupt handler increase function
void counterIncrease(void)
{
  counter++;
}
