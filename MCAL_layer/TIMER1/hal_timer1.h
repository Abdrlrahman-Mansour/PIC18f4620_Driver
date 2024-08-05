/* 
 * File:   hal_timer1.h
 * Author: laphouse
 *
 * Created on July 10, 2024, 6:14 PM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

/*section :     Includes    */
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"
#include "pic18f4620.h"
#include "../MCAL_std_types.h"


/*section :     Macros Declarations    */
#define TIMER1_TIMER_MODE           0
#define TIMER1_COUNTER_MODE         1

#define TIMER1_ASYNC_COUNTER_MODE         1
#define TIMER1_SYNC_COUNTER_MODE          0

#define TIMER1_OSC_ENABLE           1
#define TIMER1_OSC_DESABLE          0

#define TIMER1_PRESCALER_VALUE_DIV_BY_1         0     
#define TIMER1_PRESCALER_VALUE_DIV_BY_2         1     
#define TIMER1_PRESCALER_VALUE_DIV_BY_4         2     
#define TIMER1_PRESCALER_VALUE_DIV_BY_8         3     

#define TIMER1_REGESTER_SIZE_8BIT   0
#define TIMER1_REGESTER_SIZE_16BIT  1

/*section :     Macro Function Declarations    */
#define TIMER1_ENABLE()                           (T1CONbits.TMR1ON = 1)
#define TIMER1_DESABLE()                          (T1CONbits.TMR1ON = 0)

#define TIMER1_TIMER_MODE_ENABLE()                (T1CONbits.TMR1CS = 0)
#define TIMER1_COUNTER_MODE_ENABLE()              (T1CONbits.TMR1CS = 1)

#define TIMER1_ASYNC_COUNTER_MODE_ENABLE()        (T1CONbits.T1SYNC = 1)
#define TIMER1_SYNC_COUNTER_MODE_ENABLE()         (T1CONbits.T1SYNC = 0)

#define TIMER1_OSC_HW_ENABLE()                    (T1CONbits.T1OSCEN = 1)
#define TIMER1_OSC_HW_DESABLE()                   (T1CONbits.T1OSCEN = 0)

#define TIMER1_PRESCALER_SELECT(_x)               (T1CONbits.T1CKPS = _x)

#define TIMER1_SYSTEM_CLK_STATUS()                (T1CONbits.T1RUN)

#define TIMER1_CONFIG_AS_8BIT()                   (T1CONbits.RD16 = 0)  
#define TIMER1_CONFIG_AS_16BIT()                  (T1CONbits.RD16 = 1)  

/*section :     Data Type Declarations    */


typedef struct{   
  #if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
   void (* Timer1_InterruptHandler)(void);
    interrupt_priority_cfg priority;
 #endif
uint16 timer1_preload_val;
uint8 timer1_PRESCALER_VAL     : 2 ;
uint8 timer1_mode              : 1 ;
uint8 timer1_counter_mode      : 1 ;
uint8 timer1_osc_cfg           : 1 ;
uint8 timer1_reg_rw_mode       : 1 ;
uint8 timer1_reserved          : 2 ;
}timer1_t;
/*section :      Function Declarations    */
Std_ReturnType Timer1_Init(const timer1_t *timer);
Std_ReturnType Timer1_DeInit(const timer1_t *timer);
Std_ReturnType Timer1_Write_Value(const timer1_t *timer , uint16 value);
Std_ReturnType Timer1_Read_Value(const timer1_t *timer , uint16 *value);

#endif	/* HAL_TIMER1_H */

