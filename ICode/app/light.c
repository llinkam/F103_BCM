#include "light.h"
static Light_RuntimeType Light_Runtime = {
    .State = Light_off, .Duty = 0, .LastKey = DIN_INACTIVE};
void Light_Init(void) {
  Din_Msp_Init();
  Pwm_Msp_Init();
}
void Light_MainFunction(void) {
  Din_LevelType Level;
  Din_MainFunction();
  Din_Read(DIN_CH_1, &Level);
  if ((Level == DIN_ACTIVE) && (Light_Runtime.LastKey == DIN_INACTIVE)) {
    if (Light_Runtime.State == Light_on) {
      Light_Runtime.State = Light_off;
    } else {
      Light_Runtime.State = Light_on;
    }
  }
  Light_Runtime.LastKey = Level;
  if (Light_Runtime.State == Light_on) {
    if (Light_Runtime.Duty <= 1000) {
      Light_Runtime.Duty += 50;
      Light_Runtime.Duty = Light_Runtime.Duty;
      if (Light_Runtime.Duty >= 1000) {
        Light_Runtime.Duty = 1000;
      }
    }
  } else {
    if (Light_Runtime.Duty > 0) {
      Light_Runtime.Duty -= 50;
      Light_Runtime.Duty = Light_Runtime.Duty;
      if (Light_Runtime.Duty <= 0) {
        Light_Runtime.Duty = 0;
      }
    }
  }
  Pwm_SetDuty(PWM_CH_1, Light_Runtime.Duty);
}
