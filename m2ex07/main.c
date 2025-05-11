/*Exercício 7: Medindo tempo.
Meça o tempo de execução das duas linhas de código abaixo.
volatile double hardVar = 128.43984610923f;
hardVar = (sqrt(hardVar * 3.14159265359) + 30.3245)/1020.2331556 – 0.11923;
*/

#include <msp430f5529.h>
#include <math.h>

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    TA0CCTL0 = CAP | CM_2;

    P1DIR |= BIT0 ;
    P1OUT &= ~BIT0;
    volatile unsigned int d_time;

    while (1) 
    {
        TA0CCTL0 |= CCIS_3; //set Capture/compare input select --> VCC
        TA0CTL = TASSEL_2 | MC__CONTINUOUS | TACLR; //inicio contagem
        
        P1OUT |= BIT0;
        
        volatile double hardVar = 128.43984610923f;
        hardVar = (sqrt(hardVar * 3.14159265359) + 30.3245)/1020.2331556 - 0.11923;
        
        TA0CCTL0 &= ~BITC;  //set Capture/compare input select --> GND
        if (TA0CCTL0 & CCIFG) {
            
            d_time = TA0CCR0;
            P1OUT &= ~BIT0;
            TA0CCTL0 &= ~CCIFG;
        }

    }
}
