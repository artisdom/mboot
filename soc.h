/*
 *------------------------------------------------------------------------------
 *
 *------------------------------------------------------------------------------
 */

#ifndef __SOC_H__
#define __SOC_H__

#define BOARD_MAINOSC	12000000
#define BOARD_MCK		((unsigned long)((BOARD_MAINOSC / 3 / 2 / 3) * 200 )) // 133MHz

#define rWDT_SR			(*(volatile U32 *)(0xFFFFFD44))
#define rSHDW_MR		(*(volatile U32 *)(0xFFFFFD14))
#define rSYS_RSTC		(*(volatile U32 *)(0xFFFFFD08))
#define rSCKCR			(*(volatile U32 *)(0xFFFFFD50))

#define rCKGR_MOR		(*(volatile U32 *)(0xFFFFFC20))
#define rCKGR_PLLAR		(*(volatile U32 *)(0xFFFFFC28))
#define rCKGR_UCKR		(*(volatile U32 *)(0xFFFFFC1C))

#define rPMC_MCKR		(*(volatile U32 *)(0xFFFFFC30))
#define rPMC_PLLICPR	(*(volatile U32 *)(0xFFFFFC80))
#define rPMC_SR			(*(volatile U32 *)(0xFFFFFC68))
#define rPMC_SCER		(*(volatile U32 *)(0xFFFFFC00))
#define rPMC_SCDR		(*(volatile U32 *)(0xFFFFFC04))
#define rPMC_SCSR		(*(volatile U32 *)(0xFFFFFC08))
#define rPMC_USB		(*(volatile U32 *)(0xFFFFFC38))
#define rPMC_PCER		(*(volatile U32 *)(0xFFFFFC10))
#define rPMC_PCDR		(*(volatile U32 *)(0xFFFFFC14))
#define rPMC_PCSR		(*(volatile U32 *)(0xFFFFFC18))
#define rPMC_PCK0		(*(volatile U32 *)(0xFFFFFC40))
#define rPMC_PCK1		(*(volatile U32 *)(0xFFFFFC44))

#define rAIC_SMR(id)	(*(volatile U32 *)(0xFFFFF000+id*0x4))
#define rAIC_SVR(id)	(*(volatile U32 *)(0xFFFFF000+id*0x4+0x80))
#define rAIC_IECR		(*(volatile U32 *)(0xFFFFF120))
#define rAIC_IDCR		(*(volatile U32 *)(0xFFFFF124))
#define rAIC_ICCR		(*(volatile U32 *)(0xFFFFF128))
#define rAIC_EOICR		(*(volatile U32 *)(0xFFFFF130))
#define rAIC_SPU		(*(volatile U32 *)(0xFFFFF134))

#define rRTT_MR			(*(volatile U32 *)(0xFFFFFD20)) // Mode Register Read-write 0x0000_8000
#define rRTT_AR			(*(volatile U32 *)(0xFFFFFD24)) // Alarm Register Read-write 0xFFFF_FFFF
#define rRTT_VR			(*(volatile U32 *)(0xFFFFFD28)) // Value Register Read-only 0x0000_0000
#define rRTT_SR			(*(volatile U32 *)(0xFFFFFD2C)) // Status Register Read-only 0x0000_0000

#define rPIT_MR			(*(volatile U32 *)(0xFFFFFD30)) // Mode Register Read-write 0x000F_FFFF
#define rPIT_SR			(*(volatile U32 *)(0xFFFFFD34)) // Status Register Read-only 0x0000_0000
#define rPIT_PIVR		(*(volatile U32 *)(0xFFFFFD38)) // Periodic Interval Value Register Read-only 0x0000_0000
#define rPIT_PIIR		(*(volatile U32 *)(0xFFFFFD3C)) // Periodic Interval Image Register Read-only 0x0000_0000

