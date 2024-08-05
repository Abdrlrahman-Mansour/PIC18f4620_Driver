/* 
 * File:   hal_timer3.h
 * Author: laphouse
 *
 * Created on July 11, 2024, 9:11 AM
 */
#include "hal_timer3.h"

 #if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (* Timer3_InterruptHandler)(void) = NULL;
 #endif
static uint16  timer3_preload = 0;

static inline void Timer3_Mode_Select(const timer3_t *timer);
/**
 * 
 * @param timer
 * @return 
 */
Std_ReturnType Timer3_Init(const timer3_t *timer){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
         TIMER3_DESABLE();
         TIMER3_PRESCALER_SELECT(timer->timer3_PRESCALER_VAL);
         Timer3_Mode_Select(timer);
        TMR3H = ((timer->timer3_preload_val) >> 8);
        TMR3L = (uint8)(timer->timer3_preload_val);
        timer3_preload = timer->timer3_preload_val;
        #if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER3_InterruptEnable();
        TIMER3_InterruptFlagClear();
        Timer3_InterruptHandler = timer->Timer3_InterruptHandler;
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(INTERRUPT_HIGH_PRIORITY == timer->priority){
            TIMER3_HighPrioritySet();
            INTERRUPT_GlobalInterruptHighEnable();
        }
        else if(INTERRUPT_LOW_PRIORITY == timer->priority){
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER3_LowPrioritySet();
        }
        else{}
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        #endif

        TIMER3_ENABLE();
    }
    return ret;
}
/**
 * 
 * @param timer
 * @return 
 */
Std_ReturnType Timer3_DeInit(const timer3_t *timer){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
         TIMER3_DESABLE();
        #if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER3_InterruptDisable();
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
Std_ReturnType Timer3_Write_Value(const timer3_t *timer , uint16 value){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        TMR3H = (value >> 8);
        TMR3L = (uint8)value;
    }
    return ret;
}
/**
 * 
 * @param timer
 * @param value
 * @return 
 */
Std_ReturnType Timer3_Read_Value(const timer3_t *timer , uint16 *value){
    Std_ReturnType ret = E_OK;
    uint8 _tmr3l = 0;
    uint8 _tmr3h = 0;
    if((NULL == timer) || (NULL == value)){
        ret = E_NOT_OK;
    }
    else{
        _tmr3l = TMR3L ;
        _tmr3h = TMR3H ;
        *value = (uint16)((_tmr3h << 8) + _tmr3l) ;       
    }
    return ret;
}


static inline void Timer3_Mode_Select(const timer3_t *timer){
    if(TIMER3_TIMER_MODE == timer->timer3_mode){
        TIMER3_TIMER_MODE_ENABLE();
    }
    else if (TIMER3_COUNTER_MODE == timer->timer3_mode){
        TIMER3_COUNTER_MODE_ENABLE();
        if(TIMER3_ASYNC_COUNTER_MODE == timer->timer3_counter_mode){
            TIMER3_ASYNC_COUNTER_MODE_ENABLE();
        }
        else if(TIMER3_SYNC_COUNTER_MODE == timer->timer3_counter_mode){
            TIMER3_SYNC_COUNTER_MODE_ENABLE();
        }
        else {/*Nothing*/}
    }
    else{/*Nothing*/}
}

void TMR3_ISR(void){
    TIMER3_InterruptFlagClear();
    TMR3H = ((timer3_preload) >> 8);
    TMR3L = (uint8)(timer3_preload);
    if(Timer3_InterruptHandler){
        Timer3_InterruptHandler(); 
    }
}