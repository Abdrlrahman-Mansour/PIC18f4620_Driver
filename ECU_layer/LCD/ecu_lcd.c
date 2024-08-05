/* 
 * File:   ecu_lcd.c
 * Author: laphouse
 *
 * Created on July 3, 2024, 9:35 AM
 */
#include "ecu_lcd.h"

static Std_ReturnType lcd_send_4bits(const lcd_4bit_t *lcd , uint8 command);
static Std_ReturnType lcd_4bit_send_enable(const lcd_4bit_t *lcd );
static Std_ReturnType lcd_8bit_send_enable(const lcd_8bit_t *lcd );
static Std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t *lcd ,uint8 row , uint8 column );
static Std_ReturnType lcd_4bit_set_cursor(const lcd_4bit_t *lcd ,uint8 row , uint8 column );
/**
 * 
 * @param lcd
 * @return 
 */
Std_ReturnType lcd_4bit_init(const lcd_4bit_t *lcd){
    Std_ReturnType ret = E_OK ;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
      ret=  gpio_pin_direction_init(&(lcd->lcd_rs));
      ret=  gpio_pin_write_logic(&(lcd->lcd_rs),lcd->lcd_rs.logic);
      ret= gpio_pin_direction_init(&(lcd->lcd_en));
      ret=  gpio_pin_write_logic(&(lcd->lcd_en),lcd->lcd_en.logic);
      ret=  gpio_pin_direction_init(&(lcd->lcd_data[0]));
      ret=  gpio_pin_direction_init(&(lcd->lcd_data[1]));
      ret=  gpio_pin_direction_init(&(lcd->lcd_data[2]));
      ret=  gpio_pin_direction_init(&(lcd->lcd_data[3]));
      ret=  gpio_pin_write_logic(&(lcd->lcd_data[0]),lcd->lcd_data[0].logic);
      ret=  gpio_pin_write_logic(&(lcd->lcd_data[1]),lcd->lcd_data[1].logic);
      ret=  gpio_pin_write_logic(&(lcd->lcd_data[2]),lcd->lcd_data[2].logic);
      ret=  gpio_pin_write_logic(&(lcd->lcd_data[3]),lcd->lcd_data[3].logic);
      
     __delay_ms(20);
      ret = lcd_4bit_send_command(lcd,LCD_8BIT_MODE_2_LINE);
      __delay_ms(5);
      ret = lcd_4bit_send_command(lcd,LCD_8BIT_MODE_2_LINE);
       __delay_us(150);
      ret = lcd_4bit_send_command(lcd,LCD_8BIT_MODE_2_LINE);
      ret = lcd_4bit_send_command(lcd,LCD_CLEAR);
      ret = lcd_4bit_send_command(lcd,LCD_RETURN_HOME);
      ret = lcd_4bit_send_command(lcd,LCD_ENTRY_MODE_INC_SHIFT_OFF);
      ret = lcd_4bit_send_command(lcd,LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
      ret = lcd_4bit_send_command(lcd,LCD_4BIT_MODE_2_LINE);
      ret = lcd_4bit_send_command(lcd,_LCD_DDRAM_START);
      
    }
    return ret ;
}
/**
 * 
 * @param lcd
 * @param command
 * @return 
 */
Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t *lcd,uint8 command){
    Std_ReturnType ret = E_OK ;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),LOW);
        ret = lcd_send_4bits(lcd,(command >> 4 ));
        ret = lcd_4bit_send_enable(lcd);
        ret = lcd_send_4bits(lcd,command);
        ret = lcd_4bit_send_enable(lcd);
    }
    return ret ;
}
/**
 * 
 * @param lcd
 * @param data
 * @return 
 */
Std_ReturnType lcd_4bit_send_char_data(const lcd_4bit_t *lcd,uint8 data){
    Std_ReturnType ret = E_OK ;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),HIGH);
        ret = lcd_send_4bits(lcd,(data >> 4 ));
        ret = lcd_4bit_send_enable(lcd);
        ret = lcd_send_4bits(lcd,data);
        ret = lcd_4bit_send_enable(lcd);
    }
    return ret ;
}
/**
 * 
 * @param lcd
 * @param row
 * @param col
 * @param data
 * @return 
 */
