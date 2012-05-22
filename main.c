/* ----------------------------------------------------------------------------
 *		 
 *        mboot for Lophilo embedded system
 *		
 * ----------------------------------------------------------------------------
 * GPLv2
 * ----------------------------------------------------------------------------
 */

#include <stdio.h>
#include <string.h>

#include "def.h"
#include "shell.h"
#include "trace.h"

#include "soc.h"
#include "system.h"

#include "init_hw.h"

#include "cp15.h"

#include "Media.h"
#include "dbgu.h"

#include "sdmmc_mci.h"
#include "mci_hs.h"

#include "bootx.h"

#include "board.h"
#include "MEDSdcard.h"
#include "math.h"
#include "fatfs_config.h"

void mbootBanner(void);
static void LoadImage(void);
static FRESULT scan_files(char* path);

//------------------------------------------------------------------------------
//         Local constants
//------------------------------------------------------------------------------

/// Maximum number of LUNs which can be defined.
/// (Logical drive = physical drive = medium number)
#define MAX_LUNS        1

/// Available medias.
Media medias[MAX_LUNS];

//------------------------------------------------------------------------------
//         Local variables
//------------------------------------------------------------------------------

#define ID_DRV DRV_MMC

#if _FS_TINY == 0
#define STR_ROOT_DIRECTORY "0:"
#else
#define STR_ROOT_DIRECTORY ""
#endif

#if defined(at91cap9stk)
#define MCI_ID 1 //no connector for MCIO/SPI0
#else
#define MCI_ID 0
#endif

#define ZRELADDR			0x70008000

#define FPGA_SPI_EN()		{rSPI_CR(1) = (1 << 0);}
#define FPGA_SPI_DIS()		{rSPI_CR(1) = (1 << 1);}
#define FPGA_SPI_RST()		{rSPI_CR(1) = (1 << 7);}
#define FPGA_SPI_LSTTRX()	{rSPI_CR(1) = (1 << 24);}

#define FPGA_SPI_TDRE		((rSPI_SR(1) >> 1)&(0x1))
#define FPGA_SPI_TXEMPTY	((rSPI_SR(1) >> 9)&(0x1))
#define FPGA_SPI_ENS		((rSPI_SR(1) >> 16)&(0x1))

#define FPGA_CONF_N()		{rPIOB_CODR = (1 << 17);}
#define FPGA_CONF_P()		{rPIOB_SODR = (1 << 17);}

#define FPGA_DCLK_N()		{rPIOB_CODR = (1 << 16);}
#define FPGA_DCLK_P()		{rPIOB_SODR = (1 << 16);}

#define FPGA_DATA_N()		{rPIOB_CODR = (1 << 15);}
#define FPGA_DATA_P()		{rPIOB_SODR = (1 << 15);}

#define FPGA_DONE			((rPIOB_PDSR >> 14)&(0x1))
#define FPGA_STAT			((rPIOD_PDSR >> 28)&(0x1))

#define BITINV8(i)			((i >> 7)&(0x01)) | ((i >> 5)&(0x02)) | ((i >> 3)&(0x04)) | ((i >> 1)&(0x08)) | ((i << 1)&(0x10)) | ((i << 3)&(0x20)) | ((i << 5)&(0x40)) | ((i << 7)&(0x80))


const char* gridName = STR_ROOT_DIRECTORY "grid.rbf";
const char* zImageName = STR_ROOT_DIRECTORY "zImage";

#define TEST_SIZE 512
#define TEST_ADDR 0x0
#define SPI_FLASH_ID 0x1620C2

void (*run)(void);

//------------------------------------------------------------------------------
//         Local functions
//------------------------------------------------------------------------------

void
Config_FPGA_PS_SPI(void)
{
	PMC_PeriEn(AT91C_ID_SPI1);
	rSPI_CR(1) = (1 << 7);
	rSPI_CR(1) = (1 << 7);
	rSPI_MR(1) = (0x6 << 24) + (0xF << 16) + (1 << 7) + (0 << 5) + (1 << 4) + (0 << 2) + (0 << 1) + (1 << 0);
	rSPI_IDR(1) = 0xFFFFFFFF;
	PMC_PeriDis(AT91C_ID_SPI1);
	rSPI_CSR0(1) = (0x1 << 24) + (0x1 << 16) + (0x4 << 8) + (0x0 << 4) + (0 << 3) + (1 << 1) + (0 << 0);
}


//------------------------------------------------------------------------------
/// Scan files under a certain path
/// /param path    folder path
/// \return scan result, 1: success.
//------------------------------------------------------------------------------
static FRESULT scan_files(char* path)
{
    FRESULT res;
    FILINFO fno;
    DIR dir;
    int i;
    char *fn;
#if _USE_LFN
    static char lfn[_MAX_LFN * (_DF1S ? 2 : 1) + 1];
    fno.lfname = lfn;
    fno.lfsize = sizeof(lfn);
#endif


    res = f_opendir(&dir, path);
    if (res == FR_OK) {
        i = strlen(path);
        for (;;) {
            res = f_readdir(&dir, &fno);
            if (res != FR_OK || fno.fname[0] == 0) break;
#if _USE_LFN
            fn = *fno.lfname ? fno.lfname : fno.fname;
#else
            fn = fno.fname;
#endif
            if (*fn == '.') continue;
            if (fno.fattrib & AM_DIR) {
                TRACE_MSG(&path[i], "/%s", fn);
                res = scan_files(path);
                if (res != FR_OK) break;
                path[i] = 0;
            } else {
                DEBUG_MSG("%s/%s", path, fn);
            }
        }
    }

    return res;
}

