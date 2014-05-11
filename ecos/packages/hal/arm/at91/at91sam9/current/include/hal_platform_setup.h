#ifndef CYGONCE_HAL_PLATFORM_SETUP_H
#define CYGONCE_HAL_PLATFORM_SETUP_H

/*=============================================================================
//
//      hal_platform_setup.h
//
//      Platform specific support for HAL
//
//=============================================================================
// ####ECOSGPLCOPYRIGHTBEGIN####
// -------------------------------------------
// This file is part of eCos, the Embedded Configurable Operating System.
// Copyright (C) 1998, 1999, 2000, 2001, 2002, 2006 Free Software Foundation, Inc.
//
// eCos is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 or (at your option) any later
// version.
//
// eCos is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// for more details.
//
// You should have received a copy of the GNU General Public License
// along with eCos; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//
// As a special exception, if other files instantiate templates or use
// macros or inline functions from this file, or you compile this file
// and link it with other works to produce a work based on this file,
// this file does not by itself cause the resulting work to be covered by
// the GNU General Public License. However the source code for this file
// must still be made available in accordance with section (3) of the GNU
// General Public License v2.
//
// This exception does not invalidate any other reasons why a work based
// on this file might be covered by the GNU General Public License.
// -------------------------------------------
// ####ECOSGPLCOPYRIGHTEND####
//=============================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):   Owen Kirby
// Contributors:gthomas, asl
// Date:        2009-11-12
// Purpose:     AT91SAM9 platform specific support routines
// Description:
// Usage:       #include <cyg/hal/hal_platform_setup.h>
//
//####DESCRIPTIONEND####
//
//===========================================================================*/

#include <cyg/hal/var_io.h>
#include <cyg/hal/plf_io.h>
#include <cyg/hal/hal_mmu.h>

// Macro to initialise the Memory Controller
        .macro _flash_init
__flash_init__:
        ldr     r0,=AT91_MC
#if CYGNUM_HAL_ARM_AT91_CLOCK_SPEED > 60000000
        // When the clock is running faster than 60MHz we need two wait states
        ldr     r1,=(AT91_MC_FMR_2FWS)
#else
# if CYGNUM_HAL_ARM_AT91_CLOCK_SPEED > 30000000
        // When the clock is running faster than 30MHz we need a wait state
        ldr     r1,=(AT91_MC_FMR_1FWS)
# else
        // We have a slow clock, no extra wait states are needed
        ldr     r1,=AT91_MC_FMR_0FWS
