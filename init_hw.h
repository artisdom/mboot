#ifndef __INIT_HW_H__
#define __INIT_HW_H__

#define PERIF_ID_FIQ    ( 0) // Advanced Interrupt Controller (FIQ)
#define PERIF_ID_SYS    ( 1) // System Controller
#define PERIF_ID_PIOA   ( 2) // Parallel IO Controller A
#define PERIF_ID_PIOB   ( 3) // Parallel IO Controller B
#define PERIF_ID_PIOC   ( 4) // Parallel IO Controller C
#define PERIF_ID_PIOD_E ( 5) // Parallel IO Controller D and E
#define PERIF_ID_TRNG   ( 6) // True Random Number Generator
#define PERIF_ID_US0    ( 7) // USART 0
#define PERIF_ID_US1    ( 8) // USART 1
#define PERIF_ID_US2    ( 9) // USART 2
#define PERIF_ID_US3    (10) // USART 2
#define PERIF_ID_MCI0   (11) // Multimedia Card Interface 0
#define PERIF_ID_TWI0   (12) // TWI 0
#define PERIF_ID_TWI1   (13) // TWI 1
#define PERIF_ID_SPI0   (14) // Serial Peripheral Interface
#define PERIF_ID_SPI1   (15) // Serial Peripheral Interface
#define PERIF_ID_SSC0   (16) // Serial Synchronous Controller 0
#define PERIF_ID_SSC1   (17) // Serial Synchronous Controller 1
#define PERIF_ID_TC     (18) // Timer Counter 0, 1, 2, 3, 4, 5
#define PERIF_ID_PWMC   (19) // Pulse Width Modulation Controller
#define PERIF_ID_TSADC  (20) // Touch Screen Controller
#define PERIF_ID_HDMA   (21) // HDMA
#define PERIF_ID_UHPHS  (22) // USB Host High Speed
#define PERIF_ID_LCDC   (23) // LCD Controller
#define PERIF_ID_AC97C  (24) // AC97 Controller
#define PERIF_ID_EMAC   (25) // Ethernet MAC
#define PERIF_ID_ISI    (26) // Image Sensor Interface
#define PERIF_ID_UDPHS  (27) // USB Device HS

#define PERIF_ID_MCI1   (29) // Multimedia Card Interface 1
#define PERIF_ID_VDEC   (30) // Video Decoder
#define PERIF_ID_IRQ0   (31) // Advanced Interrupt Controller (IRQ0)

void InitHW(void);

#endif /* __INIT_HW_H__ */
