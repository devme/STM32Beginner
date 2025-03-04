#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>

void Serial_Init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStruct);
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_Mode = USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART1,&USART_InitStructure);

    USART_Cmd(USART1,ENABLE);
}

void Serial_SendByte(uint8_t Byte) {
    USART_SendData(USART1,Byte);
    while (USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
}

void Serial_SendArray(uint8_t *Array, uint16_t Length) {
    uint16_t i;
    for (i = 0; i < Length; i++) {
        Serial_SendByte(Array[i]);
    }
}

void Serial_SendString(char *String) {
    uint8_t i;
    for (i = 0; String[i]!='\0'; i++) {
        Serial_SendByte(String[i]);
    }
}

uint32_t Serial_Pow(uint32_t X,uint32_t Y) {
    uint32_t Result = 1;
    while (Y--) {
        Result *= X;
    }
    return Result;
}

void Serial_SendNumber(uint32_t Number,uint8_t Length) {
    uint8_t i;
    for (i = 0; i < Length; i++) {
        Serial_SendByte(Number/Serial_Pow(10,Length-i-1) % 10 + '0');
    }
}

int __io_putchar(int ch) {
    Serial_SendByte(ch);
    return ch;
}

void Serial_Printf(char *Format,...) {
    char String[100];
    va_list args;
    va_start(args,Format);
    vsprintf(String,Format,args);
    va_end(args);
    Serial_SendString(String);
}
