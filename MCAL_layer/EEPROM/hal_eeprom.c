/* 
 * File:   hal_eeprom.h
 * Author: laphouse
 *
 * Created on July 6, 2024, 5:56 PM
 */
#include "hal_eeprom.h"
/**
 * 
 * @param bAdd
 * @param bData
 * @return 
 */
Std_ReturnType eeprom_write_byte(uint16 bAdd,uint8 bData){
    Std_ReturnType ret = E_OK ;
    uint8 status_interrupt=INTCONbits.GIE;
    
    EEADRH = (uint8)((bAdd >> 8) & 0x03); 
    EEADR = (uint8)(bAdd & 0xFF);
    
    EEDATA = bData;
    
    EECON1bits.EEPGD = ACCSESS_EEPROM_PROGRAM_MEMORY;
    EECON1bits.CFGS = Access_FLASH_EEPROM_MEMORY;
    
    EECON1bits.WREN = Allows_write_cycles_to_Flash_or_EEPROM;
    
    INTERRUPT_GlobalInterruptDisable();
    
    EECON2 = 0x55;
    EECON2 = 0xAA;
    
    EECON1bits.WR = Initiates_data_EEPROM_erase_write;
    
    while(EECON1bits.WR);
    
    EECON1bits.WREN = Inhibits_write_cycles_to_Flash_or_EEPROM;
    
    INTCONbits.GIE = status_interrupt;
    return ret;
}
/**
 * 
 * @param bAdd
 * @param bData
 * @return 
 */
Std_ReturnType eeprom_read_byte(uint16 bAdd,uint8 *bData){
   Std_ReturnType ret = E_NOT_OK;
   if(NULL == bData){
       ret = E_NOT_OK;
   }
   else {
       EEADRH = (uint8)((bAdd >> 8) & 0x03); 
       EEADR = (uint8)(bAdd & 0xFF);
       
       EECON1bits.EEPGD = ACCSESS_EEPROM_PROGRAM_MEMORY;
       EECON1bits.CFGS = Access_FLASH_EEPROM_MEMORY;
       
       EECON1bits.RD = Initiates_data_EEPROM_Read;
       NOP();
       NOP();
       
       *bData = EEDATA;
       ret =E_OK;
   }
    return ret;
}