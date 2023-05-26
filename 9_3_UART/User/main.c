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
#include "AD.h"
#include "MYDMA.h"

uint8_t data_src[] = {0x01, 0x02, 0x03, 0x04};
uint8_t data_dst[] = {0, 0, 0, 0};

int main()
{   
    OLED_Init();
    AD_Init();

    OLED_ShowString(1, 1, "AD1:");
    OLED_ShowString(2, 1, "AD2:");
    OLED_ShowString(3, 1, "AD3:");
    OLED_ShowString(4, 1, "AD4:");

    while(1)
	{
        OLED_ShowNum(1, 5, AD_value[0], 4);
        OLED_ShowNum(2, 5, AD_value[1], 4);
        OLED_ShowNum(3, 5, AD_value[2], 4);
        OLED_ShowNum(4, 5, AD_value[3], 4);
        Delay_ms(100);
    }
}
