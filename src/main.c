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

int main (void) {

while (1) {
	U1PWRCbits.USBPWR = 1; // Start USB
	TRISBSET = 0x0080;
return 1;
}
}
