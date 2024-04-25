/* 
 * File:   ecu_lcd.c
 * Author: houda
 *
 * Created on February 18, 2024, 4:39 PM
 * to generate custom character : https://maxpromer.github.io/LCD-Character-Creator/
 */

#include "ecu_lcd.h"


static Std_ReturnType lcd_send_4bits             (const chr_lcd_4bit_t *lcd,  uint8 data_command);
static Std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd);
static Std_ReturnType lcd_4bit_set_cursor        (const chr_lcd_4bit_t *lcd ,uint8 row, uint8 column);
static Std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd);
static Std_ReturnType lcd_8bit_set_cursor        (const chr_lcd_8bit_t *lcd ,uint8 row, uint8 column);


// 4bit LCD:
Std_ReturnType lcd_4bit_intialize         (const chr_lcd_4bit_t *lcd){
    Std_ReturnType ret = E_OK;
    uint8 counter = 0;
    if (NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_initialization(&(lcd->lcd_rs));
        ret = gpio_pin_initialization(&(lcd->lcd_en));
        for(counter = 0 ; counter < 4 ; counter++){
            ret = gpio_pin_initialization(&(lcd->lcd_data[counter]));
        }
        __delay_ms(20);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        
        ret = lcd_4bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_4bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_4bit_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
        ret = lcd_4bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command(lcd, 0x80);   
    }
    return ret;
}
Std_ReturnType lcd_4bit_send_command      (const chr_lcd_4bit_t *lcd, uint8 command){
    Std_ReturnType ret = E_OK;
    uint8 counter = 0;
    if (NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), LOW_T);
        ret = lcd_send_4bits(lcd ,(command>>4));
        ret = lcd_4bit_send_enable_signal(lcd);
        ret = lcd_send_4bits(lcd ,(command));
        ret = lcd_4bit_send_enable_signal(lcd);
    }
    return ret;  
}
Std_ReturnType lcd_4bit_send_char_data    (const chr_lcd_4bit_t *lcd, uint8 data){
    Std_ReturnType ret = E_OK;
    uint8 counter = 0;
    if (NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), HIGH_T);
        ret = lcd_send_4bits(lcd ,(data>>4));
        ret = lcd_4bit_send_enable_signal(lcd);
        ret = lcd_send_4bits(lcd ,(data));
        ret = lcd_4bit_send_enable_signal(lcd);
    }
    return ret;
}
Std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd,uint8 row, uint8 column, uint8 data){
    Std_ReturnType ret = E_OK;
    column--;
     if (NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
       ret = lcd_4bit_set_cursor(lcd,row,column);
       ret = lcd_4bit_send_char_data(lcd,data);
    }
    return ret;
}
Std_ReturnType lcd_4bit_send_string       (const chr_lcd_4bit_t *lcd, uint8 *str){
    Std_ReturnType ret = E_OK;
    uint8 counter = 0;
     if (NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
       ret = gpio_pin_write_logic(&(lcd->lcd_rs), HIGH_T);
       while(*str){
           ret = lcd_4bit_send_char_data(lcd,*str++);
       }
    }
    return ret;
}
Std_ReturnType lcd_4bit_send_string_pos   (const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str){
    Std_ReturnType ret = E_OK;
    column--;
     if (NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
       ret = lcd_4bit_set_cursor (lcd,row,column);
       ret = lcd_4bit_send_string(lcd,str);
    }
    return ret;
}
Std_ReturnType lcd_4bit_send_custom_char  (const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, 
                                           const uint8 _chr[], uint8 mem_pos){
    Std_ReturnType ret = E_OK;
    uint8 lcd_counter = ZERO_INIT;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{    
        ret = lcd_4bit_send_command(lcd, (_LCD_CGRAM_START+(mem_pos*8)));
        for(lcd_counter=0; lcd_counter<=7; ++lcd_counter){
            ret = lcd_4bit_send_char_data(lcd, _chr[lcd_counter]);
        }
        ret = lcd_4bit_send_char_data_pos(lcd, row, column, mem_pos);
    }
    return ret;
}

// 8bit LCD:

Std_ReturnType lcd_8bit_intialize         (const chr_lcd_8bit_t *lcd){
    Std_ReturnType ret = E_OK;
    uint8 counter = 0;
    if (NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_initialization(&(lcd->lcd_rs));
        ret = gpio_pin_initialization(&(lcd->lcd_en));
        for(counter = 0 ; counter < 8 ; counter++){
            ret = gpio_pin_initialization(&(lcd->lcd_data[counter]));
        }
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        
        ret = lcd_8bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_8bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_8bit_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
        ret = lcd_8bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_command(lcd, 0x80);
    }
    return ret;
}
Std_ReturnType lcd_8bit_send_command      (const chr_lcd_8bit_t *lcd, uint8 command){
    Std_ReturnType ret = E_OK;
    uint8 counter = 0;
     if (NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
       ret = gpio_pin_write_logic(&(lcd->lcd_rs), LOW_T);
       for(counter = 0; counter < 8 ; counter++){
           ret = gpio_pin_write_logic(&(lcd->lcd_data[counter]), (command >> counter) & BIT_MASK);
       }
       ret = lcd_8bit_send_enable_signal(lcd);
    }
    return ret;
}
Std_ReturnType lcd_8bit_send_char_data    (const chr_lcd_8bit_t *lcd, uint8 data){
    Std_ReturnType ret = E_OK;
    uint8 counter = 0;
     if (NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
       ret = gpio_pin_write_logic(&(lcd->lcd_rs), HIGH_T);
       for(counter = 0; counter < 8 ; counter++){
           ret = gpio_pin_write_logic(&(lcd->lcd_data[counter]), (data >> counter) & BIT_MASK);
       }
       ret = lcd_8bit_send_enable_signal(lcd);
    }
    return ret;
}
Std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd,uint8 row, uint8 column, uint8 data){
    Std_ReturnType ret = E_OK;
    column--;
     if (NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
       ret = lcd_8bit_set_cursor(lcd,row,column);
       ret = lcd_8bit_send_char_data(lcd,data);
    }
    return ret;
}
Std_ReturnType lcd_8bit_send_string       (const chr_lcd_8bit_t *lcd, uint8 *str){
    Std_ReturnType ret = E_OK;
    uint8 counter = 0;
     if (NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
       ret = gpio_pin_write_logic(&(lcd->lcd_rs), HIGH_T);
       while(*str){
           ret = lcd_8bit_send_char_data(lcd,*str++);
       }
    }
    return ret;
}
Std_ReturnType lcd_8bit_send_string_pos   (const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str){
    Std_ReturnType ret = E_OK;
    column--;
     if (NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
       ret = lcd_8bit_set_cursor (lcd,row,column);
       ret = lcd_8bit_send_string(lcd,str);
    }
    return ret;
}
Std_ReturnType lcd_8bit_send_custom_char  (const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, 
                                           const uint8 _chr[], uint8 mem_pos){
    Std_ReturnType ret = E_OK;
    uint8 lcd_counter = ZERO_INIT;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{    
        ret = lcd_8bit_send_command(lcd, (_LCD_CGRAM_START+(mem_pos*8)));
        for(lcd_counter=0; lcd_counter<=7; ++lcd_counter){
            ret = lcd_8bit_send_char_data(lcd, _chr[lcd_counter]);
        }
        ret = lcd_8bit_send_char_data_pos(lcd, row, column, mem_pos);
    }
    return ret;
}

//string:

Std_ReturnType convert_uint8_to_string (uint8 value,  uint8 *str){
    Std_ReturnType ret = E_OK;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{    
        memset((char *)str, '\0', 4);
        sprintf(str, "%i", value);
    }
    return ret;
}
Std_ReturnType convert_uint16_to_string(uint16 value, uint8 *str){
    Std_ReturnType ret = E_OK;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{    
        memset((char *)str, '\0', 6);
        sprintf(str, "%i", value);
    }
    return ret;
}
Std_ReturnType convert_uint32_to_string(uint32 value, uint8 *str){
    Std_ReturnType ret = E_OK;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{    
        memset((char *)str, '\0', 11);
        sprintf(str, "%i", value);
    }
    return ret;
}


// helper functions:
static Std_ReturnType lcd_send_4bits             (const chr_lcd_4bit_t *lcd,  uint8 data_command){
    Std_ReturnType ret = E_OK;
    ret = gpio_pin_write_logic(&(lcd->lcd_data[0]), (data_command >> 0) & BIT_MASK);
    ret = gpio_pin_write_logic(&(lcd->lcd_data[1]), (data_command >> 1) & BIT_MASK);
    ret = gpio_pin_write_logic(&(lcd->lcd_data[2]), (data_command >> 2) & BIT_MASK);
    ret = gpio_pin_write_logic(&(lcd->lcd_data[3]), (data_command >> 3) & BIT_MASK);
    return ret;
}
static Std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd){
    Std_ReturnType ret = E_OK;
    ret = gpio_pin_write_logic(&(lcd->lcd_en), HIGH_T);
    __delay_us(5);
    ret = gpio_pin_write_logic(&(lcd->lcd_en), LOW_T);
    return ret;
}
static Std_ReturnType lcd_4bit_set_cursor        (const chr_lcd_4bit_t *lcd ,uint8 row, uint8 column){
    Std_ReturnType ret = E_OK;
    switch (row){
    case ROW1 : ret = lcd_4bit_send_command(lcd, (0x80+column));break;
    case ROW2 : ret = lcd_4bit_send_command(lcd, (0xc0+column));break;
    case ROW3 : ret = lcd_4bit_send_command(lcd, (0x94+column));break;
    case ROW4 : ret = lcd_4bit_send_command(lcd, (0xd4+column));break;
    default: /* do nothing */;
    }
    return ret;
}
static Std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd){
    Std_ReturnType ret = E_OK;
    ret = gpio_pin_write_logic(&(lcd->lcd_en), HIGH_T);
    __delay_us(5);
    ret = gpio_pin_write_logic(&(lcd->lcd_en), LOW_T);
    return ret;
}
static Std_ReturnType lcd_8bit_set_cursor        (const chr_lcd_8bit_t *lcd ,uint8 row, uint8 column){
    Std_ReturnType ret = E_OK;
    switch (row){
    case ROW1 : ret = lcd_8bit_send_command(lcd, (0x80+column));break;
    case ROW2 : ret = lcd_8bit_send_command(lcd, (0xc0+column));break;
    case ROW3 : ret = lcd_8bit_send_command(lcd, (0x94+column));break;
    case ROW4 : ret = lcd_8bit_send_command(lcd, (0xd4+column));break;
    default: /* do nothing */;
    }
    return ret;
}
