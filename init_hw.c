/*
 * ------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------
 */
 
#include "def.h"

#include "soc.h"
#include "init_hw.h"

static void InitHW_Basic(void);
static void InitHW_Clock(void);
static void InitHW_GPIO(void);

static void InitHW_AIC(void);
static void InitHW_LED(void);
static void InitHW_RTC(void);
static void InitHW_DDRAM(void);
static void InitHW_EMIF(void);

static void InitHW_DBGU(void);

static void SFR_DELAY(U32 time);

void defaultSpuriousHandler(void);
void defaultFiqHandler(void);
void defaultIrqHandler(void);

void InitHW(void)
{
	InitHW_Basic();
	InitHW_Clock();
	InitHW_AIC();
	
	rMATRIX_MRCR = (0x1 << 0) | (0x1 << 1);
	
	rRTT_MR &= ~((0x1 << 16) | (0x1 << 17));
	rPIT_MR &= ~((0x1 << 24) | (0x1 << 25));
	
	InitHW_GPIO();
	InitHW_DDRAM();
	InitHW_RTC();
	InitHW_EMIF();
	InitHW_LED();
	InitHW_DBGU();
	
	rPIOA_SODR = (1<<29);
}

static void InitHW_Basic(void)
{
	rWDT_SR			= 0x3EFF8FFF;	// Disable the dame watch dog timer
	rSHDW_MR		= 0x00000001;	// Enable Wake-up button
	rSYS_RSTC		= 0xA5000001;	// Enable external reset
}

static void InitHW_Clock(void)
{
	rCKGR_MOR		= 0x00008001;	// Try to Enable the 12 MHz Crystal Oscillator

	while((rPMC_SR & 0x1) != 0x1);	// Let the 12 MHz be stable.
	
	rPMC_MCKR		= 0x00001301;	// Switch the System Clock to 12 MHz

	/* DIV = 3, MUL = 199 (MAIN_CLOCK = 12MHz, APLL = 800MHz, SYS_CLK = 400MHz) */
	
	rPMC_PLLICPR	= 0x0;			// PLL CP Current setting
	rCKGR_PLLAR 	= 0x20C73F03;
	
	while((rPMC_SR & 0x3) != 0x3);
	
	/* MCLK = 133MHz, DDR_CLK = 133MHz, DDR_Rate = 266MHz */
	
	rPMC_MCKR		= 0x00001302;

	while((rPMC_SR & 0xF) != 0xB);

	rCKGR_UCKR		= 0xF1F10000;		// Enable UPLL
	while(((rPMC_SR>>6) & 0x1) != 0x1);

	if(rSCKCR != 0x0000000A)	// Enable the 32k Quartz Crystal
	{
		rSCKCR		= 0x00000003;	
		SFR_DELAY(5);	
		rSCKCR		= 0x0000000B;
		SFR_DELAY(5);
		rSCKCR		= 0x0000000A; 
		SFR_DELAY(5);
	}

	rPMC_SCER		= 0x344;
	
//	EFECD17C 0824000C
	
//	rPMC_PCDR		= 0xEFECD97C;
//	rPMC_PCER		= 0xEFECD97C;
	
	rPMC_PCER		= 0x0028503C;
	rPMC_PCDR		= 0xFFD7AFC0;
	
	rPMC_PCK0		= 0x106;	// Set the PCK0 = 66.66 MHz
	rPMC_PCK1		= 0x106;	// Set the PCK1 = 66.66 MHz
	while(((rPMC_SR>>8) & 0x3) != 0x3);
}

static void InitHW_AIC(void)
{
	U32 i = 0;
	
	rAIC_IDCR = 0xFFFFFFFF;
    rAIC_SVR(0) = (U32) defaultFiqHandler;
    for (i = 1; i < 31; i++) rAIC_SVR(i) = (U32) defaultIrqHandler;
    rAIC_SPU = (U32) defaultSpuriousHandler;
    for (i = 0; i < 8 ; i++) rAIC_EOICR = 0;
}


static void InitHW_RTC(void)
{

}

static void InitHW_LED(void)
{
	//	PWM mode register
	//	Since MCLK = 133.33 MHz
	//	Set CLKA = 66.66 MHz
	//	Set CLKB = 1 kHz
	rPWM_MR		= (0x0 << 28) + (0xA << 24) + (0x82 << 16) + (0x0 << 12) + (0x1 << 8) + (0x1 << 0);
	rPWM_ENA	= 0xF; // Enalbe all PWM channels
	rPWM_IDR	= 0xF; // Disable PWM as interrupt source

	rPWM_CMR(0)		= 0xC;
	rPWM_CDTY(0)	= 0x1F4;
	rPWM_CPRD(0)	= 0x3E8;
	rPWM_CUPD(0)	= 0x0;

	rPWM_CMR(1)		= 0xC;
	rPWM_CDTY(1)	= 0x1F4;
	rPWM_CPRD(1)	= 0x3E8;
	rPWM_CUPD(1)	= 0x0;
	
	rPWM_CMR(2)		= 0xC;
	rPWM_CDTY(2)	= 0x1F4;
	rPWM_CPRD(2)	= 0x3E8;
	rPWM_CUPD(2)	= 0x0;
	
	rPWM_CMR(3)		= 0xC;
	rPWM_CDTY(3)	= 0x1F4;
	rPWM_CPRD(3)	= 0x3E8;
	rPWM_CUPD(3)	= 0x0;

}

