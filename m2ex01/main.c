/*Exercício 1: Configuração dos pinos
Escreva um programa que faça o LED verde imitar o estado da chave S1. Se S1 estiver
pressionado o LED deverá estar aceso, se estiver solto, o LED deve apagar.*/

#include <msp430.h>

int main(void)
{
  volatile unsigned int i;

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
    if (P1IN & BIT1) {
      P1OUT &= ~BIT0;
    }else if (!(P1IN & BIT1)) {
      P1OUT |= BIT0;
    }
  }
}
