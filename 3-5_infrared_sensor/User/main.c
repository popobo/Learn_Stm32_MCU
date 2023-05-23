#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Led.h"
#include "Key.h"
#include "Buzzer.h"
#include "LightSensor.h"
#include "OLed.h"

int main()
{   
    OLED_Init();
    OLED_ShowString(1, 1, "hello");

    while(1)
	{
	}
}
