/* 
 * File:   mcal_interrupt_gen_cfg.h
 * Author: houda
 *
 * Created on February 26, 2024, 7:56 PM
 */

#ifndef MCAL_INTERRUPT_GEN_CFG_H
#define	MCAL_INTERRUPT_GEN_CFG_H

#define INTERRUPT_ENABLE_FEATURE    1
#define INTERRUPT_DISABLE_FEATURE   0 

/* global */
#define INTERRUPT_PRIORITY_FEATURE  INTERRUPT_DISABLE_FEATURE /* enable the interrupt priority */

/* EXTERNAL INTERRUPT CONFIGURATIONS */

#define INTERRUPT_INTx_FEATURE      INTERRUPT_ENABLE_FEATURE   /* enable the edge interrupt */
#define INTERRUPT_ON_CHANGE_FEATURE INTERRUPT_ENABLE_FEATURE   /* enable the on change interrupt */

/* INTERNAL INTERRUPT CONFIGURATIONS */

//  ADC interrupt macros:
#define ADC_INTURRUPT_FUNCTION_ENABLE     INTERRUPT_ENABLE_FEATURE   /* enable the ADC interrupt */

//  timers interrupt macros:
#define TIMER0_INTURRUPT_FUNCTION_ENABLE  INTERRUPT_ENABLE_FEATURE   // enable the timer0 interrupt 
#define TIMER1_INTURRUPT_FUNCTION_ENABLE  INTERRUPT_ENABLE_FEATURE   // enable the timer1 interrupt
#define TIMER2_INTURRUPT_FUNCTION_ENABLE  INTERRUPT_ENABLE_FEATURE   // enable the timer2 interrupt
#define TIMER3_INTURRUPT_FUNCTION_ENABLE  INTERRUPT_ENABLE_FEATURE   // enable the timer3 interrupt

//  CCP interrupt macros:  
#define CCP1_INTURRUPT_FUNCTION_ENABLE    INTERRUPT_ENABLE_FEATURE   // enable the CCP1 interrupt
#define CCP2_INTURRUPT_FUNCTION_ENABLE    INTERRUPT_ENABLE_FEATURE   // enable the CCP1 interrupt

//  USART interrupt macros:
#define EUSART_TX_INTURRUPT_FUNCTION_ENABLE   INTERRUPT_ENABLE_FEATURE   // enable the EUSART tx interrupt
#define EUSART_RX_INTURRUPT_FUNCTION_ENABLE   INTERRUPT_ENABLE_FEATURE   // enable the EUSART rx interrupt

//  SPI interrupt macros:
#define SPI_INTURRUPT_FUNCTION_ENABLE    INTERRUPT_ENABLE_FEATURE   // enable the SPI interrupt


#endif	/* MCAL_INTERRUPT_GEN_CFG_H */

