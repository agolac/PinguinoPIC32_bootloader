/*      ----------------------------------------------------------------------------
        FILE:                           crt0.S
        PROJECT:                        pinguino - http://www.pinguino.cc/
        PURPOSE:                        C startup code
        PROGRAMER:                      Andrej Golac <andrej.golac@runbox.com>
        FIRST RELEASE:                  January 2014
        LAST RELEASE:
        ----------------------------------------------------------------------------
        This is free software; you can redistribute it and/or modify it under the 
        terms of the GNU Lesser General Public License as published by the Free 
        Software Foundation; either version 2.1 of the License, or (at your option) 
        any later version.

        This software is distributed in the hope that it will be useful, but WITHOUT 
        ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
        FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more 
        details.

        You should have received a copy of the GNU Lesser General Public License along 
        with this library; if not, write to the Free Software Foundation, Inc., 59 
        Temple Place, Suite 330, Boston, MA  02111-1307  USA
        ----------------------------------------------------------------------------
*/




#include <xc.h>
#include <cp0defs.h>
#include <regdef.h>

.section .reset, "ax", @progbits
.align 2
.set noreorder
.ent _reset
_reset:
		la	t0, _startup
		jr	t0	

.align 2
.end _reset
.globl _reset

.section .startup, "ax", @progbits
.align 2
.set noreorder
.ent _startup
_startup:
		la	sp, _stack		/* Initialize Stack */
		la	gp, _gp			/* Initialize Global pointer */
		mtc0	zero, _CP0_COUNT	/* Initialize COUNT register */
		mtc0	zero, _CP0_COMPARE	/* Initialize COMPARE register */
		li	t0, 0x00800000
		mtc0	t0, _CP0_CAUSE		/* Initialize CAUSE register */
		la	t1, _ebase_address
		mtc0	t1, _CP0_EBASE		/* Initialize EBASE register */
.end _startup
