#include "Delay.h"
#include "stm32f10x.h"
#include "OLED.h"
#include "Motor.h"
#include "Key.h"

uint8_t KeyNum;
int8_t Speed;
//TODO Speed是负数的时候开发板好像会不停断电，插在USB扩展的鼠标键盘也会失灵，没搞明白什么问题🙋
int main(){
    OLED_Init();
    Motor_Init();
    Key_Init();
    OLED_ShowString(1,1,"Speed");
    while(1){
        KeyNum = Key_GetNum();
        if (KeyNum == 1) {
            Speed+=20;
            if (Speed>100) {
                Speed=-100;
            }
        }
        Motor_SetSpeed(Speed);
        OLED_ShowSignedNum(2,1,Speed,3);
    }
}
