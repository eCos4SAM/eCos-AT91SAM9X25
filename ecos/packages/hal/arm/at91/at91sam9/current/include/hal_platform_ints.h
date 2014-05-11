#ifndef CYGONCE_HAL_PLATFORM_INTS_H
#define CYGONCE_HAL_PLATFORM_INTS_H
//==========================================================================
//
//      hal_platform_ints.h
//
//      HAL Interrupt and clock assignments for AT91SAM7
//
//==========================================================================
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
//==========================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):    gthomas
// Contributors: gthomas, Oliver Munz, Andrew Lunn, John Eigelaar
// Date:         2001-07-12
// Purpose:      Define Interrupt support
// Description:  The interrupt specifics for the AT91SAM9 platform are
//               defined here.
//
// Usage:        #include <cyg/hal/hal_platform_ints.h>
//               ...
//
//
//####DESCRIPTIONEND####
//
//==========================================================================
// =============================================================================
// Key-change    Date       Author   Description
// --------------+----------+--------+------------------------------------------
// SAM9X25-0001  2011/03/21 TuPN     Create file - Update address of peripherals
//
// =============================================================================

#include <pkgconf/hal_arm_at91sam9.h>

#define CYGNUM_HAL_INTERRUPT_FIQ        0
#define CYGNUM_HAL_INTERRUPT_SYS        1

