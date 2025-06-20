#include <msp430.h>
#include "sys_init.h"
#include "stdint.h"


void debounce(volatile unsigned int i){
    while(i--);
}

void stopwd(){
    WDTCTL = WDTPW | WDTHOLD;  // Parar watchdog
}

void ta1_init(void){
    
    P2SEL |= BIT0;

    TA1CTL = TASSEL__SMCLK | TACLR | MC__CONTINOUS;

    TA1CCTL1 = CAP | CM_3 | CCIE;
    TA1CCTL1 &= ~CCIFG;
}

void sys_init(void){
    stopwd(); 
}

void port1_init(void){
    //P1.0
   // P1DIR &= ~BIT0;        //P1.0 ativa interrupção 
   // P1REN |= BIT0;
   // P1OUT |= BIT0;
   // P1IES |= BIT0;
    //P1IE |= BIT0;

    //P1.2 (TA0.1) PWM
    P1DIR |= BIT2;
    P1SEL |= BIT2;

    //P1.3 Output
    P1DIR |= BIT3;

    //P1.4 Output
    P1DIR |= BIT4;
}

void ta0_init(void){
    TA0CTL = TASSEL__SMCLK | MC__UP | TACLR;
    TA0CCR0 = 52;
    TA0CCTL1 = OUTMOD_3;
    TA0CCR1 = 8;

}


void i2c_config(void){
    //--------------------------GPIO CONFIG----------------------//
    P4SEL |= BIT1;                          //seleciona função dedicada 
    P4SEL |= BIT2;
    P4DIR &= ~(BIT1 | BIT2);                //dir = 0: INPUT
    P4REN |= BIT1 | BIT2;                   //habilita Resistor Pull up
    P4OUT |= BIT1 | BIT2;                   //out = 1: PULLUP

    PMAPKEYID = 0x02D52;                    //habilita uso de mapeamento das portas
    P4MAP1 = PM_UCB1SDA;                    //habilita P4.1 e P4.2 para uso do módulo (USCI B1)
    P4MAP2 = PM_UCB1SCL;

    //--------------------------USCI I2C INITIALIZATION----------------------//
    UCB1CTL1 |= UCSWRST;                    //software reset enable
    UCB1CTL1 |= UCSSEL__SMCLK;              //seleciona smclk como fonte do clock 
    UCB1CTL0 |= UCMST | UCMODE_3;           //modo mestre, modo i2c 
    UCB1BR0 = 0x0A;                         // smclk/10
    UCB1BR1 = 0x00;
    UCB1CTL1 &= ~UCSWRST;                   //software reset disable
}

uint8_t i2c_send(uint8_t addr, uint8_t data){
    UCB1I2CSA = addr;                       //slave address
    UCB1CTL1 |= UCTR;                       // Transmitter Mode
    UCB1CTL1 |= UCTXSTT;                    //START 
    UCB1TXBUF = data;

    if ((UCB1IFG & UCTXIFG) & !(UCB1CTL1 & UCTXSTT)) {        //Transmission has begun 
            UCB1CTL1 |= UCTXSTP;         //Generate STOP 
            UCB1IFG &= ~UCTXIFG;
            return (UCB1IFG & UCTXNACK); //0: ACK, 1: NACK
    } else if (UCB1IFG & UCNACKIFG) {
            return (UCB1IFG & UCTXNACK);  //0: ACK, 1: NACK                 
    }
    return 0xff;      
}
