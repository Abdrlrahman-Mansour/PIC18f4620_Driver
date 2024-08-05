/* 
 * File:   hal_usart.h
 * Author: laphouse
 *
 * Created on July 14, 2024, 8:32 PM
 */
#include "hal_usart.h"

 #if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (* EUSART_TX_InterruptHandler)(void) = NULL;
 #endif
 #if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (* EUSART_RX_InterruptHandler)(void) = NULL;
static void (* EUSART_FramingErrorHandler)(void) = NULL;
static void (* EUSART_OverrunErrorHandler)(void) = NULL;
 #endif


static void Baud_Rate_Calc(const usart_t *usart);
static void Usart_Async_TX_Init(const usart_t *usart);
static void Usart_Async_RX_Init(const usart_t *usart);

Std_ReturnType EUSART_ASYNC_Init(const usart_t *usart){
    Std_ReturnType ret = E_OK;
    if(NULL == usart){
        ret = E_NOT_OK;
    }
    else {
        RCSTAbits.SPEN = EUSART_DESABLE;
        TRISCbits.RC7 = 1;
        TRISCbits.RC6 = 1;
        Baud_Rate_Calc(usart);
        Usart_Async_TX_Init(usart);
        Usart_Async_RX_Init(usart);
        RCSTAbits.SPEN = EUSART_ENABLE;
    }
    return ret ;
}
Std_ReturnType EUSART_ASYNC_DeInit(const usart_t *usart){
    Std_ReturnType ret = E_OK;
    if(NULL == usart){
        ret = E_NOT_OK;
    }
    else {
        RCSTAbits.SPEN = EUSART_DESABLE;
    }
    return ret ;
}
Std_ReturnType EUSART_ASYNC_ReadByteBlocking(uint8 *data){
    Std_ReturnType ret = E_OK;
    if(NULL == data){
        ret = E_NOT_OK;
    }
    else {
        while(!PIR1bits.RCIF);
        *data =RCREG;
    }
    return ret ;
}
Std_ReturnType EUSART_ASYNC_ReadByteNonBlocking( uint8 *data){
    Std_ReturnType ret = E_OK;
    if(NULL == data){
        ret = E_NOT_OK;
    }
    else {
        if(PIR1bits.RCIF == 1){
            *data =RCREG;
        }
        else{
            ret = E_NOT_OK;
        }
    }
    return ret ;

}

Std_ReturnType EUSART_ASYNC_Restart_RX(void){
 Std_ReturnType ret = E_OK;
 RCSTAbits.CREN = 0;
 RCSTAbits.CREN = 1;
return ret ;
}

Std_ReturnType EUSART_ASYNC_WriteByteBlocking( uint8 data){
    Std_ReturnType ret = E_OK;
    while(!TXSTAbits.TRMT);
    #if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    USART_TX_InterruptEnable();
    #endif
    TXREG = data ;
    return ret ;
}
Std_ReturnType EUSART_ASYNC_WriteByteNonBlocking( uint8 data){
    Std_ReturnType ret = E_OK;
    if(TXSTAbits.TRMT == 1){
            TXREG = data ;
        }
        else{
            ret = E_NOT_OK;
        }
    
    return ret ;
}

Std_ReturnType EUSART_ASYNC_WriteStringBlocking( uint8 *data , uint8 length){
    Std_ReturnType ret = E_OK;
    uint8 counter = 0;
    if(NULL == data){
        ret = E_NOT_OK;
    }
    else {
        for(counter = 0 ; counter <length ; counter++){
            ret = EUSART_ASYNC_WriteByteBlocking(data[counter]);
        }
    }
    return ret ;

}

Std_ReturnType EUSART_ASYNC_WriteStringNonBlocking( uint8 *data , uint8 length){
    Std_ReturnType ret = E_OK;
    uint8 counter = 0;
    if(NULL == data){
            ret = E_NOT_OK;
        }
    else {
            for(counter = 0 ; counter <length ; counter++){
                if(TXSTAbits.TRMT == 1){
                    TXREG = data[counter];
                    
                }
                else{
                    ret = E_NOT_OK;
                }
            }
        }
        return ret ;
}

static void Baud_Rate_Calc(const usart_t *usart){
    float baudrate =0;
    switch(usart->baudrate_gen){
        case BAUDRATE_ASYNC_8BIT_LOW_SPEED :
            TXSTAbits.SYNC = 0;
            TXSTAbits.BRGH = 0;
            BAUDCONbits.BRG16 = 0;
            baudrate = ((_XTAL_FREQ / (float)usart->baudrate) / 64)- 1;
            break;
        case BAUDRATE_ASYNC_8BIT_HIGH_SPEED :
            TXSTAbits.SYNC = 0;
            TXSTAbits.BRGH = 1;
            BAUDCONbits.BRG16 = 0;
            baudrate = ((_XTAL_FREQ / (float)usart->baudrate) / 16)- 1;
            break;
        case BAUDRATE_ASYNC_16BIT_LOW_SPEED :
            TXSTAbits.SYNC = 0;
            TXSTAbits.BRGH = 0;
            BAUDCONbits.BRG16 = 1;
            baudrate = ((_XTAL_FREQ / (float)usart->baudrate) / 16)- 1;
            break;
        case BAUDRATE_ASYNC_16BIT_HIGH_SPEED :
            TXSTAbits.SYNC = 0;
            TXSTAbits.BRGH = 1;
            BAUDCONbits.BRG16 = 1;
            baudrate = ((_XTAL_FREQ / (float)usart->baudrate) / 4)- 1;
            break;
        case BAUDRATE_SYNC_8BIT :
            TXSTAbits.SYNC = 1;
            TXSTAbits.BRGH = 0;
            BAUDCONbits.BRG16 = 0;
            baudrate = ((_XTAL_FREQ / (float)usart->baudrate) / 4)- 1;
            break;
        case BAUDRATE_SYNC_16BIT :
            TXSTAbits.SYNC = 1;
            TXSTAbits.BRGH = 0;
            BAUDCONbits.BRG16 = 1;
            baudrate = ((_XTAL_FREQ / (float)usart->baudrate) / 4)- 1;
            break;
        default : 
            break;
    }
    SPBRG = (uint8)((uint32)baudrate);
    SPBRGH = (uint8)(((uint32)baudrate) >> 8);
}

