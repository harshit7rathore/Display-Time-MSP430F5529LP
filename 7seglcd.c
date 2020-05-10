#include <msp430.h>



char arr[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0xFC,0x39,0x5E,0x79,0x71};
char pos[] = {0x01,0x02,0x04,0x08};


unsigned int num1 , num2 ;

void lcdinit()
{
    P6DIR = 0xFF ;
    P6OUT = 0xFF ;

    P3DIR |= BIT0 + BIT1 + BIT2 + BIT3 ;
    P3OUT |= BIT0 + BIT1 + BIT2 + BIT3 ;

    P4DIR |= BIT0 ;
    P4OUT |= BIT0 ;
}


void split(unsigned int num)
{
    num1 = num / 10 ;
    num2 = num % 10 ;
}

void dispd(unsigned char pos1 , unsigned int num)
{
    P3OUT = pos1;
    P6OUT = ~ arr[num];
}

void dispm(unsigned int m)
{
    split(m);
    dispd(pos[0],num1);
    __delay_cycles(10000);
    dispd(pos[1],num2);
    __delay_cycles(10000);
}

void disph(unsigned int h)
{
    split(h);
    dispd(pos[2],num1);
    __delay_cycles(10000);
    dispd(pos[3],num2);
    __delay_cycles(10000);
}



void disp(unsigned int m , unsigned int h)
{
    split(m);
    dispd(pos[0],num1);
    __delay_cycles(10000);
    dispd(pos[1],num2);
    __delay_cycles(10000);
    split(h);
    dispd(pos[2],num1);
    __delay_cycles(10000);
    dispd(pos[3],num2);
    __delay_cycles(10000);
}

