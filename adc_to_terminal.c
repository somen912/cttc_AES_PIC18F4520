
// PIC18F4520 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config OSC = HS         // Oscillator Selection bits (HS oscillator)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = OFF      // MCLR Pin Enable bit (RE3 input pin enabled; MCLR disabled)

// CONFIG4L
#pragma config STVREN = OFF     // Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 20000000


void initialize_uart(unsigned char data_txsta,unsigned char data_rcsta)
{
    TXSTA=data_txsta;
    SPEN=1;
    RCSTA=data_rcsta;
    SPBRG=32;
}

void transfer(unsigned char value2)
{
    TXREG=value2;
    while(TXIF==0);
    TXIF=0;
}

char receive()
{
    unsigned char data;
    
    while(RCIF==0);
    data=RCREG;
    RCIF=0;
    return data;
}

void bcd_ascii(unsigned char value1)
{
    unsigned char temp= value1;
    temp&=0xF0;
    temp>>=4;
    temp|=0x30;
    transfer(temp);
    
    temp=value1;
    temp&=0x0F;
    temp|=0x30;
    transfer(temp);
    
    TXREG=0x0D;
    while(TXIF==0);
    TXIF=0;

}

void initialize_adc(unsigned char value0,unsigned char value1,unsigned char value2)
{
    ADCON0=value0;
    ADCON1=value1;
    ADCON2=value2;
}

char adc_getvalue() // designed for right justified
{
    unsigned char l_byte,h_byte,temp;
    __delay_ms(1);
        
    ADCON0bits.GO=1;
    while(ADCON0bits.DONE == 1);
    
    l_byte=ADRESL;
    h_byte=ADRESH;
    
    l_byte>>=2;
    l_byte&=0x3F;
    
    h_byte<<=6;
    h_byte&=0xC0;
    
    temp=l_byte|h_byte;
    __delay_ms(250);
    return temp;
    

}


void main()
{
    unsigned char buffer[1];
    
    TRISD=0;
    TRISA0=1;
    TRISC6=0;
    TRISC7=1;
   
    initialize_adc(0x01,0x0E,0x80); // its arguments are ADCON0,ADCON1,ADCON2
    
    initialize_uart(0x20,0x90);  // its arguments are TXSTA, RCSTA
    
    while(1)
    {
        __delay_ms(1);
        unsigned char temp;
        
        temp=adc_getvalue();
        bcd_ascii(temp);
        
        
        
    }
    
}
