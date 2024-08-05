/* 
 * File:   mcal_interrupt_manager.h
 * Author: laphouse
 *
 * Created on July 5, 2024, 7:45 AM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/*section :     Includes    */


#include "mcal_interrupt_cfg.h"


/*section :     Macros Declarations    */

/*section :     Macro Function Declarations    */


/*section :     Data Type Declarations    */

/*section :      Function Declarations    */
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(uint8 RB4_Source);
void RB5_ISR(uint8 RB5_Source);
void RB6_ISR(uint8 RB6_Source);
void RB7_ISR(uint8 RB7_Source);
void ADC_ISR(void);
void TMR0_ISR(void);
void TMR1_ISR(void);
void TMR2_ISR(void);
void TMR3_ISR(void);
void CCP1_ISR(void);
void CCP2_ISR(void);
void USART_TX_ISR(void);
void USART_RX_ISR(void);
void MSSP_SPI_ISR(void);
void MSSP_I2C_ISR(void);
void MSSP_I2C_BC_ISR(void);
#endif	/* MCAL_INTERRUPT_MANAGER_H */

