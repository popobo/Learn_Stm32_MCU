#ifndef __COUNTSENSOR_H_
#define __COUNTSENSOR_H_

typedef void(*CountSensor_Handler)(void);

void CountSensor_Init(void);

void CountSensor_Set_Handler(CountSensor_Handler handler);

#endif
