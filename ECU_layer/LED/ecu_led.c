/* 
 * File:   application.c
 * Author: laphouse
 *
 * Created on June 27, 2024, 10:20 PM
 */
#include "ecu_led.h"
Std_ReturnType led_init(const led_t *led){
Std_ReturnType ret = E_OK;


if(NULL == led){
    ret =E_NOT_OK;
}
else{
 pin_config_t pin_obj={
    .port = led->port ,  
    .pin= led->pin , 
    .direction = GPIO_OUTPUT , 
    .logic = led->status};
     gpio_pin_direction_init(&pin_obj);
     gpio_pin_write_logic(&pin_obj,pin_obj.logic);
}
return  ret;
}
/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType led_turn_on(const led_t *led){
Std_ReturnType ret = E_OK;
if(NULL == led){
    ret =E_NOT_OK;
}
else{
    pin_config_t pin_obj={
    .port = led->port ,  
    .pin= led->pin , 
    .direction = GPIO_OUTPUT , 
    .logic = led->status};
    gpio_pin_write_logic(&pin_obj,HIGH);
}
return  ret;

}
/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType led_turn_off(const led_t *led){
Std_ReturnType ret = E_OK;
if(NULL == led){
    ret =E_NOT_OK;
}
else{
    pin_config_t pin_obj={
        .port = led->port ,  
        .pin= led->pin , 
        .direction = GPIO_OUTPUT , 
        .logic = led->status};
        gpio_pin_write_logic(&pin_obj,LOW);
    }
return  ret;

}
/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType led_toggle(const led_t *led){
Std_ReturnType ret = E_OK;
if(NULL == led){
    ret =E_NOT_OK;
}
else{
    pin_config_t pin_obj={
    .port = led->port ,  
    .pin= led->pin , 
    .direction = GPIO_OUTPUT , 
    .logic = led->status};
    gpio_pin_toggle_logic(&pin_obj);
}
return  ret;

}
/**
 * 
 * @param led
 * @return 
 */