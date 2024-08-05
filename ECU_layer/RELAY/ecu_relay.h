/* 
 * File:   ecu_relay.h
 * Author: laphouse
 *
 * Created on June 30, 2024, 9:30 AM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H
/*section :     Includes    */
#include "ecu_relay_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"




/*section :     Macros Declarations    */
#define RELAY_ON_STATUS     0x01U
#define RELAY_OFF_STATUS    0x00U
/*section :     Macro Function Declarations    */


/*section :     Data Type Declarations    */
typedef struct {
    uint8   relay_port  : 4;
    uint8   relay_pin   : 3;
    uint8   relay_status : 1;
}relay_t;


/*section :      Function Declarations    */
Std_ReturnType relay_init(const relay_t *relay);
Std_ReturnType relay_turn_on(const relay_t *relay);
Std_ReturnType relay_turn_off(const relay_t *relay);
#endif	/* ECU_RELAY_H */

