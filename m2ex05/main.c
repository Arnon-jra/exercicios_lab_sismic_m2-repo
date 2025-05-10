/*Exercício 5: Temporização imprecisa
Ainda sem usar timers (use laços de programa) faça o LED piscar em aproximadamente 1Hz, ou
seja, fique 500ms apagado e 500ms aceso.*/

#include "msp430f5529.h"

#define LED2 BIT7
#define DELAYLOOPS 10000

void delay_loop(volatile unsigned int delay)
{
    volatile unsigned int i=0, j; //ou uint16_t (ANSI)
    for (i; i<delay; i++) 
    {
        for (j=0; j<DELAYLOOPS; j++);
    }
}
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    //Set LED 2 (P4.7) as DIR OUT
    P4DIR |= LED2;
    
    while (1) 
    {
        delay_loop(8);
        P4OUT ^= LED2;
    }
}
