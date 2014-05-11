/*==========================================================================
//
//      at91sam9x25ek_misc.c
//
//      HAL misc board support code for Atmel AT91SAM9X25-EK board
//
//==========================================================================
// ####ECOSGPLCOPYRIGHTBEGIN####
// -------------------------------------------
// This file is part of eCos, the Embedded Configurable Operating System.
// Copyright (C) 2006 Free Software Foundation, Inc.
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
// Author(s):    danielh
// Date:         2010-01-01
// Purpose:      HAL board support
// Description:  Implementations of HAL board interfaces
//
//####DESCRIPTIONEND####
//
//========================================================================*/
// =============================================================================
// Key-change    Date       Author   Description
// --------------+----------+--------+------------------------------------------
// SAM9X25-0002  2011/03/21 TuPN     Create file - Update address of peripherals
//
// =============================================================================

#include <pkgconf/system.h>
#include <pkgconf/hal.h>

#include <sys/reent.h>

#include <cyg/hal/hal_io.h>             // IO macros
#include <cyg/hal/hal_diag.h>

#define errno (*__errno())

//extern int *__errno ( void );

// MATRIX defines
#define AT91C_MATRIX_SCFG4        				(0xFFFFDE50)
#define AT91C_MATRIX_DEFMSTR_TYPE 				(0x3UL << 16) // (MATRIX) Default Master Type
#define	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR	(0x2UL << 16)    // (MATRIX) Fixed Default Master. At the end of current slave access, if no other master request is pending, the slave connects with fixed which number is in FIXED_DEFMSTR field. This results in not having the one cycle latency when the fixed master re-trying access on the slave.
#define AT91C_MATRIX_FIXED_DEFMSTR4 			(0xFUL << 18) // (MATRIX) Fixed Index of Default Master
#define	AT91C_MATRIX_FIXED_DEFMSTR4_DMA1_PORT0 	(0x4UL << 18)  // (MATRIX) DMA1 Port 0 Master is Default Master

// -------------------------------------------------------------------------
// Hardware init

