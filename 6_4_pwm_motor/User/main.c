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
#include "Motor.h"

int main()
{   
    OLED_Init();
    Motor_Init();
    Key_Init();

    Motor_SetSpeed(0);
    uint8_t key = 0;
    int8_t speed = 0;
    while(1)
	{
        key = Key();
        if(key == 1)
        {
            speed += 20;
        }
        else if (key == 2)
        {
            speed -= 20;
        }
        Motor_SetSpeed(speed);
        OLED_ShowSignedNum(1, 1, speed, 3);
	}
}
