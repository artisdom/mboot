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
#include "init_hw.h"
//#include "dma.h"

#include "system.h"
//
////------------------------------------------------------------------------------
////         Local types
////------------------------------------------------------------------------------
////------------------------------------------------------------------------------
///// DMA transfer descriptor. Tracks the status and parameters of a transfer
///// on the DMA bus.
////------------------------------------------------------------------------------
//typedef struct _DmaTransfer {
//    /// Buffer transfer status.
//    volatile U8 status;
//    /// Transfer buffer size in byte.
//    U32 bufSize;
//    /// Total transfer size to byte.
//    volatile U32 transferSize;
//    /// Optional callback function.
//    DmaCallback callback;
//} DmaTransfer;
//
////------------------------------------------------------------------------------
///// DMAD driver structure. Monitors the status of transfers on all
///// DMA channels.
////------------------------------------------------------------------------------
//typedef struct _Dmad {
//
//    /// List of transfers occuring on each channel.
//    DmaTransfer transfers[8];
//} Dmad;
//
////------------------------------------------------------------------------------
////         Local variables
////------------------------------------------------------------------------------
//
///// Global DMA transfer instance.
//static Dmad dmad;
//
////------------------------------------------------------------------------------
////         Local functions
////------------------------------------------------------------------------------
////------------------------------------------------------------------------------
///// This handler function must be called by the DMAC interrupt service routine.
///// Identifies which event was activated and calls the associated function.
////------------------------------------------------------------------------------ 
//void DMAD_Handler()
//{
//    U32 status;
//    U8 channel;
//    DmaTransfer *pTransfer;
//    status = DMA_GetStatus();
//    // Check if the buffer transfer completed is set.
//    if(status & (0xFF << 0))
//    {
//        // Scan each channel status.
//        for(channel = 0; channel < 8; channel++) {
//            if(!(status & (0x1 << channel))){
//                continue;
//            }
//            
//            dmad.transfers[channel].transferSize -= dmad.transfers[channel].bufSize;
//            // if next buffer is to be the last buffer in the transfer, then clear the automatic mode bit.
//            if(dmad.transfers[channel].transferSize <= dmad.transfers[channel].bufSize) {
//                DMA_ClearAutoMode(channel);
//            }
//            // Transfer finished
//            if(dmad.transfers[channel].transferSize == 0) {
//                pTransfer = &(dmad.transfers[channel]);
//                pTransfer->callback();
//                DMA_DisableIt(0x1 << channel); 
//                DMA_DisableChannel(channel);
//            }
//            else
//            {
//                // Write the KEEPON field to clear the STALL states.
//                DMA_KeeponChannel(channel);
//            }
//        }
//    }
//}
//
////------------------------------------------------------------------------------
///// Initializes the DMA controller.
///// \param channel Particular channel number
///// \param defaultHandler Using the default dmad interrupt handler.
////------------------------------------------------------------------------------
//void DMAD_Initialize(U8 channel, U8 defaultHandler)
//{
//    U32 status;
//    U32 flag;
//
//    // Read the channel handler status to ensure the channel is a free channel.
//    status = DMA_GetChannelStatus();
////    TRACE_MSG("DMAD_Initialize channel: %x, Status: %x", channel, status);
//    // Clear any pending interrupts on the channel.
//    DMA_GetStatus();
//    // Disble the channel.
//    DMA_DisableChannel(channel);
//    // Disable the interrupt
//    flag = 0xffffff;
//    DMA_DisableIt(flag);
//    // Enable DMA.
//    DMA_Enable();
//    if(defaultHandler) 
//    {
//        IRQ_PeriConf(PERIF_ID_HDMA, 0, DMAD_Handler);
//        IRQ_PeriEn(PERIF_ID_HDMA);
//    }
//    // Initialize transfer instance.
//    dmad.transfers[channel].transferSize = 0;
//}
// 
////------------------------------------------------------------------------------
///// Configure the DMA transfer buffer by giving transfer mode, it could be single 
///// buffer or multi-buffer(LLI/auto-reload/contiguous buffers) with or without 
///// Picture-In-Picture mode.
///// \param channel Particular channel number.
///// \param sourceTransferMode Source buffer transfer mode.
///// \param destTransferMode Destination buffer transfer mode.
///// \param lli Pointer to a DmaLinkList structure instance.
///// \param pip Pointer to a PictureInPicture structure.
////------------------------------------------------------------------------------
//U8 DMAD_Configure_Buffer(U8 channel,
//                           U8 sourceTransferMode,
//                           U8 destTransferMode,
//                           DmaLinkList *lli,
//                           PictureInPicture *pip)
//{
//    DmaTransfer *pTransfer = &(dmad.transfers[channel]);
//    // Check that no transfer is pending on the channel
//    if (pTransfer-> transferSize > 0 ) {
//        TRACE_ERR("DAM transfer is already pending\n\r");
//        return DMAD_ERROR_BUSY;
//    }
//    // Configure source transfer mode.
//    DMA_SetSourceBufferMode(channel, sourceTransferMode, 0);
//    
//    // Configure destination transfer mode.
//    DMA_SetDestBufferMode(channel, destTransferMode, 0);
//    
//    if(lli){
//        DMA_SetDescriptorAddr(channel, (U32)(&lli[0]));
//    }
//    else {
//        DMA_SetDescriptorAddr(channel, 0);
//    }
//    
//    if(pip){
//        #if defined(AT91C_SRC_PIP)
//        // If source picture-in-picture mode is enabled, program the DMAC_SPIP.
//        if(pip->pipSourceBoundarySize){
//        // If destination picture-in-picture mode is enabled, program the DMAC_DPIP.
//            DMA_SPIPconfiguration(channel, pip->pipSourceHoleSize, pip->pipSourceBoundarySize);
//        }
//        #endif
//
//        #if defined(AT91C_DST_PIP)
//        if(pip->pipDestBoundarySize){
//            DMA_DPIPconfiguration(channel, pip->pipDestHoleSize, pip->pipDestBoundarySize);
//        }
//        #endif
//    }
//    return 0;
//}
//
////------------------------------------------------------------------------------
///// Configure the DMA transfer control infomation.
///// \param channel Particular channel number.
///// \param bufSize Buffer transfer size in byte.
///// \param sourceWidth Source transfer width.
///// \param destWidth Destination transfer width.
///// \param sourceAddress Destination transfer width.
///// \param destAddress Destination transfer width.
////------------------------------------------------------------------------------
//U8 DMAD_Configure_TransferController(U8 channel,
//                                      U32 bufSize,
//                                      U8 sourceWidth,
//                                      U8 destWidth,
//                                      U32 sourceAddress,
//                                      U32 destAddress)
//{
//    DmaTransfer *pTransfer = &(dmad.transfers[channel]);
//    // Check that no transfer is pending on the channel
//    if (pTransfer-> transferSize > 0 ) {
//        TRACE_ERR("DAM transfer is already pending\n\r");
//        return DMAD_ERROR_BUSY;
//    }
//    pTransfer->bufSize = bufSize; 
//    
//    // Set up the transfer width and transfer size.
//    DMA_SetSourceBufferSize(channel, bufSize, sourceWidth, destWidth, 0);
//
//    if(sourceAddress) {
//        // Write the starting source address.
//        DMA_SetSourceAddr(channel, sourceAddress);
//    }
//    if(destAddress){
//        // Write the starting destination address.
//        DMA_SetDestinationAddr(channel, destAddress);
//    }
//    return 0;
//}                                 
//                           
////------------------------------------------------------------------------------
///// Starts buffer transfer on the given channel
///// \param channel Particular channel number.
///// \param size Total transfer size in byte.
///// \param callback Optional callback function.
///// \param polling Polling channel status enable.
////------------------------------------------------------------------------------
//U8 DMAD_BufferTransfer(U8 channel, 
//                                  U32 size, 
//                                  DmaCallback callback, 
//                                  U8 polling)
//{
//    DmaTransfer *pTransfer = &(dmad.transfers[channel]);
//    // Check that no transfer is pending on the channel
//    if (pTransfer-> transferSize > 0 ) {
//        TRACE_ERR("DAM transfer is already pending\n\r");
//        return DMAD_ERROR_BUSY;
//    }
//    pTransfer->status = DMAD_ERROR_BUSY; 
//    pTransfer->transferSize = size;
//    pTransfer->callback = callback; 
//    
//    if(!polling){
//        DMA_EnableIt(0x1 << channel);
//    }
//    // Enable the channel.
//    DMA_EnableChannel(channel);
//    
//    if(polling){
//        while ((DMA_GetChannelStatus() & (0x1 << channel)) == (0x1 << channel));
//        if (pTransfer->callback) {
//            pTransfer->callback();
//        }
//        pTransfer->transferSize = 0;
//        DMA_DisableChannel(channel);
//    }
//    return 0;
//}
//
////------------------------------------------------------------------------------
///// Returns 1 if no transfer is currently pending on the given channel;
///// otherwise, returns 0.
///// \param channel  Channel number.
////------------------------------------------------------------------------------
//U8 DMAD_IsFinished(U8 channel)
//{
//    if (dmad.transfers[channel].transferSize > 0) {
//        return 0;
//    }
//    else {
//        DMA_DisableChannel(channel);
//        return 1;
//    }
//}

