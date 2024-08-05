/* 
 * File:   mcal_internal_interrupt.h
 * Author: laphouse
 *
 * Created on July 5, 2024, 7:43 AM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H
/*section :     Includes    */
#include "mcal_interrupt_cfg.h"





/*section :     Macros Declarations    */

/*section :     Macro Function Declarations    */
                /*ADC */
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
#define ADC_InterruptDisable()         (PIE1bits.ADIE = 0)
#define ADC_InterruptEnable()          (PIE1bits.ADIE = 1)
#define ADC_InterruptFlagClear()       (PIR1bits.ADIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
#define ADC_HighPrioritySet()           (IPR1bits.ADIP = 1)
#define ADC_LowPrioritySet()            (IPR1bits.ADIP = 0)
#endif

#endif

                /*Timer 0  */
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
#define TIMER0_InterruptDisable()         (INTCONbits.TMR0IE = 0)
#define TIMER0_InterruptEnable()          (INTCONbits.TMR0IE = 1)
#define TIMER0_InterruptFlagClear()       (INTCONbits.TMR0IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
#define TIMER0_HighPrioritySet()           (INTCON2bits.TMR0IP = 1)
#define TIMER0_LowPrioritySet()            (INTCON2bits.TMR0IP = 0)
#endif

#endif

                    /*Timer 1  */
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
#define TIMER1_InterruptDisable()         (PIE1bits.TMR1IE = 0)
#define TIMER1_InterruptEnable()          (PIE1bits.TMR1IE = 1)
#define TIMER1_InterruptFlagClear()       (PIR1bits.TMR1IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
#define TIMER1_HighPrioritySet()           (IPR1bits.TMR1IP = 1)
#define TIMER1_LowPrioritySet()            (IPR1bits.TMR1IP = 0)
#endif

#endif

                    /*Timer 2  */
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
#define TIMER2_InterruptDisable()         (PIE1bits.TMR2IE = 0)
#define TIMER2_InterruptEnable()          (PIE1bits.TMR2IE = 1)
#define TIMER2_InterruptFlagClear()       (PIR1bits.TMR2IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
#define TIMER2_HighPrioritySet()           (IPR1bits.TMR2IP = 1)
#define TIMER2_LowPrioritySet()            (IPR1bits.TMR2IP = 0)
#endif

#endif

                    /*Timer 3  */
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
#define TIMER3_InterruptDisable()         (PIE2bits.TMR3IE = 0)
#define TIMER3_InterruptEnable()          (PIE2bits.TMR3IE = 1)
#define TIMER3_InterruptFlagClear()       (PIR2bits.TMR3IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
#define TIMER3_HighPrioritySet()           (IPR2bits.TMR3IP = 1)
#define TIMER3_LowPrioritySet()            (IPR2bits.TMR3IP = 0)
#endif
#endif

                    /* CCP1 */
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
#define CCP1_InterruptDisable()         (PIE1bits.CCP1IE = 0)
#define CCP1_InterruptEnable()          (PIE1bits.CCP1IE = 1)
#define CCP1_InterruptFlagClear()       (PIR1bits.CCP1IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
#define CCP1_HighPrioritySet()           (IPR1bits.CCP1IP = 1)
#define CCP1_LowPrioritySet()            (IPR1bits.CCP1IP = 0)
#endif
#endif

                    /* CCP2 */
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
#define CCP2_InterruptDisable()         (PIE2bits.CCP2IE = 0)
#define CCP2_InterruptEnable()          (PIE2bits.CCP2IE = 1)
#define CCP2_InterruptFlagClear()       (PIR2bits.CCP2IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
#define CCP2_HighPrioritySet()           (IPR2bits.CCP2IP = 1)
#define CCP2_LowPrioritySet()            (IPR2bits.CCP2IP = 0)
#endif
#endif
                    /* Usart TX */
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
#define USART_TX_InterruptDisable()         (PIE1bits.TXIE = 0)
#define USART_TX_InterruptEnable()          (PIE1bits.TXIE = 1)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
#define USART_TX_HighPrioritySet()           (IPR1bits.TXIP = 1)
#define USART_TX_LowPrioritySet()            (IPR1bits.TXIP = 0)
#endif
#endif

                    /* Usart RX */
#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
#define USART_RX_InterruptDisable()         (PIE1bits.RCIE = 0)
#define USART_RX_InterruptEnable()          (PIE1bits.RCIE = 1)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
#define USART_RX_HighPrioritySet()           (IPR1bits.RCIP = 1)
#define USART_RX_LowPrioritySet()            (IPR1bits.RCIP = 0)
#endif
#endif

                    /* SPI */
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
#define MSSP_SPI_InterruptDisable()         (PIE1bits.SSPIE = 0)
#define MSSP_SPI_InterruptEnable()          (PIE1bits.SSPIE = 1)
#define MSSP_SPI_InterruptFlagClear()       (PIR1bits.SSPIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
#define MSSP_SPI_HighPrioritySet()           (IPR1bits.SSPIP = 1)
#define MSSP_SPI_LowPrioritySet()            (IPR1bits.SSPIP = 0)
#endif
#endif

                    /* I2C */
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
#define MSSP_I2C_InterruptDisable()         (PIE1bits.SSPIE = 0)
#define MSSP_I2C_BUS_COL_InterruptDisable() (PIE2bits.BCLIE = 0)

#define MSSP_I2C_InterruptEnable()          (PIE1bits.SSPIE = 1)
#define MSSP_I2C_BUS_COL_InterruptEnable()  (PIE2bits.BCLIE = 1)

#define MSSP_I2C_InterruptFlagClear()          (PIR1bits.SSPIF = 0)
#define MSSP_I2C_BUS_COL_InterruptFlagClear()  (PIR2bits.BCLIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
#define MSSP_I2C_HighPrioritySet()           (IPR1bits.SSPIP = 1)
#define MSSP_I2C_BUS_COL_HighPrioritySet()   (IPR2bits.BCLIP = 1)

#define MSSP_I2C_LowPrioritySet()            (IPR1bits.SSPIP = 0)
#define MSSP_I2C_BUS_COL_LowPrioritySet()    (IPR2bits.BCLIP = 0)
#endif
#endif
/* ----------------- Data Type Declarations -----------------*/

/* ----------------- Software Interfaces Declarations -----------------*/

/*section :     Data Type Declarations    */

/*section :      Function Declarations    */

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

