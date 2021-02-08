
// PIC18F4520 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config OSC = HS         // Oscillator Selection bits (HS oscillator)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
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

#define _XTAL_FREQ 20000000

#define rs RC0
#define rw RC1
#define en RC2

#define pin1 RC3
#define pin2 RC4
#define pin3 RC5
#define pin4 RC6

#define push_button1 RB0
#define push_button2 RB1



void lcd_cmd(unsigned char command)
{
    PORTD=command;
    rs=0;
    rw=0;
    en=1;
    __delay_ms(25);
    en=0;
}

void lcd_data(unsigned char dat)
{
    PORTD=dat;
    rs=1;
    rw=0;
    en=1;
    __delay_ms(25);
    en=0;
}

void lcd_string(const unsigned char *str, unsigned char num)
{
    unsigned char i;
    
    for(i=0;i<num;i++)
    {
        lcd_data(str[i]);
    }
}

void lcd_initialize()
{
    lcd_cmd(0x38);  // 2 lines and 5X7 matrix
    lcd_cmd(0x06);  // increment cursor (shift cursor to right)
    lcd_cmd(0x0C);  // display on cursor off 
    lcd_cmd(0x01);  // clear display screen
}


void main()
{
    TRISB0=1;
    TRISB1=1;
    TRISC0=0;
    TRISC1=0;
    TRISC2=0;
    TRISC3=0;
    TRISC4=0;
    TRISC5=0;
    TRISC6=0;
    TRISD=0;
    
    lcd_initialize();
            
    if(push_button1==1)
    {
        pin1=1;
        pin2=0;
        pin3=1;
        pin4=0;
        
        lcd_cmd(0x01);
        lcd_cmd(0x80);  // force cursor to begin from the 1st line
        lcd_string("ROTATING FORWARD",16);
    }
    else if(push_button2==1)
    {
        pin1=0;
        pin2=1;
        pin3=0;
        pin4=1;
        
        lcd_cmd(0x01);
        lcd_cmd(0xC0); // force cursor to begin from the second line
        lcd_string("ROTATING REVERSE",16);
    }
    else
    {
        pin1=0;
        pin2=0;
        pin3=0;
        pin4=0;
        
        lcd_cmd(0x01);
        lcd_cmd(0xC0); // force cursor to begin from the second line
        lcd_string("MOTOR STOPPED",16);
    
    }
}