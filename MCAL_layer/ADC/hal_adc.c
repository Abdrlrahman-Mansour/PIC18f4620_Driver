/* 
 * File:   hal_adc.h
 * Author: laphouse
 *
 * Created on July 7, 2024, 5:43 PM
 */
#include "hal_adc.h"
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (* ADC_InterruptHandler)(void) = NULL;
#endif

static inline void adc_input_channel_port_config(adc_channel_select_t channel);
static inline void adc_Select_result_format(const adc_config_t *adc);
static inline void adc_select_volt_ref(const adc_config_t *adc);


/**
 * 
 * @param adc
 * @return 
 */
Std_ReturnType ADC_Init(const adc_config_t *adc){
    Std_ReturnType ret =E_OK;
    if(NULL == adc){
        ret = E_NOT_OK;
    }
    else{
        ADC_CONVERTER_DESABLE();
        
        ADCON2bits.ACQT = adc->acquisition_time;
        
        ADCON2bits.ADCS = adc->convertion_clock;
        
        ADCON0bits.CHS = adc->channel_select;
        adc_input_channel_port_config(adc->channel_select);
        
        #if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
     
        ADC_InterruptEnable();
        ADC_InterruptFlagClear();
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        if(INTERRUPT_HIGH_PRIORITY == adc->priority){
            ADC_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == adc->priority){
            ADC_LowPrioritySet();
        }
        else{}
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        ADC_InterruptHandler = adc->ADC_InterruptHandler;
        #endif
        
        
        adc_Select_result_format(adc);
        
        adc_select_volt_ref(adc);
        
        ADC_CONVERTER_ENABLE();
    }
    return ret;
}
/**
 * 
 * @param adc
 * @return 
 */
Std_ReturnType ADC_DeInit(const adc_config_t *adc){
    Std_ReturnType ret =E_OK;
    if(NULL == adc){
        ret = E_NOT_OK;
    }
    else{
        ADC_CONVERTER_DESABLE();
        ADC_InterruptDisable();
        
    }
    return ret;
}
/**
 * 
 * @param adc
 * @param channel
 * @return 
 */
Std_ReturnType ADC_SelectChannel(const adc_config_t *adc, adc_channel_select_t channel){
    Std_ReturnType ret =E_OK;
    if(NULL == adc){
        ret = E_NOT_OK;
    }
    else{
        ADCON0bits.CHS = channel;
        adc_input_channel_port_config(channel);
    }
    return ret;
}
/**
 * 
 * @param adc
 * @return 
 */
Std_ReturnType ADC_StartConversion(const adc_config_t *adc){
    Std_ReturnType ret =E_OK;
    if(NULL == adc){
        ret = E_NOT_OK;
    }
    else{
        ADC_START_CONVERTION();
    }
    return ret;
}
/**
 * 
 * @param adc
 * @param conversion_status
 * @return 
 */
Std_ReturnType ADC_IsConversionDone(const adc_config_t *adc , uint8 *conversion_status){
    Std_ReturnType ret =E_OK;
    if((NULL == adc) || (NULL == conversion_status)){
        ret = E_NOT_OK;
    }
    else{
       *conversion_status = (uint8)(!(ADCON0bits.GO_nDONE));
    }
    return ret;
}
/**
 * 
 * @param adc
 * @param conversion_result
 * @return 
 */
Std_ReturnType ADC_GetConversionResult(const adc_config_t *adc , uint16 *conversion_result){
    Std_ReturnType ret =E_OK;
    if((NULL == adc) || (NULL == conversion_result)){
        ret = E_NOT_OK;
    }
    else{
         if( ADC_RESULT_RIGHT == adc->result_format){
         *conversion_result= (uint16)((ADRESH<<8)   +  ADRESL); 
    }
    else if (ADC_RESULT_LEFT == adc->result_format){
      *conversion_result = (uint16)(((ADRESH<<8)   +  ADRESL) >> 6);
    }
    else {
          *conversion_result= (uint16)((ADRESH<<8)   +  ADRESL); 
    }
    }
    return ret;
}
/**
 * 
 * @param adc
 * @param channel
 * @param conversion_status
 * @return 
 */
