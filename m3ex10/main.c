/*Exercício 10: Escreva a função uint16_t adcRead(uint8_t pin) que faz uma leitura pontual de qualquer
pino da porta P6. Considere no pior caso, sensores com 50kΩ de resistência. Use 12 bits de
resolução. Use o modo single-channel, single-conversion.*/

// R_ext = 50k ohms
// t_cap = RC ln(2^(N+1)) + tg
// t_cap = (1,8k + R_ext) 25pF (12+1) 0,7 + 800ns
// t_cap = 12,6 us
// T_clk = 4.768 us (209715.2 Hz, ADC12DIV__5, SMCLK @1MHz
// --> 3 clock cycles

#include <msp430.h>
#include "stdint.h"
#include "sys_init.h"
#include "stdio.h"

uint16_t adcRead(uint8_t pin){
  
  ADC12CTL0 = 0;
  ADC12CTL0 = ADC12ON |
				      ADC12SHT0_0; // 4 T_clk

  ADC12CTL1 = ADC12SHP;           //pulse sample mode
                                  //0b = SAMPCON signal is sourced from the sample-input signal.
                                  //1b = SAMPCON signal is sourced from the sampling timer.
  
  P6SEL = (BIT0 << pin);

  ADC12MCTL1 = pin;
  ADC12CTL1 |= ADC12CSTARTADD_1;

  ADC12CTL0 |= ADC12ENC;		// habilita o gatilho
  ADC12CTL0 |= ADC12SC;		// gera um gatilho

  // depois de 4 x T_clk 
	// + 12 T_clk + 1 T_clk
	while(!(ADC12IFG & BIT1)); //indica que ADC12MEM0 foi carregada com o resultado da conversão
	return ADC12MEM1;


}

int main(){

  volatile unsigned int i;
  volatile unsigned int tensao;

  while (1) {
    tensao = adcRead(3);
    if (tensao > 50) {
      i = 1;
    }else {
      i = 0;
    }
  }
}
