/* 
 * File:   ecu_motor.h
 * Author: laphouse
 *
 * Created on June 30, 2024, 12:32 PM
 */

#ifndef ECU_MOTOR_H
#define	ECU_MOTOR_H

/*section :     Includes    */
#include "ecu_motor_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"

/*section :     Macros Declarations    */
#define MOTOR_ON_STATUS     0x01U
#define MOTOR_OFF_STATUS    0x00U
/*section :     Macro Function Declarations    */


/*section :     Data Type Declarations    */
typedef struct {
    uint8 motor_port  : 4;
    uint8 motor_pin   : 3;
    uint8 motor_status : 1;
}motor_pin_t;

typedef struct {
    motor_pin_t motor[2];
}motor_t;

/*section :      Function Declarations    */
Std_ReturnType motor_init(const motor_t *motor);
Std_ReturnType motor_move_right(const motor_t *motor);
Std_ReturnType motor_move_left(const motor_t *motor);
Std_ReturnType motor_stop(const motor_t *motor);



#endif	/* ECU_MOTOR_H */

