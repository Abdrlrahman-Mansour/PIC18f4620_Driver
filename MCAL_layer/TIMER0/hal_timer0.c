/* 
 * File:   hal_timer0.c
 * Author: laphouse
 *
 * Created on July 9, 2024, 9:19 AM
 */
#include "hal_timer0.h"

 #if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (* Timer0_InterruptHandler)(void) = NULL;
 #endif
static uint16  timer0_preload = 0;

static inline void Timer0_prescaler_config(const timer0_t *timer);
static inline void Timer0_Mode_Select(const timer0_t *timer);
static inline void Timer0_Reg_Size(const timer0_t *timer);
/**
 * 
 * @param timer
 * @return 
 */

Std_ReturnType Timer0_Init(const timer0_t *timer){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER0_DESABLE();
        Timer0_prescaler_config(timer);
        Timer0_Mode_Select(timer);
        Timer0_Reg_Size(timer);
        TMR0H = ((timer->timer0_preload_val) >> 8);
        TMR0L = (uint8)(timer->timer0_preload_val);
        timer0_preload = timer->timer0_preload_val;
        #if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER0_InterruptEnable();
        TIMER0_InterruptFlagClear();
        Timer0_InterruptHandler = timer->Timer0_InterruptHandler;
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(INTERRUPT_HIGH_PRIORITY == timer->priority){
            TIMER0_HighPrioritySet();
            INTERRUPT_GlobalInterruptHighEnable();
        }
        else if(INTERRUPT_LOW_PRIORITY == timer->priority){
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER0_LowPrioritySet();
        }
        else{}
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        #endif

        TIMER0_ENABLE();
    }
    return ret;
}
/**
 * 
 * @param timer
 * @return 
 */
Std_ReturnType Timer0_DeInit(const timer0_t *timer){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER0_DESABLE();
        #if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER0_InterruptDisable();
        #endif
    }
    return ret;
}
/**
 * 
 * @param timer
 * @param value
 * @return 
 */
Std_ReturnType Timer0_Write_Value(const timer0_t *timer , uint16 value){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        TMR0H = (value >> 8);
        TMR0L = (uint8)value;
    }
    return ret;
}
/**
 * 
 * @param timer
 * @param value
 * @return 
 */
Std_ReturnType Timer0_Read_Value(const timer0_t *timer , uint16 *value){
    Std_ReturnType ret = E_OK;
    uint8 _tmr0l = 0;
    uint8 _tmr0h = 0;
    if((NULL == timer) || (NULL == value)){
        ret = E_NOT_OK;
    }
    else{
        _tmr0l = TMR0L ;
        _tmr0h = TMR0H ;
        *value = (uint16)((_tmr0h << 8) + _tmr0l) ;
        
    }
    return ret;
}

void TMR0_ISR(void){
    TIMER0_InterruptFlagClear();
    TMR0H = ((timer0_preload) >> 8);
    TMR0L = (uint8)(timer0_preload);
    if(Timer0_InterruptHandler){
        Timer0_InterruptHandler(); 
    }
    
}

static inline void Timer0_prescaler_config(const timer0_t *timer){
    if(TIMER0_PRESCALER_ENABLE == timer->prescaler_enable){
        TIMER0_PRESCALER_ASSIGNED();
        T0CONbits.T0PS = timer->prescaler_val;
    }
    else if (TIMER0_PRESCALER_DESABLE == timer->prescaler_enable){
        TIMER0_PRESCALER_NOT_ASSIGNED();
    }
    else{/*Nothing*/}
}

static inline void Timer0_Mode_Select(const timer0_t *timer){
    if(TIMER0_TIMER_MODE == timer->timer0_mode){
        TIMER0_TIMER_MODE_ENABLE();
    }
    else if (TIMER0_COUNTER_MODE == timer->timer0_mode){
        TIMER0_COUNTER_MODE_ENABLE();
        if(TIMER0_RISING_EDGE_CFG == timer->timer0_edge){
            TIMER0_RISING_EDGE();
        }
        else if (TIMER0_FALLING_EDGE_CFG == timer->timer0_edge){
            TIMER0_FALLING_EDGE();
        }
        else{/*Nothing*/}
    }
    else{/*Nothing*/}
}

static inline void Timer0_Reg_Size(const timer0_t *timer){
    if(TIMER0_REGESTER_SIZE_8BIT == timer->timer0_reg_size){
        TIMER0_CONFIG_AS_8BIT();
    }
    else if (TIMER0_REGESTER_SIZE_16BIT == timer->timer0_reg_size){
        TIMER0_CONFIG_AS_16BIT();
    }
    else{/*Nothing*/}
}