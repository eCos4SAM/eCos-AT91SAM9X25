// eCos memory layout - Wed Apr 11 13:49:55 2001

// This is a generated file - do not edit
// =============================================================================
// Key-change    Date       Author   Description
// --------------+----------+--------+------------------------------------------
// SAM9X25-0001  2011/03/20 TuPN     Create new platform (base on g20)
//
// =============================================================================

#ifndef __ASSEMBLER__
#include <cyg/infra/cyg_type.h>
#include <stddef.h>
#endif

// Boot region can be ROM, EBI_NCS0, or SRAM depending on BMS and REMAP.
#define CYGMEM_REGION_boot          (0x0)
#define CYGMEM_REGION_boot_SIZE     (0x00100000)
#define CYGMEM_REGION_boot_ATTR     (CYGMEM_REGION_ATTR_R | CYGMEM_REGION_ATTR_W)

// Internal ROM
#define CYGMEM_REGION_irom          (0x00100000)
#define CYGMEM_REGION_irom_SIZE     (0x8000)
#define CYGMEM_REGION_irom_ATTR     (CYGMEM_REGION_ATTR_R)

// Internal SRAM (two regions) and USB host controller memory.
#define CYGMEM_REGION_sram0         (0x00305800)
#define CYGMEM_REGION_sram0_SIZE    (0x2800)
#define CYGMEM_REGION_sram0_ATTR    (CYGMEM_REGION_ATTR_R | CYGMEM_REGION_ATTR_W)
#define CYGMEM_REGION_uhp           (0x00500000)
#define CYGMEM_REGION_uhp_SIZE      (0x4000)
#define CYGMEM_REGION_uhp_ATTR      (CYGMEM_REGION_ATTR_R | CYGMEM_REGION_ATTR_W)

// 64MB SDRAM
#define CYGMEM_REGION_sdram         (0x20000000)
#define CYGMEM_REGION_sdram_SIZE    (0x04000000)
#define CYGMEM_REGION_sdram_ATTR    (CYGMEM_REGION_ATTR_R | CYGMEM_REGION_ATTR_W)

// Map region names to eCos names.
#define BOOTLOADER_RAM_SIZE     (0x00100000)
#define CYGMEM_REGION_rom       CYGMEM_REGION_flash
#define CYGMEM_REGION_rom_SIZE  CYGMEM_REGION_flash_SIZE
#define CYGMEM_REGION_rom_ATTR  CYGMEM_REGION_flash_ATTR
#define CYGMEM_REGION_ram       (CYGMEM_REGION_sdram + CYGMEM_REGION_sdram_SIZE - BOOTLOADER_RAM_SIZE)
#define CYGMEM_REGION_ram_SIZE  BOOTLOADER_RAM_SIZE
#define CYGMEM_REGION_ram_ATTR  CYGMEM_REGION_sdram_ATTR

#ifndef __ASSEMBLER__
extern char CYG_LABEL_NAME (__heap1) [];
#endif
#define CYGMEM_SECTION_heap1 (CYG_LABEL_NAME (__heap1))
#define CYGMEM_SECTION_heap1_SIZE (CYGMEM_REGION_ram + CYGMEM_REGION_ram_SIZE - (size_t) CYG_LABEL_NAME (__heap1))

