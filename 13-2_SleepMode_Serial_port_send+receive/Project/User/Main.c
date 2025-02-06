#include <stdio.h>

#include "Delay.h"
#include "stm32f10x.h"
#include "OLED.h"
#include "Serial.h"

uint8_t RxData;

int main(){

    OLED_Init();
    OLED_ShowString(1,1,"RxData:");
    Serial_Init();
    while(1){
        /*
        if (USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == SET) {
            RxData = USART_ReceiveData(USART1);
            OLED_ShowHexNum(1,1,RxData,2);
        }
        */
        if (Serial_GetRxFlag()) {
            RxData = Serial_GetRxData();
            Serial_SendByte(RxData);
            OLED_ShowHexNum(1,8,RxData,2);
        }
        OLED_ShowString(2,1,"Running");
        Delay_ms(500);
        OLED_ShowString(2,1,"       ");
        Delay_ms(500);

        __WFI();
    }
}
