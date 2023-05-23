#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Led.h"
#include "Key.h"
#include "Buzzer.h"
#include "LightSensor.h"

int main()
{   
    Buzzer_Init();
    LightSensor_Init();
    while(1)
	{
        if (LightSensor_Is_On())
        {
            Buzzer_On();
        }
        else
        {
            Buzzer_Off();
        }
	}
}
