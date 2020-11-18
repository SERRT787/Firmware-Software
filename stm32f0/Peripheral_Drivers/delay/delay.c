#include "delay.h"

static uint32_t counter;

void delayInit(void)
{
    
  SysTick_Config(SystemCoreClock / 1000);

}

//Function for generating delay
void delay(uint32_t ms)
{
  counter = 0;
  while(counter < ms);
}

//Interrupt handler increase function
void counterIncrease(void)
{
  counter++;
}
