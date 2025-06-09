#include <msp430.h>
#include "sys_init.h"

void debounce(volatile unsigned int i){
    while(i--);
}

void stopwd(){
    WDTCTL = WDTPW | WDTHOLD;  // Parar watchdog
}

void ta1_init(void){
    
    P2SEL |= BIT0;

    TA1CTL = TASSEL__SMCLK | TACLR | MC__CONTINOUS;

    TA1CCTL1 = CAP | CM_3 | CCIE;
    TA1CCTL1 &= ~CCIFG;
}

void sys_init(void){
    stopwd(); 
}

void port1_init(void){
    //P1.0
   // P1DIR &= ~BIT0;        //P1.0 ativa interrupção 
   // P1REN |= BIT0;
   // P1OUT |= BIT0;
   // P1IES |= BIT0;
    //P1IE |= BIT0;

    //P1.2 (TA0.1) PWM
    P1DIR |= BIT2;
    P1SEL |= BIT2;

    //P1.3 Output
    P1DIR |= BIT3;

    //P1.4 Output
    P1DIR |= BIT4;
}

void ta0_init(void){
    TA0CTL = TASSEL__SMCLK | MC__UP | TACLR;
    TA0CCR0 = 52;
    TA0CCTL1 = OUTMOD_3;
    TA0CCR1 = 8;

}
