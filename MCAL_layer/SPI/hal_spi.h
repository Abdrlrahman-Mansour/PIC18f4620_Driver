/* 
 * File:   hal_spi.h
 * Author: laphouse
 *
 * Created on July 15, 2024, 10:59 PM
 */

#ifndef HAL_SPI_H
#define	HAL_SPI_H

/*section :     Includes    */
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"
#include "pic18f4620.h"
#include "../MCAL_std_types.h"




/*section :     Macros Declarations    */
#define SPI_MASTER_FOSC_DIV_4    0
#define SPI_MASTER_FOSC_DIV_16   1
#define SPI_MASTER_FOSC_DIV_64   2
#define SPI_MASTER_FOSC_TMR2     3
#define SPI_SLAVE_SS_ENABLE      4
#define SPI_SLAVE_SS_DESABLE     5


#define SPI_IDLE_STATE_HIGH_LEVEL   1 
#define SPI_IDLE_STATE_LOW_LEVEL    0 

#define SPI_DATA_SAMPLE_MIDDLE      0 
#define SPI_DATA_SAMPLE_END         1 

#define SPI_TRANSMIT_ACTIVE_TO_IDLE 1 
#define SPI_TRANSMIT_IDLE_TO_ACTIVE 0 

#define SPI_SLAVE_RECEIVE_OVERFLOW_DETECTED      1
#define SPI_SLAVE_RECEIVE_OVERFLOW_NOT_DETECTED  0

#define SPI_WRITE_COLLISION_DETECTED             1
#define SPI_WRITE_COLLISION_NOT_DETECTED         0

#define SPI_BUFFER_FULL_RECEIVE_COMPLETE         1
#define SPI_BUFFER_FULL_RECEIVE_NOT_COMPLETE     0

/*section :     Macro Function Declarations    */
#define SPI_ENABLE_MODULE()    (SSPCON1bits.SSPEN = 1) 
#define SPI_DISABLE_MODULE()   (SSPCON1bits.SSPEN = 0) 

/*section :     Data Type Declarations    */
typedef struct{
    uint8 ClockPolarity : 2; /* Clock Polarity Select */
    uint8 SampleSelect : 2;  /* SPI Sample Select */
    uint8 ClockSelect : 2;   /* SPI Clock Select */
    uint8 Reserved : 2;
}SPI_Control_Config;

typedef struct{
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* MSSP_SPI_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    uint8 spi_mode;
    SPI_Control_Config spi_config;
}SPI_Config;
/*section :      Function Declarations    */
Std_ReturnType SPI_Init(const SPI_Config *Config);
Std_ReturnType SPI_DeInit(const SPI_Config *Config);
Std_ReturnType SPI_Send_Byte(const SPI_Config *Config, const uint8 _data);
Std_ReturnType SPI_Read_Byte(const SPI_Config *Config, uint8 *_data);

#endif	/* HAL_SPI_H */

