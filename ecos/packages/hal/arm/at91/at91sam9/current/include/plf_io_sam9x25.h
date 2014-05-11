#ifndef CYGONCE_HAL_PLF_IO_SAM9X25_H
#define CYGONCE_HAL_PLF_IO_SAM9X25_H
//=============================================================================
//
//      plf_io.h
//
//      AT91SAM9X25 specific registers
//
//=============================================================================
// ####ECOSGPLCOPYRIGHTBEGIN####
// -------------------------------------------
// This file is part of eCos, the Embedded Configurable Operating System.
// Copyright (C) 1998, 1999, 2000, 2001, 2002 Free Software Foundation, Inc.
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
// Author(s):   xxxxxxx
// Contributors:
// Date:        2011-03-21
// Purpose:     Atmel AT91SAM9 board specific registers
// Description:
// Usage:       #include <cyg/hal/plf_io.h>
//
//####DESCRIPTIONEND####
//
//=============================================================================

// =============================================================================
// Key-change    Date       Author   Description
// --------------+----------+--------+------------------------------------------
// SAM9X25-0001  2011/03/21 TuPN     Create file - Update address of peripherals
//
// =============================================================================
#include <pkgconf/hal_arm_at91sam9.h>

// Cache translation
#define CYGARC_UNCACHED_ADDRESS(x) ((cyg_uint32)(x) |  0x80000000)
#define CYGARC_CACHED_ADDRESS(x)   ((cyg_uint32)(x) & ~0x80000000)

// Error Correcting Code Controller
#define AT91_ECC    0xFFFFE000

// SDRAM Controller
#define AT91_SDRAMC 0xFFFFE800

// Peripheral Input/Output Controllers
#define AT91_PIOA   0xFFFFF400
#define AT91_PIOB   0xFFFFF600
#define AT91_PIOC   0xFFFFF800
#define AT91_PIOD   0xFFFFFA00
#define AT91_PIO    AT91_PIOA

//Select POI controllers
#define AT91_PIO_ABCDSR1	0x70	//POI Peripheral ABCD Select Register 1
#define AT91_PIO_ABCDSR2	0x74	//POI Peripheral ABCD Select Register 2

//SAM9X25-0002.ADD.Start
// Periodic Interval Timer Controller
#define AT91_PITC 			0xFFFFFE30
//SAM9X25-0002.ADD.End

// Static Memory Controller
#define AT91_SMC    		0xFFFFEA00

// Watchdog
#define AT91_WD             0xFFFFFE40

// Real Time Timer Controller
#define AT91_RTTC 0xFFFFFEB0

// TC - Timer Counter
//SAM9X25-0002.ADD.Start
#define AT91_TC      0xF8008000
#define AT91_TC3    (0xFFFEC000 - 0xFFFA0000)   		/* T.B.D - Donot understand */
#define AT91_TC4    (AT91_TC3 + AT91_TC_TC_SIZE)
#define AT91_TC5    (AT91_TC3 + 2 * AT91_TC_TC_SIZE)
//SAM9X25-0002.ADD.Start

// UDP - UDP Device Port
#define AT91_UDP    0xF803C000 /* SAM9X25-0002.ADD */

// TWI - Two Wire Interface
//SAM9X25-0002.ADD.Start
#define AT91_TWI0    0xF8010000
#define AT91_TWI1    0xF8014000  /* T.B.D - Difference g20 */
#define AT91_TWI2    0xF8018000  /* T.B.D - Difference g20 */
#define AT91_TWI     AT91_TWI0
//SAM9X25-0002.ADD.End

// USART
//SAM9X25-0002.ADD.Start
#define AT91_USART0 0xF801C000
#define AT91_USART1 0xF8020000
#define AT91_USART2 0xF8024000
#define AT91_USART3 0xF8028000 /* T.B.D - Difference g20 */
//SAM9X25-0002.ADD.End

