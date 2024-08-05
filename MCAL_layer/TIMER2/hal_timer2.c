/* 
 * File:   hal_timer2.c
 * Author: laphouse
 *
 * Created on July 10, 2024, 11:03 PM
 */
#include "hal_timer2.h"

 #if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (* Timer2_InterruptHandler)(void) = NULL;
 #endif
static uint16  timer2_preload = 0;



/**
 * 
 * @param timer
 * @return 
 */
Std_ReturnType Timer2_Init(const timer2_t *timer){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
         TIMER2_DESABLE();
         TIMER2_PRESCALER_SELECT(timer->timer2_PRESCALER_VAL);
         TIMER2_POSTSCALER_SELECT(timer->timer2_POSTSCALER_VAL);
        TMR2 = timer->timer2_preload_val ;
        timer2_preload = timer->timer2_preload_val;
        #if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER2_InterruptEnable();
        TIMER2_InterruptFlagClear();
        Timer2_InterruptHandler = timer->Timer2_InterruptHandler;
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(INTERRUPT_HIGH_PRIORITY == timer->priority){
            TIMER2_HighPrioritySet();
            INTERRUPT_GlobalInterruptHighEnable();
        }
        else if(INTERRUPT_LOW_PRIORITY == timer->priority){
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER2_LowPrioritySet();
        }
        else{}
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        #endif
         
         TIMER2_ENABLE();
    }
    return ret ;
}
/**
 * 
 * @param timer
 * @return 
 */
Std_ReturnType Timer2_DeInit(const timer2_t *timer){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER2_DESABLE();
        #if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER2_InterruptDisable();
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
Std_ReturnType Timer2_Write_Value(const timer2_t *timer , uint8 value){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        TMR2 = value;
    }
    return ret ;
}
/**
 * 
 * @param timer
 * @param value
 * @return 
 */
Std_ReturnType Timer2_Read_Value(const timer2_t *timer , uint8 *value){
    Std_ReturnType ret = E_OK;
    if((NULL == timer) || (NULL == value)){
        ret = E_NOT_OK;
    }
    else{
        *value = TMR2;
    }
    return ret ;
}

void TMR2_ISR(void){
    TIMER2_InterruptFlagClear();
    TMR2 = timer2_preload;
    if(Timer2_InterruptHandler){
        Timer2_InterruptHandler(); 
    }
}