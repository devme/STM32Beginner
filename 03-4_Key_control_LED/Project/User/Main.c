#include "stm32f10x.h"
#include "LED.h"
#include "Key.h"

uint8_t KeyNum;
int main(){

    LED_Init();
    Key_Init();
    while(1){
        KeyNum = Key_GetNum();
        if(KeyNum == 1){
            LED1_Turn();
        }else if(KeyNum == 2){
            LED2_Turn();
        }
    }
}
