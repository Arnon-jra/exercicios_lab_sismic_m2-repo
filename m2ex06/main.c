/*Exercício 6: Amostrando flags do timer
Escreva um programa em C que faça piscar o LED verde (P4.7) em exatamente 1Hz (0,5s
apagado e 0,5s aceso). Use a técnica de amostragem (polling) da flag de overflow (TAIFG) ou a
flag do canal 0 (CCIFG) para saber quando o timer atingiu o valor máximo.*/

// .5s with 32768Hz --> Tmax = 1/f * 2^16 = 2s; Tled = 1/f * (N+1)
#include "msp430f5529.h"


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    //set clock source (ACLK | SMCLK)
    TA0CTL |= BIT8;
    //set divider 
    TA0CTL &= ~BIT7;
    TA0CTL &= ~BIT6;
    //mode control up
    TA0CTL &= ~BIT5;
    TA0CTL |= BIT4;
    //set CCR0 = 16384
    TA0CCR0 = 16384;

    //set LED2 config
    P4DIR |= BIT7;

    while (1) 
    {
        //check CCIFG 
        if (TA0CCTL0 & BIT0) {
            //zera a flag
            TA0CCTL0 &= ~BIT0;
            //toggle LED 2 (P4.7)
            P4OUT ^= BIT7;        
        }
    }
}