//------------------------------------------------------------------------------
/// Enables the clock of a peripheral. The peripheral ID (AT91C_ID_xxx) is used
/// to identify which peripheral is targetted.
/// Note that the ID must NOT be shifted (i.e. 1 << AT91C_ID_xxx).
/// \param id  Peripheral ID (AT91C_ID_xxx).
//------------------------------------------------------------------------------
void
PMC_PeriEn(U32 id)
{
	if(id > 31) return;

	if(!((rPMC_PCSR >> id) & 0x1))
	{
		rPMC_PCER = (0x1 << id);
	}
}

//------------------------------------------------------------------------------
/// Disables the clock of a peripheral. The peripheral ID (AT91C_ID_xxx) is used
/// to identify which peripheral is targetted.
/// Note that the ID must NOT be shifted (i.e. 1 << AT91C_ID_xxx).
/// \param id  Peripheral ID (AT91C_ID_xxx).
//------------------------------------------------------------------------------
void
PMC_PeriDis(U32 id)
{
	if(id > 31) return;
	
	if((rPMC_PCSR >> id) & 0x1)
	{
		rPMC_PCDR = (0x1 << id);
	}
}

/*
 * ------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------
 */
 
//------------------------------------------------------------------------------
/// Configures an interrupt in the AIC. The interrupt is identified by its
/// source (AT91C_ID_xxx) and is configured to use the specified mode and
/// interrupt handler function. Mode is the value that will be put in AIC_SMRx
/// and the function address will be set in AIC_SVRx.
/// The interrupt is disabled before configuration, so it is useless
/// to do it before calling this function. When AIC_ConfigureIT returns, the
/// interrupt will always be disabled and cleared; it must be enabled by a
/// call to AIC_EnableIT().
/// \param source  Interrupt source to configure.
/// \param mode  Triggering mode and priority of the interrupt.
/// \param handler  Interrupt handler function.
//------------------------------------------------------------------------------
void
IRQ_PeriConf(U32 id, U32 mode, void( *handler )( void ))
{
	if(id > 31) return;
	rAIC_IDCR = (0x1 << id);
	rAIC_SMR(id) = mode;
	rAIC_SVR(id) = (U32) handler;
	rAIC_ICCR = (0x1 << id);
}