#define rMATRIX_MCFG0	(*(volatile U32 *)(0xFFFFEA00)) // Master Configuration Register 0  Read-write 0x00000001
#define rMATRIX_MCFG1	(*(volatile U32 *)(0xFFFFEA04)) // Master Configuration Register 1 Read-write 0x00000000
#define rMATRIX_MCFG2	(*(volatile U32 *)(0xFFFFEA08)) // Master Configuration Register 2 Read-write 0x00000000
#define rMATRIX_MCFG3	(*(volatile U32 *)(0xFFFFEA0C)) // Master Configuration Register 3 Read-write 0x00000000
#define rMATRIX_MCFG4	(*(volatile U32 *)(0xFFFFEA10)) // Master Configuration Register 4 Read-write 0x00000000
#define rMATRIX_MCFG5	(*(volatile U32 *)(0xFFFFEA14)) // Master Configuration Register 5 Read-write 0x00000000
#define rMATRIX_MCFG6	(*(volatile U32 *)(0xFFFFEA18)) // Master Configuration Register 6 Read-write 0x00000000
#define rMATRIX_MCFG7	(*(volatile U32 *)(0xFFFFEA1C)) // Master Configuration Register 7 Read-write 0x00000000
#define rMATRIX_MCFG8	(*(volatile U32 *)(0xFFFFEA20)) // Master Configuration Register 8 Read-write 0x00000000
#define rMATRIX_MCFG9	(*(volatile U32 *)(0xFFFFEA24)) // Master Configuration Register 9 Read-write 0x00000000
#define rMATRIX_MCFG10	(*(volatile U32 *)(0xFFFFEA28)) // Master Configuration Register 10 Read-write 0x00000000
#define rMATRIX_MCFG11	(*(volatile U32 *)(0xFFFFEA2C)) // Master Configuration Register 11 Read-write 0x00000000
#define rMATRIX_SCFG0	(*(volatile U32 *)(0xFFFFEA40)) // Slave Configuration Register 0 Read-write 0x000001FF
#define rMATRIX_SCFG1	(*(volatile U32 *)(0xFFFFEA44)) // Slave Configuration Register 1 Read-write 0x000001FF
#define rMATRIX_SCFG2	(*(volatile U32 *)(0xFFFFEA48)) // Slave Configuration Register 2 Read-write 0x000001FF
#define rMATRIX_SCFG3	(*(volatile U32 *)(0xFFFFEA4C)) // Slave Configuration Register 3 Read-write 0x000001FF
#define rMATRIX_SCFG4	(*(volatile U32 *)(0xFFFFEA50)) // Slave Configuration Register 4 Read-write 0x000001FF
#define rMATRIX_SCFG5	(*(volatile U32 *)(0xFFFFEA54)) // Slave Configuration Register 5 Read-write 0x000001FF
#define rMATRIX_SCFG6	(*(volatile U32 *)(0xFFFFEA58)) // Slave Configuration Register 6 Read-write 0x000001FF
#define rMATRIX_SCFG7	(*(volatile U32 *)(0xFFFFEA5C)) // Slave Configuration Register 7 Read-write 0x000001FF
#define rMATRIX_PRAS0	(*(volatile U32 *)(0xFFFFEA80)) // Priority Register A for Slave 0 Read-write 0x00000000
#define rMATRIX_PRBS0	(*(volatile U32 *)(0xFFFFEA84)) // Priority Register B for Slave 0 Read-write 0x00000000
#define rMATRIX_PRAS1	(*(volatile U32 *)(0xFFFFEA88)) // Priority Register A for Slave 1 Read-write 0x00000000
#define rMATRIX_PRBS1	(*(volatile U32 *)(0xFFFFEA8C)) // Priority Register B for Slave 1 Read-write 0x00000000
#define rMATRIX_PRAS2	(*(volatile U32 *)(0xFFFFEA90)) // Priority Register A for Slave 2 Read-write 0x00000000
#define rMATRIX_PRBS2	(*(volatile U32 *)(0xFFFFEA94)) // Priority Register B for Slave 2 Read-write 0x00000000
#define rMATRIX_PRAS3	(*(volatile U32 *)(0xFFFFEA98)) // Priority Register A for Slave 3 Read-write 0x00000000
#define rMATRIX_PRBS3	(*(volatile U32 *)(0xFFFFEA9C)) // Priority Register B for Slave 3 Read-write 0x00000000
#define rMATRIX_PRAS4	(*(volatile U32 *)(0xFFFFEAA0)) // Priority Register A for Slave 4 Read-write 0x00000000
#define rMATRIX_PRBS4	(*(volatile U32 *)(0xFFFFEAA4)) // Priority Register B for Slave 4 Read-write 0x00000000
#define rMATRIX_PRAS5	(*(volatile U32 *)(0xFFFFEAA8)) // Priority Register A for Slave 5 Read-write 0x00000000
#define rMATRIX_PRBS5	(*(volatile U32 *)(0xFFFFEAAC)) // Priority Register B for Slave 5 Read-write 0x00000000
#define rMATRIX_PRAS6	(*(volatile U32 *)(0xFFFFEAB0)) // Priority Register A for Slave 6 Read-write 0x00000000
#define rMATRIX_PRBS6	(*(volatile U32 *)(0xFFFFEAB4)) // Priority Register B for Slave 6 Read-write 0x00000000
#define rMATRIX_PRAS7	(*(volatile U32 *)(0xFFFFEAB8)) // Priority Register A for Slave 7 Read-write 0x00000000
#define rMATRIX_PRBS7	(*(volatile U32 *)(0xFFFFEABC)) // Priority Register B for Slave 7 Read-write 0x00000000
#define rMATRIX_MRCR	(*(volatile U32 *)(0xFFFFEB00)) // Master Remap Control Register Read-write 0x00000000
#define rMATRIX_WPMR	(*(volatile U32 *)(0xFFFFEBE4)) // Write Protect Mode Register Read-write 0x00000000
#define rMATRIX_WPSR	(*(volatile U32 *)(0xFFFFEBE8)) // Write Protect Status Register Read-only 0x00000000

#define rDMAC_GCFG		(*(volatile U32 *)(0xFFFFEC00))
#define rDMAC_EN		(*(volatile U32 *)(0xFFFFEC04))
#define rDMAC_SREQ		(*(volatile U32 *)(0xFFFFEC08))
#define rDMAC_CREQ		(*(volatile U32 *)(0xFFFFEC0C))
#define rDMAC_LAST		(*(volatile U32 *)(0xFFFFEC10))
#define rDMAC_EBCIER	(*(volatile U32 *)(0xFFFFEC18))
#define rDMAC_EBCIDR	(*(volatile U32 *)(0xFFFFEC1C))
#define rDMAC_EBCIMR	(*(volatile U32 *)(0xFFFFEC20))
#define rDMAC_EBCISR	(*(volatile U32 *)(0xFFFFEC24))
#define rDMAC_CHER		(*(volatile U32 *)(0xFFFFEC28))
#define rDMAC_CHDR		(*(volatile U32 *)(0xFFFFEC2C))
#define rDMAC_CHSR		(*(volatile U32 *)(0xFFFFEC30))
#define rDMAC_SADDR(ch)	(*(volatile U32 *)(0xFFFFEC3C+ch*(0x28)+(0x0)))
#define rDMAC_DADDR(ch)	(*(volatile U32 *)(0xFFFFEC3C+ch*(0x28)+(0x4)))
#define rDMAC_DSCR(ch)	(*(volatile U32 *)(0xFFFFEC3C+ch*(0x28)+(0x8)))
#define rDMAC_CTRLA(ch)	(*(volatile U32 *)(0xFFFFEC3C+ch*(0x28)+(0xC)))
#define rDMAC_CTRLB(ch)	(*(volatile U32 *)(0xFFFFEC3C+ch*(0x28)+(0x10)))
#define rDMAC_CFG(ch)	(*(volatile U32 *)(0xFFFFEC3C+ch*(0x28)+(0x14)))
#define rDMAC_SPIP(ch)	(*(volatile U32 *)(0xFFFFEC3C+ch*(0x28)+(0x18)))
#define rDMAC_DPIP(ch)	(*(volatile U32 *)(0xFFFFEC3C+ch*(0x28)+(0x1C)))

