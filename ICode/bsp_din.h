#include "main.h"
typedef enum {
  DIN_CH_1 = 0,
  DIN_CH_2,
  DIN_CH_3,
  DIN_CH_4,
  DIN_CH_5,
  DIN_CH_6,
  DIN_CH_7,
  DIN_CH_8,
  DIN_CH_NUM
} Din_ChannelType;
typedef struct {
  GPIO_TypeDef *GPIOx;
  uint16_t GPIO_Pin;
} Din_ConfigType;
typedef enum {
  DIN_ACTIVE = 0,
  DIN_INACTIVE = 1,
} Din_StatusType;
void din_msp_Init(void);