Std_ReturnType ADC_GetConversion_Blocking(const adc_config_t *adc, adc_channel_select_t channel,uint8 *conversion_status){
    Std_ReturnType ret =E_OK;
  
    if((NULL == adc) || (NULL == conversion_status)){
        ret = E_NOT_OK;
    }
    else{
       ret = ADC_SelectChannel(adc , channel);
       ret = ADC_StartConversion(adc);
       
       while(ADCON0bits.GODONE);
        ret = ADC_GetConversionResult(adc , conversion_status); 
     
    }
    return ret;
}

Std_ReturnType ADC_StartConversion_Interrupt(const adc_config_t *adc, adc_channel_select_t channel){
    Std_ReturnType ret =E_OK;
  
    if(NULL == adc){
        ret = E_NOT_OK;
    }
    else{
       ret = ADC_SelectChannel(adc , channel);
       ret = ADC_StartConversion(adc);
    }
    return ret;
}


static inline void adc_input_channel_port_config(adc_channel_select_t channel){
    switch (channel){
        case ADC_CHANNEL_AN0:   SET_BIT(TRISA ,_TRISA_RA0_POSN);  break;
        case ADC_CHANNEL_AN1:   SET_BIT(TRISA ,_TRISA_RA1_POSN);  break;
        case ADC_CHANNEL_AN2:   SET_BIT(TRISA ,_TRISA_RA2_POSN);  break;
        case ADC_CHANNEL_AN3:   SET_BIT(TRISA ,_TRISA_RA3_POSN);  break;
        case ADC_CHANNEL_AN4:   SET_BIT(TRISA ,_TRISA_RA5_POSN);  break;
        case ADC_CHANNEL_AN5:   SET_BIT(TRISE ,_TRISE_RE0_POSN);  break;
        case ADC_CHANNEL_AN6:   SET_BIT(TRISE ,_TRISE_RE1_POSN);  break;
        case ADC_CHANNEL_AN7:   SET_BIT(TRISE ,_TRISE_RE2_POSN);  break;
        case ADC_CHANNEL_AN8:   SET_BIT(TRISB ,_TRISB_RB2_POSN);  break;
        case ADC_CHANNEL_AN9:   SET_BIT(TRISB ,_TRISB_RB3_POSN);  break;
        case ADC_CHANNEL_AN10:  SET_BIT(TRISB ,_TRISB_RB1_POSN);  break;
        case ADC_CHANNEL_AN11:  SET_BIT(TRISB ,_TRISB_RB4_POSN);  break;
        case ADC_CHANNEL_AN12:  SET_BIT(TRISB ,_TRISB_RB0_POSN);  break;
    }
}

static inline void adc_Select_result_format(const adc_config_t *adc){
    if( ADC_RESULT_RIGHT == adc->result_format){
        ADC_CONVERTER_RIGHT_JUSTIFIED();
    }
    else if (ADC_RESULT_LEFT == adc->result_format){
        ADC_CONVERTER_LEFT_JUSTIFIED();
    }
    else {
            ADC_CONVERTER_RIGHT_JUSTIFIED();
    }
}

static inline void adc_select_volt_ref(const adc_config_t *adc){
    if(ADC_VOLT_REF_EANBLE == adc->volt_ref){
        ADC_EANBLE_VOLTAGE_REF();
    }
    else if(ADC_VOLT_REF_DESABLE == adc->volt_ref){
        ADC_DESABLE_VOLTAGE_REF();
    }
    else {
        ADC_DESABLE_VOLTAGE_REF();
    }
}

void ADC_ISR(void){
    ADC_InterruptFlagClear();
    if(ADC_InterruptHandler){
        ADC_InterruptHandler(); 
    }
    
}