#define rPIOA_PER		(*(volatile U32 *)(0xFFFFF200)) // PIO Enable Register Write-only
#define rPIOA_PDR		(*(volatile U32 *)(0xFFFFF204)) // PIO Disable Register Write-only
#define rPIOA_PSR		(*(volatile U32 *)(0xFFFFF208)) // PIO Status Register Read-only
#define rPIOA_OER		(*(volatile U32 *)(0xFFFFF210)) // Output Enable Register Write-only
#define rPIOA_ODR		(*(volatile U32 *)(0xFFFFF214)) // Output Disable Register Write-only
#define rPIOA_OSR		(*(volatile U32 *)(0xFFFFF218)) // Output Status Register Read-only 0x00000000
#define rPIOA_IFER		(*(volatile U32 *)(0xFFFFF220)) // Glitch Input Filter Enable Register Write-only
#define rPIOA_IFDR		(*(volatile U32 *)(0xFFFFF224)) // Glitch Input Filter Disable Register Write-only
#define rPIOA_IFSR		(*(volatile U32 *)(0xFFFFF228)) // Glitch Input Filter Status Register Read-only 0x00000000
#define rPIOA_SODR		(*(volatile U32 *)(0xFFFFF230)) // Set Output Data Register Write-only
#define rPIOA_CODR		(*(volatile U32 *)(0xFFFFF234)) // Clear Output Data Register Write-only
#define rPIOA_ODSR		(*(volatile U32 *)(0xFFFFF238)) // Output Data Status Register 
#define rPIOA_PDSR		(*(volatile U32 *)(0xFFFFF23C)) // Pin Data Status Register Read-only
#define rPIOA_IER		(*(volatile U32 *)(0xFFFFF240)) // Interrupt Enable Register Write-only
#define rPIOA_IDR		(*(volatile U32 *)(0xFFFFF244)) // Interrupt Disable Register Write-only
#define rPIOA_IMR		(*(volatile U32 *)(0xFFFFF248)) // Interrupt Mask Register  Read-only 0x00000000
#define rPIOA_ISR		(*(volatile U32 *)(0xFFFFF24C)) // Interrupt Status Register Read-only 0x00000000
#define rPIOA_MDER		(*(volatile U32 *)(0xFFFFF250)) // Multi-driver Enable Register Write-only
#define rPIOA_MDDR		(*(volatile U32 *)(0xFFFFF254)) // Multi-driver Disable Register Write-only
#define rPIOA_MDSR		(*(volatile U32 *)(0xFFFFF258)) // Multi-driver Status Register Read-only 0x00000000
#define rPIOA_PUDR		(*(volatile U32 *)(0xFFFFF260)) // Pull-up Disable Register Write-only
#define rPIOA_PUER		(*(volatile U32 *)(0xFFFFF264)) // Pull-up Enable Register Write-only
#define rPIOA_PUSR		(*(volatile U32 *)(0xFFFFF268)) // Pad Pull-up Status Register Read-only 0x00000000
#define rPIOA_ASR		(*(volatile U32 *)(0xFFFFF270)) // Peripheral A Select Register Write-only
#define rPIOA_BSR		(*(volatile U32 *)(0xFFFFF274)) // Peripheral B Select Register Write-only
#define rPIOA_ABSR		(*(volatile U32 *)(0xFFFFF278)) // AB Status Register Read-only 0x00000000
#define rPIOA_OWER		(*(volatile U32 *)(0xFFFFF2A0)) // Output Write Enable Write-only
#define rPIOA_OWDR		(*(volatile U32 *)(0xFFFFF2A4)) // Output Write Disable Write-only
#define rPIOA_OWSR		(*(volatile U32 *)(0xFFFFF2A8)) // Output Write Status Register Read-only 0x00000000
#define rPIOA_DELAYR0	(*(volatile U32 *)(0xFFFFF2C0)) // I/O Delay Register 0 Read/Write 0x00000000
#define rPIOA_DELAYR1	(*(volatile U32 *)(0xFFFFF2C4)) // I/O Delay Register 1 Read/Write 0x00000000
#define rPIOA_DELAYR2	(*(volatile U32 *)(0xFFFFF2C8)) // I/O Delay Register 2 Read/Write 0x00000000
#define rPIOA_DELAYR3	(*(volatile U32 *)(0xFFFFF2CC)) // I/O Delay Register 3 Read/Write 0x00000000
#define rPIOA_WPMR		(*(volatile U32 *)(0xFFFFF2E4)) // Write Protect Mode Register  Read-write 0x00000000
#define rPIOA_WPSR		(*(volatile U32 *)(0xFFFFF2E8)) // Write Protect Status Register 

#define rPIOB_PER		(*(volatile U32 *)(0xFFFFF400)) // PIO Enable Register Write-only
#define rPIOB_PDR		(*(volatile U32 *)(0xFFFFF404)) // PIO Disable Register Write-only
#define rPIOB_PSR		(*(volatile U32 *)(0xFFFFF408)) // PIO Status Register Read-only
#define rPIOB_OER		(*(volatile U32 *)(0xFFFFF410)) // Output Enable Register Write-only
#define rPIOB_ODR		(*(volatile U32 *)(0xFFFFF414)) // Output Disable Register Write-only
#define rPIOB_OSR		(*(volatile U32 *)(0xFFFFF418)) // Output Status Register Read-only 0x00000000
#define rPIOB_IFER		(*(volatile U32 *)(0xFFFFF420)) // Glitch Input Filter Enable Register Write-only
#define rPIOB_IFDR		(*(volatile U32 *)(0xFFFFF424)) // Glitch Input Filter Disable Register Write-only
#define rPIOB_IFSR		(*(volatile U32 *)(0xFFFFF428)) // Glitch Input Filter Status Register Read-only 0x00000000
#define rPIOB_SODR		(*(volatile U32 *)(0xFFFFF430)) // Set Output Data Register Write-only
#define rPIOB_CODR		(*(volatile U32 *)(0xFFFFF434)) // Clear Output Data Register Write-only
#define rPIOB_ODSR		(*(volatile U32 *)(0xFFFFF438)) // Output Data Status Register 
#define rPIOB_PDSR		(*(volatile U32 *)(0xFFFFF43C)) // Pin Data Status Register Read-only
#define rPIOB_IER		(*(volatile U32 *)(0xFFFFF440)) // Interrupt Enable Register Write-only
#define rPIOB_IDR		(*(volatile U32 *)(0xFFFFF444)) // Interrupt Disable Register Write-only
#define rPIOB_IMR		(*(volatile U32 *)(0xFFFFF448)) // Interrupt Mask Register  Read-only 0x00000000
#define rPIOB_ISR		(*(volatile U32 *)(0xFFFFF44C)) // Interrupt Status Register Read-only 0x00000000
#define rPIOB_MDER		(*(volatile U32 *)(0xFFFFF450)) // Multi-driver Enable Register Write-only
#define rPIOB_MDDR		(*(volatile U32 *)(0xFFFFF454)) // Multi-driver Disable Register Write-only
#define rPIOB_MDSR		(*(volatile U32 *)(0xFFFFF458)) // Multi-driver Status Register Read-only 0x00000000
#define rPIOB_PUDR		(*(volatile U32 *)(0xFFFFF460)) // Pull-up Disable Register Write-only
#define rPIOB_PUER		(*(volatile U32 *)(0xFFFFF464)) // Pull-up Enable Register Write-only
#define rPIOB_PUSR		(*(volatile U32 *)(0xFFFFF468)) // Pad Pull-up Status Register Read-only 0x00000000
#define rPIOB_ASR		(*(volatile U32 *)(0xFFFFF470)) // Peripheral A Select Register Write-only
#define rPIOB_BSR		(*(volatile U32 *)(0xFFFFF474)) // Peripheral B Select Register Write-only
#define rPIOB_ABSR		(*(volatile U32 *)(0xFFFFF478)) // AB Status Register Read-only 0x00000000
#define rPIOB_OWER		(*(volatile U32 *)(0xFFFFF4A0)) // Output Write Enable Write-only
#define rPIOB_OWDR		(*(volatile U32 *)(0xFFFFF4A4)) // Output Write Disable Write-only
#define rPIOB_OWSR		(*(volatile U32 *)(0xFFFFF4A8)) // Output Write Status Register Read-only 0x00000000
#define rPIOB_DELAYR0	(*(volatile U32 *)(0xFFFFF4C0)) // I/O Delay Register 0 Read/Write 0x00000000
#define rPIOB_DELAYR1	(*(volatile U32 *)(0xFFFFF4C4)) // I/O Delay Register 1 Read/Write 0x00000000
#define rPIOB_DELAYR2	(*(volatile U32 *)(0xFFFFF4C8)) // I/O Delay Register 2 Read/Write 0x00000000
#define rPIOB_DELAYR3	(*(volatile U32 *)(0xFFFFF4CC)) // I/O Delay Register 3 Read/Write 0x00000000
#define rPIOB_WPMR		(*(volatile U32 *)(0xFFFFF4E4)) // Write Protect Mode Register  Read-write 0x00000000
#define rPIOB_WPSR		(*(volatile U32 *)(0xFFFFF4E8)) // Write Protect Status Register 

