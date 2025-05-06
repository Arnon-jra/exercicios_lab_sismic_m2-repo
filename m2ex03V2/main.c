/*Exercício 3: Remoção de rebotes
Refaça o exercício 2 removendo os rebotes das chaves. Para isso, defina uma função
debounce() que consome tempo do processador através de um loop que decremente uma
variável. Não deixe de declará-la como volatile para evitar que o recurso de otimização do
compilador a remova. SEM OCUPAR O PROCESSADOR*/

#include <msp430.h>
#include "system_init.h"
#include <stdbool.h>

void io_config(void);
void debounce(volatile unsigned int i);

int main(void)
{
  volatile unsigned int i;
  WDTCTL = WDTPW+WDTHOLD;               // Stop WDT
  
  bool estado_anterior = P1IN & BIT1; //chave aberta
  io_config();
  while(1)                                
  {
    //estado_anterior = P1IN & BIT1;
    if ((P1IN & BIT1) & estado_anterior) {
      estado_anterior = 1;
    }else if ((P1IN & BIT1) & !estado_anterior) { 
      estado_anterior = 1;
      debounce(50000);
    }

    if (!(P1IN & BIT1) & !estado_anterior) {
      estado_anterior = 0;  //chave aberta
    }else if (!(P1IN & BIT1) & estado_anterior) {
      estado_anterior = 0;  //chave fechada
      P1OUT ^= BIT0; 
      debounce(50000);
    }
  }  
}

void debounce(volatile unsigned int i){
  while (i--){}
}
