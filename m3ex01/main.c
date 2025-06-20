/*Módulo 3 - Comunicação USCI I2C*/

#include <msp430.h>
#include "sys_init.h"
#include "stdio.h"

int main(){
i2c_config();         

  while (1) {

    i2c_send(0x27, 0x00);
    __delay_cycles(500000);
    i2c_send(0x27, 0x08);
    __delay_cycles(500000);
  }
}