void
hal_plf_hardware_init (void)
{
	// MATRIX setup
	cyg_uint32 val;
	
	HAL_READ_UINT32(AT91C_MATRIX_SCFG4, val);
	val &= ~(AT91C_MATRIX_DEFMSTR_TYPE | AT91C_MATRIX_FIXED_DEFMSTR4);
	val |= (AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR | AT91C_MATRIX_FIXED_DEFMSTR4_DMA1_PORT0);
	HAL_WRITE_UINT32(AT91C_MATRIX_SCFG4, val);

  /* Enable serial port pins and clocks if UARTS are used for debug output */
#ifdef CYGBLD_HAL_ARM_AT91_SERIAL_UART
#if defined(CYGPKG_IO_SERIAL_ARM_AT91_SERIAL0)
  HAL_ARM_AT91_PIO_CFG(AT91_USART_RXD0);
  HAL_ARM_AT91_PIO_CFG(AT91_USART_TXD0);
  HAL_WRITE_UINT32(AT91_PMC+AT91_PMC_PCER, AT91_PMC_PCER_US0);
#endif
#if defined(CYGPKG_IO_SERIAL_ARM_AT91_SERIAL1)
  HAL_ARM_AT91_PIO_CFG(AT91_USART_RXD1);
  HAL_ARM_AT91_PIO_CFG(AT91_USART_TXD1);
  HAL_WRITE_UINT32(AT91_PMC+AT91_PMC_PCER, AT91_PMC_PCER_US1);
#endif
#endif

#if 1 /* TUPN.TEST */
  HAL_ARM_AT91_PIO_CFG(AT91_USART_RXD0);
  HAL_ARM_AT91_PIO_CFG(AT91_USART_TXD0);
  HAL_WRITE_UINT32(AT91_PMC+AT91_PMC_PCER, AT91_PMC_PCER_US0);

  HAL_ARM_AT91_PIO_CFG(AT91_USART_RXD1);
  HAL_ARM_AT91_PIO_CFG(AT91_USART_TXD1);
  HAL_WRITE_UINT32(AT91_PMC+AT91_PMC_PCER, AT91_PMC_PCER_US1);

  HAL_ARM_AT91_PIO_CFG(AT91_USART_RXD2);
  HAL_ARM_AT91_PIO_CFG(AT91_USART_TXD2);
  HAL_WRITE_UINT32(AT91_PMC+AT91_PMC_PCER, AT91_PMC_PCER_US2);

  HAL_ARM_AT91_PIO_CFG(AT91_USART_RXD3);
  HAL_ARM_AT91_PIO_CFG(AT91_USART_TXD3);
  HAL_WRITE_UINT32(AT91_PMC+AT91_PMC_PCER, AT91_PMC_PCER_US3);
#endif

  /* Enable port pins if DBG port is used for debug output */
#if defined(CYGBLD_HAL_ARM_AT91_SERIAL_DBG)
  HAL_ARM_AT91_PIO_CFG(AT91_DBG_DTXD);
  HAL_ARM_AT91_PIO_CFG(AT91_DBG_DRXD);
#endif

  /* Setup the Reset controller. Allow user resets */
  HAL_WRITE_UINT32(AT91_RST + AT91_RST_RMR,
                   AT91_RST_RMR_URSTEN | 10 << 8 | AT91_RST_RMR_KEY);

#ifdef CYGBLD_HAL_ARM_AT91_TIMER_TC
  /* Enable peripheral clocks for TC 0 and 2 if they are to be used */

//SAM9X25-0002.DEL  HAL_WRITE_UINT32(AT91_PMC+AT91_PMC_PCER,
//SAM9X25-0002.DEL                   AT91_PMC_PCER_TC0 | AT91_PMC_PCER_TC2);
//SAM9X25-0002.ADD.Start
  HAL_WRITE_UINT32(AT91_PMC+AT91_PMC_PCER, AT91_PMC_PCER_TC);
//SAM9X25-0002.ADD.End

#endif

//TUPN.DEL - PB8,PB9 use for Eth0 -
//TUPN.DEL  /* Initialize GPIOs */ /* T.B.D */
//TUPN.DEL  /* Configure IO pins for LEDS. */
//TUPN.DEL  HAL_ARM_AT91_GPIO_CFG_PULLUP(AT91_GPIO_PB8, AT91_PIN_PULLUP_DISABLE);
//TUPN.DEL  HAL_ARM_AT91_GPIO_CFG_PULLUP(AT91_GPIO_PB9, AT91_PIN_PULLUP_DISABLE);
//TUPN.DEL  HAL_ARM_AT91_GPIO_CFG_DIRECTION(AT91_GPIO_PB8, AT91_PIN_OUT);
//TUPN.DEL  HAL_ARM_AT91_GPIO_CFG_DIRECTION(AT91_GPIO_PB9, AT91_PIN_OUT);
//TUPN.DEL  // Clear the user LED to off and set the power LED to on.
//TUPN.DEL  // The logic is inverted for the user LED.
//TUPN.DEL  HAL_ARM_AT91_GPIO_PUT(AT91_GPIO_PB8, 1);
//TUPN.DEL  HAL_ARM_AT91_GPIO_PUT(AT91_GPIO_PB9, 1);

  /* Configure IO pins for push-button switches.*/
  HAL_ARM_AT91_GPIO_CFG_PULLUP(AT91_GPIO_PA30, AT91_PIN_PULLUP_DISABLE);
  HAL_ARM_AT91_GPIO_CFG_PULLUP(AT91_GPIO_PA31, AT91_PIN_PULLUP_DISABLE);
  HAL_ARM_AT91_GPIO_CFG_DIRECTION(AT91_GPIO_PA30, AT91_PIN_IN);
  HAL_ARM_AT91_GPIO_CFG_DIRECTION(AT91_GPIO_PA31, AT91_PIN_IN);

  /* Enable peripheral clock to PIOA and PIOB and PIOC. */
  HAL_WRITE_UINT32(AT91_PMC + AT91_PMC_PCER,
                   AT91_PMC_PCER_PIOA | AT91_PMC_PCER_PIOB | AT91_PMC_PCER_PIOC);

#ifndef CYGPKG_IO_WATCHDOG
  /* Disable the watchdog. The eCos philosophy is that the watchdog is
     disabled unless the watchdog driver is used to enable it.
     Whoever if we disable it here we cannot re-enable it in the
     watchdog driver, hence the conditional compilation. */
//  HAL_WRITE_UINT32(AT91_WDTC + AT91_WDTC_WDMR, AT91_WDTC_WDMR_DIS);
#endif

/* Perform some platform specific bits to get the Ethernet hardware
   setup. Specifically if a specific phy is used and does not start in
   the correct mode a function needs to be supplied as part of the plf
   to do the necessary initializations.
*/
#ifdef CYGPKG_DEVS_ETH_ARM_AT91
#ifdef HAL_PLF_ETH_INIT
       HAL_PLF_ETH_INIT();
#endif
#endif
}

