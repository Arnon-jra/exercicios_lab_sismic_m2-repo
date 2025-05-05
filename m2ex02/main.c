/*Exercício 2: Escreva na função main() uma rotina que alterne o estado do LED vermelho toda vez que o
usuário apertar o botão S1. Não remova os rebotes.*/

#include <msp430.h>

int main(void)
{

  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  
  //P1IN = P1IN | BIT0;                     TODO: Preciso dessa linha?
  P1DIR = P1DIR | BIT0;
  P1OUT = P1OUT | BIT0;                     // P1.0 set as high logic signal
  P1REN = P1REN & ~BIT0;                    //TODO: Preciso dessa linha?
  P1SEL = P1SEL & ~BIT0;

  //P1IN = P1IN | BIT0;                     
  P1DIR &= ~BIT1;
  P1OUT |= BIT1;                
  P1REN |= BIT1;               
  P1SEL &= ~BIT1;

  while(1)                                  // continuous loop
  {
    while (P1IN & BIT1) { 
    }
    P1OUT ^= BIT0;
    while (!(P1IN & BIT1)){
    }
  }
  
}
