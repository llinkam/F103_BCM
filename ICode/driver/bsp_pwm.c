#include "bsp_pwm.h"
static TIM_HandleTypeDef htim3;
static const Pwm_ConfigType Pwm_Config[PWM_CH_NUM] = {{&htim3, TIM_CHANNEL_1}};
void Pwm_Msp_Init(void) {
  __HAL_RCC_TIM3_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  htim3.Instance = TIM3;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = PWM_DUTY_MAX - 1;
  htim3.Init.RepetitionCounter = 0;
  /* APB1 定时器时钟 170MHz / 170 = 1MHz，1MHz / 1000 = 1kHz PWM */
  htim3.Init.Prescaler = 170 - 1;
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK) {
    Error_Handler();
  }
  TIM_OC_InitTypeDef sConfig = {0};
  sConfig.OCFastMode = TIM_OCFAST_ENABLE;
  sConfig.OCMode = TIM_OCMODE_PWM1;
  sConfig.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  sConfig.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfig.Pulse = 0;
  sConfig.OCPolarity = TIM_OCPOLARITY_LOW;
  HAL_TIM_PWM_ConfigChannel(&htim3, &sConfig, TIM_CHANNEL_1);
  GPIO_InitTypeDef gpio = {0};
  gpio.Mode = GPIO_MODE_AF_PP;
  gpio.Pin = GPIO_PIN_6;
  gpio.Pull = GPIO_NOPULL;
  gpio.Speed = GPIO_SPEED_FREQ_HIGH;
  gpio.Alternate = GPIO_AF2_TIM3; /* PC6 = TIM3_CH1，接 LED1（低电平亮，靠 OCPolarity LOW 反相） */
  HAL_GPIO_Init(GPIOC, &gpio);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
}
Pwm_StatusType Pwm_SetDuty(Pwm_ChannelType Channel, uint16_t Duty) {
  if ((Channel >= PWM_CH_NUM) || (Duty > PWM_DUTY_MAX)) {
    return Pwm_error;
  }
  __HAL_TIM_SET_COMPARE(Pwm_Config[Channel].htim, Pwm_Config[Channel].Channel, Duty);
  return Pwm_OK;
}