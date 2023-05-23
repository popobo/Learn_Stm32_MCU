#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Led.h"
#include "Key.h"

static uint8_t key_num;

int main()
{   
    Led_Init();
    Key_Init();

    while(1)
	{
        key_num = Key();
        if (key_num == 1)
        {
            Led1_Turn();
        }
        else if (key_num == 2)
        {
            Led2_Turn();
        }
	}
}
