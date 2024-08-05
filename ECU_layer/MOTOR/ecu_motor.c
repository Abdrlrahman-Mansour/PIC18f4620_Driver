/* 
 * File:   ecu_motor.h
 * Author: laphouse
 *
 * Created on June 30, 2024, 12:32 PM
 */
#include "ecu_motor.h"
/**
 * 
 * @param motor
 * @return 
 */
Std_ReturnType motor_init(const motor_t *motor){
Std_ReturnType ret = E_OK;
if(NULL == motor){
    ret = E_NOT_OK;
}
else {
    pin_config_t obj1 ={
    .port = motor->motor[0].motor_port,
    .pin = motor->motor[0].motor_pin,
    .direction=  GPIO_OUTPUT,
    .logic = motor->motor[0].motor_status, 
    };
    pin_config_t obj2={
    .port = motor->motor[1].motor_port,
    .pin = motor->motor[1].motor_pin,
    .direction=  GPIO_OUTPUT,
    .logic = motor->motor[1].motor_status,
    };
    gpio_pin_direction_init(&obj1);
    gpio_pin_write_logic(&obj1,obj1.logic);
    gpio_pin_direction_init(&obj2);
    gpio_pin_write_logic(&obj2,obj2.logic);
}
return ret;
}
/**
 * 
 * @param motor
 * @return 
 */
Std_ReturnType motor_move_right(const motor_t *motor){
Std_ReturnType ret = E_OK;
if(NULL == motor){
    ret = E_NOT_OK;
}
else {
    pin_config_t obj1 ={
    .port = motor->motor[0].motor_port,
    .pin = motor->motor[0].motor_pin,
    .direction=  GPIO_OUTPUT,
    .logic = motor->motor[0].motor_status, 
    };
    pin_config_t obj2={
    .port = motor->motor[1].motor_port,
    .pin = motor->motor[1].motor_pin,
    .direction=  GPIO_OUTPUT,
    .logic = motor->motor[1].motor_status,
    };
    gpio_pin_write_logic(&obj1,HIGH);
    gpio_pin_write_logic(&obj2,LOW);

}
return ret;
}
/**
 * 
 * @param motor
 * @return 
 */
Std_ReturnType motor_move_left(const motor_t *motor){
Std_ReturnType ret = E_OK;
if(NULL == motor){
    ret = E_NOT_OK;
}
else {
    pin_config_t obj1 ={
    .port = motor->motor[0].motor_port,
    .pin = motor->motor[0].motor_pin,
    .direction=  GPIO_OUTPUT,
    .logic = motor->motor[0].motor_status, 
    };
    pin_config_t obj2={
    .port = motor->motor[1].motor_port,
    .pin = motor->motor[1].motor_pin,
    .direction=  GPIO_OUTPUT,
    .logic = motor->motor[1].motor_status,
    };
    gpio_pin_write_logic(&obj1,LOW);
    gpio_pin_write_logic(&obj2,HIGH);
}
return ret;
}
/**
 * 
 * @param motor
 * @return 
 */
Std_ReturnType motor_stop(const motor_t *motor){
Std_ReturnType ret = E_OK;
if(NULL == motor){
    ret = E_NOT_OK;
}
else {
    pin_config_t obj1 ={
    .port = motor->motor[0].motor_port,
    .pin = motor->motor[0].motor_pin,
    .direction=  GPIO_OUTPUT,
    .logic = motor->motor[0].motor_status, 
    };
    pin_config_t obj2={
    .port = motor->motor[1].motor_port,
    .pin = motor->motor[1].motor_pin,
    .direction=  GPIO_OUTPUT,
    .logic = motor->motor[1].motor_status,
    };
    gpio_pin_write_logic(&obj1,LOW);
    gpio_pin_write_logic(&obj2,LOW);
}
return ret;
}
