/*
* mcal_timer1.c
*   
*  Created on: 10/7/2020
*/

#include "mcal_timer1.h"

static inline void select_clock_soruce(const timer1_config_t *timer);
static inline void select_read_write_mode(const timer1_config_t *timer);

#if TIMER1_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
    void (*TIMER1_ISR_handler)(void) = NULL;
#endif

static volatile uint16 preloaded_value = 0;

Std_ReturnType timer1_Init  (timer1_config_t *timer){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        /* disable timer1 */
        TIMER1_DISABLE();
        /* prescaler configuration */
        TIMER1_PRESCALER_SELECT(timer->prescaler);
        /* mode : counter or timer */
        select_clock_soruce(timer);
        /* load the timer1 register if 8 bit is enabled*/
        TMR1H = (timer->preloaded_value >> 8);
        TMR1L = (uint8)(timer->preloaded_value);
        /* save the preloaded value for interrupt purpose "to use this value in TIMER1_ISR" */
        preloaded_value = timer->preloaded_value;
        /* interrupt config */
#if TIMER1_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
        TIMER1_InterruptEnable();
        TIMER1_InterruptFlagClear();
        TIMER1_ISR_handler = timer->timer1_callback;
        /* interrupt with periority config */
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_ENABLE_FEATURE
        INTERRUPT_InterruptPriorityEnable();
        if (timer->interrupt_priority == INTERRUPT_HIGH_PRIORITY){
            INTERRUPT_globalInterruptEnableHigh();
            TIMER1_InterruptPriorityHIGH();
        }
        else if (timer->interrupt_priority == INTERRUPT_LOW_PRIORITY){
            INTERRUPT_globalInterruptEnableLow();
            TIMER1_InterruptPriorityLOW();
        }
#else
        INTERRUPT_globalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
        /* enable timer1 */ 
        TIMER1_ENABLE();

    }
    return ret;
}                

Std_ReturnType timer1_DeInit(timer1_config_t *timer){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        /* disable timer1 */
        TIMER1_DISABLE();
        /* disable interrupt */
    #if TIMER1_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
        TIMER1_InterruptDisable();
    #endif
    }
    return ret;
}   

Std_ReturnType timer1_write_value (timer1_config_t *timer, uint16 value){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        /* load the timer1 register */
        TMR1H = (value >> 8);
        TMR1L = (uint8)(value);
    }
    return ret;
}  

Std_ReturnType timer1_read_value  (timer1_config_t *timer, uint16 *value){
    Std_ReturnType ret = E_OK;
    uint8 l_high , l_low = 0;
    if(NULL == timer || NULL == value){
        ret = E_NOT_OK;
    }
    else{
        l_low  = TMR1L;
        l_high = TMR1H;
        *value = (uint16)((l_high << 8) + l_low);    
        
    }
    return ret;
}


/* TIMER1 ISR */
void TIMER1_ISR(void){
    /* clear flag */
    TIMER1_InterruptFlagClear();
    /* code  */
    TMR1H = (preloaded_value >> 8);
    TMR1L = (uint8)(preloaded_value);
    /* call back */
    if(TIMER1_ISR_handler){ TIMER1_ISR_handler(); }
}


/* HELPER FUNCTIONS */

static inline void select_clock_soruce(const timer1_config_t *timer){
    switch (timer->clock_source){
    case TIMER1_INTERNAL_CLOCK :
        TIMER1_SELECET_INTERNAL_CLOCK_TIMER_MODE();
    break;
    case TIMER1_EXTERNAL_CLOCK :
        TIMER1_SELECET_EXTERNAL_CLOCK_COUNTER_MODE();
        if (TIMER1_SYNCHRONOUS == timer->synchronization){
            TIMER1_SELECT_SYNCHRONOUS();
        }
        else if(TIMER1_ASYNCHRONOUS == timer->synchronization){
            TIMER1_SELECT_ASYNCHRONOUS();
        }
        else { /* nothing */ }
    break;
    default : /* nothing */
    break;
    }
}

static inline void select_read_write_mode(const timer1_config_t *timer){
    switch (timer->read_write_mode){
    case TIMER1_16BIT_READ_WRITE:
    TIMER1_SELECT_16bit_READ_WRITE_MODE();
    break;
    case TIMER1_8BIT_READ_WRITE:
    TIMER1_SELECT_8bit_READ_WRITE_MODE();
    break;
    default : /* nothing */
    break;
    }
}