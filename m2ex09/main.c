/*Exercício 9: PWM por hardware
Repita o programa anterior usando a saída do timer. Procure no datasheet qual pino está
conectado à saída do canal desejado...
*/
#include <msp430f5529.h>

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    //set P1.1 as TA0.0
    P1DIR |= BIT3;
    P1SEL |= BIT3;
    //TA0
    TA0CTL  = MC__UP | TASSEL__ACLK | TACLR;
    TA0CCR0 = 255;
    TA0CCTL2 = OUTMOD_2;
    TA0CCR2 = 128;
    
    while (1) 
    {
    }
}
