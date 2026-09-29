#ifndef LIGHT_H
#define LIGHT_H
#include "bsp_din.h"
#include "bsp_dout.h"
#include "bsp_fdcan.h"
#include "bsp_pwm.h"
#include "main.h"

typedef enum { light_error = 0, Light_ok } Light_StatusType;
typedef enum { Light_off = 0, Light_on } Light_StateType;
typedef struct {
  Light_StateType State;
  uint16_t Duty;
  Din_LevelType LastKey;
} Light_RuntimeType;
void Light_Init(void);
void Light_MainFunction(void);
#endif