// -------------------------------------------------------------------------
// Helper functions

// The AT91SAM9G20-EK board has 2 LEDs attached to GPIOs.
void
hal_at91sam9g20ek_led (int val)
{
	/* T.B.D */
  // Turn LEDs on or off.
  // The logic is inverted for the user LED.
//  HAL_ARM_AT91_GPIO_PUT(AT91_GPIO_PB8, !(val & 1));
//  HAL_ARM_AT91_GPIO_PUT(AT91_GPIO_PB9, val & 2);
}

void
hal_at91_set_leds(int val)
{
	/* T.B.D */
    hal_at91sam9g20ek_led(val);
}

// The AT92SAM9G20 board has 2 user push-buttons attached to GPIOs.
//cyg_uint32
//hal_at91sam9g20_pushbutton(void)
//{
//  cyg_uint32 pb0, pb1;
  /* T.B.D */

//  HAL_ARM_AT91_GPIO_GET(AT91_GPIO_PA30, pb0);
//  HAL_ARM_AT91_GPIO_GET(AT91_GPIO_PA31, pb1);

//  return (pb1 << 1) | pb0;
//}

#if (__GNUC__ >= 3)
// Versions of gcc/g++ after 3.0 (approx.), when configured for Linux
// native development (specifically, --with-__cxa_enable), have
// additional dependencies related to the destructors for static
// objects. When compiling C++ code with static objects the compiler
// inserts a call to __cxa_atexit() with __dso_handle as one of the
// arguments. __cxa_atexit() would normally be provided by glibc, and
// __dso_handle is part of crtstuff.c. Synthetic target applications
// are linked rather differently, so either a differently-configured
// compiler is needed or dummy versions of these symbols should be
// provided. If these symbols are not actually used then providing
// them is still harmless, linker garbage collection will remove them.

// gcc 3.2.2 (approx). The libsupc++ version of the new operator pulls
// in exception handling code, even when using the nothrow version and
// building with -fno-exceptions. libgcc_eh.a provides the necessary
// functions, but requires a dl_iterate_phdr() function. That is related
// to handling dynamically loaded code so is not applicable to eCos.
int
dl_iterate_phdr(void* arg1, void* arg2)
{
    return -1;
}

struct _reent impure_data = { 0, 0, "", 0, "C"}; // stub for gcc 4.6.1

struct _reent* _impure_ptr = &impure_data;

int* __errno ()
{
    return &_impure_ptr->_errno;
}

#endif

//--------------------------------------------------------------------------
// EOF at91sam9g20ek_misc.c
