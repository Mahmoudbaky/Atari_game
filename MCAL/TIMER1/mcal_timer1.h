/*
* mcal_timer1.h
*   
*  Created on: 10/7/2020
*/

#ifndef MCAL_TIMER1_H
#define	MCAL_TIMER1_H

/* INCLUDS */

#include "../GPIO/mcal_gpio.h"
#include "pic18f4620.h"
#include "../../MCAL/STD/mcal_std_types.h"
#include "../INTERRUPT/mcal_internal_interrupt.h"

/* MACRO DECLARATIONS */

#define TIMER1_16BIT_MODE  1
#define TIMER1_8BIT_MODE   0


/* MACRO FUNTIONS DECLARATIONS */

#define TIMER1_ENABLE()     (T1CONbits.TMR1ON = 1) // enable timer1
#define TIMER1_DISABLE()    (T1CONbits.TMR1ON = 0) // disable timer1

#define TIMER1_SELECET_INTERNAL_CLOCK_TIMER_MODE()  (T1CONbits.TMR1CS = 0)  // select internal clock "Fosc/4" (timer)
#define TIMER1_SELECET_EXTERNAL_CLOCK_COUNTER_MODE()  (T1CONbits.TMR1CS = 1)  // select external clock "detectes only rising edge" (counter)

#define TIMER1_SELECT_SYNCHRONOUS()     (T1CONbits.T1SYNC = 0)  // timer1 clock source is synchronized with timer1 oscillator
#define TIMER1_SELECT_ASYNCHRONOUS()    (T1CONbits.T1SYNC = 1)  // timer1 clock source is not synchronized with timer1 oscillator

#define TIMER1_OSILLATOR_ENABLE()       (T1CONbits.T1OSCEN = 1)  // timer1 oscillator enable
#define TIMER1_OSILLATOR_DISABLE()      (T1CONbits.T1OSCEN = 0)  // timer1 oscillator disable

#define TIMER1_CHECK_Timer1Osillator()  (T1CONbits.T1RUN)  // check if timer1 oscillator is enabled or not

#define TIMER1_PRESCALER_SELECT(_PRESCALER)  (T1CONbits.T1CKPS = _PRESCALER) // select prescaler value

#define TIMER1_SELECT_8bit_READ_WRITE_MODE()  (T1CONbits.RD16 = 0)  // select 8-bit read/write mode  
#define TIMER1_SELECT_16bit_READ_WRITE_MODE() (T1CONbits.RD16 = 1)  // select 16-bit read/write mode 


/* DATA TYPE DECLARATIONS (ENUMS,UNIONS,STRUCTS) */

typedef enum {
    TIMER1_INTERNAL_CLOCK = 0,
    TIMER1_EXTERNAL_CLOCK
}timer1_clock_source_t;

typedef enum {
    TIMER1_SYNCHRONOUS = 0,
    TIMER1_ASYNCHRONOUS
}timer1_synchronization_t;

typedef enum {
    TIMER1_OSC_ENABLE = 0,
    TIMER1_OSC_DISABLE
}timer1_osc_t;

typedef enum { 
    TIMER1_PRESCALER_1 = 0,  // prescaler 1:1 means no prescaler
    TIMER1_PRESCALER_2,
    TIMER1_PRESCALER_4, 
    TIMER1_PRESCALER_8
}timer1_prescaler_t;

typedef enum { 
    TIMER1_16BIT_READ_WRITE = 0,
    TIMER1_8BIT_READ_WRITE 
}timer1_read_write_mode_t;

typedef struct {
#if TIMER1_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
    void (*timer1_callback)(void);  // pointer to function to be called when timer1 overflow
    interrupt_priority_cfg interrupt_priority;  // interrupt priority
#endif
    uint16                   preloaded_value;  // timer1 value
    timer1_prescaler_t       prescaler;        // prescaler value
    timer1_clock_source_t    clock_source;     // clock source (timer / counter)
    timer1_synchronization_t synchronization;  // synchronization (for counter mode)
    timer1_osc_t             timer1_osc_en;    // timer1 osc enable
    timer1_read_write_mode_t read_write_mode;  // read/write mode
    
}timer1_config_t;

/* FUNTIONS DECLARATIONS */

Std_ReturnType timer1_Init  (timer1_config_t *timer);                      // initialize timer1
Std_ReturnType timer1_DeInit(timer1_config_t *timer);                      // deinitialize timer1
Std_ReturnType timer1_write_value (timer1_config_t *timer, uint16 value);  // write value to timer1
Std_ReturnType timer1_read_value  (timer1_config_t *timer, uint16 *value); // read value from timer1

#endif	/* MCAL_TIMER1_H */