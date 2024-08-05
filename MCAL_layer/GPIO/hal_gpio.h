/* 
 * File:   hal_gpio.h
 * Author: laphouse
 *
 * Created on June 27, 2024, 10:36 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H
/*section :     Includes    */
#include "pic18f4620.h"
#include "../device_config.h"
#include "../MCAL_std_types.h"
#include "hal_gpio_cfg.h"
/*section :     Macros Declarations    */
#define BIT_MASK    (uint8)1
#define PORT_PIN_MAX_NUMBER      8
#define PORT_MAX_NUMBER          5

#define PORTC_MASK          0xFF


/*section :     Macro Function Declarations    */
#define HWREG8(_x)          (*((volatile uint8 *)(_X)))

#define SET_BIT(REG,BIT_POSN)       (REG |= (BIT_MASK << BIT_POSN))
#define CLR_BIT(REG,BIT_POSN)       (REG &= ~(BIT_MASK << BIT_POSN))
#define TOG_BIT(REG,BIT_POSN)       (REG ^= (BIT_MASK << BIT_POSN))
#define READ_BIT(REG, BIT_POSN)    ((REG >> BIT_POSN) & BIT_MASK)
/*section :     Data Type Declarations    */
typedef enum {
    LOW,
    HIGH
}logic_t; 

typedef enum {
    GPIO_OUTPUT,
    GPIO_INPUT
}direction_t; 

typedef enum {
    PIN0,
    PIN1,  
    PIN2,  
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7
}pin_index_t; 

typedef enum {
    PORTA_INDEX,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX,
}port_index_t; 

typedef struct {
    uint8 port  : 3; /* @ref   port_index_t  */
    uint8 pin   : 3;    /* @ref pin_index_t  */
    uint8 direction     : 1;    /* @ref  direction_t  */
    uint8 logic     : 1;    /* @ref logic_t  */
}pin_config_t;
/**
 * 
 * @param _pin_config
 * @return 
 */
/*section :      Function Declarations    */

Std_ReturnType  gpio_pin_direction_init(const pin_config_t  *_pin_config);
Std_ReturnType  gpio_pin_direction_status(const pin_config_t  *_pin_config ,direction_t *dic_status);
Std_ReturnType  gpio_pin_write_logic(const pin_config_t  *_pin_config, logic_t logic );
Std_ReturnType  gpio_pin_intialize(const pin_config_t *_pin_config);
Std_ReturnType  gpio_pin_read_logic(const pin_config_t  *_pin_config, logic_t *logic );
Std_ReturnType  gpio_pin_toggle_logic(const pin_config_t  *_pin_config);


Std_ReturnType  gpio_port_direction_init(port_index_t  port ,uint8 direction);
Std_ReturnType  gpio_port_direction_status(port_index_t  port, uint8 *direction_status);
Std_ReturnType  gpio_port_write_logic(port_index_t  port , uint8 logic);
Std_ReturnType  gpio_port_read_logic(port_index_t  port , uint8 *logic);
Std_ReturnType  gpio_port_toggle_logic(port_index_t  port );
#endif	/* HAL_GPIO_H */

