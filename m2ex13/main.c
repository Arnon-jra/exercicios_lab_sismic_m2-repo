#include <msp430f5529.h>

#define LED1 BIT0
#define LED2 BIT7
#define S1 BIT1
#define S2 BIT1

volatile int contador;
volatile int inc = 0;

void debounce(){
    for(contador = 10000; contador >= 0; contador--);
}

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;  // Parar watchdog


    P1OUT &= ~LED1;            // LED inicialmente desligado
    P1DIR |= LED1;             // P1.0 é uma saída
    P4OUT &= ~LED2;            
    P4DIR |= LED2;             

    P2DIR &= ~S1;            // P2.1 é uma entrada
    P2REN |= S1;             // Habilitar resistor
    P2OUT |= S1;             // Usar resistor de pull-up
    P1DIR &= ~S2;            
    P1REN |= S2;             
    P1OUT |= S2; 

    // Configurar interrupção de P2.1
    P2IES |= S1;             // Interromper na borda de descida (o sinal vai de 1 para 0 quando a chave é pressionada)
    P2IE  |= S1;             // Habilitar interrupção para P2.1
    P2IFG &= ~S1;            // Limpar  flag
    P1IES |= S2;            
    P1IE  |= S2;             
    P1IFG &= ~S2;            


    __enable_interrupt();    // Habilitar interrupções


    // Loop infinito
    for(;;){
    }
}

// ISR de P2
#pragma vector=PORT2_VECTOR
__interrupt void Port_2_ISR(void){

    // Se S1 causou a interrupção
    if (P2IFG & S1){
        debounce();
        // Checar se a chave ainda está pressionada (se não estiver, é porque a interrupção foi causada por um rebote, ou a chave foi solta rápido demais)
        if(~P2IN & S1){
            inc++;
            if (inc == 1) {
                P1OUT &= ~LED1;
                P4OUT |= LED2;
            }else if (inc == 2) {
                P1OUT |= LED1;
                P4OUT &= ~LED2;
            }else if (inc == 3) {
                P1OUT |= LED1;
                P4OUT |= LED2;
            }else if (inc > 3) {
                P1OUT &= ~LED1;
                P4OUT &= ~LED2;
                inc = 0;
            }  
        }
        P2IFG &= ~BIT1;        // Limpar flag
    }
}

// ISR de P1
#pragma vector=PORT1_VECTOR
__interrupt void Port_1_ISR(void){

    // Se S1 causou a interrupção
    if (P1IFG & S2){
        debounce();
        // Checar se a chave ainda está pressionada (se não estiver, é porque a interrupção foi causada por um rebote, ou a chave foi solta rápido demais)
        if(~P1IN & S2){
            inc--;
            if (inc <= 0) {
                P1OUT &= ~LED1;
                P4OUT &= ~LED2;
                inc = 0;
            }else if (inc == 1) {
                P1OUT &= ~LED1;
                P4OUT |= LED2;
            }else if (inc == 2) {
                P1OUT |= LED1;
                P4OUT &= ~LED2;
            }else if (inc == 3) {
                P1OUT |= LED1;
                P4OUT |= LED2;
            }  
        }
        P1IFG &= ~BIT1;        // Limpar flag
    }
}
