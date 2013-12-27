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
