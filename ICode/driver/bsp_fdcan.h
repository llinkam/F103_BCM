#ifndef BSP_FDCAN_H
#define BSP_FDCAN_H
#include "fdcan.h"
#include "main.h"

#define CAN_ID_TEST 0x123U         /* 联调用 */
#define CAN_ID_LIGHT_CMD 0x201U    /* F407 → BCM：灯光命令 */
#define CAN_ID_LIGHT_STATUS 0x301U /* BCM → F407：灯光状态 */
typedef enum { FDcan_error = 0, FDcan_ok } Can_StatusType;
Can_StatusType Can_Init(void);
Can_StatusType FDCan_Transmit(uint32_t Can_Id, const uint8_t *TXData,
                              uint8_t Data_Len);
Can_StatusType FDCan_GetLightCmd(uint8_t *Cmd);
#endif