#define rPIOC_PER		(*(volatile U32 *)(0xFFFFF600)) // PIO Enable Register Write-only
#define rPIOC_PDR		(*(volatile U32 *)(0xFFFFF604)) // PIO Disable Register Write-only
#define rPIOC_PSR		(*(volatile U32 *)(0xFFFFF608)) // PIO Status Register Read-only
#define rPIOC_OER		(*(volatile U32 *)(0xFFFFF610)) // Output Enable Register Write-only
#define rPIOC_ODR		(*(volatile U32 *)(0xFFFFF614)) // Output Disable Register Write-only
#define rPIOC_OSR		(*(volatile U32 *)(0xFFFFF618)) // Output Status Register Read-only 0x00000000
#define rPIOC_IFER		(*(volatile U32 *)(0xFFFFF620)) // Glitch Input Filter Enable Register Write-only
#define rPIOC_IFDR		(*(volatile U32 *)(0xFFFFF624)) // Glitch Input Filter Disable Register Write-only
#define rPIOC_IFSR		(*(volatile U32 *)(0xFFFFF628)) // Glitch Input Filter Status Register Read-only 0x00000000
#define rPIOC_SODR		(*(volatile U32 *)(0xFFFFF630)) // Set Output Data Register Write-only
#define rPIOC_CODR		(*(volatile U32 *)(0xFFFFF634)) // Clear Output Data Register Write-only
#define rPIOC_ODSR		(*(volatile U32 *)(0xFFFFF638)) // Output Data Status Register 
#define rPIOC_PDSR		(*(volatile U32 *)(0xFFFFF63C)) // Pin Data Status Register Read-only
#define rPIOC_IER		(*(volatile U32 *)(0xFFFFF640)) // Interrupt Enable Register Write-only
#define rPIOC_IDR		(*(volatile U32 *)(0xFFFFF644)) // Interrupt Disable Register Write-only
#define rPIOC_IMR		(*(volatile U32 *)(0xFFFFF648)) // Interrupt Mask Register  Read-only 0x00000000
#define rPIOC_ISR		(*(volatile U32 *)(0xFFFFF64C)) // Interrupt Status Register Read-only 0x00000000
#define rPIOC_MDER		(*(volatile U32 *)(0xFFFFF650)) // Multi-driver Enable Register Write-only
#define rPIOC_MDDR		(*(volatile U32 *)(0xFFFFF654)) // Multi-driver Disable Register Write-only
#define rPIOC_MDSR		(*(volatile U32 *)(0xFFFFF658)) // Multi-driver Status Register Read-only 0x00000000
#define rPIOC_PUDR		(*(volatile U32 *)(0xFFFFF660)) // Pull-up Disable Register Write-only
#define rPIOC_PUER		(*(volatile U32 *)(0xFFFFF664)) // Pull-up Enable Register Write-only
#define rPIOC_PUSR		(*(volatile U32 *)(0xFFFFF668)) // Pad Pull-up Status Register Read-only 0x00000000
#define rPIOC_ASR		(*(volatile U32 *)(0xFFFFF670)) // Peripheral A Select Register Write-only
#define rPIOC_BSR		(*(volatile U32 *)(0xFFFFF674)) // Peripheral B Select Register Write-only
#define rPIOC_ABSR		(*(volatile U32 *)(0xFFFFF678)) // AB Status Register Read-only 0x00000000
#define rPIOC_OWER		(*(volatile U32 *)(0xFFFFF6A0)) // Output Write Enable Write-only
#define rPIOC_OWDR		(*(volatile U32 *)(0xFFFFF6A4)) // Output Write Disable Write-only
#define rPIOC_OWSR		(*(volatile U32 *)(0xFFFFF6A8)) // Output Write Status Register Read-only 0x00000000
#define rPIOC_DELAYR0	(*(volatile U32 *)(0xFFFFF6C0)) // I/O Delay Register 0 Read/Write 0x00000000
#define rPIOC_DELAYR1	(*(volatile U32 *)(0xFFFFF6C4)) // I/O Delay Register 1 Read/Write 0x00000000
#define rPIOC_DELAYR2	(*(volatile U32 *)(0xFFFFF6C8)) // I/O Delay Register 2 Read/Write 0x00000000
#define rPIOC_DELAYR3	(*(volatile U32 *)(0xFFFFF6CC)) // I/O Delay Register 3 Read/Write 0x00000000
#define rPIOC_WPMR		(*(volatile U32 *)(0xFFFFF6E4)) // Write Protect Mode Register  Read-write 0x00000000
#define rPIOC_WPSR		(*(volatile U32 *)(0xFFFFF6E8)) // Write Protect Status Register 