#if 0 /* T.B.D */
/* TUPN.ADD.FOR.TEST - x25 doesnot support the Peripheral DMA */
// USART DMA registers
#define AT91_US_RPR  0x100 // Receive Pointer Register
#define AT91_US_RCR  0x104 // Receive Counter Register
#define AT91_US_TPR  0x108 // Transmit Pointer Register
#define AT91_US_TCR  0x10C // Transmit Counter Register
#define AT91_US_NRPR 0x110 // Next Receive Pointer Register
#define AT91_US_NRCR 0x114 // Next Receive Counter Register
#define AT91_US_NTPR 0x118 // Next Transmit Pointer Register
#define AT91_US_NTCR 0x11C // Next Transmit Counter Register
#define AT91_US_PTCR 0x120 // PDC Transfer Control Register
#define AT91_US_PTSR 0x124 // PDC Transfer Status Register
#endif
//SAM9X25-0002.ADD.Start
//Reset Controller (RSTC)
#define AT91_RST			0xFFFFFE00 
//SAM9X25-0002.ADD.End

// DEBUG serial channel
#define AT91_DBG 			0xFFFFF200
#define AT91_DBG_PIO 		AT91_PIOB
#define AT91_DBG_PSR 		AT91_PIO_BSR

// Define USART6 to be the debug UART. It is similar enough to a USART
// that both the hal_diag and interrupt driven driver will work.
// However trying to change parity, start/stop bits etc will not work.
#define CYGNUM_HAL_INTERRUPT_USART6 CYGNUM_HAL_INTERRUPT_DBG
#define AT91_USART6 AT91_DBG

#ifndef __ASSEMBLER__
#ifdef CYGBLD_HAL_ARM_AT91_BAUD_DYNAMIC
extern cyg_uint32 hal_at91_us_baud(cyg_uint32 baud);
#define AT91_US_BAUD(baud) hal_at91_us_baud(baud)
#endif
#endif // __ASSEMBLER__

// SSC - Synchronous Serial Controller
#define AT91_SSC    0xF0010000 /* SAM9X25-0002.ADD */

// EMAC - Ethernet Medium Access Controller
//SAM9X25-0002.ADD.Start
#define AT91_EMAC0   0xF802C000
#define AT91_EMAC1   0xF8030000 /*T.B.D New in x25 */
#define AT91_EMAC    AT91_EMAC0
//SAM9X25-0002.ADD.End

//SAM9X25-0002.ADD.Start
#define AT91_CAN0	0xF8000000 /* T.B.D New in x25 */
#define AT91_CAN1	0xF8000000 /* T.B.D New in x25 */
//SAM9X25-0002.ADD.End

//SPI - Serial Peripheral Interface
//SAM9X25-0002.ADD.Start
#define AT91_SPI0   0xF0000000
#define AT91_SPI1   0xF0004000
//SAM9X25-0002.ADD.End
#define AT91_SPI    AT91_SPI0

// SPI DMA registers (same offsets as UART)
#define AT91_SPI_RPR  0x100 // Receive Pointer Register
#define AT91_SPI_RCR  0x104 // Receive Counter Register
#define AT91_SPI_TPR  0x108 // Transmit Pointer Register
#define AT91_SPI_TCR  0x10C // Transmit Counter Register
#define AT91_SPI_NRPR 0x110 // Next Receive Pointer Register
#define AT91_SPI_NRCR 0x114 // Next Receive Counter Register
#define AT91_SPI_NTPR 0x118 // Next Transmit Pointer Register
#define AT91_SPI_NTCR 0x11C // Next Transmit Counter Register
#define AT91_SPI_PTCR 0x120 // PDC Transfer Control Register
#define AT91_SPI_PTSR 0x124 // PDC Transfer Status Register

// ADC - Analog to Digital Converter
//SAM9X25-0002.DEL #define AT91_ADC    0xFFFE0000
#define AT91_ADC    0xF804C000 /* SAM9X25-0002.ADD */

/******************************************************************************
 * Power Management Controller
 *
 * ***************************************************************************/
#define AT91_PMC    0xFFFFFC00

