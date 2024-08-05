/* 
 * File:   ecu_led.h
 * Author: laphouse
 *
 * Created on June 27, 2024, 10:53 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H
/*section :     Includes    */
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "ecu_led_cfg.h"
#include "../../MCAL_layer/CCP1/hal_ccp1.h"
/*section :     Macros Declarations    */

/*section :     Macro Function Declarations    */


/*section :     Data Type Declarations    */
typedef enum {
    LED_OFF,
    LED_ON
}led_status_t;

typedef struct {
    uint8 port : 4;
    uint8 pin  : 3;
    uint8 status : 1;
}led_t;


/*section :      Function Declarations    */
Std_ReturnType led_init(const led_t *led);
Std_ReturnType led_turn_on(const led_t *led);
Std_ReturnType led_turn_off(const led_t *led);
Std_ReturnType led_toggle(const led_t *led);

#endif	/* ECU_LED_H */

