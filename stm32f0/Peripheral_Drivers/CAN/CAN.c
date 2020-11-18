#include "CAN.h"

uint16_t CAN_ID;

void CANInit(void)
{

  //Enable GPIOD
  RCC->AHBENR |= RCC_AHBENR_GPIODEN;
  GPIOD->MODER |= GPIO_MODER_MODER0;
  GPIOD->MODER |= GPIO_MODER_MODER1;
  GPIOD->AFR[0] &= ~GPIO_AFRL_AFR0;
  GPIOD->AFR[0] &= ~GPIO_AFRL_AFR1;

  //Enable bxCAN Tx/Rx
  RCC->APB1ENR |= RCC_APB1ENR_CANEN;
  CAN->MCR |= CAN_MCR_INRQ; 
  while((CAN->MSR & CAN_MSR_INAK) != CAN_MSR_INAK);
  CAN->BTR |= 0x001C000BUL; 
  CAN->MCR &= ~CAN_MCR_INRQ;
  while((CAN->MSR & CAN_MSR_INAK) == CAN_MSR_INAK);

}

void CANFilterInit(void)
{

  //Configure Filters
  CAN->FMR |= CAN_FMR_FINIT;
  CAN->FA1R |= CAN_FA1R_FACT0;
  CAN->FS1R |= CAN_FS1R_FSC0;
  CAN->FM1R &= ~CAN_FM1R_FBM0;
  
  CAN->sFilterRegister[0].FR1 = CAN_ID << 21;
  CAN->sFilterRegister[0].FR2 = 0xFFF10000UL;
  CAN->FMR &= ~CAN_FMR_FINIT;

}
