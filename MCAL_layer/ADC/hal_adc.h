/* 
 * File:   hal_adc.h
 * Author: laphouse
 *
 * Created on July 7, 2024, 5:43 PM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H


/*section :     Includes    */
#include "hal_adc_cfg.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"
#include "pic18f4620.h"
#include "../MCAL_std_types.h"




/*section :     Macros Declarations    */
#define ADC_AN0_ANALOG_FUNCTIONALITY     0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY     0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY     0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY     0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY     0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY     0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY     0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY     0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY     0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY     0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY    0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY    0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY    0x02
#define ADC_ALL_ANALOG_FUNCTIONALITY     0x00
#define ADC_ALL_DIGITAL_FUNCTIONALITY    0x0F

#define ADC_RESULT_RIGHT            0x01U
#define ADC_RESULT_LEFT             0x00U

#define ADC_VOLT_REF_EANBLE         0x01U
#define ADC_VOLT_REF_DESABLE        0x00U

#define ADC_CONVERSION_COMPLETED        0x01
#define ADC_CONVERSION_NOT_COMPLETED    0x00
/*section :     Macro Function Declarations    */
#define ADC_CONVERTION_STATUS()     (ADCON0bits.GODONE)
#define ADC_START_CONVERTION()      (ADCON0bits.GODONE = 1)

#define ADC_CONVERTER_ENABLE()      (ADCON0bits.ADON = 1)
#define ADC_CONVERTER_DESABLE()      (ADCON0bits.ADON = 0)

#define ADC_EANBLE_VOLTAGE_REF()        do{ADCON1bits.VCFG1 = 1; \
                                           ADCON1bits.VCFG0 = 1; \
                                             }while(0)
#define ADC_DESABLE_VOLTAGE_REF()        do{ADCON1bits.VCFG1 = 0; \
                                           ADCON1bits.VCFG0 = 0; \
                                             }while(0)


#define ADC_ANALOG_DIGITAL_PORT_CONFIG(_x)      (ADCON1bits.PCFG = _x)


#define ADC_CONVERTER_RIGHT_JUSTIFIED()             (ADCON2bits.ADFM = 1)
#define ADC_CONVERTER_LEFT_JUSTIFIED()              (ADCON2bits.ADFM = 0)


/*section :     Data Type Declarations    */
typedef enum {
    ADC_CHANNEL_AN0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12,
}adc_channel_select_t;


typedef enum {
    ADC_0_TAD,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD,
}adc_Acquisition_time_t;

typedef enum {
    ADC_FOSC_DIV_2,
    ADC_FOSC_DIV_8,
    ADC_FOSC_DIV_32,
    ADC_FOSC_DIV_FRC,
    ADC_FOSC_DIV_4,
    ADC_FOSC_DIV_16,
    ADC_FOSC_DIV_64,
}adc_convertion_clock_t;

typedef struct {
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* ADC_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
adc_Acquisition_time_t acquisition_time ;
adc_convertion_clock_t  convertion_clock;
adc_channel_select_t   channel_select;
uint8 volt_ref :    1;
uint8 result_format :1;
uint8  adc_reserved : 6;
}adc_config_t;
/*section :      Function Declarations    */
Std_ReturnType ADC_Init(const adc_config_t *adc);
Std_ReturnType ADC_DeInit(const adc_config_t *adc);
Std_ReturnType ADC_SelectChannel(const adc_config_t *adc, adc_channel_select_t channel);
Std_ReturnType ADC_StartConversion(const adc_config_t *adc);
Std_ReturnType ADC_IsConversionDone(const adc_config_t *adc , uint8 *conversion_status);
Std_ReturnType ADC_GetConversionResult(const adc_config_t *adc , uint16 *conversion_result);
Std_ReturnType ADC_GetConversion_Blocking(const adc_config_t *adc, adc_channel_select_t channel,uint8 *conversion_status);
Std_ReturnType ADC_StartConversion_Interrupt(const adc_config_t *adc, adc_channel_select_t channel);

#endif	/* HAL_ADC_H */

