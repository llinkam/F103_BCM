#ifndef BSP_DIN_H
#define BSP_DIN_H
#include "main.h"

#define DIN_SAMPLE_PERIOD_MS 10u
#define DIN_DEBOUNCE_CNT 3u

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
typedef enum {
  DIN_INACTIVE = 0,
  DIN_ACTIVE = 1,
} Din_LevelType;
typedef enum {
  Din_error = 0,
  Din_OK = 1,
} Din_StatusType;

void Din_Msp_Init(void);
void Din_MainFunction(void);
Din_StatusType Din_Read(Din_ChannelType Channel, Din_LevelType *pLevel);
Din_StatusType Din_GetRaw(Din_ChannelType Channel, Din_LevelType *pLevel);
#endif