Std_ReturnType lcd_4bit_send_char_data_pos(const lcd_4bit_t *lcd,uint8 row,uint8 col,uint8 data){
    Std_ReturnType ret = E_OK ;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_4bit_set_cursor(lcd,row,col);
        ret = lcd_4bit_send_char_data(lcd ,data);
    }
    return ret ;
}
/**
 * 
 * @param lcd
 * @param str
 * @return 
 */
Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t *lcd,uint8 *str){
    Std_ReturnType ret = E_OK ;
    if((NULL == lcd) || (NULL == str)){
        ret = E_NOT_OK;
    }
    else{
        while(*str){
            ret = lcd_4bit_send_char_data(lcd, *str);
            *str++;
        }
    }
    return ret ;
}
/**
 * 
 * @param lcd
 * @param row
 * @param col
 * @param str
 * @return 
 */
Std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t *lcd,uint8 row,uint8 col,uint8 *str){
    Std_ReturnType ret = E_OK ;
    if((NULL == lcd) || (NULL == str)){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_4bit_set_cursor(lcd , row , col);
        ret = lcd_4bit_send_string(lcd , str);
    }
    return ret ;
}
/**
 * 
 * @param lcd
 * @param row
 * @param col
 * @param _char
 * @param mem_pos
 * @return 
 */
Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t *lcd,uint8 row,uint8 col ,const uint8 _char[],uint8 mem_pos){
    Std_ReturnType ret = E_OK ;
    uint8 count = 0;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
         ret = lcd_4bit_send_command(lcd,(_LCD_CGRAM_START+(mem_pos*8)));
        for(count = 0 ; count < 8; count++){
            ret = lcd_4bit_send_char_data(lcd,_char[count]);
        }
        ret = lcd_4bit_send_char_data_pos(lcd,row,col,mem_pos);
    }
    return ret ;
}









/**
 * 
 * @param lcd
 * @return 
 */