//------------------------------------------------------------------------------
/// Enables interrupts coming from the given (unique) source (AT91C_ID_xxx).
/// \param source  Interrupt source to enable.
//------------------------------------------------------------------------------
void
IRQ_PeriEn(U32 id)
{
	if(id > 31) return;
	rAIC_IECR = (0x1 << id);
}

//------------------------------------------------------------------------------
/// Disables interrupts coming from the given (unique) source (AT91C_ID_xxx).
/// \param source  Interrupt source to enable.
//------------------------------------------------------------------------------
void
IRQ_PeriDis(U32 id)
{
	if(id > 31) return;
	rAIC_IDCR = (0x1 << id);
}

//------------------------------------------------------------------------------
///
///
///
//------------------------------------------------------------------------------
void
ResetOut(BOOL reset)
{
	if(reset) rPIOA_CODR = (1<<29);
	else rPIOA_SODR = (1<<29);
}

//------------------------------------------------------------------------------
///
///
///
//------------------------------------------------------------------------------
void
SFR_WR32(U32 ioaddr, U32 data)
{
	*((volatile U32 *)(ioaddr)) = data;
}

//------------------------------------------------------------------------------
///
///
///
//------------------------------------------------------------------------------
U32
SFR_RD32(U32 ioaddr)
{
	return *((volatile U32 *)(ioaddr));
}

//------------------------------------------------------------------------------
///
///
///
//------------------------------------------------------------------------------
void
SFR_WR16(U32 ioaddr, U16 data)
{
	*((volatile U16 *)(ioaddr)) = data;
}

//------------------------------------------------------------------------------
///
///
///
//------------------------------------------------------------------------------
U16
SFR_RD16(U32 ioaddr)
{
	return *((volatile U16 *)(ioaddr));
}

//------------------------------------------------------------------------------
///
///
///
//------------------------------------------------------------------------------
void
SFR_WR8(U32 ioaddr, U8 data)
{
	*((volatile U8 *)(ioaddr)) = data;
}

//------------------------------------------------------------------------------
///
///
///
//------------------------------------------------------------------------------
U8
SFR_RD8(U32 ioaddr)
{
	return *((volatile U8 *)(ioaddr));
}