//SAM9X25-0001.ADD.Start
#ifdef CYGHWR_HAL_ARM_AT91SAM9_at91sam9x25
#define CYGNUM_HAL_INTERRUPT_PIOAB		2 	/**<  2 AT91SAM9X25 Parallel I/O Controller A and B (PIOAB) */
#define CYGNUM_HAL_INTERRUPT_PIOCD		3 	/**<  3 AT91SAM9X25 Parallel I/O Controller C and D (PIOCD) */
#define CYGNUM_HAL_INTERRUPT_SMD		4 	/**<  4 AT91SAM9X25 SMD Soft Modem (SMD) */
#define CYGNUM_HAL_INTERRUPT_USART0		5 	/**<  5 AT91SAM9X25 USART 0 (USART0) */
#define CYGNUM_HAL_INTERRUPT_USART1		6 	/**<  6 AT91SAM9X25 USART 1 (USART1) */
#define CYGNUM_HAL_INTERRUPT_USART2		7 	/**<  7 AT91SAM9X25 USART 2 (USART2) */
#define CYGNUM_HAL_INTERRUPT_USART3		8 	/**<  8 AT91SAM9X25 USART 3 (USART3) */
#define CYGNUM_HAL_INTERRUPT_TWI0		9 	/**<  9 AT91SAM9X25 Two-Wire Interface 0 (TWI0) */
#define CYGNUM_HAL_INTERRUPT_TWI1		10	/**< 10 AT91SAM9X25 Two-Wire Interface 1 (TWI1) */
#define CYGNUM_HAL_INTERRUPT_TWI2		11	/**< 11 AT91SAM9X25 Two-Wire Interface 2 (TWI2) */
#define CYGNUM_HAL_INTERRUPT_HSMCI0		12	/**< 12 AT91SAM9X25 High Speed Multimedia Card Interface 0 (HSMCI0) */
#define CYGNUM_HAL_INTERRUPT_SPI0		13	/**< 13 AT91SAM9X25 Serial Peripheral Interface 0 (SPI0) */
#define CYGNUM_HAL_INTERRUPT_SPI1		14	/**< 14 AT91SAM9X25 Serial Peripheral Interface 1 (SPI1) */
#define CYGNUM_HAL_INTERRUPT_UART0		15	/**< 15 AT91SAM9X25 UART 0 (UART0) */
#define CYGNUM_HAL_INTERRUPT_UART1		16	/**< 16 AT91SAM9X25 UART 1 (UART1) */
#define CYGNUM_HAL_INTERRUPT_TC01		17	/**< 17 AT91SAM9X25 Timer Counter 0 + 1 (TC01) */
#define CYGNUM_HAL_INTERRUPT_PWM		18	/**< 18 AT91SAM9X25 Pulse Width Modulation Controller (PWM) */
#define CYGNUM_HAL_INTERRUPT_ADC		19	/**< 19 AT91SAM9X25 ADC Controller (ADC) */
#define CYGNUM_HAL_INTERRUPT_DMAC0		20	/**< 20 AT91SAM9X25 DMA Controller 0 (DMAC0) */
#define CYGNUM_HAL_INTERRUPT_DMAC1		21	/**< 21 AT91SAM9X25 DMA Controller 1 (DMAC1) */
#define CYGNUM_HAL_INTERRUPT_UHPHS		22	/**< 22 AT91SAM9X25 USB Host High Speed (UHPHS) */
#define CYGNUM_HAL_INTERRUPT_UDPHS		23	/**< 23 AT91SAM9X25 USB Device High Speed (UDPHS) */
#define CYGNUM_HAL_INTERRUPT_EMAC		24	/**< 24 AT91SAM9X25 Ethernet MAC 0 (EMAC0) */
#define CYGNUM_HAL_INTERRUPT_HSMCI1		26	/**< 26 AT91SAM9X25 High Speed Multimedia Card Interface 1 (HSMCI1) */
#define CYGNUM_HAL_INTERRUPT_EMAC1		27	/**< 27 AT91SAM9X25 Ethernet MAC 1 (EMAC1) */
#define CYGNUM_HAL_INTERRUPT_SSC		28	/**< 28 AT91SAM9X25 Synchronous Serial Controller (SSC) */
#define CYGNUM_HAL_INTERRUPT_CAN0		29	/**< 29 AT91SAM9X25 CAN controller 0 (CAN0) */
#define CYGNUM_HAL_INTERRUPT_CAN1		30	/**< 30 AT91SAM9X25 CAN controller 1 (CAN1) */
#define CYGNUM_HAL_INTERRUPT_IRQ		31  /**< 31 AT91SAM9X25 Advanced Interrupt Controller (IRQ) */
//SAM9G45-0001.ADD.Start
#elif defined(CYGHWR_HAL_ARM_AT91SAM9_at91sam9g45)
#define CYGNUM_HAL_INTERRUPT_PIOA   ( 2) /** Parallel IO Controller A */
#define CYGNUM_HAL_INTERRUPT_PIOB   ( 3) /** Parallel IO Controller B */
#define CYGNUM_HAL_INTERRUPT_PIOC   ( 4) /** Parallel IO Controller C */
#define CYGNUM_HAL_INTERRUPT_PIOD_E ( 5) /** Parallel IO Controller D and E */
#define CYGNUM_HAL_INTERRUPT_TRNG   ( 6) /** True Random Number Generator */
#define CYGNUM_HAL_INTERRUPT_USART0    ( 7) /** USART 0 */
#define CYGNUM_HAL_INTERRUPT_USART1    ( 8) /** USART 1 */
#define CYGNUM_HAL_INTERRUPT_USART2    ( 9) /** USART 2 */
#define CYGNUM_HAL_INTERRUPT_USART3    (10) /** USART 2 */
#define CYGNUM_HAL_INTERRUPT_MCI0   (11) /** Multimedia Card Interface 0 */
#define CYGNUM_HAL_INTERRUPT_TWI0   (12) /** TWI 0 */
#define CYGNUM_HAL_INTERRUPT_TWI1   (13) /** TWI 1 */
#define CYGNUM_HAL_INTERRUPT_SPI0   (14) /** Serial Peripheral Interface */
#define CYGNUM_HAL_INTERRUPT_SPI1   (15) /** Serial Peripheral Interface */
#define CYGNUM_HAL_INTERRUPT_SSC0   (16) /** Serial Synchronous Controller 0 */
#define CYGNUM_HAL_INTERRUPT_SSC1   (17) /** Serial Synchronous Controller 1 */
#define CYGNUM_HAL_INTERRUPT_TC     (18) /** Timer Counter 0, 1, 2, 3, 4, 5 */
#define CYGNUM_HAL_INTERRUPT_PWMC   (19) /** Pulse Width Modulation Controller */
#define CYGNUM_HAL_INTERRUPT_TSADC  (20) /** Touch Screen Controller */
#define CYGNUM_HAL_INTERRUPT_HDMA   (21) /** HDMA */
#define CYGNUM_HAL_INTERRUPT_UHPHS  (22) /** USB Host High Speed */
#define CYGNUM_HAL_INTERRUPT_LCDC   (23) /** LCD Controller */
#define CYGNUM_HAL_INTERRUPT_AC97C  (24) /** AC97 Controller */
#define CYGNUM_HAL_INTERRUPT_EMAC   (25) /** Ethernet MAC */
#define CYGNUM_HAL_INTERRUPT_ISI    (26) /** Image Sensor Interface */
#define CYGNUM_HAL_INTERRUPT_UDPHS  (27) /** USB Device HS */
#define CYGNUM_HAL_INTERRUPT_MCI1   (29) /** Multimedia Card Interface 1 */
#define CYGNUM_HAL_INTERRUPT_VDEC   (30) /** Video Decoder */
#define CYGNUM_HAL_INTERRUPT_IRQ0   (31) /** Advanced Interrupt Controller (IRQ0) */
#define AT91C_ALL_INT   (0xEFFFFFFF) /** ALL VALID INTERRUPTS */
//SAM9G45-0001.ADD.End
#else
//SAM9X25-0001.ADD.End
#define CYGNUM_HAL_INTERRUPT_PIOA       2
#define CYGNUM_HAL_INTERRUPT_PIOB       3
#define CYGNUM_HAL_INTERRUPT_PIOC       4
#define CYGNUM_HAL_INTERRUPT_ADC        5
#define CYGNUM_HAL_INTERRUPT_USART0     6
#define CYGNUM_HAL_INTERRUPT_USART1     7
#define CYGNUM_HAL_INTERRUPT_USART2     8
#define CYGNUM_HAL_INTERRUPT_MCI        9
#define CYGNUM_HAL_INTERRUPT_UDP        10
#define CYGNUM_HAL_INTERRUPT_TWI        11
#define CYGNUM_HAL_INTERRUPT_SPI        12
#define CYGNUM_HAL_INTERRUPT_SPI1       13
#define CYGNUM_HAL_INTERRUPT_SSC        14

