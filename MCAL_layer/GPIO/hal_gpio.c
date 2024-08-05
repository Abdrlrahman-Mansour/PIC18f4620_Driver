/* 
 * File:   hal_gpio.c
 * Author: laphouse
 *
 * Created on June 27, 2024, 10:20 PM
 */
#include "hal_gpio.h"

uint8 volatile *tris_reg[]={&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
uint8 volatile *lat_reg[]={&LATA,&LATB,&LATC,&LATD,&LATE};   
uint8 volatile *port_reg[]={&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};



#if GPIO_PORT_PIN_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType gpio_pin_intialize(const pin_config_t *_pin_config){
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_init(_pin_config);
        ret = gpio_pin_write_logic(_pin_config, _pin_config->logic);
    }
    return ret;
}
#endif

#if PORT_PIN_CONFIG == ENABLE
Std_ReturnType  gpio_pin_direction_init(const pin_config_t  *_pin_config){
    Std_ReturnType ret = E_OK;
    
    if((NULL == _pin_config) || (_pin_config->pin > PORT_PIN_MAX_NUMBER -1)){
    ret = E_NOT_OK;
    
    }
    else{
     switch(_pin_config->direction){
        case GPIO_OUTPUT :
            CLR_BIT(*tris_reg[_pin_config->port], _pin_config->pin);
        break;
        case GPIO_INPUT :
            SET_BIT(*tris_reg[_pin_config->port],_pin_config->pin);
            break;
        default :  ret = E_NOT_OK;
    }
    
    }
   
    return ret;
}
#endif
/**
 * 
 * @param _pin_config
 * @param dic_status
 * @return 
 */
#if PORT_PIN_CONFIG == ENABLE
Std_ReturnType  gpio_pin_direction_status(const pin_config_t  *_pin_config ,direction_t *dic_status){
 Std_ReturnType ret = E_OK;
 if((NULL == _pin_config ) || (NULL == dic_status ) || (_pin_config->pin > PORT_PIN_MAX_NUMBER -1)){
     ret = E_NOT_OK;
 
 }
 else{
     *dic_status= READ_BIT(*tris_reg[_pin_config->port],_pin_config->pin);
 
 }

return ret;
}
#endif
/**
 * 
 * @param _pin_config
 * @param logic
 * @return 
 */
#if PORT_PIN_CONFIG == ENABLE
Std_ReturnType  gpio_pin_write_logic(const pin_config_t  *_pin_config, logic_t logic ){
Std_ReturnType ret = E_OK;
 if((NULL == _pin_config) || (_pin_config->pin > PORT_PIN_MAX_NUMBER -1)){
     ret = E_NOT_OK;
 
 }
 else{
     switch(logic){
         case LOW : 
             CLR_BIT(*lat_reg[_pin_config->port], _pin_config->pin);
             break;
         case HIGH :
              SET_BIT(*lat_reg[_pin_config->port], _pin_config->pin);
             break;
         
         default : ret = E_NOT_OK;
     
     }
 }


return ret;


}
#endif
/**
 * 
 * @param _pin_config
 * @param logic
 * @return 
 */
#if PORT_PIN_CONFIG == ENABLE
Std_ReturnType  gpio_pin_read_logic(const pin_config_t  *_pin_config, logic_t *logic ){
Std_ReturnType ret = E_OK;
 if((NULL == _pin_config) || (NULL == logic)|| (_pin_config->pin > PORT_PIN_MAX_NUMBER -1)){
     ret = E_NOT_OK;
 
 }
 else{
     *logic= READ_BIT(*port_reg[_pin_config->port],_pin_config->pin);
 
 }
return ret;

}
#endif
/**
 * 
 * @param _pin_config
 * @return 
 */
#if PORT_PIN_CONFIG == ENABLE
Std_ReturnType  gpio_pin_toggle_logic(const pin_config_t  *_pin_config){
Std_ReturnType ret = E_OK;
 if((NULL == _pin_config) || (_pin_config->pin > PORT_PIN_MAX_NUMBER -1)){
     ret = E_NOT_OK;
 
 }
 else{
     TOG_BIT(*lat_reg[_pin_config->port], _pin_config->pin);
 }
return ret;
}
#endif
/**
 * 
 * @param port
 * @return 
 */
#if PORT_CONFIG == ENABLE 
Std_ReturnType  gpio_port_direction_init(port_index_t  port,uint8 direction){
Std_ReturnType ret = E_OK;
if(port > PORT_MAX_NUMBER-1){
Std_ReturnType ret = E_NOT_OK;
}
else{
      *tris_reg[port] = direction;
}

return ret;
}
#endif
/**
 * 
 * @param port
 * @param direction_status
 * @return 
 */
#if PORT_CONFIG == ENABLE 
Std_ReturnType  gpio_port_direction_status(port_index_t  port, uint8 *direction_status){
Std_ReturnType ret = E_OK;
 if(NULL == direction_status || port > PORT_MAX_NUMBER-1){
     ret = E_NOT_OK;
    
 }
 else{
   *direction_status  =   *tris_reg[port];
 }
return ret;
}
#endif
/**
 * 
 * @param port
 * @param logic
 * @return 
 */
#if PORT_CONFIG == ENABLE 
Std_ReturnType  gpio_port_write_logic(port_index_t  port , uint8 logic){
Std_ReturnType ret = E_OK;
if(port > PORT_MAX_NUMBER-1){
Std_ReturnType ret = E_NOT_OK;
}
else{
      *lat_reg[port] = logic;
}
return ret;
}
#endif
/**
 * 
 * @param port
 * @param logic
 * @return 
 */
#if PORT_CONFIG == ENABLE 
Std_ReturnType  gpio_port_read_logic(port_index_t  port , uint8 *logic){
Std_ReturnType ret = E_OK;
if(NULL == logic || port > PORT_MAX_NUMBER-1){
     ret = E_NOT_OK;
 }
 else{
    *logic = *lat_reg[port];
 
 }
return ret;
}
#endif
/**
 * 
 * @param port
 * @param logic
 * @return 
 */
#if PORT_CONFIG == ENABLE 
Std_ReturnType  gpio_port_toggle_logic(port_index_t  port ){
Std_ReturnType ret = E_OK;
if( port > PORT_MAX_NUMBER-1){
     ret = E_NOT_OK;
 }
 else{
    *lat_reg[port]  = *lat_reg[port] ^ PORTC_MASK;
 }
return ret;
}
#endif
/**
 * 
 * @param port
 * @param logic
 * @return 
 */