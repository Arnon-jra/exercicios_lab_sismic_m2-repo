/*Exercício 3: Remoção de rebotes
Refaça o exercício 2 removendo os rebotes das chaves. Para isso, defina uma função
debounce() que consome tempo do processador através de um loop que decremente uma
variável. Não deixe de declará-la como volatile para evitar que o recurso de otimização do
compilador a remova.*/

#include <msp430.h>
#include "system_init.h"

void io_config(void);
void debounce(volatile unsigned int i);

int main(void)
{
  WDTCTL = WDTPW+WDTHOLD;               // Stop WDT
  io_config();
  while(1)                                
  {
    while (P1IN & BIT1);
    P1OUT ^= BIT0;
    debounce(50000);
    while (!(P1IN & BIT1));
    debounce(50000);
  }  
}


void debounce(volatile unsigned int i){
  while (i--);
}

void io_config(void){
  P1DIR = P1DIR | BIT0;
  P1OUT = P1OUT | BIT0;                     // P1.0 set as high logic signal
  P1REN = P1REN & ~BIT0;                    //Preciso dessa linha? não pois P1.0 está setado como saída(ver datasheet)
  P1SEL = P1SEL & ~BIT0;
                   
  P1DIR &= ~BIT1;
  P1OUT |= BIT1;                
  P1REN |= BIT1;               
  P1SEL &= ~BIT1;
}