#define CYGNUM_HAL_INTERRUPT_TC0        17
#define CYGNUM_HAL_INTERRUPT_TC1        18
#define CYGNUM_HAL_INTERRUPT_TC2        19
#define CYGNUM_HAL_INTERRUPT_UHP        20
#define CYGNUM_HAL_INTERRUPT_EMAC       21
#define CYGNUM_HAL_INTERRUPT_ISI        22
#define CYGNUM_HAL_INTERRUPT_USART3     23
#define CYGNUM_HAL_INTERRUPT_USART4     24
#define CYGNUM_HAL_INTERRUPT_USART5     25
#define CYGNUM_HAL_INTERRUPT_TC3        26
#define CYGNUM_HAL_INTERRUPT_TC4        27
#define CYGNUM_HAL_INTERRUPT_TC5        28
#define CYGNUM_HAL_INTERRUPT_IRQ0       29
#define CYGNUM_HAL_INTERRUPT_IRQ1       30
#define CYGNUM_HAL_INTERRUPT_IRQ2       31
#endif

// Interrupts which are multiplexed on to the System Interrupt
//SAM9X25-0001.DEL #define CYGNUM_HAL_INTERRUPT_SDRAMC     32 /* T.B.D. Need check */
#define CYGNUM_HAL_INTERRUPT_PITC       33
//SAM9X25-0001.DEL #define CYGNUM_HAL_INTERRUPT_RTTC       34 /* T.B.D. Need check */
//SAM9X25-0001.DEL #define CYGNUM_HAL_INTERRUPT_PMC        35 /* T.B.D. Need check */
//SAM9X25-0001.DEL #define CYGNUM_HAL_INTERRUPT_WDTC       36 /* T.B.D. Need check */
//SAM9X25-0001.DEL #define CYGNUM_HAL_INTERRUPT_RSTC       37 /* T.B.D. Need check */
#define CYGNUM_HAL_INTERRUPT_DBG        38

#define CYGNUM_HAL_ISR_MIN              0
#define CYGNUM_HAL_ISR_MAX              38

#define CYGNUM_HAL_ISR_COUNT            (CYGNUM_HAL_ISR_MAX + 1)

// The vector used by the Real time clock
#ifdef CYGBLD_HAL_ARM_AT91_TIMER_TC
#define CYGNUM_HAL_INTERRUPT_RTC        CYGNUM_HAL_INTERRUPT_TC0
#endif
#ifdef CYGBLD_HAL_ARM_AT91_TIMER_PIT
// used by Exegin application
#define CYGNUM_HAL_INTERRUPT_RTC        CYGNUM_HAL_INTERRUPT_PITC
#endif

//----------------------------------------------------------------------------
// Reset.
__externC void hal_at91_reset_cpu(void);
#define HAL_PLATFORM_RESET() hal_at91_reset_cpu()

#define HAL_PLATFORM_RESET_ENTRY 0x0000000

#endif // CYGONCE_HAL_PLATFORM_INTS_H
