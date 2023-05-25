#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Led.h"
#include "Key.h"
#include "Buzzer.h"
#include "LightSensor.h"
#include "OLed.h"
#include "CountSensor.h"
#include "Encoder.h"
#include "Timer.h"
#include "Pwm.h"
#include "Servo.h"
#include "IC.h"

int16_t speed;

void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        speed = Encoder_Get();
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}

int main()
{   
    OLED_Init();
    Encoder_Init();
    Timer_Init();
    OLED_ShowString(1, 1, "CNT:00000");

    while(1)
	{
        OLED_ShowSignedNum(1, 5, speed, 5);
	}
}
