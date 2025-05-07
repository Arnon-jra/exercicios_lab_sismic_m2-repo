/*Exercício 3: Remoção de rebotes
Refaça o exercício 2 removendo os rebotes das chaves. Para isso, defina uma função
debounce() que consome tempo do processador através de um loop que decremente uma
variável. Não deixe de declará-la como volatile para evitar que o recurso de otimização do
compilador a remova. SEM OCUPAR O PROCESSADOR*/

#include <msp430.h>
#include <stdint.h>
#include "system_init.h"


void io_config(void);
void debounce(volatile unsigned int i);

int main(void)
{
  WDTCTL = WDTPW+WDTHOLD;               // Stop WDT
  
  io_config();
  uint16_t estado_anterior = P1IN & BIT1;
  while(1)                                
  {
    if ((P1IN & BIT1) & estado_anterior) {
      estado_anterior = 0x02;
    }else if ((P1IN & BIT1) & (~estado_anterior)&BIT1) { 
      estado_anterior = 0x02;
      debounce(50000);
    }

    if (~((P1IN & BIT1)&BIT1) & ~estado_anterior&BIT1) {
      estado_anterior = 0x00;  
    }else if ((~(P1IN & BIT1))&BIT1 & estado_anterior) {
      estado_anterior = 0x00;  
      P1OUT ^= BIT0; 
      debounce(50000);
    }
  }  
}

void debounce(volatile unsigned int i){
  while (i--){}
}

void io_config(void){
  P1DIR = P1DIR | BIT0;
  P1OUT = P1OUT & ~BIT0;                     // P1.0 set as low logic signal
  P1SEL = P1SEL & ~BIT0;
                   
  P1DIR &= ~BIT1;
  P1OUT |= BIT1;                
  P1REN |= BIT1;               
  P1SEL &= ~BIT1;
}
