/* 
 * File:   mcal_internal_interrupt.h
 * Author: houda
 *
 * Created on February 26, 2024, 6:08 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/* INCLUDS */

#include "mcal_interrupt_config.h"

/* MACRO DECLARATIONS */

/* MACRO FUNTIONS DECLARATIONS */

// ADC interrupt macros:
#if ADC_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
/* This routine clears the interrupt enable for the ADC module*/
#define ADC_InterruptDisable()         (PIE1bits.ADIE = 0)
/* This routine sets the interrupt enable for the ADC module*/
#define ADC_InterruptEnable()          (PIE1bits.ADIE = 1)
/* This routine clears the interrupt flag for the ADC module*/
#define ADC_InterruptFlagClear()       (PIR1bits.ADIF = 0)
/* This routine sets the interrupt priority for the ADC module*/
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_ENABLE_FEATURE
/* This routine set the ADC Interrupt Priority to be High priority */
#define ADC_InterruptPriorityHIGH()     (IPR1bits.ADIP = 1)
/* This routine set the ADC Interrupt Priority to be Low priority */
#define ADC_InterruptPriorityLOW()      (IPR1bits.ADIP = 0)
#endif
#endif

// timer0 interrupt macros:
#if TIMER0_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
/* This routine clears the interrupt enable for the timer0 module*/
#define TIMER0_InterruptDisable()         (INTCONbits.TMR0IE = 0)
/* This routine sets the interrupt enable for the timer0 module*/
#define TIMER0_InterruptEnable()          (INTCONbits.TMR0IE = 1)
/* This routine clears the interrupt flag for the timer0 module*/
#define TIMER0_InterruptFlagClear()       (INTCONbits.TMR0IF = 0)
/* This routine sets the interrupt priority for the timer0 module*/
#if INTERRUPT_PRIORITY_FEATURE  == INTERRUPT_ENABLE_FEATURE
/* This routine set the timer0 Interrupt Priority to be High priority */
#define TIMER0_InterruptPriorityHIGH()     (INTCON2bits.TMR0IP = 1)
/* This routine set the timer0 Interrupt Priority to be Low priority */
#define TIMER0_InterruptPriorityLOW()      (INTCON2bits.TMR0IP = 0)
#endif
#endif


// timer1 interrupt macros:

#if TIMER1_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
/* This routine clears the interrupt enable for the timer1 module*/
#define TIMER1_InterruptDisable()         (PIE1bits.TMR1IE = 0)
/* This routine sets the interrupt enable for the timer1 module*/
#define TIMER1_InterruptEnable()          (PIE1bits.TMR1IE = 1)
/* This routine clears the interrupt flag for the timer1 module*/
#define TIMER1_InterruptFlagClear()       (PIR1bits.TMR1IF = 0)
#if INTERRUPT_PRIORITY_FEATURE  == INTERRUPT_ENABLE_FEATURE
/* This routine set the timer1 Interrupt Priority to be High priority */
#define TIMER1_InterruptPriorityHIGH()     (IPR1bits.TMR1IP = 1)
/* This routine set the timer1 Interrupt Priority to be Low priority */
#define TIMER1_InterruptPriorityLOW()      (IPR1bits.TMR1IP = 0)
#endif
#endif

// timer2 interrupt macros:
#if TIMER2_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
/* This routine clears the interrupt enable for the timer2 module*/
#define TIMER2_InterruptDisable()        (PIE1bits.TMR2IE = 0)
/* This routine sets the interrupt enable for the timer2 module*/
#define TIMER2_InterruptEnable()         (PIE1bits.TMR2IE = 1)
/* This routine clears the interrupt flag for the timer2 module*/
#define TIMER2_InterruptFlagClear()      (PIR1bits.TMR2IF = 0)
#if INTERRUPT_PRIORITY_FEATURE  == INTERRUPT_ENABLE_FEATURE
/* This routine set the timer2 Interrupt Priority to be High priority */
#define TIMER2_InterruptPriorityHIGH()   (IPR1bits.TMR2IP = 1)
/* This routine set the timer2 Interrupt Priority to be Low priority */
#define TIMER2_InterruptPriorityLOW()    (IPR1bits.TMR2IP = 0)
#endif
#endif


// timer3 interrupt macros:
#if TIMER3_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
/* This routine clears the interrupt enable for the timer3 module*/
#define TIMER3_InterruptDisable()        (PIE2bits.TMR3IE = 0)
/* This routine sets the interrupt enable for the timer3 module*/
#define TIMER3_InterruptEnable()         (PIE2bits.TMR3IE = 1)
/* This routine clears the interrupt flag for the timer3 module*/
#define TIMER3_InterruptFlagClear()      (PIR2bits.TMR3IF = 0)
#if INTERRUPT_PRIORITY_FEATURE  == INTERRUPT_ENABLE_FEATURE
/* This routine set the timer3 Interrupt Priority to be High priority */
#define TIMER3_InterruptPriorityHIGH()   (IPR2bits.TMR3IP = 1)
/* This routine set the timer3 Interrupt Priority to be Low priority */
#define TIMER3_InterruptPriorityLOW()    (IPR2bits.TMR3IP = 0)
#endif
#endif


