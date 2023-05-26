#include "stm32f10x.h"
#include "Pwm.h"

void Servo_Init(void)
{
    PWM_Init();
}

/*
0 500

180 2500
*/

void Servo_SetAngle(float angle)
{
    Pwm_SetCompare2(angle / 180 * 2000 + 500);
}