#define rPIOD_PER		(*(volatile U32 *)(0xFFFFF800)) // PIO Enable Register Write-only
#define rPIOD_PDR		(*(volatile U32 *)(0xFFFFF804)) // PIO Disable Register Write-only
#define rPIOD_PSR		(*(volatile U32 *)(0xFFFFF808)) // PIO Status Register Read-only
#define rPIOD_OER		(*(volatile U32 *)(0xFFFFF810)) // Output Enable Register Write-only
#define rPIOD_ODR		(*(volatile U32 *)(0xFFFFF814)) // Output Disable Register Write-only
#define rPIOD_OSR		(*(volatile U32 *)(0xFFFFF818)) // Output Status Register Read-only 0x00000000
#define rPIOD_IFER		(*(volatile U32 *)(0xFFFFF820)) // Glitch Input Filter Enable Register Write-only
#define rPIOD_IFDR		(*(volatile U32 *)(0xFFFFF824)) // Glitch Input Filter Disable Register Write-only
#define rPIOD_IFSR		(*(volatile U32 *)(0xFFFFF828)) // Glitch Input Filter Status Register Read-only 0x00000000
#define rPIOD_SODR		(*(volatile U32 *)(0xFFFFF830)) // Set Output Data Register Write-only
#define rPIOD_CODR		(*(volatile U32 *)(0xFFFFF834)) // Clear Output Data Register Write-only
#define rPIOD_ODSR		(*(volatile U32 *)(0xFFFFF838)) // Output Data Status Register 
#define rPIOD_PDSR		(*(volatile U32 *)(0xFFFFF83C)) // Pin Data Status Register Read-only
#define rPIOD_IER		(*(volatile U32 *)(0xFFFFF840)) // Interrupt Enable Register Write-only
#define rPIOD_IDR		(*(volatile U32 *)(0xFFFFF844)) // Interrupt Disable Register Write-only
#define rPIOD_IMR		(*(volatile U32 *)(0xFFFFF848)) // Interrupt Mask Register  Read-only 0x00000000
#define rPIOD_ISR		(*(volatile U32 *)(0xFFFFF84C)) // Interrupt Status Register Read-only 0x00000000
#define rPIOD_MDER		(*(volatile U32 *)(0xFFFFF850)) // Multi-driver Enable Register Write-only
#define rPIOD_MDDR		(*(volatile U32 *)(0xFFFFF854)) // Multi-driver Disable Register Write-only
#define rPIOD_MDSR		(*(volatile U32 *)(0xFFFFF858)) // Multi-driver Status Register Read-only 0x00000000
#define rPIOD_PUDR		(*(volatile U32 *)(0xFFFFF860)) // Pull-up Disable Register Write-only
#define rPIOD_PUER		(*(volatile U32 *)(0xFFFFF864)) // Pull-up Enable Register Write-only
#define rPIOD_PUSR		(*(volatile U32 *)(0xFFFFF868)) // Pad Pull-up Status Register Read-only 0x00000000
#define rPIOD_ASR		(*(volatile U32 *)(0xFFFFF870)) // Peripheral A Select Register Write-only
#define rPIOD_BSR		(*(volatile U32 *)(0xFFFFF874)) // Peripheral B Select Register Write-only
#define rPIOD_ABSR		(*(volatile U32 *)(0xFFFFF878)) // AB Status Register Read-only 0x00000000
#define rPIOD_OWER		(*(volatile U32 *)(0xFFFFF8A0)) // Output Write Enable Write-only
#define rPIOD_OWDR		(*(volatile U32 *)(0xFFFFF8A4)) // Output Write Disable Write-only
#define rPIOD_OWSR		(*(volatile U32 *)(0xFFFFF8A8)) // Output Write Status Register Read-only 0x00000000
#define rPIOD_DELAYR0	(*(volatile U32 *)(0xFFFFF8C0)) // I/O Delay Register 0 Read/Write 0x00000000
#define rPIOD_DELAYR1	(*(volatile U32 *)(0xFFFFF8C4)) // I/O Delay Register 1 Read/Write 0x00000000
#define rPIOD_DELAYR2	(*(volatile U32 *)(0xFFFFF8C8)) // I/O Delay Register 2 Read/Write 0x00000000
#define rPIOD_DELAYR3	(*(volatile U32 *)(0xFFFFF8CC)) // I/O Delay Register 3 Read/Write 0x00000000
#define rPIOD_WPMR		(*(volatile U32 *)(0xFFFFF8E4)) // Write Protect Mode Register  Read-write 0x00000000
#define rPIOD_WPSR		(*(volatile U32 *)(0xFFFFF8E8)) // Write Protect Status Register 

