/* 
 * File:   hal_timer2.h
 * Author: laphouse
 *
 * Created on July 10, 2024, 11:03 PM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

/*section :     Includes    */
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"
#include "pic18f4620.h"
#include "../MCAL_std_types.h"

/*section :     Macros Declarations    */
#define TIMER2_POSTSCALER_VALUE_DIV_BY_1        0     
#define TIMER2_POSTSCALER_VALUE_DIV_BY_2        1     
#define TIMER2_POSTSCALER_VALUE_DIV_BY_3        2     
#define TIMER2_POSTSCALER_VALUE_DIV_BY_4        3     
#define TIMER2_POSTSCALER_VALUE_DIV_BY_5        4     
#define TIMER2_POSTSCALER_VALUE_DIV_BY_6        5     
#define TIMER2_POSTSCALER_VALUE_DIV_BY_7        6     
#define TIMER2_POSTSCALER_VALUE_DIV_BY_8        7     
#define TIMER2_POSTSCALER_VALUE_DIV_BY_9        8     
#define TIMER2_POSTSCALER_VALUE_DIV_BY_10       9     
#define TIMER2_POSTSCALER_VALUE_DIV_BY_11       10     
#define TIMER2_POSTSCALER_VALUE_DIV_BY_12       11    
#define TIMER2_POSTSCALER_VALUE_DIV_BY_13       12    
#define TIMER2_POSTSCALER_VALUE_DIV_BY_14       13    
#define TIMER2_POSTSCALER_VALUE_DIV_BY_15       14    
#define TIMER2_POSTSCALER_VALUE_DIV_BY_16       15    

#define TIMER2_PRESCALER_VALUE_DIV_BY_1         0     
#define TIMER2_PRESCALER_VALUE_DIV_BY_4         1     
#define TIMER2_PRESCALER_VALUE_DIV_BY_16        2     
  


/*section :     Macro Function Declarations    */
#define TIMER2_ENABLE()                            (T2CONbits.TMR2ON = 1)
#define TIMER2_DESABLE()                           (T2CONbits.TMR2ON = 0)

#define TIMER2_PRESCALER_SELECT(_x)                (T2CONbits.T2CKPS = _x)
#define TIMER2_POSTSCALER_SELECT(_x)               (T2CONbits.TOUTPS = _x)
/*section :     Data Type Declarations    */
typedef struct{   
  #if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
   void (* Timer2_InterruptHandler)(void);
    interrupt_priority_cfg priority;
 #endif
uint8 timer2_preload_val;
uint8 timer2_POSTSCALER_VAL     : 4 ;
uint8 timer2_PRESCALER_VAL      : 2 ;
uint8 timer2_reserved           : 2 ;
}timer2_t;
/*section :      Function Declarations    */
Std_ReturnType Timer2_Init(const timer2_t *timer);
Std_ReturnType Timer2_DeInit(const timer2_t *timer);
Std_ReturnType Timer2_Write_Value(const timer2_t *timer , uint8 value);
Std_ReturnType Timer2_Read_Value(const timer2_t *timer , uint8 *value);


#endif	/* HAL_TIMER2_H */

