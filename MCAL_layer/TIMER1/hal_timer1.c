/* 
 * File:   hal_timer1.c
 * Author: laphouse
 *
 * Created on July 10, 2024, 6:14 PM
 */
#include "hal_timer1.h"

 #if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (* Timer1_InterruptHandler)(void) = NULL;
 #endif
static uint16  timer1_preload = 0;


static inline void Timer1_Mode_Select(const timer1_t *timer);

/**
 * 
 * @param timer
 * @return 
 */
Std_ReturnType Timer1_Init(const timer1_t *timer){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
         TIMER1_DESABLE();
         TIMER1_PRESCALER_SELECT(timer->timer1_PRESCALER_VAL);
         Timer1_Mode_Select(timer);
        TMR1H = ((timer->timer1_preload_val) >> 8);
        TMR1L = (uint8)(timer->timer1_preload_val);
        timer1_preload = timer->timer1_preload_val;
        #if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER1_InterruptEnable();
        TIMER1_InterruptFlagClear();
        Timer1_InterruptHandler = timer->Timer1_InterruptHandler;
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(INTERRUPT_HIGH_PRIORITY == timer->priority){
            TIMER1_HighPrioritySet();
            INTERRUPT_GlobalInterruptHighEnable();
        }
        else if(INTERRUPT_LOW_PRIORITY == timer->priority){
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER1_LowPrioritySet();
        }
        else{}
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        #endif

        TIMER1_ENABLE();
    }
    return ret ;
}
/**
 * 
 * @param timer
 * @return 
 */
Std_ReturnType Timer1_DeInit(const timer1_t *timer){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER1_DESABLE();
        #if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER1_InterruptDisable();
        #endif
    }
    return ret ;
}
/**
 * 
 * @param timer
 * @param value
 * @return 
 */
Std_ReturnType Timer1_Write_Value(const timer1_t *timer , uint16 value){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        TMR1H = (value >> 8);
        TMR1L = (uint8)value;
    }
    return ret ;
}
/**
 * 
 * @param timer
 * @param value
 * @return 
 */
Std_ReturnType Timer1_Read_Value(const timer1_t *timer , uint16 *value){
    Std_ReturnType ret = E_OK;
    uint8 _tmr1l = 0;
    uint8 _tmr1h = 0;
    if((NULL == timer) || (NULL == value)){
        ret = E_NOT_OK;
    }
    else{
        _tmr1l = TMR1L ;
        _tmr1h = TMR1H ;
        *value = (uint16)((_tmr1h << 8) + _tmr1l) ;
        
    }
    return ret ;
}


static inline void Timer1_Mode_Select(const timer1_t *timer){
    if(TIMER1_TIMER_MODE == timer->timer1_mode){
        TIMER1_TIMER_MODE_ENABLE();
    }
    else if (TIMER1_COUNTER_MODE == timer->timer1_mode){
        TIMER1_COUNTER_MODE_ENABLE();
        if(TIMER1_ASYNC_COUNTER_MODE == timer->timer1_counter_mode){
            TIMER1_ASYNC_COUNTER_MODE_ENABLE();
        }
        else if(TIMER1_SYNC_COUNTER_MODE == timer->timer1_counter_mode){
            TIMER1_SYNC_COUNTER_MODE_ENABLE();
        }
        else {/*Nothing*/}
    }
    else{/*Nothing*/}
}

void TMR1_ISR(void){
    TIMER1_InterruptFlagClear();
    TMR1H = ((timer1_preload) >> 8);
    TMR1L = (uint8)(timer1_preload);
    if(Timer1_InterruptHandler){
        Timer1_InterruptHandler(); 
    }
}