# endif
#endif
        str     r1,[r0,#AT91_MC_FMR]
#if defined(AT91_MC_FMR1)
          // If we have a second flash controller we need to set that up as well
        str     r1,[r0,#AT91_MC_FMR1]
#endif
        .endm

// Macro to start the main clock.
        .macro  _main_clock_init
__main_clock_init__:
        ldr     r0,=AT91_PMC

          // Check that we have a stable clock before we start switching
wait_pmc_sr_0:
        ldr     r1,[r0,#AT91_PMC_SR]
        ands    r1,r1,#AT91_PMC_SR_MCKRDY
        beq     wait_pmc_sr_0

          // Swap to the slow clock, just to be sure.
        ldr     r1,=(AT91_PMC_MCKR_PRES_CLK|AT91_PMC_MCKR_SLOW_CLK)
        str     r1,[r0,#AT91_PMC_MCKR]

#if defined(CYGNUM_HAL_ARM_AT91_CLOCK_TYPE_EXTCLOCK)
        ldr     r1,=(AT91_PMC_MOR_OSCBYPASS)
#else
        ldr     r1,=(AT91_PMC_MOR_OSCCOUNT(CYGNUM_HAL_ARM_AT91_PMC_MOR_OSCCOUNT)|AT91_PMC_MOR_MOSCEN)
#endif
        str     r1,[r0,#AT91_PMC_MOR]

        // Wait for oscilator start timeout
wait_pmc_sr_1:
        ldr     r1,[r0,#AT91_PMC_SR]
        ands    r1,r1,#AT91_PMC_SR_MOSCS
        beq     wait_pmc_sr_1

        // Set the PLL multiplier and divider. 16 slow clocks go by
        // before the LOCK bit is set. */
        ldr     r1,=((AT91_PMC_PLLR_DIV(CYGNUM_HAL_ARM_AT91_PLL_DIVIDER))|(AT91_PMC_PLLR_PLLCOUNT(CYGNUM_HAL_ARM_AT91_PLL_COUNT))|(AT91_PMC_PLLR_MUL(CYGNUM_HAL_ARM_AT91_PLL_MULTIPLIER-1)))
        str     r1,[r0,#AT91_PMC_PLLR]

        // Wait for PLL locked indication
wait_pmc_sr_2:
        ldr     r1,[r0,#AT91_PMC_SR]
        ands    r1,r1,#AT91_PMC_SR_LOCK
        beq     wait_pmc_sr_2

        // Enable the PLL clock and set the prescale to 2 */
        ldr     r1,=(AT91_PMC_MCKR_PRES_CLK_2|AT91_PMC_MCKR_PLL_CLK)
        str     r1,[r0,#AT91_PMC_MCKR]

        // Wait for the MCLK ready indication
wait_pmc_sr_3:
        ldr     r1,[r0,#AT91_PMC_SR]
        ands    r1,r1,#AT91_PMC_SR_MCKRDY
        beq     wait_pmc_sr_3
        .endm

// Remap the flash from address 0x0 and place RAM there instead.
        .macro  _remap_flash
__remap_flash:
        ldr     r0,=0x000004 // Use the underfined instruction exception
        ldr     r1,=0x200004
        ldr     r2,[r0]      // Save away copies so we can restore them
        ldr     r3,[r1]
        ldr     r4,=0xffffff
        eor     r4,r3,r4     // XOR the contents of 0x20004
        str     r4,[r1]      // and write it
        ldr     r5,[r0]      // Read from low memory
        cmp     r5,r4
        beq     remap_done
        ldr     r0,=AT91_MC  // Need to do a remap
        ldr     r5,=1
        str     r5,[r0,#AT91_MC_RCR]
remap_done:
        str     r3,[r1]      // restore the value we changed
        .endm

// Flush and disable the caches
        .macro _disable_cache
__disable_cache:
// Flush the entire dcache (and then both TLBs, just in case)
        mov     r0, #0
        mcr     p15,0,r0,c7,c6,0
        mcr     p15,0,r0,c8,c7,0

// Disable and clear caches
        mrc     p15,0,r0,c1,c0,0
        bic     r0,r0,#0x1000           // disable ICache
        bic     r0,r0,#0x000F           // disable DCache,
                                        // MMU and alignment faults
        mcr     p15,0,r0,c1,c0,0
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        mov     r0, #0
        mcr     p15,0,r0,c7,c6,0        // clear data cache
        mcr     p15,0,r0,c7,c5,0        // clear instruction cache

#if 0
        mrc     p15,0,r0,c15,c1,0       // disable streaming
        orr     r0, r0, #0x80
        mcr     p15,0,r0,c15,c1,0
#endif
        .endm

#if defined(CYG_HAL_STARTUP_ROM)
        .macro  _setup
        _flash_init
        _main_clock_init
        _remap_flash
        .endm
#else
        .macro _setup
        _disable_cache
        ldr     sp,.__startup_stack
        bl      hal_mmu_init

        // Enable MMU
        ldr     r1, =1f
		mrc     MMU_CP,0,r0,MMU_Control,c0
        orr     r0,r0, #(MMU_Control_Init | MMU_Control_M)
        mcr     MMU_CP,0,r0,MMU_Control,c0
        mov     pc, r1                  // Change address spaces
        nop
        nop
        nop
        nop
        nop
1:
        // force init of SWI exception vector
        mov     r0, #(CPSR_IRQ_DISABLE|CPSR_FIQ_DISABLE|CPSR_UNDEF_MODE)
        msr     cpsr, r0
        .endm
#endif

#define PLATFORM_SETUP1 _setup

//-----------------------------------------------------------------------------
// end of hal_platform_setup.h
#endif // CYGONCE_HAL_PLATFORM_SETUP_H
