#ifndef BSP_PWM_H
#define BSP_PWM_H
#include "main.h"
#define PWM_DUTY_MAX 1000u
typedef struct
{
    TIM_HandleTypeDef *htim;
    uint16_t Channel;
}Pwm_ConfigType ;
typedef enum {
  PWM_CH_1 = 0,
  PWM_CH_NUM
} Pwm_ChannelType;
typedef enum {
  Pwm_error = 0,
  Pwm_OK = 1,
} Pwm_StatusType;
void Pwm_Msp_Init(void);
Pwm_StatusType Pwm_SetDuty(Pwm_ChannelType Channel, uint16_t Duty);
#endif
