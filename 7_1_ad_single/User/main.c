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

uint16_t AD_value1;
uint16_t AD_value2;
uint16_t AD_value3;
uint16_t AD_value4;
float voltage;

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
        AD_value1 = AD_GetValue(ADC_Channel_0);
        AD_value2 = AD_GetValue(ADC_Channel_1);
        AD_value3 = AD_GetValue(ADC_Channel_2);
        AD_value4 = AD_GetValue(ADC_Channel_3);
        OLED_ShowNum(1, 5, AD_value1, 4);
        OLED_ShowNum(2, 5, AD_value2, 4);
        OLED_ShowNum(3, 5, AD_value3, 4);
        OLED_ShowNum(4, 5, AD_value4, 4);
        Delay_ms(100);
    }
}
