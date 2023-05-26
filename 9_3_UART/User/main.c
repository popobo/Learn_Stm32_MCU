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
#include "Serial.h"
#include <string.h>
#include <stdio.h>

int main()
{   
    OLED_Init();
    Serial_Init();
    
    const char* array = "hello world!\r\n";

    Serial_SenByte(0x41);

    Serial_SendArray((uint8_t *)array, (uint16_t)strlen(array));

    Serial_SendString(array);

    Serial_SendNumber(12345, 5);

    printf("hello world %d", 6);

    Serial_printf("hello world %d", 6);

    Serial_printf("你好 %d", 6);

    while(1)
	{
    }
}

int fputc(int ch, FILE* f)
{
    Serial_SenByte(ch);
    return ch;
}
