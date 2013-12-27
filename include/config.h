/*      ----------------------------------------------------------------------------
        FILE:                           config.h
        PROJECT:                        pinguino - http://www.pinguino.cc/
        PURPOSE:                        Pinguino PIC32 bootloader config header
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


#define INPUT	1
#define OUTPUT	0

#if defined(__32MX440F256H__)
        #pragma config UPLLEN   = ON    // USB Clock (48 Mhz)
        #pragma config UPLLDIV  = DIV_2 // USB PLL Divider
        #pragma config FPLLMUL  = MUL_20// PLL Multiplier
        #pragma config FPLLIDIV = DIV_2 // PLL Input Divider
        #pragma config FPLLODIV = DIV_1 // PLL Output Divider
        #pragma config FPBDIV   = DIV_1 // Peripheral Clock Divider
        #pragma config IESO     = OFF   // Internal External switch-over
        #pragma config FWDTEN   = OFF   // Watchdog Timer
        #pragma config WDTPS    = PS1   // Watchdog Timer Postscale
        #pragma config POSCMOD  = HS    // Primary Oscillator
        #pragma config SOSCEN   = OFF   // Secondary Oscillator
        #pragma config FNOSC    = PRIPLL// Oscillator selection
        #pragma config OSCIOFNC = OFF   // CLKO Enable
        #pragma config FCKSM    = CSECMD// Clock switching enabled, Fail Safe Clock Monitor Disabled
        #pragma config DEBUG    = OFF   // Background Debugger
        #pragma config BWP      = OFF   // Boot Flash write protect
        #pragma config PWP      = OFF   // Program Flash write protect
        #pragma config CP       = OFF   // Code Protect
#endif
