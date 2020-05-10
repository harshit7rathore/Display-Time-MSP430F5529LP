#include <msp430.h> 
#include "7seglcd.h"

/**
 * main.c
 */

    unsigned int s = 0;
    unsigned int m = 0;
    unsigned int h = 0;


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	

	P2DIR &= ~BIT1 ;
	P2REN |= BIT1 ;
	P2OUT |= BIT1 ;
    P2IE |= BIT1 ;
    P2IES |= BIT1 ;
    P2IFG &= ~BIT1 ;

    P1DIR &= ~BIT1 ;
    P1REN |= BIT1 ;
    P1OUT |= BIT1 ;
    P1IE |= BIT1 ;
    P1IES |= BIT1 ;
    P1IFG &= ~BIT1 ;


    lcdinit();


	TA0CCR0 = 32767 ;
	TA0CCTL0 |= CCIE ;
	TA0CTL |= TAIE + MC_1 + TACLR + TASSEL_1 ;

	__bis_SR_register(GIE+LPM0_bits);
	disp(m,h);
	return 0;
}


#pragma vector = TIMER0_A0_VECTOR
__interrupt void delay (void)
{
    s++;
    if(s == 60)
    {
        m++;
        s = 0;
    }
    if(m == 60)
    {
        h++;
        m = 0;
    }
    if(h == 24)
    {
        h = 0;
    }
    TA0CTL |= TACLR ;
    TA0CTL &= ~TAIFG ;
    __bic_SR_register_on_exit(LPM0_bits);
}

#pragma vector = PORT2_VECTOR
__interrupt void p2isr()
{
    m++;
    s=0;
    if(m == 60)
    {
        h++;
        m=0;
    }
    if(h == 24)
    {
        h = 0;
    }
    P2IFG &= ~BIT1;
    P2IES |= BIT1;
}

#pragma vector = PORT1_VECTOR
__interrupt void p1isr()
{
    h++;
    s=0;
    if(h == 24)
    {
        h = 0;
    }
    P1IFG &= ~BIT1;
    P1IES |= BIT1;
}
