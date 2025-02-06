#include "Delay.h"
#include "stm32f10x.h"
#include "OLED.h"
#include "Timer.h"
#include "Encoder.h"
int16_t Speed;
int main(){

    OLED_Init();
    Timer_Init();
    Encoder_Init();
    OLED_ShowString(1,1,"Speed:");
    while(1){
        OLED_ShowSignedNum(1,7,Speed,5);
        Delay_ms(1000);
    }
}

void TIM2_IRQHandler(){
    if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET){
        Speed = Encoder_Get();
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }

}
