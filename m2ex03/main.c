/*Exercício 3: Remoção de rebotes
Refaça o exercício 2 removendo os rebotes das chaves. Para isso, defina uma função
debounce() que consome tempo do processador através de um loop que decremente uma
variável. Não deixe de declará-la como volatile para evitar que o recurso de otimização do
compilador a remova.*/

#include <msp430.h>
#include "system_init.h"

void io_config(void);

int main(void)
{
  volatile unsigned int i;
  WDTCTL = WDTPW+WDTHOLD;               // Stop WDT
  io_config();
  while(1)                                
  {
    while (P1IN & BIT1) { 
    }
    P1OUT ^= BIT0;
    for (i=0; i++; i<50000) {
    }
    while (!(P1IN & BIT1)){
    }
    for (i=0; i++; i<50000) {
    }
  }  
}
