/*
 *------------------------------------------------------------------------------
 *
 *------------------------------------------------------------------------------
 */

#ifndef __DBGU_H__
#define __DBGU_H__

// -------- DBGU_CR : (USART Offset: 0x0)  Control Register -------- 
#define DBGU_RSTRX		(0x1 <<  2) // (USART) Reset Receiver
#define DBGU_RSTTX		(0x1 <<  3) // (USART) Reset Transmitter
#define DBGU_RXEN		(0x1 <<  4) // (USART) Receiver Enable
#define DBGU_RXDIS		(0x1 <<  5) // (USART) Receiver Disable
#define DBGU_TXEN		(0x1 <<  6) // (USART) Transmitter Enable
#define DBGU_TXDIS		(0x1 <<  7) // (USART) Transmitter Disable
#define DBGU_RSTSTA		(0x1 <<  8) // (USART) Reset Status Bits

// -------- DBGU_IER : (USART Offset: 0x8)  Interrupt Enable Register -------- 
#define DBGU_RXRDY		(0x1 <<  0) // (USART) RXRDY Interrupt
#define DBGU_TXRDY		(0x1 <<  1) // (USART) TXRDY Interrupt
#define DBGU_ENDRX		(0x1 <<  3) // (USART) End of Receive Transfer Interrupt
#define DBGU_ENDTX		(0x1 <<  4) // (USART) End of Transmit Interrupt
#define DBGU_OVRE		(0x1 <<  5) // (USART) Overrun Interrupt
#define DBGU_FRAME		(0x1 <<  6) // (USART) Framing Error Interrupt
#define DBGU_PARE		(0x1 <<  7) // (USART) Parity Error Interrupt
#define DBGU_TXEMPTY	(0x1 <<  9) // (USART) TXEMPTY Interrupt
#define DBGU_TXBUFE		(0x1 << 11) // (USART) TXBUFE Interrupt
#define DBGU_RXBUFF		(0x1 << 12) // (USART) RXBUFF Interrupt
#define DBGU_COMMTX		(0x1 << 30) // (USART) Clear To Send Input Change Flag
#define DBGU_COMMRX		(0x1 << 31) // (USART) Manchester Error Interrupt

//void DBGU_TxEN(void);
//void DBGU_TxDIS(void);
//void DBGU_RxEN(void);
//void DBGU_RxDIS(void);

void DBGU_PutByte(S8 c);
S8 DBGU_GetByte(void);
S8 DBGU_GetKey(void);

#endif /* __DBGU_H__ */
