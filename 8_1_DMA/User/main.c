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
    MYDMA_Init((uint32_t)data_src, (uint32_t)data_dst, sizeof(data_src));

    while(1)
	{
        data_src[0]++;
        data_src[1]++;
        data_src[2]++;
        data_src[3]++;

        OLED_ShowHexNum(1+2, 1, data_src[0], 2);
        OLED_ShowHexNum(1+2, 4, data_src[1], 2);
        OLED_ShowHexNum(1+2, 7, data_src[2], 2);
        OLED_ShowHexNum(1+2, 10, data_src[3], 2);

        Delay_ms(500);
        MYDMA_Transfer(sizeof(data_src));

        OLED_ShowHexNum(2+2, 1, data_dst[0], 2);
        OLED_ShowHexNum(2+2, 4, data_dst[1], 2);
        OLED_ShowHexNum(2+2, 7, data_dst[2], 2);
        OLED_ShowHexNum(2+2, 10, data_dst[3], 2);
        
    }
}
