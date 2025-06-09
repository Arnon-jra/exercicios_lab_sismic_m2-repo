#include <msp430.h>

#define LED1 BIT0
#define LED2 BIT7
#define S1 BIT1
#define S2 BIT1

void stopwd(void);
void debounce(volatile unsigned int i);
void sys_init(void);
void port1_init(void);
void ta0_init(void);
void ta1_init(void);

