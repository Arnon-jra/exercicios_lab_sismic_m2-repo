/*Módulo 3 - Comunicação USCI I2C*/

#include <msp430.h>
#include "sys_init.h"
#include "stdio.h"


int main(){
i2c_config();         
uint8_t ret = 1;

  while (1) {

    ret =  i2c_send(0x27, 0x08);
    __delay_cycles(500000);
    ret =  i2c_send(0x27, 0x08);
    __delay_cycles(500000);
  }
}
