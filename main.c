// PIC24FJ128GA204 Configuration Bit Settings

// 'C' source line config statements

// CONFIG4
#pragma config DSWDTPS = DSWDTPS3       // Deep Sleep Watchdog Timer Postscale Select bits (1: 256 (8.3 mS))
#pragma config DSWDTOSC = LPRC          // DSWDT Reference Clock Select (DSWDT uses LPRC as reference clock)
#pragma config DSBOREN = OFF            // Deep Sleep BOR Enable bit (DSBOR Disabled)
#pragma config DSWDTEN = ON             // Deep Sleep Watchdog Timer Enable (DSWDT Enabled)
#pragma config DSSWEN = ON              // DSEN Bit Enable (Deep Sleep is controlled by the register bit DSEN)
#pragma config PLLDIV = DISABLED        // USB 96 MHz PLL Prescaler Select bits (PLL Disabled)
#pragma config I2C1SEL = DISABLE        // Alternate I2C1 enable bit (I2C1 uses SCL1 and SDA1 pins)
#pragma config IOL1WAY = ON             // PPS IOLOCK Set Only Once Enable bit (Once set, the IOLOCK bit cannot be cleared)

// CONFIG3
#pragma config WPFP = WPFP127           // Write Protection Flash Page Segment Boundary (Page 127 (0x1FC00))
#pragma config SOSCSEL = ON             // SOSC Selection bits (SOSC circuit selected)
#pragma config WDTWIN = PS25_0          // Window Mode Watchdog Timer Window Width Select (Watch Dog Timer Window Width is 25 percent)
#pragma config PLLSS = PLL_PRI          // PLL Secondary Selection Configuration bit (PLL is fed by the Primary oscillator)
#pragma config BOREN = ON               // Brown-out Reset Enable (Brown-out Reset Enable)
#pragma config WPDIS = WPDIS            // Segment Write Protection Disable (Disabled)
#pragma config WPCFG = WPCFGDIS         // Write Protect Configuration Page Select (Disabled)
#pragma config WPEND = WPENDMEM         // Segment Write Protection End Page Select (Write Protect from WPFP to the last page of memory)

// CONFIG2
#pragma config POSCMD = NONE            // Primary Oscillator Select (Primary Oscillator Disabled)
#pragma config WDTCLK = LPRC            // WDT Clock Source Select bits (WDT uses LPRC)
#pragma config OSCIOFCN = OFF           // OSCO Pin Configuration (OSCO/CLKO/RA3 functions as CLKO (FOSC/2))
#pragma config FCKSM = CSDCMD           // Clock Switching and Fail-Safe Clock Monitor Configuration bits (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = FRCDIV           // Initial Oscillator Select (Fast RC Oscillator with Postscaler (FRCDIV))
#pragma config ALTCMPI = CxINC_RB       // Alternate Comparator Input bit (C1INC is on RB13, C2INC is on RB9 and C3INC is on RA0)
#pragma config WDTCMX = WDTCLK          // WDT Clock Source Select bits (WDT clock source is determined by the WDTCLK Configuration bits)
#pragma config IESO = ON                // Internal External Switchover (Enabled)

// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler Select (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler Ratio Select (1:128)
#pragma config WINDIS = OFF             // Windowed WDT Disable (Standard Watchdog Timer)
#pragma config FWDTEN = ON              // Watchdog Timer Enable (WDT enabled in hardware)
#pragma config ICS = PGx1               // Emulator Pin Placement Select bits (Emulator functions are shared with PGEC1/PGED1)
#pragma config LPCFG = OFF              // Low power regulator control (Disabled - regardless of RETEN)
#pragma config GWRP = OFF               // General Segment Write Protect (Write to program memory allowed)
#pragma config GCP = OFF                // General Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = ON              // JTAG Port Enable (Enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>


#define _XTAL_FREQ 8000000
#define FCY _XTAL_FREQ
#include <libpic30.h>
#include <stdio.h>


int main(void) {
    
    TRISCbits.TRISC5 = 0;
    /* Enable RTC? */
    
    RCFGCALbits.RTCEN = 1;
    ALCFGRPTbits.ALRMEN = 1;
    ALCFGRPTbits.AMASK = 0b0001;
    
    while(1)
    {
        
        PORTCbits.RC5 = 1;
        __delay_ms(500);
        PORTCbits.RC5 = 0;
        __delay_ms(500);
        PORTCbits.RC5 = 1;
        __delay_ms(500);
        
        enterDeepSleep();
        
        PORTCbits.RC5 = 0;
        __delay_ms(500);
    }
    
    return 0;
}

void enterDeepSleep(void)
{
    RCONbits.DPSLP = 0;
    DSWAKE = 0;
    RCONbits.RETEN = 1;
    
    /* Required Deep Sleep sequence */
    DSCONbits.DSEN = 1;
    DSCONbits.DSEN = 1;
    
    Nop();
    Nop();
    Nop();
    
    //asm("PWRSAV #0");
    Sleep();
}