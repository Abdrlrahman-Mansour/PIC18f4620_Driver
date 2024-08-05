/* 
 * File:   hal_timer0.h
 * Author: laphouse
 *
 * Created on July 9, 2024, 9:19 AM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H
/*section :     Includes    */
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"
#include "pic18f4620.h"
#include "../MCAL_std_types.h"



/*section :     Macros Declarations    */
#define TIMER0_PRESCALER_ENABLE     1
#define TIMER0_PRESCALER_DESABLE    0

#define TIMER0_RISING_EDGE_CFG      1
#define TIMER0_FALLING_EDGE_CFG     0

#define TIMER0_TIMER_MODE           1
#define TIMER0_COUNTER_MODE         0

#define TIMER0_REGESTER_SIZE_8BIT   1
#define TIMER0_REGESTER_SIZE_16BIT  0

/*section :     Macro Function Declarations    */
#define TIMER0_PRESCALER_ASSIGNED()               (T0CONbits.PSA = 0)
#define TIMER0_PRESCALER_NOT_ASSIGNED()           (T0CONbits.PSA = 1)

#define TIMER0_RISING_EDGE()                      (T0CONbits.T0SE = 0)
#define TIMER0_FALLING_EDGE()                     (T0CONbits.T0SE = 1)

#define TIMER0_CONFIG_AS_8BIT()                   (T0CONbits.T08BIT = 1)  
#define TIMER0_CONFIG_AS_16BIT()                  (T0CONbits.T08BIT = 0)  

#define TIMER0_ENABLE()                           (T0CONbits.TMR0ON = 1)
#define TIMER0_DESABLE()                          (T0CONbits.TMR0ON = 0)

#define TIMER0_TIMER_MODE_ENABLE()                (T0CONbits.T0CS = 0)
#define TIMER0_COUNTER_MODE_ENABLE()              (T0CONbits.T0CS = 1)
/*section :     Data Type Declarations    */
typedef enum {
    TIMER0_PRESCALER_VALUE_DIV_BY_2,
    TIMER0_PRESCALER_VALUE_DIV_BY_4,
    TIMER0_PRESCALER_VALUE_DIV_BY_8,
    TIMER0_PRESCALER_VALUE_DIV_BY_16,
    TIMER0_PRESCALER_VALUE_DIV_BY_32,
    TIMER0_PRESCALER_VALUE_DIV_BY_64,
    TIMER0_PRESCALER_VALUE_DIV_BY_128,
    TIMER0_PRESCALER_VALUE_DIV_BY_256,
}timer0_prescaler_t;

typedef struct{   
  #if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
   void (* Timer0_InterruptHandler)(void);
    interrupt_priority_cfg priority;
 #endif
timer0_prescaler_t prescaler_val;
uint16 timer0_preload_val;
uint8 prescaler_enable : 1 ;
uint8 timer0_edge      : 1 ;
uint8 timer0_mode      : 1 ;
uint8 timer0_reg_size  : 1 ;
uint8 timer0_reserved  : 4 ;
}timer0_t;
/*section :      Function Declarations    */
Std_ReturnType Timer0_Init(const timer0_t *timer);
Std_ReturnType Timer0_DeInit(const timer0_t *timer);
Std_ReturnType Timer0_Write_Value(const timer0_t *timer , uint16 value);
Std_ReturnType Timer0_Read_Value(const timer0_t *timer , uint16 *value);



#endif	/* HAL_TIMER0_H */