static void InitHW_DBGU(void)
{
	rDBGU_CR = (0x1 << 7) + (0x1 << 5) + (0x1 << 3) + (0x1 << 2);
	rDBGU_IDR = 0xFFFFFFFF;
	rDBGU_BRGR = 0x48; // (5 << 16) + 144; (0x48)
	rDBGU_MR = (0x0 << 14) + (0x4 << 9);
	rDBGU_PTCR = (0x1 << 1) | (0x1 << 9);
	rDBGU_CR = (0x1 << 6) + (0x1 << 4);
}

static void InitHW_EMIF(void)
{

}

static void InitHW_GPIO(void)
{
	rPIOA_PER	= 0x780003C0;
	rPIOA_PDR	= 0x87FFFC3F;
	rPIOA_OER	= 0x20000000;
	rPIOA_ODR	= 0x580003C0;
	rPIOA_IFER	= 0x0;
	rPIOA_IFDR	= 0x0;
	rPIOA_SODR	= 0x0;
	rPIOA_CODR	= 0x20000000;
	rPIOA_IER	= 0x0;
	rPIOA_IDR	= 0xFFFFFFFF;
	rPIOA_IMR	= 0x0;
	rPIOA_MDER	= 0x0;
	rPIOA_MDDR	= 0xFFFFFFFF;
	rPIOA_PUDR	= 0xFFFFFFFF;
	rPIOA_PUER	= 0x583003C0;
	rPIOA_ASR	= 0x87FFFC3F;
	rPIOA_BSR	= 0x0;
	
	rPIOB_PER	= 0xFC0C0;
	rPIOB_PDR	= 0xFFF03F3F;
	rPIOB_OER	= 0xB8000;
	
	//rPIOB_PER	= 0xE40C0;
	//rPIOB_PDR	= 0xFFF1BF3F;
	//rPIOB_OER	= 0xA0000;
	rPIOB_ODR	= 0x440C0;
	rPIOB_IFER	= 0x0;
	rPIOB_IFDR	= 0x0;
	rPIOB_SODR	= 0x80000;
	rPIOB_CODR	= 0x20000;
	rPIOB_IER	= 0x0; 			// 0x44000;
	rPIOB_IDR	= 0xFFFFFFFF;	// 0xFFFBBFFF;
	rPIOB_IMR	= 0x0;
	rPIOB_MDER	= 0x0;
	rPIOB_MDDR	= 0xFFFFFFFF;
	rPIOB_PUDR	= 0xFFFFFFFF;
	rPIOB_PUER	= 0xFFFC7FFF;
	rPIOB_ASR	= 0xFFF1B03F;
	rPIOB_BSR	= 0xF00;
	rPIOC_PER	= 0x1F83;
	rPIOC_PDR	= 0xFFFFE07C;
	rPIOC_OER	= 0x0;
	rPIOC_ODR	= 0x1F83;
	rPIOC_IFER	= 0x0;
	rPIOC_IFDR	= 0x1F83;
	rPIOC_SODR	= 0x0;
	rPIOC_CODR	= 0x0;
	rPIOC_IER	= 0x0;
	rPIOC_IDR	= 0xFFFFFFFF;
	rPIOC_IMR	= 0x0;
	rPIOC_MDER	= 0x0;
	rPIOC_MDDR	= 0xFFFFFFFF;
	rPIOC_PUDR	= 0x0;
	rPIOC_PUER	= 0xFFFFFFFF;
	rPIOC_ASR	= 0xFFFFE07C;
	rPIOC_BSR	= 0x0;
	rPIOD_PER	= 0x180FEC3E;
	rPIOD_PDR	= 0xE7F013C1;
	rPIOD_OER	= 0x8000004;
	rPIOD_ODR	= 0x100FEC3A;
	rPIOD_IFER	= 0x30000;
	rPIOD_IFDR	= 0x1000EC38;
	rPIOD_SODR	= 0x4;
	rPIOD_CODR	= 0x8000000;
	rPIOD_IER	= 0x0; 			// 0x100EEC12;
	rPIOD_IDR	= 0xFFFFFFFF;	// 0xEFF113ED;
	rPIOD_IMR	= 0x0;
	rPIOD_MDER	= 0x0;
	rPIOD_MDDR	= 0xFFFFFFFF;
	rPIOD_PUDR	= 0xFFFFFFFF;
	rPIOD_PUER	= 0xF0F3026A;
	rPIOD_ASR	= 0xE0F003C0;
	rPIOD_BSR	= 0x7001001;
	rPIOE_PER	= 0x6;
	rPIOE_PDR	= 0xFFFFFFF9;
	rPIOE_OER	= 0x0;
	rPIOE_ODR	= 0x6;
	rPIOE_IFER	= 0x0;
	rPIOE_IFDR	= 0x6;
	rPIOE_SODR	= 0x0;
	rPIOE_CODR	= 0x0;
	rPIOE_IER	= 0x0; 			// 0x6;
	rPIOE_IDR	= 0xFFFFFFFF;	// 0xFFFFFFF9;
	rPIOE_IMR	= 0x0;
	rPIOE_MDER	= 0x0;
	rPIOE_MDDR	= 0xFFFFFFFF;
	rPIOE_PUDR	= 0xFFFFFFFF;
	rPIOE_PUER	= 0x0;
	rPIOE_ASR	= 0x7FFFFFF8;
	rPIOE_BSR	= 0x80000001;
}

