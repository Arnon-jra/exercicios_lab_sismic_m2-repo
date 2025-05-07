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
  io_config();
  uint16_t estado_atual_p1 = P1IN & BIT1;
  uint16_t estado_atual_p2 = P2IN & BIT1;
  uint16_t estado_anterior = (P1IN | P2IN) & BIT1;
  while(1)                                
  {
    estado_atual_p1 = P1IN & BIT1;
    estado_atual_p2 = P2IN & BIT1;
    
    if ((estado_atual_p1 & estado_atual_p2) & estado_anterior) {
      estado_anterior = 0x02;
    }else if (~(estado_atual_p1 & estado_atual_p2)&BIT1 & estado_anterior) { 
      estado_anterior = 0x00;  
      P1OUT ^= BIT0; 
      debounce(50000);
    }else if ((estado_atual_p1 & estado_atual_p2) & ((~estado_anterior)&BIT1)) {
      estado_anterior = 0x02;
      debounce(50000);
    }else if (~(estado_atual_p1 & estado_atual_p2)&BIT1 & ((~estado_anterior)&BIT1)) {
      estado_anterior = 0x00;
    }
  }  
}

void debounce(volatile unsigned int i){
  while (i--){}
}

void io_config(void){
  WDTCTL = WDTPW+WDTHOLD;               // Stop WDT

  //LED 1 (P1.0)
  P1DIR = P1DIR | BIT0;
  P1OUT = P1OUT & ~BIT0;

  //PUSH BUTTON 1 (P1.1)
  P1DIR &= ~BIT1;
  P1OUT |= BIT1;                
  P1REN |= BIT1;               
  P1SEL &= ~BIT1;

  //PUSH BUTTON 2 (P2.1)
  P2DIR &= ~BIT1;
  P2OUT |= BIT1;                
  P2REN |= BIT1;               
  P2SEL &= ~BIT1;
}
