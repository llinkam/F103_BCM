#ifndef BSP_DIN_H
#define BSP_DIN_H
#include "main.h"
typedef enum {
  DIN_CH_1 = 0, /* SW1 PB15 */
  DIN_CH_2,     /* SW2 PB14 */
  DIN_CH_NUM
} Din_ChannelType;
typedef enum {
  DIN_ACTIVE = 0,
  DIN_INACTIVE = 1,
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
