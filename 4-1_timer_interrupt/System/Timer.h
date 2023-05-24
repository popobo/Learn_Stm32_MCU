#ifndef __TIMER_H_
#define __TIMER_H_

typedef void(*Timer_Handler)(void);

void Timer_Set_Handler(Timer_Handler handler);

void Timer_Init(void);

#endif