//------------------------------------------------------------------------------
/// Do file system tests
/// \return test result, 1: success.
//------------------------------------------------------------------------------
static void
LoadImage(void)
{
    unsigned int i, j;
    unsigned int ByteToRead;
    unsigned int ByteRead;
	
	U8 buf, cnt;

    FRESULT res;
    DIR dirs;
    FATFS fs;             // File system object
    FIL FileObject;

    if (!MEDSdcard_Initialize(&medias[ID_DRV], MCI_ID))
	{
        TRACE_ERR("SD Init fail\n\r");
        return;
    }
    numMedias = 1;

    // Mount disk
    DEBUG_MSG("Mount disk %d", ID_DRV);
    memset(&fs, 0, sizeof(FATFS));      // Clear file system object
    res = f_mount(ID_DRV, &fs);
    if( res != FR_OK )
	{
        TRACE_ERR("f_mount pb: 0x%X", res);
        return;
    }

    // Test if the disk is formated
    res = f_opendir (&dirs,STR_ROOT_DIRECTORY);
    if(res == FR_OK )
	{
		scan_files(STR_ROOT_DIRECTORY);
    	res = f_open(&FileObject, zImageName, FA_OPEN_EXISTING|FA_READ);
    	if( res != FR_OK )
		{
        	TRACE_ERR("f_open read pb: 0x%X", res);
        	return;
    	}

    // Read file
		DEBUG_MSG("Read file");
    	ByteToRead = FileObject.fsize;
		res = f_read(&FileObject, (void*)0x70008000, ByteToRead, &ByteRead);
    	if(res != FR_OK)
		{
        	TRACE_ERR("f_read pb: 0x%X", res);
        	return;
		}
		
    	res = f_open(&FileObject, gridName, FA_OPEN_EXISTING|FA_READ);
    	if( res != FR_OK )
		{
        	TRACE_ERR("f_open read pb: 0x%X", res);
        	return;
    	}		
	    ByteToRead = FileObject.fsize;
		res = f_read(&FileObject, (void*)0x71008000, ByteToRead, &ByteRead);
    	if(res != FR_OK)
		{
        	TRACE_ERR("f_read pb: 0x%X", res);
        	return;
		}	
		
		
    }
	
	PRINT_F("\n\r\n\r");

	FPGA_CONF_N();
	FPGA_CONF_P();

	while(!FPGA_STAT);
	
	for(i=0;i<0x1000000;i++)
	{
		buf = SFR_RD8(0x71008000+i);
		
		for(cnt = 0; cnt < 8; cnt++)
		{
			if(((buf>>(cnt))&(0x1))==0x1)
			{
				FPGA_DATA_P();
			}
			else
			{
				FPGA_DATA_N();
			}	
			FPGA_DCLK_P();
			FPGA_DCLK_N();
		}
		if(FPGA_DONE) break;
	}

	for(i=0;i<64;i++) for(j=0;j<8;j++) CP15_CleanInvalidateDcacheIndex((i<<26)|(j<<5));
	CP15_DisableDcache();
	CP15_DisableIcache();
	CP15_InvalidateIcache();
	CP15_DisableMMU();
	CP15_InvalidateTLB(); 

	run = (void (*)(void))0x70008000;

	BootmSet_ParamAddr(0x70008000 - 0x7F00);
	BootmSet_MachineID(1830);
	run();
}



S32
main()
{
	mbootBanner();
	LoadImage();
//	


	
	
//	TRACE_MSG("THE RESULT IS: 0x%02x", j);



	while(1);
}

void
mbootBanner(void)
{
	ShellAllClear();
	
	SHELL_INF("        __                      __"); 
	SHELL_INF("       /\\ \\                    /\\ \\__"); 
	SHELL_INF("___ ___\\ \\ \\____    ___     ___\\ \\ ,_\\"); 
	SHELL_INF(" __` __`\\ \\ '__`\\  / __`\\  / __`\\ \\ \\/"); 
	SHELL_INF(" \\/\\ \\/\\ \\ \\ \\_\\ \\/\\ \\_\\ \\/\\ \\_\\ \\ \\ \\_"); 
	SHELL_INF("\\_\\ \\_\\ \\_\\ \\_,__/\\ \\____/\\ \\____/\\ \\__\\"); 
	SHELL_INF("/_/\\/_/\\/_/\\/___/  \\/___/  \\/___/  \\/__/"); 
	
	// Above banner is generated by: http://www.network-science.de/ascii/
	// HTML-Frontend (c) 1996-2012 by Jorg Seyfferth
	
	SHELL_EMPTY();
	SHELL_INF("Lophilo-mboot V0.1 (%s %s)", __DATE__, __TIME__);
	SHELL_INF("By Shyu Lee and Ricky Ng-Adam");
	SHELL_BNNER();
	SHELL_EMPTY();
}
