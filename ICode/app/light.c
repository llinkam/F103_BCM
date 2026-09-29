#include "light.h"
#include "bsp_fdcan.h"
#include <stdint.h>
static Light_RuntimeType Light_Runtime = {
    .State = Light_off, .Duty = 0, .LastKey = DIN_INACTIVE};
static uint8_t cmd;
void Light_Init(void) {
  Din_Msp_Init();
  Pwm_Msp_Init();
}
void Light_MainFunction(void) {
  Din_LevelType Level;
  Din_MainFunction();
  Din_Read(DIN_CH_1, &Level);
  if (FDCan_GetLightCmd(&cmd) == FDcan_ok) {
    Light_Runtime.State = (cmd == Light_on ? Light_on : Light_off);
  }
  if (((Level == DIN_ACTIVE) && (Light_Runtime.LastKey == DIN_INACTIVE))) {
    if (Light_Runtime.State == Light_on) {
      Light_Runtime.State = Light_off;
    } else {
      Light_Runtime.State = Light_on;
    }
  }
  Light_Runtime.LastKey = Level;
  if (Light_Runtime.State == Light_on) {
    if (Light_Runtime.Duty <= 1000) {
      Light_Runtime.Duty += 10;
      if (Light_Runtime.Duty >= 1000) {
        Light_Runtime.Duty = 1000;
      }
    }
  } else {
    if (Light_Runtime.Duty > 0) {
      Light_Runtime.Duty -= 10;
      if (Light_Runtime.Duty <= 0) {
        Light_Runtime.Duty = 0;
      }
    }
  }
  Pwm_SetDuty(PWM_CH_1, Light_Runtime.Duty);
  static uint8_t Light_StatusCnt = 0U;
  if (++Light_StatusCnt >= 10U) {
    Light_StatusCnt = 0U;
    uint8_t Light_Status[3] = {(uint8_t)Light_Runtime.State,
                               (uint8_t)(Light_Runtime.Duty >> 8),
                               (uint8_t)Light_Runtime.Duty};
    FDCan_Transmit(CAN_ID_LIGHT_STATUS, Light_Status, 3);
  }
};
