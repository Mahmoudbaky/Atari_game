/* 
 * File:   app.c
 * Author: mahmoud_saleh
 *
 * Created on April 23, 2024, 2:01 AM
 */

#include "app.h"


/***********  functions declarations  *************/

void obj_init(void);

Std_ReturnType move_ball_left_to_right(uint8 flag);
Std_ReturnType move_ball_right_to_left(uint8 flag);

Std_ReturnType The_Game(button_p *left_btn ,button_p *right_btn);
//void loser_detector(void);

void left_btn_bush_ball(void);
void right_btn_bush_ball(void);


/***********  objects  ************/

chr_lcd_4bit_t lcd = {
    .lcd_en.port      = PORTD_T,
    .lcd_en.pin       = PIN_0,
    .lcd_en.direction = OUTPUT_T,
    .lcd_en.logic     = LOW_T,
    
    .lcd_rs.port      = PORTD_T,
    .lcd_rs.pin       = PIN_1,
    .lcd_rs.direction = OUTPUT_T,
    .lcd_rs.logic     = LOW_T,
    
    .lcd_data[0].port      = PORTC_T,
    .lcd_data[0].pin       = PIN_0,
    .lcd_data[0].direction = OUTPUT_T,
    .lcd_data[0].logic     = LOW_T,
    
    .lcd_data[1].port      = PORTC_T,
    .lcd_data[1].pin       = PIN_1,
    .lcd_data[1].direction = OUTPUT_T,
    .lcd_data[1].logic     = LOW_T,
    
    .lcd_data[2].port      = PORTC_T,
    .lcd_data[2].pin       = PIN_2,
    .lcd_data[2].direction = OUTPUT_T,
    .lcd_data[2].logic     = LOW_T,
    
    .lcd_data[3].port      = PORTC_T,
    .lcd_data[3].pin       = PIN_3,
    .lcd_data[3].direction = OUTPUT_T,
    .lcd_data[3].logic     = LOW_T
   
};

button_p left_btn = {
    .button_connection = BUTTON_ACTIVE_HIGH,
    .button_state      = BUTTON_RELEASED,
    
    .button_pin.port      = PORTC_T,
    .button_pin.pin       = PIN_4,
    .button_pin.direction = INPUT_T,
    .button_pin.logic     = LOW_T
};

button_p right_btn = {
    .button_connection = BUTTON_ACTIVE_HIGH,
    .button_state      = BUTTON_RELEASED,
    
    .button_pin.port      = PORTC_T,
    .button_pin.pin       = PIN_5,
    .button_pin.direction = INPUT_T,
    .button_pin.logic     = LOW_T
};


timer1_config_t TIMER = {
    .preloaded_value = 3036,
    .prescaler       = TIMER1_PRESCALER_8,
    .clock_source    = TIMER1_INTERNAL_CLOCK,
    .read_write_mode = TIMER1_8BIT_READ_WRITE,
    .timer1_osc_en   = TIMER1_OSC_DISABLE
    //.timer1_callback = loser_detector
};



/*************** variables *****************/
const uint8 person_on_left[]  = {0x07, 0x04, 0x0E, 0x1F, 0x0E, 0x11, 0x11, 0x11};
const uint8 person_on_right[] = {0x1C, 0x04, 0x0E, 0x1F, 0x0E, 0x11, 0x11, 0x11};
const uint8 ball[]            = {0x00, 0x00, 0x04, 0x0E, 0x0E, 0x04, 0x00, 0x00};
uint8 start_messeage[14]        = "start the game";

        
uint8 *left_btn_click  = NULL;
uint8 *right_btn_click = NULL;


uint8 flag1 = 1;
uint8 flag2 = 1;
uint8 flag3 = E_NOT_OK;
uint8 flag4 = E_NOT_OK;
uint8 flag5 = 1;

Std_ReturnType ret = E_NOT_OK;


int main(){
    
    obj_init();
    
    ret = lcd_4bit_send_custom_char(&lcd, 2 , 2  , person_on_left  , 0);
    ret = lcd_4bit_send_custom_char(&lcd, 2 , 19 , person_on_right , 1);
    
    
    
    while(1){
        ret = The_Game(&left_btn,&right_btn);
    }
    
    
    return(EXIT_SUCCESS);
}


void obj_init(void){
    Std_ReturnType ret = E_NOT_OK;
    ret = lcd_4bit_intialize(&lcd);
    ret = button_initialize(&left_btn);
    ret = button_initialize(&right_btn);
    ret = timer1_Init(&TIMER);
}

Std_ReturnType move_ball_left_to_right(uint8 flag){
    
    if(flag == 1){
    for (uint8 i = 3 ; i <= 18 ; i ++){
        ret = lcd_4bit_send_custom_char(&lcd, 2 , i , ball , 3);
        __delay_ms(100);
        if (i < 18){
            ret = lcd_4bit_send_char_data_pos(&lcd, 2 , i , ' ');
        }
        else { /*nothing*/ }
        }
    }
    else{ /*nothing*/ }
    
    ret = E_OK;
}

Std_ReturnType move_ball_right_to_left(uint8 flag){
    
    if (flag == 1){
        for (uint8 i = 18 ; i >= 3 ; i --){
        ret = lcd_4bit_send_custom_char(&lcd, 2 , i , ball , 3);
        __delay_ms(100);
        if (i > 3){
            ret = lcd_4bit_send_char_data_pos(&lcd, 2 , i , ' ');
        }
        else { /*nothing*/ }
        }
    }
    else{ /*nothing*/ }
    
    ret = E_OK;
}


Std_ReturnType The_Game(button_p *left_btn ,button_p *right_btn){
    button_state_p left_click  = BUTTON_RELEASED ;
    button_state_p right_click = BUTTON_RELEASED ;
    Std_ReturnType ret = E_OK;
    
    
    
    if((left_btn ==  NULL) || (right_btn == NULL)){
        ret = E_NOT_OK;
    }
    else{
        if(flag5 == 1){ lcd_4bit_send_string_pos(&lcd,1,4,start_messeage); }
        
        button_read_state(left_btn,&left_click);
        button_read_state(right_btn,&right_click);
        
        if(left_click == BUTTON_PRESSED){
            lcd_4bit_send_string_pos(&lcd,1,4,"              ");
            flag5 = 0;
            flag3 = move_ball_left_to_right(flag1);
            if((flag3 == E_OK) && (flag1 == 1)){
                flag1  = 0;
                flag2  = 1;
            }
            
        }
        else if(right_click == BUTTON_PRESSED){
            lcd_4bit_send_string_pos(&lcd,1,4,"              ");
            flag5 = 0;
            flag4 = move_ball_right_to_left(flag2);
            if(flag4 == E_OK && flag2 == 1){
                flag2 = 0;
                flag1 = 1;
            }
            
        }
    }
}




// void left_btn_bush_ball(void){}

// void right_btn_bush_ball(void){}