// CCP1 interrupt macros:
#if CCP1_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
/* This routine clears the interrupt enable for the CCP1 module*/
#define CCP1_InterruptDisable()        (PIE1bits.CCP1IE = 0)
/* This routine sets the interrupt enable for the CCP1 module*/
#define CCP1_InterruptEnable()         (PIE1bits.CCP1IE = 1)
/* This routine clears the interrupt flag for the CCP1module*/
#define CCP1_InterruptFlagClear()      (PIR1bits.CCP1IF = 0)
#if INTERRUPT_PRIORITY_FEATURE  == INTERRUPT_ENABLE_FEATURE
/* This routine set the CCP1 Interrupt Priority to be High priority */
#define CCP1_InterruptPriorityHIGH()   (IPR1bits.CCP1IP = 1)
/* This routine set the CCP1 Interrupt Priority to be Low priority */
#define CCP1_InterruptPriorityLOW()    (IPR1bits.CCP1IP = 0)
#endif
#endif


// CCP2 interrupt macros:
#if CCP2_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
/* This routine clears the interrupt enable for the CCP2 module*/
#define CCP2_InterruptDisable()        (PIE2bits.CCP2IE = 0)
/* This routine sets the interrupt enable for the CCP2 module*/
#define CCP2_InterruptEnable()         (PIE2bits.CCP2IE = 1)
/* This routine clears the interrupt flag for the CCP2 module*/
#define CCP2_InterruptFlagClear()      (PIR2bits.CCP2IF = 0)
#if INTERRUPT_PRIORITY_FEATURE  == INTERRUPT_ENABLE_FEATURE
/* This routine set the CCP2 Interrupt Priority to be High priority */
#define CCP2_InterruptPriorityHIGH()   (IPR2bits.CCP2IP = 1)
/* This routine set the CCP2 Interrupt Priority to be Low priority */
#define CCP2_InterruptPriorityLOW()    (IPR2bits.CCP2IP = 0)
#endif
#endif

// USART interrupt macros:
#if EUSART_TX_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
/* This routine clears the interrupt enable for the EUSART tx module*/
#define EUSART_TX_InterruptDisable()        (PIE1bits.TXIE = 0)
/* This routine sets the interrupt enable for the EUSART tx module*/
#define EUSART_TX_InterruptEnable()         (PIE1bits.TXIE = 1)
/* This routine clears the interrupt flag for the EUSART tx module*/
// flag is cleared by writing to TXREG
#if INTERRUPT_PRIORITY_FEATURE  == INTERRUPT_ENABLE_FEATURE
/* This routine set the EUSART tx Interrupt Priority to be High priority */
#define EUSART_TX_InterruptPriorityHIGH()   (IPR1bits.TXIP = 1)
/* This routine set the EUSART tx Interrupt Priority to be Low priority */
#define EUSART_TX_InterruptPriorityLOW()    (IPR1bits.TXIP = 0)
#endif
#endif

#if EUSART_RX_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
/* This routine clears the interrupt enable for the EUSART rx module*/
#define EUSART_RX_InterruptDisable()        (PIE1bits.RCIE = 0)
/* This routine sets the interrupt enable for the EUSART rx module*/
#define EUSART_RX_InterruptEnable()         (PIE1bits.RCIE = 1)
/* This routine clears the interrupt flag for the EUSART rx module*/
// flag is cleared by reading RCREG
#if INTERRUPT_PRIORITY_FEATURE  == INTERRUPT_ENABLE_FEATURE
/* This routine set the EUSART rx Interrupt Priority to be High priority */
#define EUSART_RX_InterruptPriorityHIGH()   (IPR1bits.RCIP = 1)
/* This routine set the EUSART rx Interrupt Priority to be Low priority */
#define EUSART_RX_InterruptPriorityLOW()    (IPR1bits.RCIP = 0)
#endif
#endif

#if SPI_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
/* This routine clears the interrupt enable for the SPI module*/
#define SPI_InterruptDisable()        (PIE1bits.SSPIE = 0)
/* This routine sets the interrupt enable for the SPI module*/
#define SPI_InterruptEnable()         (PIE1bits.SSPIE = 1)
/* This routine clears the interrupt flag for the SPI module*/
#define SPI_InterruptFlagClear()      (PIR1bits.SSPIF = 0)
#if INTERRUPT_PRIORITY_FEATURE  == INTERRUPT_ENABLE_FEATURE
/* This routine set the SPI Interrupt Priority to be High priority */
#define SPI_InterruptPriorityHIGH()   (IPR1bits.SSPIP = 1)
/* This routine set the SPI Interrupt Priority to be Low priority */
#define SPI_InterruptPriorityLOW()    (IPR1bits.SSPIP = 0)
#endif
#endif


/* DATA TYPE DECLARATIONS (ENUMS,UNIONS,STRUCTS) */

/* FUNTIONS DECLARATIONS */

#endif
