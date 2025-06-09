#include <msp430f5529.h>
#include "sys_init.h"

#define freq_smclk 1

volatile unsigned int vector_tempos[100], stop, ta_atual, ta_anterior, conta11 = 11, tempo_volta = 0;  //var globais para registrar o valor de CCR2
volatile unsigned int i=0, ov_counter = 32;
volatile int momento, pulse = 0,dif;

void main(void)
{
    sys_init();
    port1_init();
    ta0_init();
    ta1_init();                 //captura evento de subida

    P1OUT &= ~BIT3;             
    P1OUT &= ~BIT4;
    
    __enable_interrupt();    // Habilitar interrupções

    volatile int tempo = 0;
    
    __delay_cycles(3000000);
    for(;;){
        if (i >= 99) {
            stop = 1;
            P1OUT &= ~BIT3;             
            P1OUT &= ~BIT4;
        }else {
            P1OUT |= BIT3;            
            P1OUT &= ~BIT4;
        }
    }
}


#pragma vector = 48
__interrupt void isr_ta1(void){
    if(TA1IV);
    if (momento == 0){ 
        ta_anterior = TA1CCR1;
        momento = 1;
    }else if (momento == 1){ 
        ta_atual = TA1CCR1; 
        dif = ta_atual - ta_anterior;
        if (dif<0) 
        dif = dif + 0xFFFF;
        dif = abs(dif);
        if (conta11 == 0) {
            vector_tempos[i] = tempo_volta;
            i++;
            tempo_volta = 0;
            ta_anterior = ta_atual;
            conta11 = 11; 
        }else {
            tempo_volta = tempo_volta + dif;
            ta_anterior = ta_atual;
            conta11--;
        }
    }
}

