 /****************************************************
 *  BDC board - iCub Facility - 2013                 *
 *  Timers configuration                             *
 *                                                   *
 *  Written by Andrea Mura                           *
 *  <andrea.mura@iit.it>                             *
 ****************************************************/
 
#include "stm32f10x.h"
#include "define.h"
#include "globals.h"

// ----------------------------------------------------------------------------
// initialize TIM1
// ----------------------------------------------------------------------------
void TIM1_Init (void) {

	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;		// enable clock for TIM1
	
  TIM1->PSC   = (3000)-1;								// set prescaler   = 10KHz
  TIM1->ARR   = 1000-1;										// set auto-reload
  TIM1->RCR   =  1-1;									// set repetition counter

  TIM1->DIER = TIM_DIER_UIE;						// Update Interrupt enable
  NVIC_EnableIRQ(TIM1_UP_IRQn);					// TIM1   Interrupt enable

  TIM1->CR1  |= TIM_CR1_CEN;						// timer enable
}

// ----------------------------------------------------------------------------
// initialize TIM2
// ----------------------------------------------------------------------------
void TIM2_Init (void) {
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;		// enable clock for TIM2

  TIM2->PSC   = (3000)-1;								// set prescaler   = 10KHz
  TIM2->ARR   = 6000-1;									// set auto-reload (es: 2000 = 100 ms)
  TIM2->RCR   =  0;											// set repetition counter

  TIM2->DIER = TIM_DIER_UIE;						// Update Interrupt enable
  NVIC_EnableIRQ(TIM2_IRQn);						// TIM1   Interrupt enable

  TIM2->CR1  |= TIM_CR1_CEN;						// timer enable
}

// ----------------------------------------------------------------------------
// Timer1 Update Interrupt Handler
// ----------------------------------------------------------------------------
void TIM1_UP_IRQHandler (void) {

  if (TIM1->SR & (TIM_SR_UIF)) {                  /* UIF set?                 */

    if (ledDir == 0){
			ledDir=1;
			//LED1_OFF;
		}
    else{
			ledDir=0;
			//LED1_ON;
		}
		
		//rx=GetKey1();
			
    TIM1->SR &= ~(TIM_SR_UIF);                    /* clear UIF flag           */
  }
}

// ----------------------------------------------------------------------------
// Timer2 Update Interrupt Handler
// ----------------------------------------------------------------------------
void TIM2_IRQHandler (void) {

  if (TIM2->SR & (TIM_SR_UIF)) {                  /* UIF set?                 */

    if (ledDir1 == 0){
			ledDir1=1;
			LED1_ON;
		}
    else if (ledDir1 == 1){
			ledDir1=0;
			LED1_OFF;
		}		
    TIM2->SR &= ~(TIM_SR_UIF);                    /* clear UIF flag           */
  }
}

