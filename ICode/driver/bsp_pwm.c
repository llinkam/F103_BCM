#include "bsp_pwm.h"
static TIM_HandleTypeDef htim3;
static const Pwm_ConfigType Pwm_Config[PWM_CH_NUM]={
    {&htim3,TIM_CHANNEL_2}
};
void Pwm_Msp_Init(void)
{   
    __HAL_RCC_TIM3_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_AFIO_CLK_ENABLE();
    __HAL_AFIO_REMAP_TIM3_PARTIAL();
    htim3.Init.AutoReloadPreload=TIM_AUTORELOAD_PRELOAD_ENABLE;
    htim3.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    htim3.Init.CounterMode=TIM_COUNTERMODE_UP;
    htim3.Init.Period=1000-1;
    htim3.Init.RepetitionCounter=0;
    htim3.Init.Prescaler=72-1;
    htim3.Instance=TIM3;
    HAL_TIM_Base_Init(&htim3);
    TIM_OC_InitTypeDef sConfig={0};
    sConfig.OCFastMode=TIM_OCFAST_ENABLE;
    sConfig.OCMode=TIM_OCMODE_PWM1;
    sConfig.OCIdleState=TIM_OCIDLESTATE_RESET;
    sConfig.OCNIdleState=TIM_OCNIDLESTATE_RESET;
    sConfig.OCNPolarity=TIM_OCNPOLARITY_HIGH;
    sConfig.Pulse=100;
    sConfig.OCPolarity=TIM_OCPOLARITY_LOW;
    HAL_TIM_PWM_ConfigChannel(&htim3,&sConfig,TIM_CHANNEL_2);
    GPIO_InitTypeDef gpio={0};
    gpio.Mode=GPIO_MODE_AF_PP;
    gpio.Pin=GPIO_PIN_5;
    gpio.Pull=GPIO_NOPULL;
    gpio.Speed=GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &gpio);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
}
Pwm_StatusType Pwm_SetDuty(Pwm_ChannelType Channel, uint16_t Duty)
{
    if(Duty>1000)
    {
        return Pwm_error;
    }
    else {
        __HAL_TIM_SET_COMPARE(Pwm_Config[Channel].htim,Pwm_Config[Channel].Channel,Duty);
        return Pwm_OK;
    }  
}