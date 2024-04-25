/* 
 * File:   mcal_gpio.c
 * Author: mahmoud_saleh
 *
 * Created on April 22, 2024, 12:03 AM
 */

/***** INCLUDS  ******/

#include "mcal_gpio.h"


volatile uint8 *tris_registers[] = {&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
volatile uint8 *port_registers[] = {&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};
volatile uint8 *lat_registers [] = {&LATA ,&LATB ,&LATC ,&LATD ,&LATE};

Std_ReturnType gpio_pin_direction_initialization      (const pin_config_t *_pin){
    Std_ReturnType ret = E_OK ;
    if ((NULL == _pin) || (_pin->pin > (MAX_NUMBER_OF_BINS-1))){
        ret = E_NOT_OK;
    }
    else{
        switch(_pin->direction){
            case OUTPUT_T :
                CLEAR_BIT((*tris_registers[_pin->port]),_pin->pin);
                break;
            case INPUT_T :
                SET_BIT((*tris_registers[_pin->port]),_pin->pin);
                break;
            default: ret = E_NOT_OK;
        } 
    }
    return ret;
}

Std_ReturnType gpio_pin_get_direction_status     (const pin_config_t *_pin , direction_t *direction){
    Std_ReturnType ret = E_OK ;
    if ((NULL == _pin) || (NULL == direction) || (_pin->pin > (MAX_NUMBER_OF_BINS-1))){
        ret = E_NOT_OK;
    }
    else{
        *direction = BIT_READ((*tris_registers[_pin->port]),_pin->pin);
    }
    
    return ret;
}

Std_ReturnType gpio_pin_write_logic              (const pin_config_t *_pin , logic_t  logic){
    Std_ReturnType ret = E_OK ;
    if ((NULL == _pin) || (_pin->pin > (MAX_NUMBER_OF_BINS-1))){
        ret = E_NOT_OK;
    }
    else{
        switch(logic){
            case LOW_T :
                CLEAR_BIT((*lat_registers[_pin->port]),_pin->pin);
                break;
            case HIGH_T :
                SET_BIT((*lat_registers[_pin->port]),_pin->pin);
                break;
            default: ret = E_NOT_OK;
        } 
    }
    return ret; 
}

Std_ReturnType gpio_pin_read_logic               (const pin_config_t *_pin , logic_t *logic){
    Std_ReturnType ret = E_OK ;
    if ((NULL == _pin) || (NULL == logic) || (_pin->pin > (MAX_NUMBER_OF_BINS-1))){
        ret = E_NOT_OK;
    }
    else{
        *logic = BIT_READ((*port_registers[_pin->port]),_pin->pin);
    }
    
    return ret;
}

Std_ReturnType gpio_pin_toggle_logic             (const pin_config_t *_pin){
    Std_ReturnType ret = E_OK ;
    if ((NULL == _pin) || (_pin->pin > (MAX_NUMBER_OF_BINS-1))){
        ret = E_NOT_OK;
    }
    else{
        TOGGLE_BIT((*lat_registers[_pin->port]),_pin->pin);
    }
    return ret;

}

Std_ReturnType gpio_pin_initialization           (const pin_config_t *_pin){
    Std_ReturnType ret = E_OK;
    if(NULL == _pin || _pin->pin > MAX_NUMBER_OF_BINS-1){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_initialization(_pin);
        ret = gpio_pin_write_logic             (_pin, _pin->logic);
    }
    return ret;
}

Std_ReturnType gpio_port_direction_initialization      (port_index_t _port , uint8 direction){
    Std_ReturnType ret = E_OK ;
    if ((_port > (MAX_NUMBER_OF_PORTS-1))){
        ret = E_NOT_OK;
    }
    else{
        *tris_registers[_port] = direction; 
    }
    return ret;
}

Std_ReturnType gpio_port_get_direction_status          (port_index_t _port , uint8 *direction){
    Std_ReturnType ret = E_OK ;
    if ((_port > (MAX_NUMBER_OF_PORTS-1)) || (NULL == direction)){
        ret = E_NOT_OK;
    }
    else{
        *direction = *tris_registers[_port];
    }
    return ret;
}

Std_ReturnType gpio_port_write_logic                   (port_index_t _port , uint8 logic){
    Std_ReturnType ret = E_OK ;
    if ((_port > (MAX_NUMBER_OF_PORTS-1))){
        ret = E_NOT_OK;
    }
    else{
        *lat_registers[_port] = logic;
    } 
    return ret;
}

Std_ReturnType gpio_port_read_logic                    (port_index_t _port , uint8 *logic){
    Std_ReturnType ret = E_OK ;
    if ((_port > (MAX_NUMBER_OF_PORTS-1)) || (NULL == logic)){
        ret = E_NOT_OK;
    }
    else{
        *logic = *lat_registers[_port];
    }
    return ret;
}

Std_ReturnType gpio_port_toggle_logic                  (port_index_t _port){
    Std_ReturnType ret = E_OK ;
    if ((_port > (MAX_NUMBER_OF_PORTS-1))){
        ret = E_NOT_OK;
    }
    else{
        *lat_registers [_port] ^= 0xFF;
    }
    return ret;
}





