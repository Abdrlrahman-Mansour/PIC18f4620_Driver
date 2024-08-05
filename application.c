/* 
 * File:   application.c
 * Author: laphouse
 *
 * Created on June 27, 2024, 10:20 PM
 */

#include <pic18f4620.h>



#include "application.h"
#include "../pic18.h"

mssp_i2c_t i2c_obj;
static volatile uint8 i2c_slave1_rec_data;

led_t led1 = {.port = PORTD_INDEX, .pin = PIN0, .status = LOW};

void MSSP_I2C_DefaultInterruptHandler(void){
    /* Holds clock low (clock stretch) */
    I2C_CLOCK_STRETCH_ENABLE();
    if((SSPSTATbits.R_nW == 0) && (SSPSTATbits.D_nA == 0)){ /* Master Will Write Data, So i need to read it */
        uint8 dummy_buffer = SSPBUF; /* Read The Last Byte To Clear The Buffer */
        while(!SSPSTATbits.BF);
        i2c_slave1_rec_data = SSPBUF; /* read data */
    }
    else if(SSPSTATbits.R_nW == 1){ /* Master needs to read Data, So i need to write it */
        
    }
    else { /* Nothing */ }
    /* Releases clock */
    I2C_CLOCK_STRETCH_DISABLE();
}

int main() { 
    Std_ReturnType ret = E_NOT_OK;
   
    
    i2c_obj.i2c_cfg.i2c_mode = I2C_MSSP_SLAVE_MODE;
    i2c_obj.i2c_cfg.i2c_slave_address = 0x60;
    i2c_obj.i2c_cfg.i2c_mode_cfg = I2C_SLAVE_MODE_7BIT_ADDRESS;
    i2c_obj.i2c_cfg.i2c_SMBus_control = I2C_SMBus_DISABLE;
    i2c_obj.i2c_cfg.i2c_slew_rate = I2C_SLEW_RATE_DISABLE;
    i2c_obj.i2c_cfg.i2c_general_call = I2C_GENERAL_CALL_DISABLE;
    i2c_obj.I2C_DefaultInterruptHandler = MSSP_I2C_DefaultInterruptHandler;
    i2c_obj.I2C_Report_Receive_Overflow = NULL;
    i2c_obj.I2C_Report_Write_Collision = NULL;
    
    ret = MSSP_I2C_Init(&i2c_obj);
    ret = led_init(&led1);

    while(1){
        if('a' == i2c_slave1_rec_data){
            led_turn_on(&led1);
        }
        else if('c' == i2c_slave1_rec_data){
            led_turn_off(&led1); 
        }
        else {}
    }
        
    return (EXIT_SUCCESS);
}

 