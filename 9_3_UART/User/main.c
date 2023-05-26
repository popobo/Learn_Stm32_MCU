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

uint8_t rx_data;

int main()
{   
    OLED_Init();
    Serial_Init();
    
    while(1)
	{
        if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
        {
            rx_data = USART_ReceiveData(USART1);
            // 读完标志位自动清零
            OLED_ShowHexNum(1, 1, rx_data, 2);
        }
    }
}