#define rPIOE_PER		(*(volatile U32 *)(0xFFFFFA00)) // PIO Enable Register Write-only
#define rPIOE_PDR		(*(volatile U32 *)(0xFFFFFA04)) // PIO Disable Register Write-only
#define rPIOE_PSR		(*(volatile U32 *)(0xFFFFFA08)) // PIO Status Register Read-only
#define rPIOE_OER		(*(volatile U32 *)(0xFFFFFA10)) // Output Enable Register Write-only
#define rPIOE_ODR		(*(volatile U32 *)(0xFFFFFA14)) // Output Disable Register Write-only
#define rPIOE_OSR		(*(volatile U32 *)(0xFFFFFA18)) // Output Status Register Read-only 0x00000000
#define rPIOE_IFER		(*(volatile U32 *)(0xFFFFFA20)) // Glitch Input Filter Enable Register Write-only
#define rPIOE_IFDR		(*(volatile U32 *)(0xFFFFFA24)) // Glitch Input Filter Disable Register Write-only
#define rPIOE_IFSR		(*(volatile U32 *)(0xFFFFFA28)) // Glitch Input Filter Status Register Read-only 0x00000000
#define rPIOE_SODR		(*(volatile U32 *)(0xFFFFFA30)) // Set Output Data Register Write-only
#define rPIOE_CODR		(*(volatile U32 *)(0xFFFFFA34)) // Clear Output Data Register Write-only
#define rPIOE_ODSR		(*(volatile U32 *)(0xFFFFFA38)) // Output Data Status Register 
#define rPIOE_PDSR		(*(volatile U32 *)(0xFFFFFA3C)) // Pin Data Status Register Read-only
#define rPIOE_IER		(*(volatile U32 *)(0xFFFFFA40)) // Interrupt Enable Register Write-only
#define rPIOE_IDR		(*(volatile U32 *)(0xFFFFFA44)) // Interrupt Disable Register Write-only
#define rPIOE_IMR		(*(volatile U32 *)(0xFFFFFA48)) // Interrupt Mask Register  Read-only 0x00000000
#define rPIOE_ISR		(*(volatile U32 *)(0xFFFFFA4C)) // Interrupt Status Register Read-only 0x00000000
#define rPIOE_MDER		(*(volatile U32 *)(0xFFFFFA50)) // Multi-driver Enable Register Write-only
#define rPIOE_MDDR		(*(volatile U32 *)(0xFFFFFA54)) // Multi-driver Disable Register Write-only
#define rPIOE_MDSR		(*(volatile U32 *)(0xFFFFFA58)) // Multi-driver Status Register Read-only 0x00000000
#define rPIOE_PUDR		(*(volatile U32 *)(0xFFFFFA60)) // Pull-up Disable Register Write-only
#define rPIOE_PUER		(*(volatile U32 *)(0xFFFFFA64)) // Pull-up Enable Register Write-only
#define rPIOE_PUSR		(*(volatile U32 *)(0xFFFFFA68)) // Pad Pull-up Status Register Read-only 0x00000000
#define rPIOE_ASR		(*(volatile U32 *)(0xFFFFFA70)) // Peripheral A Select Register Write-only
#define rPIOE_BSR		(*(volatile U32 *)(0xFFFFFA74)) // Peripheral B Select Register Write-only
#define rPIOE_ABSR		(*(volatile U32 *)(0xFFFFFA78)) // AB Status Register Read-only 0x00000000
#define rPIOE_OWER		(*(volatile U32 *)(0xFFFFFAA0)) // Output Write Enable Write-only
#define rPIOE_OWDR		(*(volatile U32 *)(0xFFFFFAA4)) // Output Write Disable Write-only
#define rPIOE_OWSR		(*(volatile U32 *)(0xFFFFFAA8)) // Output Write Status Register Read-only 0x00000000
#define rPIOE_DELAYR0	(*(volatile U32 *)(0xFFFFFAC0)) // I/O Delay Register 0 Read/Write 0x00000000
#define rPIOE_DELAYR1	(*(volatile U32 *)(0xFFFFFAC4)) // I/O Delay Register 1 Read/Write 0x00000000
#define rPIOE_DELAYR2	(*(volatile U32 *)(0xFFFFFAC8)) // I/O Delay Register 2 Read/Write 0x00000000
#define rPIOE_DELAYR3	(*(volatile U32 *)(0xFFFFFACC)) // I/O Delay Register 3 Read/Write 0x00000000
#define rPIOE_WPMR		(*(volatile U32 *)(0xFFFFFAE4)) // Write Protect Mode Register  Read-write 0x00000000
#define rPIOE_WPSR		(*(volatile U32 *)(0xFFFFFAE8)) // Write Protect Status Register 

#define rDDRSDRC_MR		(*(volatile U32 *)(0xFFFFE600)) // DDRSDRC Mode Register Read-write 0x00000000
#define rDDRSDRC_RTR	(*(volatile U32 *)(0xFFFFE604)) // DDRSDRC Refresh Timer Register  Read-write 0x00000000
#define rDDRSDRC_CR		(*(volatile U32 *)(0xFFFFE608)) // DDRSDRC Configuration Register  Read-write 0x7024
#define rDDRSDRC_TPR0	(*(volatile U32 *)(0xFFFFE60C)) // DDRSDRC Timing Parameter 0 Register Read-write 0x20227225
#define rDDRSDRC_TPR1	(*(volatile U32 *)(0xFFFFE610)) // DDRSDRC Timing Parameter 1 Register Read-write 0x3c80808
#define rDDRSDRC_TPR2	(*(volatile U32 *)(0xFFFFE614)) // DDRSDRC Timing Parameter 2 Register Read-write 0x2062
#define rDDRSDRC_LPR	(*(volatile U32 *)(0xFFFFE61C)) // DDRSDRC Low-power Register Read-write 0x10000
#define rDDRSDRC_MD		(*(volatile U32 *)(0xFFFFE620)) // DDRSDRC Memory Device Register Read-write 0x10
#define rDDRSDRC_DLL	(*(volatile U32 *)(0xFFFFE624)) // DDRSDRC DLL Information Register Read-only 0x00000001
#define rDDRSDRC_HS		(*(volatile U32 *)(0xFFFFE62C)) // DDRSDRC High Speed Register Read-write 0x0
#define rDDRSDRC_DELAY1	(*(volatile U32 *)(0xFFFFE640)) // DDRSDRC Delay I/O Register Read-write 0x00000000
#define rDDRSDRC_DELAY2	(*(volatile U32 *)(0xFFFFE644)) // DDRSDRC Delay I/O Register Read-write 0x00000000
#define rDDRSDRC_DELAY3	(*(volatile U32 *)(0xFFFFE648)) // DDRSDRC Delay I/O Register Read-write 0x00000000
#define rDDRSDRC_DELAY4	(*(volatile U32 *)(0xFFFFE64C)) // DDRSDRC Delay I/O Register Read-write 0x00000000
#define rDDRSDRC_WPMR	(*(volatile U32 *)(0xFFFFE6E4)) // DDRSDRC Write Protect Mode Register Read-write 0x00000000
#define rDDRSDRC_WPSR	(*(volatile U32 *)(0xFFFFE6E8)) // DDRSDRC Write Protect Status Register
#define rDDRSD_BASE0	(*(volatile U32 *)(0x70000000)) // DDRSDRC Write Protect Status Register
#define rDDRSD_BASE1	(*(volatile U32 *)(0x72000000)) // DDRSDRC Write Protect Status Register
#define rDDRSD_BASE2	(*(volatile U32 *)(0x74000000)) // DDRSDRC Write Protect Status Register
#define rDDRSD_BASE3	(*(volatile U32 *)(0x76000000)) // DDRSDRC Write Protect Status Register

