/* 
 * File:   ecu_keypad.c
 * Author: laphouse
 *
 * Created on July 2, 2024, 6:05 AM
 */
#include "ecu_keypad.h"

 const uint8 btn_values[keypad_rows][keypad_columns]={{'7','8','9','/'},
                                                            {'4','5','6','*'},
                                                            {'1','2','3','-'},
                                                            {'#','0','=','+'}};

/**
 * 
 * @param keypad_obj
 * @return 
 */
 Std_ReturnType keypad_init(const keypad_t *keypad_obj){
  Std_ReturnType ret = E_OK;
  uint8 r_counter=0 , c_counter=0;
  if(NULL == keypad_obj){
      ret = E_NOT_OK;
  }
  else {
      for(r_counter = 0 ; r_counter <keypad_rows ;r_counter++){
          ret = gpio_pin_direction_init(&(keypad_obj->keypad_r_pins[r_counter]));
          ret = gpio_pin_write_logic(&(keypad_obj->keypad_r_pins[r_counter]),keypad_obj->keypad_r_pins[r_counter].logic);
          
      }
      for(c_counter = 0 ; c_counter <keypad_columns ;c_counter++ ){
          ret = gpio_pin_direction_init(&(keypad_obj->keypad_c_pins[c_counter]));
      }
  }
  return ret;
 }
 /**
  * 
  * @param keypad_obj
  * @param value
  * @return 
  */
 Std_ReturnType keypad_get_value(const keypad_t *keypad_obj ,uint8 *value){
  Std_ReturnType ret = E_OK;
    uint8 r_counter=0 , c_counter=0, l_counter=0;
    uint8 col_logic=0;
  if((NULL == keypad_obj) || (NULL == value)){
      ret = E_NOT_OK;
  }
  else {
      for(r_counter = 0 ; r_counter <keypad_rows ;r_counter++){
          for(l_counter = 0 ;l_counter <keypad_rows ;l_counter++){
              ret = gpio_pin_write_logic(&(keypad_obj->keypad_r_pins[l_counter]),LOW);
          }
          ret = gpio_pin_write_logic(&(keypad_obj->keypad_r_pins[r_counter]),HIGH);
          
          for(c_counter = 0 ; c_counter <keypad_columns ;c_counter++){
              ret = gpio_pin_read_logic(&(keypad_obj->keypad_c_pins[c_counter]),&col_logic);
              if(HIGH == col_logic){
                  *value = btn_values[r_counter][c_counter];
              }
          }
      }
  }
  return ret;
 }


