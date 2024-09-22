#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

void systick_timer(void);


void GPIO_PORT_F_init(void)
{
    SYSCTL_RCGC2_R |= 0x00000020;
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R   = 0x1F;
    GPIO_PORTF_DEN_R  = 0x1F;
    GPIO_PORTF_DIR_R  = 0x0E;
    GPIO_PORTF_PUR_R  = 0x11;

    NVIC_EN0_R |= 1 << 30;
    GPIO_PORTF_IS_R  = 0x00;
    GPIO_PORTF_IBE_R = 0x00;
    GPIO_PORTF_IEV_R = 0x00;
    GPIO_PORTF_IM_R  |= 0x11;
}
void systickInit(void)
{
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_CTRL_R = 0x05;
    NVIC_ST_RELOAD_R = 4000000;
}

void systick_timer()
{
    systickInit();
           NVIC_ST_RELOAD_R = 4000000;
           while((NVIC_ST_CTRL_R & 0x10000)==0)
                    {

                    }
           NVIC_ST_CTRL_R = 0x0;
}

void Portf_interrupt_handler(void)
{
    systick_timer();
    if (GPIO_PORTF_RIS_R & 0x10)
    {
    GPIO_PORTF_DATA_R ^= 0x02;
    GPIO_PORTF_ICR_R = 0x10;
    }

    if (GPIO_PORTF_RIS_R & 0x01)
    {
    GPIO_PORTF_DATA_R ^= 0x02;
    GPIO_PORTF_ICR_R = 0x01;
    }
}
int main(void)
{
    GPIO_PORT_F_init();
    systick_timer();
    while (1)
    {
    }
}
