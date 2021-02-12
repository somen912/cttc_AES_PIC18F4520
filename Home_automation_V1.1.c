
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

#define led RB0
#define fan_pin1 RB1
#define fan_pin2 RB2
#define pump_pin1 RB3
#define pump_pin2 RB4


#define rs RC0
#define rw RC1
#define en RC2


char text1[]="To on light press 'a'";
char text2[]="To on fan press 'b'";
char text3[]="To off light press 'c'";
char text4[]="To off fan press 'd'";
char text11[]="To on pump press 'e'";
char text12[]="To off pump press 'f'";

char text5[]="#---------- Light is on -------------#";
char text6[]="#---------- Light is off -------------#";
char text7[]="#---------- Fan is on -------------#";
char text8[]="#---------- Fan is off -------------#";
char text13[]="#---------- Pump is on -------------#";
char text14[]="#---------- Pump is off -------------#";
char text9[]="Enter valid key";
char text10[]="#---- Welcome to Home Autoomation ----#";

int i;

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

void press_enter()   // press enter function
{
  TXREG=0x0D;
  while(TXIF==0);
  TXIF=0;
}


void main()
{
    TRISB=0;
    TRISD=0;
    TRISC0=0;
    TRISC1=0;
    TRISC2=0;
    
    int value;
    
    
    TXSTA=0x20;
    SPEN=1;
    
    RCSTA=0x90;
    SPBRG=32;
    
    lcd_initialize();
    
    lcd_cmd(0x80);
    lcd_string("Connected..!!",13);
    
    while(1)
    {
        
        press_enter();
        
      for(i=0;i<sizeof text10;i++)
      {
          TXREG=text10[i];
          while(TXIF==0);
          TXIF=0;
      }
        
        
        press_enter();
        
      for(i=0;i<sizeof text1;i++)
      {
          TXREG=text1[i];
          while(TXIF==0);
          TXIF=0;
      }
      
        press_enter();
      
      for(i=0;i<sizeof text2;i++)
      {
          TXREG=text2[i];
          while(TXIF==0);
          TXIF=0;
      }
      
        press_enter();
      
      for(i=0;i<sizeof text3;i++)
      {
          TXREG=text3[i];
          while(TXIF==0);
          TXIF=0;
      }
      
        press_enter();
      
      for(i=0;i<sizeof text4;i++)
      {
          TXREG=text4[i];
          while(TXIF==0);
          TXIF=0;
      }
      
        press_enter();
        
        for(i=0;i<sizeof text11;i++)
      {
          TXREG=text11[i];
          while(TXIF==0);
          TXIF=0;
      }
      
        press_enter();
        
        for(i=0;i<sizeof text12;i++)
      {
          TXREG=text12[i];
          while(TXIF==0);
          TXIF=0;
      }
      
        press_enter();
        
      while(RCIF==0);
      value=RCREG;
      RCIF=0;
      
      press_enter();
      
      if(value=='a')
      {
          led=1;
          lcd_cmd(0x01);
          lcd_cmd(0x80);
          lcd_string("LIGHT ON",8);
          
          for(i=0;i<sizeof text5;i++)
          {
            TXREG=text5[i];
            while(TXIF==0);
            TXIF=0;
          }
          
          press_enter();
          
          
      }
      else if(value=='c')
      {
          led=0;
          
          lcd_cmd(0x01);
          lcd_cmd(0xC0);
          lcd_string("LIGHT OFF",9);
          
          for(i=0;i<sizeof text6;i++)
          {
            TXREG=text6[i];
            while(TXIF==0);
            TXIF=0;
          }
          
          press_enter();
      }
      else if(value=='b')
      {
          fan_pin1=1;
          fan_pin2=0;
          
          lcd_cmd(0x01);
          lcd_cmd(0x80);
          lcd_string("FAN ON",6);
          
          for(i=0;i<sizeof text7;i++)
          {
            TXREG=text7[i];
            while(TXIF==0);
            TXIF=0;
          }
          
          press_enter();
      }
      else if(value=='d')
      {
          fan_pin1=0;
          fan_pin2=0;
          
          lcd_cmd(0x01);
          lcd_cmd(0xC0);
          lcd_string("FAN OFF",7);
          
          for(i=0;i<sizeof text8;i++)
          {
            TXREG=text8[i];
            while(TXIF==0);
            TXIF=0;
          }
          
          press_enter();
      }
      else if(value=='e')
      {
          pump_pin1=1;
          pump_pin2=0;
          
          lcd_cmd(0x01);
          lcd_cmd(0x80);
          lcd_string("PUMP ON",7);
          
          for(i=0;i<sizeof text13;i++)
          {
            TXREG=text13[i];
            while(TXIF==0);
            TXIF=0;
          }
          
          press_enter();
      }
      else if(value=='f')
      {
          pump_pin1=0;
          pump_pin2=0;
          
          lcd_cmd(0x01);
          lcd_cmd(0xC0);
          lcd_string("PUMP OFF",8);
          
          for(i=0;i<sizeof text14;i++)
          {
            TXREG=text14[i];
            while(TXIF==0);
            TXIF=0;
          }
          
          press_enter();
      }
      else
      {
          lcd_cmd(0x01);
          lcd_string("TRY AGAIN",9);
          
          for(i=0;i<sizeof text9;i++)
          {
            TXREG=text9[i];
            while(TXIF==0);
            TXIF=0;
          }
          
          press_enter();
      
      }
    }  
    
}