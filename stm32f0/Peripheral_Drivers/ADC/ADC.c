#include "ADC.h"

void ADCInit(void)
{

  //Enable GPIOA PA0 Analog Mode 
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;                  //Enable Clock for GPIOA
  GPIOA->MODER |= GPIO_MODER_MODER0;                  //Set PA0 to Analog mode
  
  //Enable Clock for Analog Mode 
  RCC->APB2ENR |= RCC_APB2ENR_ADCEN;                  //Enable clock for ADC
  RCC->CR2 |= RCC_CR2_HSI14ON;                        //Enable 14MHz Oscillator 
  while ((RCC->CR2 & RCC_CR2_HSI14ON) == 0);          //Wait for Oscillator 

}

void ADCCal(void)
{

  //Calibrate ADC
  if ((ADC1->CR & ADC_CR_ADEN) != 0)                  //Check if ADC is enabled
  {
    ADC1->CR |= ADC_CR_ADDIS;
  }  
  while ((ADC1->CR & ADC_CR_ADEN) != 0);              //Wait to disable ADC
  ADC1->CFGR1 &= ~ADC_CFGR1_DMAEN;                    //Dissable DMA
  ADC1->CR |= ADC_CR_ADCAL;                           //Calibrate ADC
  while ((ADC1->CR & ADC_CR_ADCAL) != 0);             //Wait for calibration 
  

}

void ADCEnable(void)
{

  //Enable ADC
  if ((ADC1->ISR & ADC_ISR_ADRDY) != 0)                 
  {
    ADC1->ISR &= ~ADC_ISR_ADRDY;
  }
  ADC1->CR |= ADC_CR_ADEN;                            //Enable ADC
  while ((ADC1->ISR & ADC_ISR_ADRDY) == 0);           //Wait for ADC
  
  //Select Channel and Sampling Rate 
  ADC1->CHSELR = ADC_CHSELR_CHSEL0;                   //Select channel 0 
  ADC1->SMPR &= ADC_SMPR_SMP;                         //Set sampling rate 

}
