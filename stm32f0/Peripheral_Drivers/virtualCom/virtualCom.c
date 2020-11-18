#include "virtualCom.h"


void serialPrintInit(void)
{

  //Enable GPIOA PA2      
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;                  //Enable clock for GPIOA
  GPIOA->MODER |= GPIO_MODER_MODER2_1;                //Set PA2 to alternate function 
  GPIOA->AFR[0] |= 0x100;                             //Set PA2 to USART2
  
  //Enable USART2 TX
  RCC->APB1ENR |= RCC_APB1ENR_USART2EN;               //Enable clock for USART2
  USART2->BRR = 0x1388;                               //Set baudrate to 9.6kbit/sec
  USART2->CR1 |= USART_CR1_UE | USART_CR1_TE;         //Enable USART2 TX

}


void serialPrint(const char *msg, ...)
{
  char buffer[64];

  va_list args;
  va_start(args, msg);
  vsprintf(buffer, msg, args);

  for(unsigned int i = 0; i < strlen(buffer); i++)    //Loop to pass character to TX data register
  {
    USART2->TDR = buffer[i];          
    while(!(USART2->ISR & USART_ISR_TXE));            //Check if TX data register is empty
  }
}



