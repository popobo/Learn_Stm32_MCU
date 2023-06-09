#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Led.h"
#include "Key.h"
#include "Buzzer.h"
#include "LightSensor.h"
#include "OLed.h"
#include "CountSensor.h"
#include "Encoder.h"

static int32_t count;

void Count(void)
{
    count++;
}

void Encoder_Count(int8_t value)
{
    count = count + value;
}

// 不要在中断函数和主函数调用相同的函数或操作同一个硬件？
int main()
{   
    OLED_Init();
    CountSensor_Init();
    Encoder_Init();
    CountSensor_Set_Handler(Count);
    Encoder_Set_Handler(Encoder_Count);
    while(1)
	{
        OLED_ShowSignedNum(1, 1, count, 4);
	}
}