#define rDBGU_CR		(*(volatile U32 *)(0xFFFFEE00)) // Control Register Write-only
#define rDBGU_MR		(*(volatile U32 *)(0xFFFFEE04)) // Mode Register Read-write 0x0
#define rDBGU_IER		(*(volatile U32 *)(0xFFFFEE08)) // Interrupt Enable Register Write-only
#define rDBGU_IDR		(*(volatile U32 *)(0xFFFFEE0C)) // Interrupt Disable Register Write-only
#define rDBGU_IMR		(*(volatile U32 *)(0xFFFFEE10)) // Interrupt Mask Register Read-only 0x0
#define rDBGU_SR		(*(volatile U32 *)(0xFFFFEE14)) // Status Register Read-only
#define rDBGU_RHR		(*(volatile U32 *)(0xFFFFEE18)) // Receive Holding Register Read-only 0x0
#define rDBGU_THR		(*(volatile U32 *)(0xFFFFEE1C)) // Transmit Holding Register Write-only
#define rDBGU_BRGR		(*(volatile U32 *)(0xFFFFEE20)) // Baud Rate Generator Register Read-write 0x0
#define rDBGU_CIDR		(*(volatile U32 *)(0xFFFFEE40)) // Chip ID Register Read-only
#define rDBGU_EXID		(*(volatile U32 *)(0xFFFFEE44)) // Chip ID Extension Register  Read-only
#define rDBGU_FNR		(*(volatile U32 *)(0xFFFFEE48)) // Force NTRST Register Read-write 0x0
#define rDBGU_RPR		(*(volatile U32 *)(0xFFFFEF00)) // Receive Pointer Register
#define rDBGU_RCR		(*(volatile U32 *)(0xFFFFEF04)) // Receive Counter Register
#define rDBGU_TPR		(*(volatile U32 *)(0xFFFFEF08)) // Transmit Pointer Register
#define rDBGU_TCR		(*(volatile U32 *)(0xFFFFEF0C)) // Transmit Counter Register
#define rDBGU_RNPR		(*(volatile U32 *)(0xFFFFEF10)) // Receive Next Pointer Register
#define rDBGU_RNCR		(*(volatile U32 *)(0xFFFFEF14)) // Receive Next Counter Register
#define rDBGU_TNPR		(*(volatile U32 *)(0xFFFFEF18)) // Transmit Next Pointer Register
#define rDBGU_TNCR		(*(volatile U32 *)(0xFFFFEF1C)) // Transmit Next Counter Register
#define rDBGU_PTCR		(*(volatile U32 *)(0xFFFFEF20)) // PDC Transfer Control Register
#define rDBGU_PTSR		(*(volatile U32 *)(0xFFFFEF24))	// PDC Transfer Status Register

#define rUS_CR(ch)		(*(volatile U32 *)(0xFFF8C000+ch*0x4000+0x0000))
#define rUS_MR(ch)		(*(volatile U32 *)(0xFFF8C000+ch*0x4000+0x0004))
#define rUS_IER(ch)		(*(volatile U32 *)(0xFFF8C000+ch*0x4000+0x0008))
#define rUS_IDR(ch)		(*(volatile U32 *)(0xFFF8C000+ch*0x4000+0x000C))
#define rUS_IMR(ch)		(*(volatile U32 *)(0xFFF8C000+ch*0x4000+0x0010))
#define rUS_CSR(ch)		(*(volatile U32 *)(0xFFF8C000+ch*0x4000+0x0014))
#define rUS_RHR(ch)		(*(volatile U32 *)(0xFFF8C000+ch*0x4000+0x0018))
#define rUS_THR(ch)		(*(volatile U32 *)(0xFFF8C000+ch*0x4000+0x001C))
#define rUS_BRGR(ch)	(*(volatile U32 *)(0xFFF8C000+ch*0x4000+0x0020))
#define rUS_RTOR(ch)	(*(volatile U32 *)(0xFFF8C000+ch*0x4000+0x0024))
#define rUS_TTGR(ch)	(*(volatile U32 *)(0xFFF8C000+ch*0x4000+0x0028))
#define rUS_FIDI(ch)	(*(volatile U32 *)(0xFFF8C000+ch*0x4000+0x0040))
#define rUS_NER(ch)		(*(volatile U32 *)(0xFFF8C000+ch*0x4000+0x0044))
#define rUS_IF(ch)		(*(volatile U32 *)(0xFFF8C000+ch*0x4000+0x004C))
#define rUS_MAN(ch)		(*(volatile U32 *)(0xFFF8C000+ch*0x4000+0x0050))
#define rUS_LINMR(ch)	(*(volatile U32 *)(0xFFF8C000+ch*0x4000+0x0054))
#define rUS_LINIR(ch)	(*(volatile U32 *)(0xFFF8C000+ch*0x4000+0x0058))

#define rSPI_CR(ch)		(*(volatile U32 *)(0xFFFA4000+ch*0x4000+0x00)) // Control Register  Write-only ---
#define rSPI_MR(ch)		(*(volatile U32 *)(0xFFFA4000+ch*0x4000+0x04)) // Mode Register  Read-write 0x0
#define rSPI_RDR(ch)	(*(volatile U32 *)(0xFFFA4000+ch*0x4000+0x08)) // Receive Data Register  Read-only 0x0
#define rSPI_TDR(ch)	(*(volatile U32 *)(0xFFFA4000+ch*0x4000+0x0C)) // Transmit Data Register  Write-only ---
#define rSPI_SR(ch)		(*(volatile U32 *)(0xFFFA4000+ch*0x4000+0x10)) // Status Register  Read-only 
#define rSPI_IER(ch)	(*(volatile U32 *)(0xFFFA4000+ch*0x4000+0x14)) // Interrupt Enable Register  Write-only ---
#define rSPI_IDR(ch)	(*(volatile U32 *)(0xFFFA4000+ch*0x4000+0x18)) // Interrupt Disable Register  Write-only ---
#define rSPI_IMR(ch)	(*(volatile U32 *)(0xFFFA4000+ch*0x4000+0x1C)) // Interrupt Mask Register  Read-only 0x0
#define rSPI_CSR0(ch)	(*(volatile U32 *)(0xFFFA4000+ch*0x4000+0x30)) // Chip Select Register 0  Read-write 0x0
#define rSPI_RPR(ch)	(*(volatile U32 *)(0xFFFA4000+ch*0x4000+0x100)) // Receive Pointer Register
#define rSPI_RCR(ch)	(*(volatile U32 *)(0xFFFA4000+ch*0x4000+0x104)) // Receive Counter Register
#define rSPI_TPR(ch)	(*(volatile U32 *)(0xFFFA4000+ch*0x4000+0x108)) // Transmit Pointer Register
#define rSPI_TCR(ch)	(*(volatile U32 *)(0xFFFA4000+ch*0x4000+0x10C)) // Transmit Counter Register
#define rSPI_RNPR(ch)	(*(volatile U32 *)(0xFFFA4000+ch*0x4000+0x110)) // Receive Next Pointer Register
#define rSPI_RNCR(ch)	(*(volatile U32 *)(0xFFFA4000+ch*0x4000+0x114)) // Receive Next Counter Register
#define rSPI_TNPR(ch)	(*(volatile U32 *)(0xFFFA4000+ch*0x4000+0x118)) // Transmit Next Pointer Register
#define rSPI_TNCR(ch)	(*(volatile U32 *)(0xFFFA4000+ch*0x4000+0x11C)) // Transmit Next Counter Register
#define rSPI_PTCR(ch)	(*(volatile U32 *)(0xFFFA4000+ch*0x4000+0x120)) // PDC Transfer Control Register
#define rSPI_PTSR(ch)	(*(volatile U32 *)(0xFFFA4000+ch*0x4000+0x124))	// PDC Transfer Status Register

