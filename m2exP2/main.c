/* Projeto Módulo 2*/

#include <msp430.h>

void debounce(volatile unsigned int i);
volatile unsigned int  BT_1, BT_2;

int main(void)
{
    WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
    //set TA0
    TA0CTL = TASSEL__SMCLK | MC__UP |TACLR;
    TA0CCTL1 = OUTMOD_7;
    TA0CCR0 = 20971;  //PWM T = 20ms
    TA0CCR1 = 523;    //2,5ms set
    //set PIN1.2
    P1DIR |= BIT2;
    P1SEL |= BIT2;
    //set S2 P1.1
    P1REN |= BIT1;
    P1OUT |= BIT1;
    //set S1 P4.7
    P2REN |= BIT1;
    P2OUT |= BIT1;

    //set TA01
    TA1CTL = TASSEL__SMCLK | MC__CONTINUOUS | ID__2 | TACLR | TAIE;

    __enable_interrupt();

  while(1)                                  // continuous loop
  { 
    //para chave 1
    if ((P1IN & BIT1) & (P2IN & BIT1)) 
    {
      debounce(10000);  //nao faca nada
      BT_1 = 0;
      BT_2 = 0;
    }
    else if (!(P1IN & BIT1)) 
    {
      debounce(10000);
      BT_1 = 1;
      while (!(P1IN & BIT1));
      debounce(10000);
      BT_1 = 0;
    }
    else if (!(P2IN&BIT1)) 
    {
        
        debounce(10000);
        BT_2 = 1;
        while (!(P2IN&BIT1));
        debounce(10000);
        BT_2 = 0;
    }
  }
}

void debounce(volatile unsigned int i){
  while (i--);
}

#pragma vector = 48
__interrupt void ta1_isr(void){
  switch (TA1IV) {
    case 0x00: break;
    case 0x0E: 
      if (BT_1) {
        TA0CCR1 += 116;
      }
  }
}

