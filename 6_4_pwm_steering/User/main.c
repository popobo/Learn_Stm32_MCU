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

// 不要在中断函数和主函数调用相同的函数或操作同一个硬件,因为硬件不会保存上下文
int main()
{   
    OLED_Init();
    PWM_Init();
    while(1)
	{
        for(int i = 0; i < 100; ++i)
        {
            Pwm_SetCompare1(i);
            Delay_ms(10);
        }

        for(int i = 100; i > 0; --i)
        {
            Pwm_SetCompare1(i);
            Delay_ms(10);
        }
	}
}
