#include "bsp_fdcan.h"
#include "stm32g4xx_hal_def.h"
#include "stm32g4xx_hal_fdcan.h"
#include <stdint.h>
extern FDCAN_HandleTypeDef hfdcan1;
static FDCAN_RxHeaderTypeDef FDCAN_RxHeader;
static FDCAN_TxHeaderTypeDef FDCAN_TxHeader;
static uint8_t FDCan_RXData[8];
static volatile uint8_t Can_LightCmd;
static volatile uint8_t Can_LightCmdFlag = 0U;
Can_StatusType Can_Init() {
  if ((HAL_FDCAN_ConfigGlobalFilter(
          &hfdcan1, FDCAN_ACCEPT_IN_RX_FIFO0, FDCAN_ACCEPT_IN_RX_FIFO0,
          FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE)) != HAL_OK) {
    return FDcan_error;
  }
  HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
  HAL_FDCAN_Start(&hfdcan1);
  HAL_NVIC_SetPriority(FDCAN1_IT0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(FDCAN1_IT0_IRQn);
  return FDcan_ok;
}
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan,
                               uint32_t RxFifo0ITs) {
  if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != 0U) {
    if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &FDCAN_RxHeader,
                               FDCan_RXData) == HAL_OK) {
      HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);
      if (FDCAN_RxHeader.Identifier == CAN_ID_LIGHT_CMD) {
        Can_LightCmd = FDCan_RXData[0];
        Can_LightCmdFlag = 1;
      }
    }
  }
}
Can_StatusType FDCan_Transmit(uint32_t Can_Id, const uint8_t *TXData,
                              uint8_t Data_Len) {
  if ((TXData == NULL) || (Data_Len > 8U)) {
    return FDcan_error;
  }
  FDCAN_TxHeader.Identifier = Can_Id;
  FDCAN_TxHeader.IdType = FDCAN_STANDARD_ID;
  FDCAN_TxHeader.TxFrameType = FDCAN_DATA_FRAME;
  FDCAN_TxHeader.DataLength = Data_Len;
  FDCAN_TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
  FDCAN_TxHeader.BitRateSwitch = FDCAN_BRS_OFF;
  FDCAN_TxHeader.FDFormat = FDCAN_CLASSIC_CAN;
  FDCAN_TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
  FDCAN_TxHeader.MessageMarker = 0U;
  if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &FDCAN_TxHeader, TXData) !=
      HAL_OK) {
    return FDcan_error;
  }
  return FDcan_ok;
}
Can_StatusType FDCan_GetLightCmd(uint8_t *Cmd) {
  if (Can_LightCmdFlag == 0U) {
    return FDcan_error;
  }
  *Cmd = Can_LightCmd;
  Can_LightCmdFlag = 0U;
  return FDcan_ok;
  
}
