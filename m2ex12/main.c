/*Exercício 12: [GPIO] Configuração de interrupções
Usando interrupções, escreva um código que alterne o estado do LED vermelho ao pressionar o
botão S1.
*/

#include <msp430f5529.h>

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    //Configurar led2 P4.7
    P4DIR |= BIT7;
    P4OUT &= ~BIT7;
    //configurar P2.1 (botao s1)
    P2DIR &= ~BIT1;
    P2REN |= BIT1;
    P2OUT |= BIT1;
    //habilitar interrupção do botão S1 (P2.1)
    P2IE |= BIT1; //enables interrupt on pin2.1
    P2IES |= BIT1; //high to low activate
    P2IFG &= ~BIT1; //zera a flag

    __enable_interrupt();   //enable interrupts (faz GIE=1)
 
    while (1) 
    {
    }
}

#pragma vector = PORT2_VECTOR
__interrupt void P21_ISR (void)
{
    switch (P2IV) {         //ao se fazer a leitura de P2IV zera-se
    case 0x0: break;        // automaticamente P2IV e sua respectiva FLAG
    case 0x2: break;
    case 0x4:
        P4OUT ^= BIT7;
    default: break;
    }
    
}

