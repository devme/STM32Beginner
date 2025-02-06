#include "stm32f10x.h"
#include "Delay.h"

int main(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStruct);
    //GPIO_SetBits(GPIOA,GPIO_Pin_0);
    //GPIO_ResetBits(GPIOA,GPIO_Pin_0);
    //GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
    //GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
    while(1){
        GPIO_WriteBit(GPIOB,GPIO_Pin_12,Bit_RESET);
        Delay_ms(100);
        GPIO_WriteBit(GPIOB,GPIO_Pin_12,Bit_SET);
        Delay_ms(100);
        GPIO_WriteBit(GPIOB,GPIO_Pin_12,Bit_RESET);
        Delay_ms(100);
        GPIO_WriteBit(GPIOB,GPIO_Pin_12,Bit_SET);
        Delay_ms(700);
    }

}