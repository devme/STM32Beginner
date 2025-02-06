#include <stdio.h>
#include "stm32f10x.h"
#include "OLED.h"
#include "Serial.h"

int main(){

    OLED_Init();
    Serial_Init();
    Serial_SendByte(0x41);
    Serial_SendString("\r\n");
    uint8_t MyArray[] = {0x42, 0x43, 0x44, 0x45};
    Serial_SendArray(MyArray, 4);
    Serial_SendString("\r\n");
    Serial_SendString("Hello World!");
    Serial_SendString("\r\n");
    Serial_SendNumber(12345,5);
    Serial_SendString("\r\n");
    printf("Num=%d\r\n",666);
    char String[100];
    sprintf(String,"Num=%d\r\n",777);
    Serial_SendString(String);
    Serial_Printf("Num=%d\r\n",888);
    Serial_Printf("你好世界\r\n");
    while(1){
    }
}