//Mark override all registers of PMC
#define AT91_PMC_REGISTERS_OVERRIDE

//Address of all registers
#define AT91_PMC_SCER           	0x00	//System Clock Enable Register
#define AT91_PMC_SCER_UHP  			(1 << 6) // USB Host Clock
#define AT91_PMC_SCER_UDP  			(1 << 7) // USB Device Clock
#define AT91_PMC_SCER_PCK0 			(1 << 8) // Programmable Clock Output
#define AT91_PMC_SCER_PCK1 			(1 << 9) // Programmable Clock Output

#define AT91_PMC_SCDR           	0x04	//System Clock Disable Register
#define AT91_PMC_SCSR           	0x08	//System Clock Status Register
#define AT91_PMC_PCER           	0x10	//Peripheral Clock Enable Register
#define AT91_PMC_PCER_FIQ  			(1 << 0) // Advanced Interrupt Controller FIQ
#define AT91_PMC_PCER_SYSC 			(1 << 1) // System Controller Interrupt
#define AT91_PMC_PCER_PIOA 			(1 << 2) // Parallel IO Controller
#define AT91_PMC_PCER_PIOB 			(1 << 2) // Parallel IO Controller
#define AT91_PMC_PCER_PIOC 			(1 << 3) // Parallel IO Controller
#define AT91_PMC_PCER_PIOD 			(1 << 3) // Parallel IO Controller
#define AT91_PMC_PCER_SMD 			(1 << 4) // Parallel IO Controller
#define AT91_PMC_PCER_US0  			(1 << 5) // USART 0
#define AT91_PMC_PCER_US1  			(1 << 6) // USART 1
#define AT91_PMC_PCER_US2  			(1 << 7) // USART 2
#define AT91_PMC_PCER_US3  			(1 << 8) // USART 3
#define AT91_PMC_PCER_TWI			(1 << 9) // Two-Wire Interface 0
#define AT91_PMC_PCER_TWI1			(1 <<10) // Two-Wire Interface 1
#define AT91_PMC_PCER_TWI2			(1 <<11) // Two-Wire Interface 2
#define AT91_PMC_PCER_HSMCI0		(1 <<12) // High Speed Multimedia Card Interface 0
#define AT91_PMC_PCER_SPI  			(1 <<13) // Serial Peripheral Interface
#define AT91_PMC_PCER_SPI1 			(1 <<14) // Serial Peripheral Interface
#define AT91_PMC_PCER_US4  			(1 <<15) // UART 0
#define AT91_PMC_PCER_US5  			(1 <<16) // UART 1
#define AT91_PMC_PCER_TC0  			(1 <<17) // Timer Counter 0
#define AT91_PMC_PCER_TC1  			(1 <<17) // Timer Counter 1
#define AT91_PMC_PCER_PWM  			(1 <<18) // Pulse Width Modulation Controller
#define AT91_PMC_PCER_ADC  			(1 <<19) // Analog-to-Digital Converter
#define AT91_PMC_PCER_DMAC0			(1 <<20) // DMA Controller 0
#define AT91_PMC_PCER_DMAC1			(1 <<21) // DMA Controller 1
#define AT91_PMC_PCER_UHP  			(1 <<22) // USB Host Port
#define AT91_PMC_PCER_UDHS 			(1 <<23) // USB Device High Speed
#define AT91_PMC_PCER_EMAC 			(1 <<24) // Ethernet MAC 0
#define AT91_PMC_PCER_RESERVED0 	(1 <<25) // Reserved
#define AT91_PMC_PCER_HSMCI1		(1 <<26) // High Speed Multimedia Card Interface 0
#define AT91_PMC_PCER_EMAC1			(1 <<27) // Ethernet MAC 1
#define AT91_PMC_PCER_SSC  			(1 <<28) // Serial Synchronous Controller
#define AT91_PMC_PCER_CAN  			(1 <<29) // CAN Controller 0
#define AT91_PMC_PCER_CAN1 			(1 <<30) // CAN Controller 1
#define AT91_PMC_PCER_IRQ0 			(1 <<31) // Advanced Interrupt Controller IRQ0

