/* Projeto Módulo 2*/

#include <msp430.h>

void debounce(volatile unsigned int i);
volatile unsigned int  BT_1, BT_2, temp = 0, fase = 0;

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
    TA1CTL = TASSEL__ACLK;
    TA1CCTL0 = CCIE;
    TA1CCR0 = 32767;

    __enable_interrupt();

  while(1)                                  // continuous loop
  { 
    //para chave 1
    if ((P1IN & BIT1) & (P2IN & BIT1)) 
    {
      debounce(10000);  //nao faca nada
    }
    else if (!(P1IN & BIT1)) 
    {
      debounce(10000);
      BT_1 = 1;
      TA1CTL |= MC__UP;
      while (!(P1IN & BIT1));
      debounce(10000);
    }
    else if (!(P2IN&BIT1)) 
    {
        debounce(10000);
        BT_2 = 1;
        TA1CTL |= MC__UP;
        while (!(P2IN&BIT1));
        debounce(10000);
    }

  if (fase == 0) {
   if (BT_1 & !BT_2) {
    fase = 1;
    BT_1 = 0;
   } else if (!BT_1 | BT_2) {
    fase = 0;
    BT_2 = 0;
   }
  }else if (fase == 1) {
    if (!BT_1 & BT_2) {
      fase = 2;
      BT_2 = 0;
    }else if (!BT_1 & !BT_2) {
      fase = 1;
    }else if (BT_1) {
      fase = 1;
      BT_1 = 0;
    }
  }else if (fase == 2) {
    if (BT_1 & !BT_2) {
      fase = 0;//action
      BT_1 = 0;
      if (TA0CCR1 < 530) {
        TA0CCR1 = 2619;
      }else if (TA0CCR1 > 2600) {
        TA0CCR1 = 523;
      }
    }else if (!BT_1 & !BT_2) {
      fase = 2;
    }else if (BT_2) {
      fase = 0;
      BT_2 = 0;
    }
  }

    
  }
  
}

void debounce(volatile unsigned int i){
  while (i--);
}

#pragma vector = 49
__interrupt void ta1_isr_ccr0(void){
      temp++;
      if (temp == 3) {
        temp = 0;
        fase = 0;
        BT_1 = 0;
        BT_2 = 0;
        TA1CTL &= ~(BIT4 | BIT5);
        TA1CTL |= TACLR;
        }
  }

