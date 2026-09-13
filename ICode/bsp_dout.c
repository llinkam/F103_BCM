#include "bsp_dout.h"
static const Dout_ConfigType Dout_Config[DOUT_CH_NUM] = {
    {GPIOB, GPIO_PIN_6}, {GPIOB, GPIO_PIN_7},  {GPIOB, GPIO_PIN_8},
    {GPIOB, GPIO_PIN_9}, {GPIOA, GPIO_PIN_15}, {GPIOB, GPIO_PIN_3},
    {GPIOB, GPIO_PIN_4}, {GPIOB, GPIO_PIN_5},  {GPIOC, GPIO_PIN_13}};
void Dout_Msp_Init(void) {
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_AFIO_CLK_ENABLE();
  __HAL_AFIO_REMAP_SWJ_NOJTAG();
  GPIO_InitTypeDef gpio = {0};
  for (int i = 0; i < DOUT_CH_NUM; i++) {
    HAL_GPIO_WritePin(Dout_Config[i].GPIOx, Dout_Config[i].GPIO_Pin,
                      GPIO_PIN_RESET);
  }
  gpio.Mode = GPIO_MODE_OUTPUT_PP;
  gpio.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_3 |
             GPIO_PIN_4 | GPIO_PIN_5;
  gpio.Pull = GPIO_NOPULL;
  gpio.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &gpio);
  gpio.Pin = GPIO_PIN_15;
  HAL_GPIO_Init(GPIOA, &gpio);
  gpio.Pin = GPIO_PIN_13;
  HAL_GPIO_Init(GPIOC, &gpio);
}
Dout_StatusType Dout_SetLevel(Dout_ChannelType Channel,
                              Dout_StateType control) {
  if (Channel >= DOUT_CH_NUM) {
    return Dout_error;
  }
  HAL_GPIO_WritePin(Dout_Config[Channel].GPIOx, Dout_Config[Channel].GPIO_Pin,
                    (GPIO_PinState)control);
  return Dout_OK;
}