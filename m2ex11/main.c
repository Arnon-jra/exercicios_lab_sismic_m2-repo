/*Exercício 11: Usando um servo motor
O servo motor é um dispositivo eletromecânico cuja rotação pode ser comandada por um sinal
PWM. Ele não gira continuamente, apenas muda o ângulo da sua posição. A posição angular é
codificada num pulso que varia de 0,5ms a 2,5ms...
*/

#include <msp430.h>

void debounce(volatile unsigned int i);

int main(void)
{
    WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
    //set TA0
    TA0CTL = TASSEL__ACLK | MC__UP |TACLR;
    TA0CCTL1 = OUTMOD_7;
    TA0CCR0 = 654;
    TA0CCR1 = 15;
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
    if (P1IN & BIT1) {
    //nao faca nada
    }
    if (!(P1IN & BIT1)) {
        TA0CCR1 = TA0CCR1 + 2;
        debounce(10000);
    }
    while (!(P1IN & BIT1));
    debounce(10000);
    
    //para chave 2
    if (P2IN & BIT1) {
    //nao faca nada
    }
    if (!(P2IN & BIT1)) {
        TA0CCR1 = TA0CCR1 - 2;
        debounce(10000);
    }
    while (!(P2IN & BIT1));
    debounce(10000);


  }
}

void debounce(volatile unsigned int i){
  while (i--);
}


