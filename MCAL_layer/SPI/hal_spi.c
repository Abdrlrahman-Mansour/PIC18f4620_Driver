/* 
 * File:   hal_spi.c
 * Author: laphouse
 *
 * Created on July 15, 2024, 10:59 PM
 */
#include "hal_spi.h"

#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (*SPI_InterruptHandler)(void) = NULL;
#endif
static void MSSP_SPI_Interrupt_Init(const SPI_Config *Config);
static void MSSP_SPI_Msster_Mode_GPIO_PIN_Configurations(const SPI_Config *Config);
static void MSSP_SPI_Slave_Mode_GPIO_PIN_Configurations(const SPI_Config *Config);
Std_ReturnType SPI_Init(const SPI_Config *Config){
    Std_ReturnType ret = E_OK;
    if(NULL == Config){
        ret = E_NOT_OK;
    }
    else{
        SPI_DISABLE_MODULE();
        SPI_DISABLE_MODULE();
        SPI_DISABLE_MODULE();
        SSPCON1bits.SSPM = Config->spi_mode;
        if((Config->spi_mode == SPI_MASTER_FOSC_DIV_4) || (Config->spi_mode == SPI_MASTER_FOSC_DIV_16) ||
            (Config->spi_mode == SPI_MASTER_FOSC_DIV_64) || (Config->spi_mode == SPI_MASTER_FOSC_TMR2)){
            MSSP_SPI_Msster_Mode_GPIO_PIN_Configurations(Config);
        }
         else if((Config->spi_mode == SPI_SLAVE_SS_ENABLE) || (Config->spi_mode == SPI_SLAVE_SS_DESABLE)){
            MSSP_SPI_Slave_Mode_GPIO_PIN_Configurations(Config);
        }
         else{/*Nothing*/}
        SSPCON1bits.CKP = Config->spi_config.ClockPolarity;
        SSPSTATbits.SMP = Config->spi_config.SampleSelect;
        SSPSTATbits.CKE = Config->spi_config.ClockSelect;
        MSSP_SPI_Interrupt_Init(Config);
         SPI_ENABLE_MODULE();
        
        
    }
    return ret;
}
Std_ReturnType SPI_DeInit(const SPI_Config *Config){
    Std_ReturnType ret = E_OK;
    if(NULL == Config){
        ret = E_NOT_OK;
    }
    else{
        SPI_DISABLE_MODULE();
        #if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            MSSP_SPI_InterruptDisable();
        #endif
    }
    return ret;
}
Std_ReturnType SPI_Send_Byte(const SPI_Config *Config, const uint8 _data){
    Std_ReturnType ret = E_OK;
    if(NULL == Config){
        ret = E_NOT_OK;
    }
    else{
        // Load the data into the buffer
        SSPBUF = _data;
        SSPBUF = _data;
        SSPBUF = _data;
        SSPBUF = _data;
        
        // Wait for the transmission to complete
       
        while(!PIR1bits.SSPIF);
        
        // Clear the interrupt flag
        PIR1bits.SSPIF = 0;
    }
    return ret;
}
Std_ReturnType SPI_Read_Byte(const SPI_Config *Config, uint8 *_data){
    Std_ReturnType ret = E_OK;
    if((NULL == Config) || (NULL == _data)){
        ret = E_NOT_OK;
    }
    else{
         while(SSPSTATbits.BF == 0); 
        *_data = SSPBUF;
    }
    return ret;
}



void MSSP_SPI_ISR(void){
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    MSSP_SPI_InterruptFlagClear();
    if(SPI_InterruptHandler){
        SPI_InterruptHandler();
    }
#endif
}

static void MSSP_SPI_Msster_Mode_GPIO_PIN_Configurations(const SPI_Config *Config){
 Std_ReturnType ret = E_NOT_OK;
    pin_config_t SPI_SDO = {.port = PORTC_INDEX, .pin = PIN5, .direction = GPIO_OUTPUT};
    pin_config_t SPI_SDI = {.port = PORTC_INDEX, .pin = PIN4, .direction = GPIO_INPUT};
    pin_config_t SPI_CLK = {.port = PORTC_INDEX, .pin = PIN3, .direction = GPIO_OUTPUT};
    
    ret = gpio_pin_direction_init(&SPI_SDO); 
    ret = gpio_pin_direction_init(&SPI_SDI);
    ret = gpio_pin_direction_init(&SPI_CLK);

}

static void MSSP_SPI_Slave_Mode_GPIO_PIN_Configurations(const SPI_Config *Config){
    Std_ReturnType ret = E_NOT_OK;
    pin_config_t SPI_SDO = {.port = PORTC_INDEX, .pin = PIN5, .direction = GPIO_OUTPUT};
    pin_config_t SPI_SDI = {.port = PORTC_INDEX, .pin = PIN4, .direction = GPIO_INPUT};
    pin_config_t SPI_CLK = {.port = PORTC_INDEX, .pin = PIN3, .direction = GPIO_INPUT};
    pin_config_t SPI_SS = {.port = PORTA_INDEX, .pin = PIN5, .direction = GPIO_INPUT};
    
    ret = gpio_pin_direction_init(&SPI_SDO); 
    ret = gpio_pin_direction_init(&SPI_SDI);
    ret = gpio_pin_direction_init(&SPI_CLK); 
    
    if(SPI_SLAVE_SS_ENABLE == Config->spi_mode){
        ret = gpio_pin_direction_init(&SPI_SS);
    }

}

static void MSSP_SPI_Interrupt_Init(const SPI_Config *Config){
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    MSSP_SPI_InterruptEnable();
    MSSP_SPI_InterruptFlagClear();
    SPI_InterruptHandler = Config->MSSP_SPI_InterruptHandler;
/* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
    INTERRUPT_PriorityLevelsEnable();
    if(INTERRUPT_HIGH_PRIORITY == Config->priority){
        /* Enables all high-priority interrupts */
        INTERRUPT_GlobalInterruptHighEnable();
        MSSP_SPI_HighPrioritySet();
    }
    else if(INTERRUPT_LOW_PRIORITY == Config->priority){
        /* Enables all unmasked peripheral interrupts */
        INTERRUPT_GlobalInterruptLowEnable();
        MSSP_SPI_LowPrioritySet();
    }
    else{ /* Nothing */ }
#else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
#endif      
#endif        

}