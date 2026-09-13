#include "bsp_din.h"
static Din_StatusType s_Stable[DIN_CH_NUM];
static uint8_t Din_Stable_Count;
static const Din_ConfigType Din_Config[DIN_CH_NUM] = {
    {GPIOB, GPIO_PIN_13}, {GPIOB, GPIO_PIN_12}, {GPIOB, GPIO_PIN_11},
    {GPIOB, GPIO_PIN_14}, {GPIOB, GPIO_PIN_0},  {GPIOB, GPIO_PIN_13},
    {GPIOA, GPIO_PIN_7},  {GPIOA, GPIO_PIN_6}};
void Din_Msp_Init(void) {
  GPIO_InitTypeDef gpio = {0};
  for (int i = 0; i < DIN_CH_NUM; i++) {
    HAL_GPIO_WritePin(Din_Config[i].GPIOx, Din_Config[i].GPIO_Pin,
                      GPIO_PIN_SET);
  }
  gpio.Mode = GPIO_MODE_INPUT;
  gpio.Pin = GPIO_PIN_13 | GPIO_PIN_12 | GPIO_PIN_14 | GPIO_PIN_11;
  gpio.Pull = GPIO_NOPULL;
  gpio.Speed = GPIO_SPEED_MEDIUM;
  HAL_GPIO_Init(GPIOA, &gpio);
}
void Din_MainFunction(void) {
  for (int i = 0; i < 3; i++) {
    for (int i = 0; i < DIN_CH_NUM; i++) {
      s_Stable[i] = (Din_StatusType)HAL_GPIO_ReadPin(Din_Config[i].GPIOx,
                                                     Din_Config[i].GPIO_Pin);
      if (s_Stable[i] == DIN_ACTIVE) {
        Din_Stable_Count += 1;
        if (Din_Stable_Count >= 3) {
        }
      } else {
        Din_Stable_Count = 0;
      }
    }
    uint32_t tick = HAL_GetTick();
    if (HAL_GetTick() - tick >= 10) {
    }
  }
}
Din_StatusType Din_Read(Din_ChannelType Channel, uint32_t *Data) {
  Din_MainFunction();
  return DIN_ACTIVE;
}