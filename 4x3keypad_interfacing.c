
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

#define col0 RB0
#define col1 RB1
#define col2 RB2
#define row0 RB4
#define row1 RB5
#define row2 RB6
#define row3 RB7

void lcd_data(unsigned char data);
void lcd_cmd(unsigned char command);
void lcd_string(const unsigned char *string, unsigned char length);
void lcd_initialize();
void keypad();

void main()
{
    TRISD=0;
    TRISC=0;
    TRISB=0xF0;
    
    lcd_initialize();
    
    lcd_cmd(0x80);
       lcd_string("Code Somenplus",14);
       __delay_ms(2000);
    
       lcd_cmd(0x01);
       lcd_cmd(0x80);
       lcd_string("Enter Digits",12);
       lcd_cmd(0xc0);
    
    while(1)
    {
       keypad();
        
    }
}

void lcd_data(unsigned char data)
{
    PORTD=data;
    rs=1;
    rw=0;
    en=1;
    __delay_ms(5);
    en=0;
}

void lcd_cmd(unsigned char command)
{
    PORTD=command;
    rs=0;
    rw=0;
    en=1;
    __delay_ms(5);
    en=0;
}

void lcd_string(const unsigned char *string, unsigned char length)
{
    unsigned char i;
    for(i=0;i<length;i++)
    {
        lcd_data(string[i]);
    }
}

void lcd_initialize()
{
    lcd_cmd(0x38);
    lcd_cmd(0x06);
    lcd_cmd(0x0c);
    lcd_cmd(0x01);
}

void keypad()
{
    col0=1;
    col1=0;
    col2=0;
    
    if(row0==1)
    {
        lcd_data('1');
        while(row0==1);  
    }
    
    if(row1==1)
    {
        lcd_data('4');
        while(row1==1);
    }
    
    if(row2==1)
    {
        lcd_data('7');
        while(row2==1);   
    }
    
    if(row3==1)
    {
        lcd_data('*');
        while(row3==1);  
    }
    
    col0=0;
    col1=1;
    col2=0;
    
    if(row0==1)
    {
        lcd_data('2');
        while(row0==1);
    }
    
    if(row1==1)
    {
        lcd_data('5');
        while(row1==1);
    }
    
    if(row2==1)
    {
        lcd_data('8');
        while(row2==1); 
    }
    
    if(row3==1)
    {
        lcd_data('0');
        while(row3==1);  
    }
    
    col0=0;
    col1=0;
    col2=1;
    
    if(row0==1)
    {
        lcd_data('3');
        while(row0==1);
    }
    
    if(row1==1)
    {
        lcd_data('6');
        while(row1==1);
    }
    
    if(row2==1)
    {
        lcd_data('9');
        while(row2==1);
    }
    
    if(row3==1)
    {
        lcd_data('#');
        while(row3==1);    
    }
}