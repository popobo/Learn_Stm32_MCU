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

uint16_t AD_value;
float voltage;

int main()
{   
    OLED_Init();
    AD_Init();

    while(1)
	{
        AD_value = AD_GetValue();
        voltage = (float)AD_value / 4095 * 3.3;
        OLED_ShowNum(1, 1, AD_value, 4);
        OLED_ShowNum(2, 1, voltage, 1);
        OLED_ShowNum(2, 3, (uint32_t)(voltage * 100) % 100, 2);
        Delay_ms(100);
    }
}
