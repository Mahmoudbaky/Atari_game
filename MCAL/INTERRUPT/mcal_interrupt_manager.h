/* 
 * File:   mcal_interrupt_manager.h
 * Author: houda
 *
 * Created on February 26, 2024, 6:13 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/* INCLUDS */
#include "mcal_interrupt_config.h"

/* MACRO DECLARATIONS */

/* MACRO FUNTIONS DECLARATIONS */

/* DATA TYPE DECLARATIONS (ENUMS,UNIONS,STRUCTS) */

/* FUNTIONS DECLARATIONS */
void INT0_ISR (void);
void INT1_ISR (void);
void INT2_ISR (void);
void RB4_ISR(uint8 RB4_Source);
void RB5_ISR(uint8 RB5_Source);
void RB6_ISR(uint8 RB6_Source);
void RB7_ISR(uint8 RB7_Source);

//void ADC_ISR(void);

//void TIMER0_ISR(void);
void TIMER1_ISR(void);
//void TIMER2_ISR(void);
//void TIMER3_ISR(void);

//void CCP1_ISR(void);
//void CCP2_ISR(void);

//void EUSART_TX_ISR(void);
//void EUSART_RX_ISR(void);

void SPI_ISR(void);

#endif	/* MCAL_INTERRUPT_MANAGER_H */

