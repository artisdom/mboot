/* ----------------------------------------------------------------------------
 *		 
 *        mboot for Lophilo embedded system
 *		
 * ----------------------------------------------------------------------------
 * GPLv2
 * ----------------------------------------------------------------------------
 */
 
#include "def.h"
#include "trace.h"
#include "soc.h"
#include "dbgu.h"
 
//void
//DBGU_TxEN(void)
//{
//	rDBGU_CR = DBGU_TXEN;
//}
//
//void
//DBGU_TxDIS(void)
//{
//	rDBGU_CR = DBGU_TXDIS;
//}
//
//void
//DBGU_RxEN(void)
//{
//	rDBGU_CR = DBGU_RXEN;
//}
//
//void
//DBGU_RxDIS(void)
//{
//	rDBGU_CR = DBGU_RXDIS;
//}

void
DBGU_PutByte(S8 c)
{
    // Wait for the transmitter to be ready  
    while ((rDBGU_SR & DBGU_TXEMPTY) == 0);
    // Send character    
    rDBGU_THR = c;
    // Wait for the transfer to complete    
    while ((rDBGU_SR & DBGU_TXEMPTY) == 0);  
}

S8
DBGU_GetByte(void)
{
    while (!(rDBGU_SR & DBGU_RXRDY));
    return rDBGU_RHR;
}

S8
DBGU_GetKey(void)
{
	if(rDBGU_SR & DBGU_RXRDY)
		return rDBGU_RHR;
	else
		return 0;
}
