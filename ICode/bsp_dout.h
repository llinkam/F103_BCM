#ifndef BSP_DOUT_H
#define BSP_DOUT_H
#include "main.h"
typedef enum {
  DOUT_CH_1 = 0, /* PB6 继电器 K2   */
  DOUT_CH_2,     /* PB7 继电器 K3   */
  DOUT_CH_3,     /* PB8 继电器 K4   */
  DOUT_CH_4,     /* PB9 继电器 K1   */
  DOUT_CH_5,     /* PA15 MOS  		  */
  DOUT_CH_6,     /* PB3  MOS        */
  DOUT_CH_7,     /* PB4  MOS        */
  DOUT_CH_8,     /* PB5  MOS        */
  DOUT_CH_9,     /* PC13            */
  DOUT_CH_NUM    /* 通道总数         */
} Dout_ChannelType;
typedef enum { Dout_off = 0, Dout_on = 1 } Dout_StateType;
typedef struct {
  GPIO_TypeDef *GPIOx;
  uint16_t GPIO_Pin;
} Dout_ConfigType;
typedef enum {
  Dout_error = 0,
  Dout_OK = 1,
} Dout_StatusType;
void Dout_Msp_Init(void);
Dout_StatusType Dout_SetLevel(Dout_ChannelType Channel, Dout_StateType control);
#endif