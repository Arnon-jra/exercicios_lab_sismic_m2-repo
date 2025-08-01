/*Exercício 10: PWM variável
Incremente o programa anterior, acrescentando a possibilidade de ajustar o duty cycle usando
os botões S1 e S2. O botão S2 aumenta e o botão S1 diminui o duty cycle em passos de 12,5%
(1/8) de CCR0.
*/


#include <msp430.h>

void debounce(volatile unsigned int i);

int main(void)
{
    WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
    //set TA0
    TA0CTL = TASSEL__ACLK | MC__UP |TACLR;
    TA0CCTL1 = OUTMOD_7;
    TA0CCR0 = 255;
    TA0CCR1 = 0;
    //set PIN1.2
    P1DIR |= BIT2;
    P1SEL |= BIT2;
    //set S2 P1.1
    P1REN |= BIT1;
    P1OUT |= BIT1;
    //set S1 P4.7
    P2REN |= BIT1;
    P2OUT |= BIT1;

  while(1)                                  // continuous loop
  { 
    //para chave 1
    if ((P1IN & BIT1) & (P2IN & BIT1)) 
    {
      debounce(10000);  //nao faca nada
    }
    else if (!(P1IN & BIT1)) 
    {
      TA0CCR1 = TA0CCR1 + 32;
      debounce(10000);
      while (!(P1IN & BIT1));
      debounce(10000);
    }
    else if (!(P2IN&BIT1)) 
    {
        TA0CCR1 = TA0CCR1 - 32;
        debounce(10000);
        while (!(P2IN&BIT1));
        debounce(10000);
    }
  }
}

void debounce(volatile unsigned int i){
  while (i--);
}



