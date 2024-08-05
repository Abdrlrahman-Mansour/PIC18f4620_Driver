/* 
 * File:   ecu_keypad.h
 * Author: laphouse
 *
 * Created on July 2, 2024, 6:05 AM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/*section :     Includes    */
#include "ecu_keypad_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"




/*section :     Macros Declarations    */
#define keypad_rows     4
#define keypad_columns  4
/*section :     Macro Function Declarations    */


/*section :     Data Type Declarations    */
typedef struct {
    pin_config_t keypad_r_pins[keypad_rows] ;
    pin_config_t keypad_c_pins[keypad_columns] ;
}keypad_t;
/*section :      Function Declarations    */

 Std_ReturnType keypad_init(const keypad_t *keypad_obj);
 Std_ReturnType keypad_get_value(const keypad_t *keypad_obj ,uint8 *value);


#endif	/* ECU_KEYPAD_H */

