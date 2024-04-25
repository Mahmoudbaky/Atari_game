/* 
 * File:   mcal_interrupt_manager.c
 * Author: houda
 *
 * Created on February 26, 2024, 6:13 PM
 */


#include "mcal_interrupt_manager.h"

static volatile uint8 RB4_Flag = 1, RB5_Flag = 1, RB6_Flag = 1, RB7_Flag = 1;

#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_ENABLE_FEATURE

void __interrupt() InterruptManagerHigh (void){
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE)&&(INTERRUPT_OCCUR == INTCONbits.INT0IF)){
        INT0_ISR();
    }
    else{/* nothing */}
    
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE)&&(INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
        INT2_ISR();
    }
    else{/* nothing */}
}

void __interrupt(low_priority) InterruptManagerLow (void){
      if((INTERRUPT_ENABLE == INTCON3bits.INT1IE)&&(INTERRUPT_OCCUR == INTCON3bits.INT1IF)){
        INT1_ISR();
    }
}

#else

void __interrupt() InterruptManager(void){
    /* ============ INTx External Interrupt Start ============ */
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE)&&(INTERRUPT_OCCUR == INTCONbits.INT0IF)){
        INT0_ISR();
    }
    else{/* nothing */}
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE)&&(INTERRUPT_OCCUR == INTCON3bits.INT1IF)){
        INT1_ISR();
    }
    else{/* nothing */}
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE)&&(INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
        INT2_ISR();
    }
    else{/* nothing */}
    /* ============ INTx External Interrupt End ============ */
    
    /* ============ PortB External On Change Interrupt Start ============ */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB4 == HIGH_T) && (RB4_Flag = 1)){
        RB4_Flag = 0;
        RB4_ISR(0);
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB4 == LOW_T) && (RB4_Flag = 0)){
        RB4_Flag = 1;
        RB4_ISR(1);
    }
    else{ /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB5 == HIGH_T) && (RB5_Flag = 1)){
        RB5_Flag = 0;
        RB5_ISR(0);
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB5 == LOW_T)&& (RB5_Flag = 0)){
        RB5_Flag = 1;
        RB5_ISR(1);
    }
    else{ /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB6 == HIGH_T) && (RB6_Flag = 1)){
        RB6_Flag = 0;
        RB6_ISR(0);
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB6 == LOW_T) && (RB6_Flag = 0)){
        RB6_Flag = 1;
        RB6_ISR(1);
    }
    else{ /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB7 == HIGH_T) && (RB7_Flag = 1)){
        RB7_Flag = 0;
        RB7_ISR(0);
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB7 == LOW_T) && (RB7_Flag = 0)){
        RB7_Flag = 1;
        RB7_ISR(1);
    }
    else{ /* Nothing */ }
    
    // internal interrupt : ADC, Timer0, Timer1

    /* ============ ADC Interrupt Start ============ */
    if((INTERRUPT_ENABLE == PIE1bits.ADIE)&&(INTERRUPT_OCCUR == PIR1bits.ADIF)){
        // ADC_ISR();
    }
    else{/* nothing */}
    /* ============ ADC Interrupt End ============ */

    /* ============ Timer0 Interrupt Start ============ */
    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE)&&(INTERRUPT_OCCUR == INTCONbits.TMR0IF)){
        // TIMER0_ISR();
    }
    else{/* nothing */}
    /* ============ Timer0 Interrupt End ============ */

    /* ============ Timer1 Interrupt Start ============ */
    if((INTERRUPT_ENABLE == PIE1bits.TMR1IE)&&(INTERRUPT_OCCUR == PIR1bits.TMR1IF)){
        TIMER1_ISR();
    }
    else{/* nothing */}
    /* ============ Timer1 Interrupt End ============ */

    /* ============ Timer2 Interrupt Start ============ */
    if((INTERRUPT_ENABLE == PIE1bits.TMR2IE)&&(INTERRUPT_OCCUR == PIR1bits.TMR2IF)){
        // TIMER2_ISR();
    }
    else{/* nothing */}
    /* ============ Timer2 Interrupt End ============ */

    /* ============ Timer3 Interrupt Start ============ */
    if((INTERRUPT_ENABLE == PIE2bits.TMR3IE)&&(INTERRUPT_OCCUR == PIR2bits.TMR3IF)){
        // TIMER3_ISR();
    }
    else{/* nothing */}
    /* ============ Timer3 Interrupt End ============ */
    

    /* ============ ccp1 and ccp2 Interrupt Start ============ */

    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE)&&(INTERRUPT_OCCUR == PIR1bits.CCP1IF)){
        // CCP1_ISR();
    }
    else{/* nothing */}

    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE)&&(INTERRUPT_OCCUR == PIR2bits.CCP2IF)){
        // CCP2_ISR();
    }
    else{/* nothing */}


    /* ============ ccp1 and ccp2 Interrupt End ============ */

    /* ============ USART Interrupt Start ============ */

    if((INTERRUPT_ENABLE == PIE1bits.TXIE)&&(INTERRUPT_OCCUR == PIR1bits.TXIF)){
        // EUSART_TX_ISR();
    }
    else{/* nothing */}

    if((INTERRUPT_ENABLE == PIE1bits.RCIE)&&(INTERRUPT_OCCUR == PIR1bits.RCIF)){
        // EUSART_RX_ISR();
    }
    else{/* nothing */}
    
    /* ============ USART Interrupt End ============ */

    /* ============ SPI Interrupt Start ============ */
    if((INTERRUPT_ENABLE == PIE1bits.SSPIE)&&(INTERRUPT_OCCUR == PIR1bits.SSPIF)){
        // SPI_ISR();
    }
    else{/* nothing */}
    /* ============ SPI Interrupt End ============ */


}

#endif