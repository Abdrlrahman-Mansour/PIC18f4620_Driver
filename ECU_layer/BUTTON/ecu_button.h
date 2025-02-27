/* 
 * File:   ecu_button.h
 * Author: laphouse
 *
 * Created on June 29, 2024, 12:08 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H



/*section :     Includes    */
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "ecu_button_cfg.h"



/*section :     Macros Declarations    */


/*section :     Macro Function Declarations    */


/*section :     Data Type Declarations    */
typedef enum{
    BUTTON_PRESSED = 0,
    BUTTON_RELEASED
}button_state_t;

typedef enum{
    BUTTON_ACTIVE_HIGH,
    BUTTON_ACTIVE_LOW
}button_active_t;

typedef struct{
    pin_config_t button_pin;
    button_state_t button_state;
    button_active_t button_connection;
}button_t;

/* ----------------- Software Interfaces Declarations -----------------*/
/**
 * @brief Initialize the assigned pin to be Input.
 * @param btn pointer to the button configurations
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType button_init(const button_t *btn);

/**
 * @brief Read the state of the button
 * @param btn pointer to the button configurations
 * @param btn_state button state @ref button_state_t
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state);


#endif	/* ECU_BUTTON_H */