static void Usart_Async_TX_Init(const usart_t *usart){
    if(EUSART_ASYNC_TX_ENABLE == usart->usart_tx.usart_tx_enable){
        TXSTAbits.TXEN = EUSART_ASYNC_TX_ENABLE;
        EUSART_TX_InterruptHandler = usart->EUSART_TXDefaultInterruptHandler;
        if(EUSART_ASYNC_INTERRUPT_TX_ENABLE == usart->usart_tx.usart_tx_interrupt_enable){
        PIE1bits.TXIE = EUSART_ASYNC_INTERRUPT_TX_ENABLE;
        #if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        USART_TX_InterruptEnable(); 
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(INTERRUPT_HIGH_PRIORITY == usart->usart_tx.priority){
            USART_TX_HighPrioritySet();
            INTERRUPT_GlobalInterruptHighEnable();
        }
        else if(INTERRUPT_LOW_PRIORITY == usart->usart_tx.priority){
            INTERRUPT_GlobalInterruptLowEnable();
            USART_TX_LowPrioritySet();
        }
        else{}
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        #endif      
        }
        else if(EUSART_ASYNC_INTERRUPT_TX_DESABLE == usart->usart_tx.usart_tx_interrupt_enable){
            PIE1bits.TXIE = EUSART_ASYNC_INTERRUPT_TX_DESABLE;
        }
        else{/*Nothing*/}

         if(EUSART_ASYNC_9BIT_TX_ENABLE == usart->usart_tx.usart_tx_9bit_enable){
            TXSTAbits.TX9 = EUSART_ASYNC_9BIT_TX_ENABLE ; 
        }
        else if(EUSART_ASYNC_9BIT_TX_DESABLE == usart->usart_tx.usart_tx_9bit_enable){
            TXSTAbits.TX9 = EUSART_ASYNC_9BIT_TX_DESABLE ; 
        }
        else{/*Nothing*/}   
    }
    else{/*Nothing*/} 
 
}


static void Usart_Async_RX_Init(const usart_t *usart){
    if(EUSART_ASYNC_RX_ENABLE == usart->usart_rx.usart_rx_enable){
        RCSTAbits.CREN = EUSART_ASYNC_RX_ENABLE ;
        EUSART_RX_InterruptHandler = usart->EUSART_RXDefaultInterruptHandler;
        EUSART_FramingErrorHandler = usart->EUSART_FramingErrorHandler;
        EUSART_OverrunErrorHandler = usart->EUSART_OverrunErrorHandler;
        if(EUSART_ASYNC_INTERRUPT_RX_ENABLE == usart->usart_rx.usart_rx_interrupt_enable){
         PIE1bits.RCIE= EUSART_ASYNC_INTERRUPT_RX_ENABLE;
         #if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        USART_RX_InterruptEnable(); 
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(INTERRUPT_HIGH_PRIORITY == usart->usart_rx.priority){
            USART_RX_HighPrioritySet();
            INTERRUPT_GlobalInterruptHighEnable();
        }
        else if(INTERRUPT_LOW_PRIORITY == usart->usart_rx.priority){
            INTERRUPT_GlobalInterruptLowEnable();
            USART_RX_LowPrioritySet();
        }
        else{}
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        #endif           
        }
        else if(EUSART_ASYNC_INTERRUPT_RX_DESABLE == usart->usart_rx.usart_rx_interrupt_enable){
            PIE1bits.RCIE = EUSART_ASYNC_INTERRUPT_RX_DESABLE;
        }
        else{/*Nothing*/}

         if(EUSART_ASYNC_9BIT_RX_ENABLE == usart->usart_rx.usart_rx_9bit_enable){
            RCSTAbits.RX9 = EUSART_ASYNC_9BIT_RX_ENABLE ; 
        }
        else if(EUSART_ASYNC_9BIT_RX_DESABLE == usart->usart_rx.usart_rx_9bit_enable){
            RCSTAbits.RX9 = EUSART_ASYNC_9BIT_RX_DESABLE ; 
        }
        else{/*Nothing*/}   
    }
    else{/*Nothing*/}

}

void USART_TX_ISR(void){
    USART_TX_InterruptDisable();
    if(EUSART_TX_InterruptHandler){
        EUSART_TX_InterruptHandler(); 
    }else{/*Nothing*/}
}
void USART_RX_ISR(void){
    if(EUSART_RX_InterruptHandler){
        EUSART_RX_InterruptHandler(); 
    }else{/*Nothing*/}
     if(EUSART_FramingErrorHandler){
        EUSART_FramingErrorHandler(); 
    }else{/*Nothing*/}
     if(EUSART_OverrunErrorHandler){
        EUSART_OverrunErrorHandler(); 
    }else{/*Nothing*/}
}