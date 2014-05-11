//==========================================================================
//
//      sync/cnt_sem.cxx
//
//      Counting semaphore implementation
//
//==========================================================================
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
//==========================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):   nickg
// Contributors:        nickg
// Date:        1997-09-24
// Purpose:     Cyg_Counting_Semaphore implementation
// Description: This file contains the implementations of the counting semaphore
//              class.
//
//####DESCRIPTIONEND####
//
//==========================================================================

#include <pkgconf/kernel.h>

#include <cyg/kernel/ktypes.h>         // base kernel types
#include <cyg/infra/cyg_trac.h>        // tracing macros
#include <cyg/infra/cyg_ass.h>         // assertion macros
#include <cyg/kernel/instrmnt.h>       // instrumentation

#include <cyg/kernel/thread.inl>       // Cyg_Thread inlines

#include <cyg/kernel/sema.hxx>         // our header

#include <cyg/kernel/sched.inl>        // scheduler inlines


// Semaphores may optionally be placed on a housekeeping list so that all semaphores may be located easily. This is useful mainly in conjunction with source-level debugging.
#ifdef CYGVAR_KERNEL_SYNCOBJ_LIST

Cyg_Counting_Semaphore *Cyg_Counting_Semaphore::csem_list = 0;

inline void
Cyg_Counting_Semaphore::add_to_list( void )
{
    Cyg_Scheduler::lock();

    if( csem_list == 0 )
        list_next = this;
    else {
        Cyg_Counting_Semaphore *prev = csem_list;
        do {
            if ( this == prev )
                break; // found it already!
            prev = prev->list_next;
        } while ( prev != csem_list );
        if ( this != prev ) {
            // insert it in the list:
            list_next = csem_list->list_next;
            csem_list->list_next = this;
        }
    }
    csem_list = this;

    Cyg_Scheduler::unlock();
}

inline void
Cyg_Counting_Semaphore::remove_from_list( void )
{
    Cyg_Scheduler::lock();

    Cyg_Counting_Semaphore *prev = csem_list;

    do {
        if( prev->list_next == this ) {
            prev->list_next = list_next;
            if( csem_list == this )
                csem_list = list_next;
            break;
        }
        prev = prev->list_next;
    } while ( prev != csem_list );
    
    Cyg_Scheduler::unlock();
}

#endif


// -------------------------------------------------------------------------
// Constructor

Cyg_Counting_Semaphore::Cyg_Counting_Semaphore(             
    cyg_count32 init_count              // Initial count value
    )
{
    count       = init_count;
	
#ifdef CYGVAR_KERNEL_SYNCOBJ_LIST
    // Add semaphore to housekeeping list
    add_to_list();
#endif    
	
}

// -------------------------------------------------------------------------
// Destructor

Cyg_Counting_Semaphore::~Cyg_Counting_Semaphore()
{
    CYG_ASSERT( queue.empty(), "Destroying semaphore with waiting threads");
	
#ifdef CYGVAR_KERNEL_SYNCOBJ_LIST
    // Remove semaphore from housekeeping list
    remove_from_list();
#endif    
	
}
        
// -------------------------------------------------------------------------
// Wait until the count can be decremented without it becoming
// negative.

cyg_bool Cyg_Counting_Semaphore::wait()
{
    cyg_bool result = true;
    Cyg_Thread *self = Cyg_Thread::self();
    
    // Prevent preemption
    Cyg_Scheduler::lock();

    CYG_INSTRUMENT_CNTSEM( CLAIM, this, count );
        
    while( count == 0 && result )
    {
        self->set_sleep_reason( Cyg_Thread::WAIT );
        
        self->sleep();
        
        queue.enqueue( self );

        CYG_INSTRUMENT_CNTSEM( WAIT, this, 0 );

        // Allow other threads to run
        Cyg_Scheduler::reschedule();

        CYG_INSTRUMENT_CNTSEM( WOKE, this, count );

        switch( self->get_wake_reason() )
        {
        case Cyg_Thread::DESTRUCT:
        case Cyg_Thread::BREAK:
            result = false;
            break;
            
        case Cyg_Thread::EXIT:            
            self->exit();
            break;

        default:
            break;
        }
    }

    if( result ) count--;
        
    // Unlock the scheduler
    Cyg_Scheduler::unlock();

    return result;
}

