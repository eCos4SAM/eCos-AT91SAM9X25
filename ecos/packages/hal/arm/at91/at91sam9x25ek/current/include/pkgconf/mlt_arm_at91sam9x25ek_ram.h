// eCos memory layout - Wed Apr 11 13:49:55 2001

// =============================================================================
// Key-change    Date       Author   Description
// --------------+----------+--------+------------------------------------------
// SAM9X25-0001  2011/03/20 TuPN     Create new platform (base on g20)
//
// =============================================================================
//SAM9X25-0001.Add.Start
#ifndef __ASSEMBLER__
#include <cyg/infra/cyg_type.h>
#include <stddef.h>

#endif
#define CYGMEM_REGION_boot          (0x0)
#define CYGMEM_REGION_boot_SIZE     (0x4000)
#define CYGMEM_REGION_boot_ATTR     (CYGMEM_REGION_ATTR_R)
#define CYGMEM_REGION_sram0         (0x00300000)  //sram start
#define CYGMEM_REGION_sram0_SIZE    (0x8000)      //32K
#define CYGMEM_REGION_sram0_ATTR    (CYGMEM_REGION_ATTR_R | CYGMEM_REGION_ATTR_W)
#define CYGMEM_REGION_sdram         (0x22000000)
#define CYGMEM_REGION_sdram_SIZE    (0x04000000) //T.B.D - Real value: 8000000 - 128M 
#define CYGMEM_REGION_sdram_ATTR    (CYGMEM_REGION_ATTR_R | CYGMEM_REGION_ATTR_W)

#define CYGMEM_REGION_rom       CYGMEM_REGION_boot
#define CYGMEM_REGION_rom_SIZE  CYGMEM_REGION_boot_SIZE
#define CYGMEM_REGION_rom_ATTR  CYGMEM_REGION_boot_ATTR
#define CYGMEM_REGION_ram       CYGMEM_REGION_sdram
#define CYGMEM_REGION_ram_SIZE  CYGMEM_REGION_sdram_SIZE
#define CYGMEM_REGION_ram_ATTR  CYGMEM_REGION_sdram_ATTR

#ifndef __ASSEMBLER__
extern char CYG_LABEL_NAME (__heap1) [];
#endif
#define CYGMEM_SECTION_heap1 (CYG_LABEL_NAME (__heap1))
#define CYGMEM_SECTION_heap1_SIZE (CYGMEM_REGION_sdram + CYGMEM_REGION_sdram_SIZE - (size_t) CYG_LABEL_NAME (__heap1))

//SAM9X25-0001.Add.End
