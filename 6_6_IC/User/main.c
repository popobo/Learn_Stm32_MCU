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

// 不要在中断函数和主函数调用相同的函数或操作同一个硬件,因为硬件不会保存上下文
int main()
{   
    Key_Init();
    Servo_Init();
    OLED_Init();
    uint8_t key_num = 0;
    float angle = 0.0;
    while(1)
	{
        key_num = Key();
        if (key_num == 1)
        {
            angle += 30;
            if (angle > 180)
            {
                angle = 0;
            }
        }
        OLED_ShowNum(1, 7, angle, 3);
        Servo_SetAngle(angle);
	}
}
