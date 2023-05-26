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

    Serial_tx_packet[0] = 0x10;
    Serial_tx_packet[1] = 0x20;
    Serial_tx_packet[2] = 0x30;
    Serial_tx_packet[3] = 0x40;

    Serial_SendPacket();

    while(1)
	{
        if(Serial_GetRxFlag() == 1)
        {
            OLED_ShowHexNum(1, 1, Serial_rx_packet[0], 2);
            OLED_ShowHexNum(1, 4, Serial_rx_packet[1], 2);
            OLED_ShowHexNum(1, 7, Serial_rx_packet[2], 2);
            OLED_ShowHexNum(1, 10, Serial_rx_packet[3], 2);
        }
    }
}
