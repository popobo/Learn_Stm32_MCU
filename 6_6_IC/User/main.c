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

// 不要在中断函数和主函数调用相同的函数或操作同一个硬件,因为硬件不会保存上下文
int main()
{   
    OLED_Init();
    PWM_Init();
    IC_Init();

    OLED_ShowString(1, 1, "Freq:00000Hz");
    Pwm_SetCompare2(500);
    Pwm_SetPrescaler2(720 - 1);

    while(1)
	{
        OLED_ShowNum(1, 6, IC_GetFreq(), 5);
	}
}