// -------------------------------------------------------------------------
// Wait until the count can be decremented without it becoming
// negative.

#ifdef CYGFUN_KERNEL_THREADS_TIMER

cyg_bool
Cyg_Counting_Semaphore::wait( cyg_tick_count timeout )
{
    cyg_bool result = true;
    Cyg_Thread *self = Cyg_Thread::self();
    
    // Prevent preemption
    Cyg_Scheduler::lock();

    CYG_INSTRUMENT_CNTSEM( CLAIM, this, count );
        
    // Set the timer _once_ outside the loop.
    self->set_timer( timeout, Cyg_Thread::TIMEOUT  );

    // If the timeout is in the past, the wake reason will have been
    // set to something other than NONE already. If the count is zero,
    // set the result false to force an immediate return. If the count
    // is non-zero, then this wait will succeed anyway.
    
    if( self->get_wake_reason() != Cyg_Thread::NONE &&
        0 == count )
        result = false;
            
    while ( 0 == count && result ) {

        // must reset the sleep reason every time
        self->set_sleep_reason( Cyg_Thread::TIMEOUT );

        self->sleep();

        queue.enqueue( self );

        CYG_INSTRUMENT_CNTSEM( WAIT, this, 0 );

        // Allow other threads to run
        Cyg_Scheduler::reschedule();

        CYG_INSTRUMENT_CNTSEM( WOKE, this, count );

        switch( self->get_wake_reason() )
        {
        case Cyg_Thread::TIMEOUT:
            result = false;
            CYG_INSTRUMENT_CNTSEM( TIMEOUT, this, count);
            break;
            
        case Cyg_Thread::DESTRUCT:
        case Cyg_Thread::BREAK:
            result = false;
            break;
            
        case Cyg_Thread::EXIT:            
            self->exit();
            break;

        default:
            break;
        }
    }

    // Clear the timeout. It is irrelevant whether the alarm has
    // actually gone off or not.
    self->clear_timer();
        
    if ( result ) count--;

    // Unlock the scheduler and maybe switch threads
    Cyg_Scheduler::unlock();

    return result;
}

#endif // CYGFUN_KERNEL_THREADS_TIMER

// -------------------------------------------------------------------------
// Try to decrement, but fail if not possible

cyg_bool Cyg_Counting_Semaphore::trywait()
{
    cyg_bool result = true;
    
    // Prevent preemption
    Cyg_Scheduler::lock();

    if( count > 0 ) count--;
    else            result = false;

    CYG_INSTRUMENT_CNTSEM( TRY, this, result );
            
    // Unlock the scheduler and maybe switch threads
    Cyg_Scheduler::unlock();
    
    return result;
}
        
// -------------------------------------------------------------------------
// Increment count

void Cyg_Counting_Semaphore::post()
{
    // Prevent preemption
    Cyg_Scheduler::lock();

    CYG_INSTRUMENT_CNTSEM( POST, this, 0 );
            
    count++;
        
    if( !queue.empty() ) {

        // The queue is non-empty, so grab the next
        // thread from it and wake it up. The waiter
        // will decrement the count when he is awakened.

        Cyg_Thread *thread = queue.dequeue();

        thread->set_wake_reason( Cyg_Thread::DONE );
        
        thread->wake();

        CYG_INSTRUMENT_CNTSEM( WAKE, this, thread );
    }
    
    // Unlock the scheduler and maybe switch threads
    Cyg_Scheduler::unlock();    
}

// -------------------------------------------------------------------------
// Get current count value

cyg_count32 Cyg_Counting_Semaphore::peek() const
{
    // This is a single read of the value of count.
    // This is already atomic, hence there is no need
    // to lock the scheduler.
    
    return count;    
}

// -------------------------------------------------------------------------
// EOF sync/cnt_sem.cxx