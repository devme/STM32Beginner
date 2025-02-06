#include "Servo.h"
#include "PWM.h"

void Servo_Init(){

    PWM_Init();
}

void Servo_SetAngle(float Angle) {

    PWM_SetCompare2(Angle/180*2000+500);

}