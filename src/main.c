/*	----------------------------------------------------------------------------
	FILE:				main.c
	PROJECT:			pinguino - http://www.pinguino.cc/
	PURPOSE:			Bootloader for 32 bit Pinguino boards
	PROGRAMER:			Andrej Golac <andrej.golac@runbox.com>
	FIRST RELEASE:			January 2014
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
	--------------------------------------------------------------------------*/

#include <xc.h>
#include <config.h>
#include <stdint.h>
#include <usb.h>

unsigned int __attribute__((nomips16))  INTEnableInterrupts(void)
{
    unsigned int status = 0;

    asm volatile("ei    %0" : "=r"(status));

    return status;
}


void __attribute__ ((nomips16)) INTEnableSystemMultiVectoredInt(void)
{
    unsigned int val;

    // set the CP0 cause IV bit high
    asm volatile("mfc0   %0,$13" : "=r"(val));
    val |= 0x00800000;
    asm volatile("mtc0   %0,$13" : "+r"(val));

    INTCONSET = _INTCON_MVEC_MASK;

    // set the CP0 status IE bit high to turn on interrupts
    INTEnableInterrupts();

}

int main (void) {

	INTEnableSystemMultiVectoredInt();
	InitializeUSB();
while (1) {
//        TRISGCLR = _PORTG_RG6_MASK;
//        PORTGCLR = _PORTG_RG6_MASK;

}
return 1;
}
