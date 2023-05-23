#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Led.h"
#include "Key.h"
#include "Buzzer.h"
#include "LightSensor.h"
#include "OLed.h"
#include "CountSensor.h"

static int32_t count;

void Count(void)
{
    count++;
}

int main()
{   
    OLED_Init();
    CountSensor_Init();
    CountSensor_Set_Handler(Count);
    while(1)
	{
        OLED_ShowNum(1, 1, count, 4);
	}
}
