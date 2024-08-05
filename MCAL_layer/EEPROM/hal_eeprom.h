/* 
 * File:   hal_eeprom.h
 * Author: laphouse
 *
 * Created on July 6, 2024, 5:56 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/*section :     Includes    */
#include "pic18f4620.h"
#include "../MCAL_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"




/*section :     Macros Declarations    */
#define ACCSESS_FLASH_PROGRAM_MEMORY        1
#define ACCSESS_EEPROM_PROGRAM_MEMORY       0
#define Access_Configuration_registers      1
#define Access_FLASH_EEPROM_MEMORY          0

#define Allows_write_cycles_to_Flash_or_EEPROM    1
#define Inhibits_write_cycles_to_Flash_or_EEPROM  0
#define Initiates_data_EEPROM_erase_write         1
#define Write_cycle_EEPROM_complete               0


#define Initiates_data_EEPROM_Read                1
#define Read_cycle_EEPROM_complete                0


/*section :     Macro Function Declarations    */


/*section :     Data Type Declarations    */

/*section :      Function Declarations    */
Std_ReturnType eeprom_write_byte(uint16 bAdd,uint8 bData);
Std_ReturnType eeprom_read_byte(uint16 bAdd,uint8 *bData);

#endif	/* HAL_EEPROM_H */

