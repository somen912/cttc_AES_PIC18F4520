
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

#define row0 RB0
#define row1 RB1
#define row2 RB2
#define row3 RB3
#define col0 RB4
#define col1 RB5
#define col2 RB6
#define col3 RB7

#define rs RC0
#define rw RC1
#define en RC2



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
    lcd_cmd(0x38);
    lcd_cmd(0x04);
    lcd_cmd(0x0C);
    lcd_cmd(0x01);
}

int column;

void main()
{
    TRISB=0xF0;
    TRISC=0;
    TRISD=0;
    
    lcd_initialize();
    
    
    while(1)
    {
        do
        {
            PORTB=0x0F;
            column=PORTB;
            column&=0xF0;
        }while(column==0x00);
        
        PORTB=0x01;
        if(row0 && col0)
        {
            lcd_cmd(0x01);
            lcd_cmd(0x80);
            lcd_string("button 1",8);
        }
        else if(row0 && col1)
        {
            lcd_cmd(0x01);
            lcd_cmd(0x80);
            lcd_string("button 2",8);
        }
        else if(row0 && col2)
        {
            lcd_cmd(0x01);
            lcd_cmd(0x80);
            lcd_string("button 3",8);
        }
        else if(row0 && col3)
        {
            lcd_cmd(0x01);
            lcd_cmd(0x80);
            lcd_string("button 4",8);
        }
        
        PORTB=0x02;
       if(row1 && col0)
        {
            lcd_cmd(0x01);
            lcd_cmd(0x80);
            lcd_string("button 5",8);
        }
        else if(row1 && col1)
        {
            lcd_cmd(0x01);
            lcd_cmd(0x80);
            lcd_string("button 6",8);
        }
        else if(row1 && col2)
        {
            lcd_cmd(0x01);
            lcd_cmd(0x80);
            lcd_string("button 7",8);
        }
        else if(row1 && col3)
        {
            lcd_cmd(0x01);
            lcd_cmd(0x80);
            lcd_string("button 8",8);
        }
        
        PORTB=0x04;
       if(row2 && col0)
        {
            lcd_cmd(0x01);
            lcd_cmd(0x80);
            lcd_string("button 9",8);
        }
        else if(row2 && col1)
        {
            lcd_cmd(0x01);
            lcd_cmd(0x80);
            lcd_string("button 10",9);
        }
        else if(row2 && col2)
        {
            lcd_cmd(0x01);
            lcd_cmd(0x80);
            lcd_string("button 11",9);
        }
        else if(row2 && col3)
        {
            lcd_cmd(0x01);
            lcd_cmd(0x80);
            lcd_string("button 12",9);
        }
        
         PORTB=0x08;
        if(row3 && col0)
        {
            lcd_cmd(0x01);
            lcd_cmd(0x80);
            lcd_string("button 13",9);
        }
        else if(row3 && col1)
        {
            lcd_cmd(0x01);
            lcd_cmd(0x80);
            lcd_string("button 14",9);
        }
        else if(row3 && col2)
        {
            lcd_cmd(0x01);
            lcd_cmd(0x80);
            lcd_string("button 15",9);
        }
        else if(row3 && col3)
        {
            lcd_cmd(0x01);
            lcd_cmd(0x80);
            lcd_string("button 16",9);
        }
        
        
    }  
    
}