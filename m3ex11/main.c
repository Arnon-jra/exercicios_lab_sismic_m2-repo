/*Exercício 11:
Configure o módulo do conversor A/D em modo repeated single channel, para amostrar a
tensão de entrada que representa apenas um eixo da posição do joystick. Use apenas 8 bits de
resolução. Configure um timer para realizar essa amostragem a cada 100ms. */

// R_ext = 10k/4 ohms
// t_cap = RC ln(2^(N+1)) + tg
// t_cap = (1,8k + R_ext) 25pF (12+1) 0,7 + 800ns
// t_cap = 1,477 us
// T_clk = 7,629 us us (131072 Hz, ADC12DIV__8, SMCLK @1MHz
// --> 1 clock cycles

#include <msp430.h>
#include "stdint.h"
#include "sys_init.h"
#include "stdio.h"

void ta0_config(void){
  TA0CTL = TASSEL__ACLK | TACLR | MC__UP | ID__8;
  TA0CCR0 = 409;
  TA0CCTL1 = OUTMOD_7;
  TA0CCR1 = 3;

  P1SEL |= BIT2;
  P1DIR |= BIT2;
}

void adcConfig(){

ADC12CTL0 &= ~ADC12ENC;             //desabilitar para configuracao
ADC12CTL0 = ADC12ON ;               //liga ADC
            //ADC12MSC |              //multiple sample and conversion
            //ADC12SHT0_0;            //sample and holder time (sampling timer activation) option 0 (4 cycles before conversion)

ADC12CTL1 = ADC12CONSEQ_2 |         //conversion sequence (single channel. single conversion)
            ADC12SSEL_3 | ADC12SHS_1;          //source clock SMCLK 
            //ADC12DIV_7 |            // clock divider (/8)
            //ADC12SHP;               // SH pulse mode (SAMPCON signal is sourced from sampling timer)

ADC12CTL2 = ADC12RES_0;             //8 bit resolution     

ADC12MCTL0 = ADC12INCH_0;           //A0 selection

P6SEL |= BIT0;                      //P6.0 as second function

ADC12CTL0 |= ADC12ENC;              //enable conversion 

}

int main(){
WDTCTL = WDTPW | WDTHOLD;  // Parar watchdog
volatile unsigned int cont = 0, data[100];
ta0_config();
adcConfig();

  while (1) { 
    
    if (cont >=99) {
      ADC12CTL0 &= ~ADC12ENC; //stop conversion
    }else {
      while(!(ADC12IFG & ADC12IFG0)); //IFG0 == 1?
      data[cont] = ADC12MEM0;
      cont++;
    }
    
  }
}