Std_ReturnType lcd_8bit_init(const lcd_8bit_t *lcd){
    Std_ReturnType ret = E_OK ;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
      ret=  gpio_pin_direction_init(&(lcd->lcd_rs));
      ret=  gpio_pin_write_logic(&(lcd->lcd_rs),lcd->lcd_rs.logic);
      ret= gpio_pin_direction_init(&(lcd->lcd_en));
      ret=  gpio_pin_write_logic(&(lcd->lcd_en),lcd->lcd_en.logic);
      ret=  gpio_pin_direction_init(&(lcd->lcd_data[0]));
      ret=  gpio_pin_direction_init(&(lcd->lcd_data[1]));
      ret=  gpio_pin_direction_init(&(lcd->lcd_data[2]));
      ret=  gpio_pin_direction_init(&(lcd->lcd_data[3]));
      ret=  gpio_pin_direction_init(&(lcd->lcd_data[4]));
      ret=  gpio_pin_direction_init(&(lcd->lcd_data[5]));
      ret=  gpio_pin_direction_init(&(lcd->lcd_data[6]));
      ret=  gpio_pin_direction_init(&(lcd->lcd_data[7]));
      ret=  gpio_pin_write_logic(&(lcd->lcd_data[0]),lcd->lcd_data[0].logic);
      ret=  gpio_pin_write_logic(&(lcd->lcd_data[1]),lcd->lcd_data[1].logic);
      ret=  gpio_pin_write_logic(&(lcd->lcd_data[2]),lcd->lcd_data[2].logic);
      ret=  gpio_pin_write_logic(&(lcd->lcd_data[3]),lcd->lcd_data[3].logic);
      ret=  gpio_pin_write_logic(&(lcd->lcd_data[4]),lcd->lcd_data[4].logic);
      ret=  gpio_pin_write_logic(&(lcd->lcd_data[5]),lcd->lcd_data[5].logic);
      ret=  gpio_pin_write_logic(&(lcd->lcd_data[6]),lcd->lcd_data[6].logic);
      ret=  gpio_pin_write_logic(&(lcd->lcd_data[7]),lcd->lcd_data[7].logic);
      
      __delay_ms(20);
      ret = lcd_8bit_send_command(lcd,LCD_8BIT_MODE_2_LINE);
      __delay_ms(5);
      ret = lcd_8bit_send_command(lcd,LCD_8BIT_MODE_2_LINE);
       __delay_us(150);
      ret = lcd_8bit_send_command(lcd,LCD_8BIT_MODE_2_LINE);
      ret = lcd_8bit_send_command(lcd,LCD_CLEAR);
      ret = lcd_8bit_send_command(lcd,LCD_RETURN_HOME);
      ret = lcd_8bit_send_command(lcd,LCD_ENTRY_MODE_INC_SHIFT_OFF);
      ret = lcd_8bit_send_command(lcd,LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
      ret = lcd_8bit_send_command(lcd,LCD_8BIT_MODE_2_LINE);
      ret = lcd_8bit_send_command(lcd,_LCD_DDRAM_START);

    }
    return ret ;
}
/**
 * 
 * @param lcd
 * @param command
 * @return 
 */
Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t *lcd, uint8 command){
    Std_ReturnType ret = E_OK ;
    uint8 count=0;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),LOW);
        for(count =0 ; count < 8 ; count ++){
            gpio_pin_write_logic(&(lcd->lcd_data[count]) , (command >> count) & (uint8)0x01);
        }
        ret = lcd_8bit_send_enable(lcd);
    }
    return ret ;
}
/**
 * 
 * @param lcd
 * @param data
 * @return 
 */
Std_ReturnType lcd_8bit_send_char_data(const lcd_8bit_t *lcd,uint8 data){
    Std_ReturnType ret = E_OK ;
    uint8 count =0;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),HIGH);
        for(count =0 ; count < 8 ; count ++){
            gpio_pin_write_logic(&(lcd->lcd_data[count]) , (data >> count) & (uint8)0x01);
        }
        ret = lcd_8bit_send_enable(lcd);
    }
    return ret ;
}
/**
 * 
 * @param lcd
 * @param row
 * @param col
 * @param data
 * @return 
 */
Std_ReturnType lcd_8bit_send_char_data_pos(const lcd_8bit_t *lcd,uint8 row,uint8 col,uint8 data){
    Std_ReturnType ret = E_OK ;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_8bit_set_cursor(lcd ,row , col);
        ret = lcd_8bit_send_char_data(lcd , data);
    }
    return ret ;
}
/**
 * 
 * @param lcd
 * @param str
 * @return 
 */
Std_ReturnType lcd_8bit_send_string(const lcd_8bit_t *lcd,uint8 *str){
    Std_ReturnType ret = E_OK ;
    if((NULL == lcd) || (NULL == str)){
        ret = E_NOT_OK;
    }
    else{
        while(*str){
            ret = lcd_8bit_send_char_data(lcd , *str);
            str++;
        }
    }
    return ret ;
}
/**
 * 
 * @param lcd
 * @param row
 * @param col
 * @param str
 * @return 
 */
Std_ReturnType lcd_8bit_send_string_pos(const lcd_8bit_t *lcd,uint8 row,uint8 col,uint8 *str){
    Std_ReturnType ret = E_OK ;
    if((NULL == lcd) || (NULL == str)){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_8bit_set_cursor(lcd, row ,col);  
        ret = lcd_8bit_send_string(lcd,str);
      
        
    }
    return ret ;
}
/**
 * 
 * @param lcd
 * @param row
 * @param col
 * @param _char
 * @param mem_pos
 * @return 
 */