static void InitHW_DDRAM(void)
{
	U32 i = 0;
	
	rDDRSDRC_MD 	= 0x16;
	rDDRSDRC_CR 	= 0x3D;
	rDDRSDRC_TPR0 	= 0x21128226;
	rDDRSDRC_TPR1 	= 0x02C8100E;
	rDDRSDRC_TPR2 	= 0x2072;
	rDDRSDRC_MR 	= 0x1;
	rDDRSD_BASE0 	= 0x0;

	SFR_DELAY(2);
	rDDRSDRC_MR 	= 0x1;
	rDDRSD_BASE0 	= 0x0;
	SFR_DELAY(1);
	rDDRSDRC_MR 	= 0x2;
	rDDRSD_BASE0 	= 0x0;
	SFR_DELAY(1);
	rDDRSDRC_MR 	= 0x5;
	rDDRSD_BASE2	= 0x0;
	SFR_DELAY(1);
	rDDRSDRC_MR 	= 0x5;
	rDDRSD_BASE3 	= 0x0;
	SFR_DELAY(1);
	rDDRSDRC_MR 	= 0x5;
	rDDRSD_BASE1 	= 0x0;
	SFR_DELAY(2);
	i = rDDRSDRC_CR; 
	i |= 0xBD;
	rDDRSDRC_CR 	= i;
	rDDRSDRC_MR 	= 0x3;
	rDDRSD_BASE0 	= 0x0;
	SFR_DELAY(1);
	rDDRSDRC_MR 	= 0x2;
	rDDRSD_BASE0 	= 0x0;
	SFR_DELAY(1);
	rDDRSDRC_MR 	= 0x4;
	rDDRSD_BASE0 	= 0x0;
	SFR_DELAY(1);
	rDDRSDRC_MR 	= 0x4;
	rDDRSD_BASE0 	= 0x0;
	SFR_DELAY(1);
	i = rDDRSDRC_CR; 
	i &= 0xFFFFFF7F;
	rDDRSDRC_CR 	= i;
	rDDRSDRC_MR 	= 0x3;
	rDDRSD_BASE0 	= 0x0;
	SFR_DELAY(1);
	i = rDDRSDRC_CR; 
	i |= (0x07 << 12);
	rDDRSDRC_CR 	= i;
	rDDRSDRC_MR		= 0x5;
	rDDRSD_BASE1 	= 0x0;
	SFR_DELAY(1);
	i = rDDRSDRC_CR; 
	i &= 0xFFFF8FFF;
	rDDRSDRC_CR 	= i;
	rDDRSDRC_MR 	= 0x5;
	rDDRSD_BASE3 	= 0x0;
	SFR_DELAY(1);
	rDDRSDRC_MR 	= 0x0;
	rDDRSD_BASE0 	= 0x0;
	SFR_DELAY(1);
	
	rDDRSDRC_RTR 	= 0x00000411;
	rDDRSDRC_HS 	= 0x04;
	
	SFR_DELAY(1);
}

static void SFR_DELAY(U32 time)	// "time" is counted in "ms"
{
	U32 i;

	if(time != 0) 
	{
		for(; time > 0; time--)
		{
			for(i = 0; i < 7300; i++)
			{
				__asm
				{
				    NOP
  				}
			}
		}
	}
}

//------------------------------------------------------------------------------
/// Default spurious interrupt handler. Infinite loop.
//------------------------------------------------------------------------------
void defaultSpuriousHandler(void)
{
   // while (1);
}

//------------------------------------------------------------------------------
/// Default handler for fast interrupt requests. Infinite loop.
//------------------------------------------------------------------------------
void defaultFiqHandler(void)
{
    while (1);
}

//------------------------------------------------------------------------------
/// Default handler for standard interrupt requests. Infinite loop.
//------------------------------------------------------------------------------
void defaultIrqHandler(void)
{
    while (1);
}
