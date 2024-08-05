/* 
 * File:   hal_usart.h
 * Author: laphouse
 *
 * Created on July 14, 2024, 8:32 PM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H
/*section :     Includes    */
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"
#include "pic18f4620.h"
#include "../MCAL_std_types.h"
#include "hal_usart_cfg.h"

/*section :     Macros Declarations    */

#define EUSART_ENABLE                          1
#define EUSART_DESABLE                         0

#define EUSART_SYNC_MODE                       1
#define EUSART_ASYNC_MODE                      0

#define EUSART_ASYNC_HIGH_SPEED                1
#define EUSART_ASYNC_LOW_SPEED                 0

#define EUSART_16BIT_BAUDRATE_GEN              1
#define EUSART_8BIT_BAUDRATE_GEN               0

#define EUSART_ASYNC_TX_ENABLE                 1
#define EUSART_ASYNC_TX_DESABLE                0 

#define EUSART_ASYNC_INTERRUPT_TX_ENABLE       1
#define EUSART_ASYNC_INTERRUPT_TX_DESABLE      0 

#define EUSART_ASYNC_9BIT_TX_ENABLE            1
#define EUSART_ASYNC_9BIT_TX_DESABLE           0 

#define EUSART_ASYNC_RX_ENABLE                 1
#define EUSART_ASYNC_RX_DESABLE                0 

#define EUSART_ASYNC_INTERRUPT_RX_ENABLE       1
#define EUSART_ASYNC_INTERRUPT_RX_DESABLE      0 

#define EUSART_ASYNC_9BIT_RX_ENABLE            1
#define EUSART_ASYNC_9BIT_RX_DESABLE           0 

#define EUSART_FRAMING_ERROR_DETECTED          1
#define EUSART_FRAMING_ERROR_CLEARED           0

#define EUSART_OVERRUN_ERROR_DETECTED          1
#define EUSART_OVERRUN_ERROR_CLEARED           0
/*section :     Macro Function Declarations    */

/*section :     Data Type Declarations    */
typedef enum{
    BAUDRATE_ASYNC_8BIT_LOW_SPEED,
    BAUDRATE_ASYNC_8BIT_HIGH_SPEED,
    BAUDRATE_ASYNC_16BIT_LOW_SPEED,
    BAUDRATE_ASYNC_16BIT_HIGH_SPEED,
    BAUDRATE_SYNC_8BIT,
    BAUDRATE_SYNC_16BIT,        
}baudrate_gen_t;

typedef struct {
    uint8 usart_tx_reserved : 5;
    uint8 usart_tx_enable : 1;
    uint8 usart_tx_interrupt_enable : 1;
    uint8 usart_tx_9bit_enable : 1;
    interrupt_priority_cfg priority;
}usart_tx_cfg_t; 

typedef struct {
    uint8 usart_rx_reserved : 5;
    uint8 usart_rx_enable : 1;
    uint8 usart_rx_interrupt_enable : 1;
    uint8 usart_rx_9bit_enable : 1;
    interrupt_priority_cfg priority;
}usart_rx_cfg_t; 

typedef union {
    struct {
        uint8 usart_reserved : 6;
        uint8 usart_ferr : 1;
        uint8 usart_oerr : 1;
    };
    uint8 status ;
}usart_error_status_t; 

typedef struct{
    uint32 baudrate ;
baudrate_gen_t baudrate_gen;
usart_tx_cfg_t  usart_tx ;
usart_rx_cfg_t  usart_rx ;
usart_error_status_t usart_error_status;
void(* EUSART_TXDefaultInterruptHandler)(void);
void(* EUSART_RXDefaultInterruptHandler)(void);
void(* EUSART_FramingErrorHandler)(void);
void(* EUSART_OverrunErrorHandler)(void);

}usart_t;


/*section :      Function Declarations    */
Std_ReturnType EUSART_ASYNC_Init(const usart_t *usart);
Std_ReturnType EUSART_ASYNC_DeInit(const usart_t *usart);

Std_ReturnType EUSART_ASYNC_ReadByteBlocking( uint8 *data);
Std_ReturnType EUSART_ASYNC_ReadByteNonBlocking( uint8 *data);
Std_ReturnType EUSART_ASYNC_Restart_RX(void);

Std_ReturnType EUSART_ASYNC_WriteByteBlocking( uint8 data);
Std_ReturnType EUSART_ASYNC_WriteStringBlocking( uint8 *data , uint8 length);
Std_ReturnType EUSART_ASYNC_WriteByteNonBlocking( uint8 data);
Std_ReturnType EUSART_ASYNC_WriteStringNonBlocking( uint8 *data , uint8 length);
#endif	/* HAL_USART_H */

