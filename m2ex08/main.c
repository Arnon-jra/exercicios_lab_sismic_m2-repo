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
    TA0CCR0 = 255;
    TA0CCR1 = 127;

    P1DIR |= BIT0;

    while (1) 
    {
        if (TA0CCTL1 & CCIFG) 
        {
            P1OUT ^= BIT0;
            TA0CCTL1 &= ~CCIFG;   
        }else if (TA0CTL & TAIFG) {
            P1OUT ^= BIT0;
            TA0CTL &= ~BIT0;
        }
    }
}
