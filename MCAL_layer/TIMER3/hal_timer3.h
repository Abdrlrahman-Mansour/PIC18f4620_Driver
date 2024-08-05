/* 
 * File:   hal_timer3.h
 * Author: laphouse
 *
 * Created on July 11, 2024, 9:11 AM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

/*section :     Includes    */
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"
#include "pic18f4620.h"
#include "../MCAL_std_types.h"


/*section :     Macros Declarations    */
#define TIMER3_TIMER_MODE           0
#define TIMER3_COUNTER_MODE         1

#define TIMER3_ASYNC_COUNTER_MODE         1
#define TIMER3_SYNC_COUNTER_MODE          0

#define TIMER3_PRESCALER_VALUE_DIV_BY_1         0     
#define TIMER3_PRESCALER_VALUE_DIV_BY_2         1     
#define TIMER3_PRESCALER_VALUE_DIV_BY_4         2     
#define TIMER3_PRESCALER_VALUE_DIV_BY_8         3     

#define TIMER3_REGESTER_SIZE_8BIT   0
#define TIMER3_REGESTER_SIZE_16BIT  1

/*section :     Macro Function Declarations    */
#define TIMER3_ENABLE()                           (T3CONbits.TMR3ON = 1)
#define TIMER3_DESABLE()                          (T3CONbits.TMR3ON = 0)

#define TIMER3_TIMER_MODE_ENABLE()                (T3CONbits.TMR3CS = 0)
#define TIMER3_COUNTER_MODE_ENABLE()              (T3CONbits.TMR3CS = 1)

#define TIMER3_ASYNC_COUNTER_MODE_ENABLE()        (T3CONbits.T3SYNC = 1)
#define TIMER3_SYNC_COUNTER_MODE_ENABLE()         (T3CONbits.T3SYNC = 0)

#define TIMER3_PRESCALER_SELECT(_x)               (T3CONbits.T3CKPS = _x)

#define TIMER3_CONFIG_AS_8BIT()                   (T3CONbits.RD16 = 0)  
#define TIMER3_CONFIG_AS_16BIT()                  (T3CONbits.RD16 = 1)  

/*section :     Data Type Declarations    */
typedef struct{   
  #if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
   void (* Timer3_InterruptHandler)(void);
    interrupt_priority_cfg priority;
 #endif
uint16 timer3_preload_val;
uint8 timer3_PRESCALER_VAL     : 2 ;
uint8 timer3_mode              : 1 ;
uint8 timer3_counter_mode      : 1 ;
uint8 timer3_reg_rw_mode       : 1 ;
uint8 timer3_reserved          : 3 ;
}timer3_t;
/*section :      Function Declarations    */
Std_ReturnType Timer3_Init(const timer3_t *timer);
Std_ReturnType Timer3_DeInit(const timer3_t *timer);
Std_ReturnType Timer3_Write_Value(const timer3_t *timer , uint16 value);
Std_ReturnType Timer3_Read_Value(const timer3_t *timer , uint16 *value);



#endif	/* HAL_TIMER3_H */

