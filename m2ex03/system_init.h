
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