#define AT91_PMC_PCDR           	0x14	 //Peripheral Clock Disable Register
#define AT91_PMC_PCSR           	0x18	 //Peripheral Clock Status Register
#define AT91_PMC_CGMR           	0x20
#define AT91_PMC_MOR    			0x20 	 // Main Oscillator Register
#define AT91_PMC_MOR_MOSCEN    		(1 << 0) // Main Oscillator Enable
#define AT91_PMC_MOR_OSCBYPASS 		(1 << 1) // Main Oscillator Bypass
#define AT91_PMC_MOR_OSCCOUNT		(x << 8) // Slow clocks ticks

#define AT91_PMC_MCFR   0x24 // Main Clock Frequency Register
#define AT91_PMC_PLLRA  0x28
#define AT91_PMC_PLLR 			   AT91_PMC_PLLRA
#define AT91_PMC_PLLR_DIV(x)      ((x) <<  0)  // PLL Devide
#define AT91_PMC_PLLR_PLLCOUNT(x) ((x) <<  8)  // PLL Count
#define AT91_PMC_PLLR_MUL(x)      ((x) << 16)  // PLL Devide
#define AT91_PMC_PLLR_OUT_0 	  (0 << 14)
#define AT91_PMC_PLLR_OUT_1       (1 << 14)
#define AT91_PMC_PLLR_OUT_2       (2 << 14)
#define AT91_PMC_PLLR_OUT_3       (3 << 14)
#define AT91_PMC_MCKR   0x30               // Master Clock Register
#define AT91_PMC_MCKR_SLOW_CLK    (0 << 0) // Slow clock selected
#define AT91_PMC_MCKR_MAIN_CLK    (1 << 0) // Main clock selected
#define AT91_PMC_MCKR_PLLA_CLK    (2 << 0) // PLLA clock selected
//SAM9X25-0001.ADD.Start
#define AT91_PMC_MCKR_UPLL_CLK    (3 << 0) // UPLL clock selected /* T.B.D New in x25 */
#define AT91_PMC_MCKR_PRES_CLK    (0 << 4) // divide by 1
#define AT91_PMC_MCKR_PRES_CLK_2  (1 << 4) // divide by 2
#define AT91_PMC_MCKR_PRES_CLK_4  (2 << 4) // divide by 4
#define AT91_PMC_MCKR_PRES_CLK_8  (3 << 4) // divide by 8
#define AT91_PMC_MCKR_PRES_CLK_16 (4 << 4) // divide by 16
#define AT91_PMC_MCKR_PRES_CLK_32 (5 << 4) // divide by 32
#define AT91_PMC_MCKR_PRES_CLK_64 (6 << 4) // divide by 64
//SAM9X25-0001.ADD.End

#define AT91_PMC_PCKR0  0x40  // Programmable Clock Register 0
#define AT91_PMC_IER    0x60 // Interrupt Enable Register
#define AT91_PMC_IDR    0x64 // Interrupt Disable Register
#define AT91_PMC_SR     0x68 // Status Register
#define AT91_PMC_SR_MOSCS   (1 << 0) // Main oscillator stable
#define AT91_PMC_SR_LOCK    (1 << 1) // PLL Locked /* SAM9X25-0001.ADD */
#define AT91_PMC_SR_MCKRDY  (1 << 3) // MCK is ready to be enabled
#define AT91_PMC_SR_PCK0RDY (1 << 8) // Pad clock 0 is ready to be enabled
#define AT91_PMC_SR_PCK1RDY (1 << 9) // Pad clock 1 is ready to be enabled
#define AT91_PMC_IMR    0x6c // Interrupt Mask Register

//SAM9X25-0002.ADD.Start
//Enable peripheral clocks for all TC0 -> TC5
#define AT91_PMC_PCER_TC		(1<<17) /* override value in var_io.h */
//SAM9X25-0002.ADD.End

#endif //CYGONCE_HAL_PLF_IO_SAM9X25_H

