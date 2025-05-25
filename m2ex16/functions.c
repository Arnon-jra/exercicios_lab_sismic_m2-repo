#include <msp430f5529.h>
#include "sys_init.h"

void debounce(volatile unsigned int i){
    while(i--);
}

void stopwd(){
    WDTCTL = WDTPW | WDTHOLD;  // Parar watchdog
}

void sys_init(void){
    stopwd(); 
    
    P2SEL |= S1;
    P2REN |= S1;
    P2OUT |= S1;

    TA1CTL = TASSEL__SMCLK | TACLR | MC__CONTINOUS;

    TA1CCTL2 = CAP | CM_3 | CCIE | SCS;
    TA1CCTL2 &= ~CCIFG;
}
