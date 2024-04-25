/* 
 * File:   mcal_interrupt_config.h
 * Author: houda
 *
 * Created on February 26, 2024, 6:27 PM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/* INCLUDS */

#include "../../MCAL/STD/mcal_std_types.h"
#include "pic18f4620.h"
#include "mcal_interrupt_gen_cfg.h"
#include "../GPIO/mcal_gpio.h"

/* MACRO DECLARATIONS */

#define INTERRUPT_ENABLE           1
#define INTERRUPT_DISABLE          0

#define INTERRUPT_OCCUR            1
#define INTERRUPT_NOT_OCCUR        0

#define INTERRUPT_PRIORITY_ENABLE  1
#define INTERRUPT_PRIORITY_DISABLE 0

/* MACRO FUNTIONS DECLARATIONS */

#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_ENABLE_FEATURE

#define INTERRUPT_InterruptPriorityEnable()    (RCONbits.IPEN = 1)
#define INTERRUPT_InterruptPriorityDisable()   (RCONbits.IPEN = 0)


#define INTERRUPT_globalInterruptEnableHigh()  (INTCONbits.GIEH = 1)
#define INTERRUPT_globalInterruptDisableHigh() (INTCONbits.GIEH = 0)

#define INTERRUPT_globalInterruptEnableLow()   (INTCONbits.GIEL = 1)
#define INTERRUPT_globalInterruptDisableLow()  (INTCONbits.GIEL = 0)

#else

#define INTERRUPT_globalInterruptEnable()       (INTCONbits.GIE = 1) 
#define INTERRUPT_globalInterruptDisable()      (INTCONbits.GIE = 0) 

#define INTERRUPT_PeripheralInterruptEnable()   (INTCONbits.PEIE = 1) 
#define INTERRUPT_PeripheralInterruptDisable()  (INTCONbits.PEIE = 0) 

#endif

/* DATA TYPE DECLARATIONS (ENUMS,UNIONS,STRUCTS) */

typedef enum{
    INTERRUPT_LOW_PRIORITY = 0,
    INTERRUPT_HIGH_PRIORITY        
}interrupt_priority_cfg;

/* FUNTIONS DECLARATIONS */

#endif	/* MCAL_INTERRUPT_CONFIG_H */

