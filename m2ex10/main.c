/*Exercício 10: PWM variável
Incremente o programa anterior, acrescentando a possibilidade de ajustar o duty cycle usando
os botões S1 e S2. O botão S2 aumenta e o botão S1 diminui o duty cycle em passos de 12,5%
(1/8) de CCR0.
*/


#include <msp430f5529.h>


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    //set timer A0
    TA0CTL = MC__UP | TASSEL__ACLK;
    TA0CCTL1 = OUTMOD_2;
    TA0CCR0 = 255;
    TA0CCR1 = 248;

    P1DIR |= BIT2;
    P1SEL |= BIT2;
    
    while (1) 
    {
        if (P1IN & BIT2) 
        {
            //LED LIGADO
            TA0CCTL1 &= ~CCIFG;   
        }else if (!(P1IN & BIT2)) {
            //LED DESLIGADO
            TA0CCTL0 &= ~BIT0;
        }
    }
}
