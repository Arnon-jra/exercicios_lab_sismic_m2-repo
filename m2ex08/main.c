/*Exercício 8: PWM com duty cycle fixo
Faça o LED vermelho piscar em 128Hz com duty cycle de 50%. É recomendado o uso das
interrupções de overflow e CCR1.
*/

#include <msp430f5529.h>


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    //set timer A0
    TA0CTL = MC__UP | TASSEL__ACLK;
    TA0CCTL0 = CCIE;
    TA0CCTL1 = CCIE;
    TA0CCR0 = 256;
    TA0CCR1 = 128;
    //set P1.0 (LED 1 vermelho)
    P1DIR |= BIT0;

    __enable_interrupt();
    while (1) 
    {
    }
}

#pragma vector = 53
__interrupt void isr_ta0_ccr0()
{
    P1OUT &= ~BIT0;
}

#pragma vector = 52
__interrupt void isr_ta0_ccr1()
{
    switch (TA0IV){
        case 0x00: break;
        case 0x02:
            P1OUT |= BIT0;
        default: break;
    }
}
