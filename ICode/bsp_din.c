#include "bsp_din.h"
typedef struct {
  GPIO_TypeDef *GPIOx;
  uint16_t GPIO_Pin;
} Din_ConfigType;
static Din_LevelType s_Raw[DIN_CH_NUM];
static Din_LevelType s_Stable[DIN_CH_NUM];
static uint8_t s_Counter[DIN_CH_NUM];
static const Din_ConfigType Din_Config[DIN_CH_NUM] = {
    {GPIOB, GPIO_PIN_13}, {GPIOB, GPIO_PIN_12}, {GPIOB, GPIO_PIN_11},
    {GPIOB, GPIO_PIN_14}, {GPIOB, GPIO_PIN_1},  {GPIOB, GPIO_PIN_0},
    {GPIOA, GPIO_PIN_7},  {GPIOA, GPIO_PIN_6}};
static Din_LevelType Din_ReadLevel(Din_ChannelType Channel) {
  GPIO_PinState pin =
      HAL_GPIO_ReadPin(Din_Config[Channel].GPIOx, Din_Config[Channel].GPIO_Pin);
  return (pin == GPIO_PIN_RESET) ? DIN_ACTIVE : DIN_INACTIVE;
}
void Din_Msp_Init(void) {
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  GPIO_InitTypeDef gpio = {0};
  gpio.Mode = GPIO_MODE_INPUT;
  gpio.Pull = GPIO_PULLUP;
  gpio.Speed = GPIO_SPEED_FREQ_LOW;
  for (int i = 0; i < DIN_CH_NUM; i++) {
    HAL_GPIO_WritePin(Din_Config[i].GPIOx, Din_Config[i].GPIO_Pin,
                      GPIO_PIN_SET);
  }
  for (int i = 0; i < DIN_CH_NUM; i++) {
    gpio.Pin = Din_Config[i].GPIO_Pin;
    HAL_GPIO_Init(Din_Config[i].GPIOx, &gpio);
  }
  HAL_Delay(5);
  for (int i = 0; i < DIN_CH_NUM; i++) {
    s_Raw[i] = Din_ReadLevel((Din_ChannelType)i);
    s_Stable[i] = s_Raw[i];
    s_Counter[i] = 0;
  }
}
void Din_MainFunction(void) {
  for (int i = 0; i < DIN_CH_NUM; i++) {
    s_Raw[i] = Din_ReadLevel((Din_ChannelType)i);
    if (s_Raw[i] != s_Stable[i]) {
      s_Counter[i]++;
      if (s_Counter[i] >= DIN_DEBOUNCE_CNT) {
        s_Stable[i] = s_Raw[i];
        s_Counter[i] = 0;
      }
    } else {
      s_Counter[i] = 0;
    }
  }
}
Din_StatusType Din_Read(Din_ChannelType Channel, Din_LevelType *pLevel) {
  if ((Channel >= DIN_CH_NUM) || (pLevel == NULL)) {
    return Din_error;
  }
  *pLevel = s_Stable[Channel];
  return Din_OK;
}
Din_StatusType Din_GetRaw(Din_ChannelType Channel, Din_LevelType *pLevel) {
  if ((Channel >= DIN_CH_NUM) || (pLevel == NULL)) {
    return Din_error;
  }
  *pLevel = s_Raw[Channel];
  return Din_OK;
}