#define rHSMCI_CR(ch)		(*(volatile U32 *)(0xFFF80000+ch*50000+0x00)) // Control Register 
#define rHSMCI_MR(ch)		(*(volatile U32 *)(0xFFF80000+ch*50000+0x04)) // Mode Register Read-write 0x0
#define rHSMCI_DTOR(ch)		(*(volatile U32 *)(0xFFF80000+ch*50000+0x08)) // Data Timeout Register Read-write 0x0
#define rHSMCI_SDCR(ch)		(*(volatile U32 *)(0xFFF80000+ch*50000+0x0C)) // SD/SDIO Card Register Read-write 0x0
#define rHSMCI_ARGR(ch)		(*(volatile U32 *)(0xFFF80000+ch*50000+0x10)) // Argument Register  Read-write 0x0
#define rHSMCI_CMDR(ch)		(*(volatile U32 *)(0xFFF80000+ch*50000+0x14)) // Command Register  Write
#define rHSMCI_BLKR(ch)		(*(volatile U32 *)(0xFFF80000+ch*50000+0x18)) // Block Register  Read-write 0x0
#define rHSMCI_CSTOR(ch)	(*(volatile U32 *)(0xFFF80000+ch*50000+0x1C)) // Completion Signal Timeout Register  Read-write 0x0
#define rHSMCI_RSPR0(ch)	(*(volatile U32 *)(0xFFF80000+ch*50000+0x20)) // Response Register Read 0x0
#define rHSMCI_RSPR1(ch)	(*(volatile U32 *)(0xFFF80000+ch*50000+0x24)) // Response Register Read 0x0
#define rHSMCI_RSPR2(ch)	(*(volatile U32 *)(0xFFF80000+ch*50000+0x28)) // Response Register Read 0x0
#define rHSMCI_RSPR3(ch)	(*(volatile U32 *)(0xFFF80000+ch*50000+0x2C)) // Response Register Read 0x0
#define rHSMCI_RDR(ch)		(*(volatile U32 *)(0xFFF80000+ch*50000+0x30)) // Receive Data Register Read 0x0
#define rHSMCI_TDR(ch)		(*(volatile U32 *)(0xFFF80000+ch*50000+0x34)) // Transmit Data Register Write
#define rHSMCI_SR(ch)		(*(volatile U32 *)(0xFFF80000+ch*50000+0x40)) // Status Register Read 0xC0E5
#define rHSMCI_IER(ch)		(*(volatile U32 *)(0xFFF80000+ch*50000+0x44)) // Interrupt Enable Register Write
#define rHSMCI_IDR(ch)		(*(volatile U32 *)(0xFFF80000+ch*50000+0x48)) // Interrupt Disable Register Write
#define rHSMCI_IMR(ch)		(*(volatile U32 *)(0xFFF80000+ch*50000+0x4C)) // Interrupt Mask Register Read 0x0
#define rHSMCI_DMA(ch)		(*(volatile U32 *)(0xFFF80000+ch*50000+0x50)) // DMA Configuration Register Read-write 0x00
#define rHSMCI_CFG(ch)		(*(volatile U32 *)(0xFFF80000+ch*50000+0x54)) // Configuration Register Read-write 0x00
#define rHSMCI_WPMR(ch)		(*(volatile U32 *)(0xFFF80000+ch*50000+0xE4)) // Write Protection Mode Register Read-write
#define rHSMCI_WPSR(ch)		(*(volatile U32 *)(0xFFF80000+ch*50000+0xE8)) // Write Protection Status Register Read-only
#define HSMCI_FIFO(ch)		(0xFFF80000+ch*50000+0x200) // FIFO Memory Aperture 0x200-0x3FFC

#define rPWM_MR 		(*(volatile U32 *)(0xFFFB8000))
#define rPWM_ENA		(*(volatile U32 *)(0xFFFB8000+0x04))
#define rPWM_DIS		(*(volatile U32 *)(0xFFFB8000+0x08))
#define rPWM_SR			(*(volatile U32 *)(0xFFFB8000+0x0C))
#define rPWM_IER		(*(volatile U32 *)(0xFFFB8000+0x10))
#define rPWM_IDR		(*(volatile U32 *)(0xFFFB8000+0x14))
#define rPWM_IMR		(*(volatile U32 *)(0xFFFB8000+0x18))
#define rPWM_ISR		(*(volatile U32 *)(0xFFFB8000+0x1C))
#define rPWM_CMR(ch)	(*(volatile U32 *)(0xFFFB8000+0x200+ch*0x20+0x00))
#define rPWM_CDTY(ch)	(*(volatile U32 *)(0xFFFB8000+0x200+ch*0x20+0x04))
#define rPWM_CPRD(ch)	(*(volatile U32 *)(0xFFFB8000+0x200+ch*0x20+0x08))
#define rPWM_CCNT(ch)	(*(volatile U32 *)(0xFFFB8000+0x200+ch*0x20+0x0C))
#define rPWM_CUPD(ch)	(*(volatile U32 *)(0xFFFB8000+0x200+ch*0x20+0x10))

#endif /*__SOC_H__*/

