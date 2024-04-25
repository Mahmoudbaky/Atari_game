/* 
 * File:   ecu_button.h
 * Author: houda
 *
 * Created on February 21, 2024, 10:52 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/* INCLUDS */

#include "ecu_button_cfg.h"
#include "../../MCAL/GPIO/mcal_gpio.h"

/* MACRO DECLARATIONS */



/* MACRO FUNTIONS DECLARATIONS */

/* DATA TYPE DECLARATIONS (ENUMS,UNIONS,STRUCTS) */

typedef enum{
    BUTTON_PRESSED = 0,
    BUTTON_RELEASED
}button_state_p;

typedef enum{
    BUTTON_ACTIVE_HIGH,
    BUTTON_ACTIVE_LOW
}button_active_p;

typedef struct{
    pin_config_t button_pin;
    button_state_p button_state;
    button_active_p button_connection;
}button_p;

/* FUNTIONS DECLARATIONS */

Std_ReturnType button_initialize(const button_p *btn);
Std_ReturnType button_read_state(const button_p *btn, button_state_p *btn_state);


#endif	/* ECU_BUTTON_H */

