/*
 *------------------------------------------------------------------------------
 *
 *------------------------------------------------------------------------------
 */

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

//------------------------------------------------------------------------------
//         Global definitions
//------------------------------------------------------------------------------
/// DMA driver is currently busy.
#define DMAD_ERROR_BUSY              1
/// Using the default interrupt handler of the DMAD
#define DMAD_USE_DEFAULT_IT          1
#define DMAD_NO_DEFAULT_IT           0

//------------------------------------------------------------------------------
//         Types
//------------------------------------------------------------------------------

/// DMA driver callback function.
typedef void (*DmaCallback)();

//------------------------------------------------------------------------------
/// DMA multi buffer transfer Linker List Item structure.
//------------------------------------------------------------------------------
typedef struct _DmaLinkList {
    /// Source address.
    U32 sourceAddress;
    /// Destination address.
    U32 destAddress;
    /// Control A value.
    U32 controlA;
    /// Control B value.
    U32 controlB;
    /// Descriptor Address.
    U32 descriptor;
} DmaLinkList;

//------------------------------------------------------------------------------
/// DMA picture-in-picture mode configuration structure. 
//------------------------------------------------------------------------------
typedef struct _PictureInPicture {
    /// Size in byte add to the source address in PIP.
    U16 pipSourceHoleSize;
    /// Number of transfer in byte to perform before the source address increase.
    U16 pipSourceBoundarySize;
    /// Size in byte add to the destination address in PIP.
    U16 pipDestHoleSize;
    /// Number of transfer in byte to perform before the destination address increase.
    U16 pipDestBoundarySize;
} PictureInPicture;


//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------
void DMAD_Initialize(U8 channel, U8 defaultHandler);
U8 DMAD_Configure_Buffer(U8 channel, U8 sourceTransferMode, U8 destTransferMode, DmaLinkList *lli, PictureInPicture *pip);
U8 DMAD_Configure_TransferController(U8 channel, U32 bufSize, U8 sourceWidth, U8 destWidth, U32 sourceAddress, U32 destAddress);                
U8 DMAD_BufferTransfer(U8 channel, U32 size, DmaCallback callback, U8 polling);
U8 DMAD_IsFinished(U8 channel);

void PMC_PeriEn(U32 id);
void PMC_PeriDis(U32 id);
void IRQ_PeriConf(U32 id, U32 mode, void( *handler )( void ));
void IRQ_PeriEn(U32 id);
void IRQ_PeriDis(U32 id);

void ResetOut(BOOL reset);
void SFR_WR32(U32 ioaddr, U32 data);
U32 SFR_RD32(U32 ioaddr);
void SFR_WR16(U32 ioaddr, U16 data);
U16 SFR_RD16(U32 ioaddr);
void SFR_WR8(U32 ioaddr, U8 data);
U8 SFR_RD8(U32 ioaddr);

#endif /* __SYSTEM_H__ */