Std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_t *lcd,uint8 row,uint8 col ,const uint8 _char[],uint8 mem_pos){
    Std_ReturnType ret = E_OK ;
    uint8 count =0;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_8bit_send_command(lcd,(_LCD_CGRAM_START+(mem_pos*8)));
        for(count = 0 ; count < 8; count++){
            ret = lcd_8bit_send_char_data(lcd,_char[count]);
        }
        ret = lcd_8bit_send_char_data_pos(lcd,row,col,mem_pos);
    }
    return ret ;
}
/**
 * 
 * @param value
 * @param str
 * @return 
 */
Std_ReturnType convert_byte_to_string(uint8 value, uint8 *str){
Std_ReturnType ret = E_OK ;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{
        memset(str ,'\0',4);
        sprintf(str,"%i",value);
    }
    return ret ;
}
/**
 * 
 * @param value
 * @param str
 * @return 
 */
Std_ReturnType convert_short_to_string(uint16 value, uint16 *str){
Std_ReturnType ret = E_OK ;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{
         memset(str ,'\0',6);
        sprintf(str,"%i",value);
    }
    return ret ;
}
/**
 * 
 * @param value
 * @param str
 * @return 
 */
Std_ReturnType convert_int_to_string(uint32 value, uint32 *str){
Std_ReturnType ret = E_OK ;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{
        memset(str ,'\0',12);
        sprintf(str,"%i",value);
    }
    return ret ;
}
/**
 * 
 * @param lcd
 */
static Std_ReturnType lcd_send_4bits(const lcd_4bit_t *lcd , uint8 command){
     Std_ReturnType ret = E_OK ;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_data[0]), (command >>0) & (uint8)0x01);
        ret = gpio_pin_write_logic(&(lcd->lcd_data[1]), (command >>1) & (uint8)0x01);
        ret = gpio_pin_write_logic(&(lcd->lcd_data[2]), (command >>2) & (uint8)0x01);
        ret = gpio_pin_write_logic(&(lcd->lcd_data[3]), (command >>3) & (uint8)0x01);
    }
    return ret ;
}
/**
 * 
 * @param lcd
 * @return 
 */
static Std_ReturnType lcd_4bit_send_enable(const lcd_4bit_t *lcd ){
     Std_ReturnType ret = E_OK ;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_en),HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en),LOW);
    }
    return ret ;
}
/**
 * 
 * @param lcd
 * @return 
 */
static Std_ReturnType lcd_8bit_send_enable(const lcd_8bit_t *lcd ){
     Std_ReturnType ret = E_OK ;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_en),HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en),LOW);
    }
    return ret ;
}
/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @return 
 */
static Std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t *lcd ,uint8 row , uint8 column ){
Std_ReturnType ret = E_OK ;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        column--;
        switch (row){
            case ROW1 : 
                ret = lcd_8bit_send_command(lcd , (0x80 + column));
                break ;
            case ROW2 : 
                ret = lcd_8bit_send_command(lcd , (0xC0 + column));
                break;
            case ROW3 :
                ret = lcd_8bit_send_command(lcd , (0x94 + column));
                break;
            case ROW4 : 
                ret = lcd_8bit_send_command(lcd , (0xD4 + column));
                break;
            default : break ;
                
        }
    }
    return ret ;

}
/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @return 
 */
static Std_ReturnType lcd_4bit_set_cursor(const lcd_4bit_t *lcd ,uint8 row , uint8 column ){
Std_ReturnType ret = E_OK ;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        column--;
        switch (row){
            case ROW1 : 
                ret = lcd_4bit_send_command(lcd , (0x80 + column));
                break ;
            case ROW2 : 
                ret = lcd_4bit_send_command(lcd , (0xC0 + column));
                break;
            case ROW3 :
                ret = lcd_4bit_send_command(lcd , (0x94 + column));
                break;
            case ROW4 : 
                ret = lcd_4bit_send_command(lcd , (0xD4 + column));
                break;
            default : break ;
                
        }
    }
    return ret ;

}