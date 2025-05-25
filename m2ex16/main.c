#include <msp430f5529.h>
#include "sys_init.h"
#define freq_smclk 1
volatile unsigned int ta_atual, ta_anterior;  //var globais para registrar o valor de CCR2
volatile unsigned int i=0, ov_counter = 32;
volatile int momento, pulse = 0,dif, vector_tempos[20];

void main(void)
{
    sys_init();
    __enable_interrupt();    // Habilitar interrupções
    volatile int tempo = 0;

    for(;;){
    }
}


#pragma vector = 48
__interrupt void isr_ta1(void){
    switch (TA1IV){
        case 0x00: break;
        case 0x04:
            if (momento == 0){ 
                ta_anterior = TA1CCR2;
                momento = 1;
                TA1CTL |= TAIE;
            }else if (momento == 1){ 
                ta_atual = TA1CCR2; 
                dif = ta_atual - ta_anterior;
                if (dif<0) 
                dif = dif + 0xFFFF;
                dif = abs(dif);
                vector_tempos[i] = dif;
                i++;
                ta_anterior = ta_atual;
            }
        case 0x0E:
            ov_counter--;
            if (!ov_counter) {
                momento = 0;
                ov_counter = 32;
                //vector_tempos[0:i] = 0;
                i = 0;
                TA1CTL &= ~TAIE;
            }
        default: break;
    }
}

