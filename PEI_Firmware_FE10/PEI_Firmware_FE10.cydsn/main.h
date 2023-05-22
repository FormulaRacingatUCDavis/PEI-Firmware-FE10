/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "project.h"
#include "CAN.h"
#include "can_manager.h"
#include "display.h"
#include "relays.h"

typedef enum {
    PEI_LV, 
    PEI_PRECHARGE,
    PEI_HV,
    PEI_FAULT
} PEI_STATE_t;

typedef enum {
    LV,
    PRECHARGING,
    HV_ENABLED,
    DRIVE,
    FAULT = 0x80,
} VCU_STATE;

typedef enum{
    VSM_START,
    PRECHARGE_INIT,
    PRECHARGE_ACTIVE,
    PRECHARGE_COMPLETE,
    VSM_WAIT,
    VSM_READY,
    MOTOR_RUNNING,
    BLINK_FAULT_CODE,
    SHUTDOWN_IN_PROCESS = 14,
    RECYCLE_POWER = 15 
} MC_VSM_STATE;

typedef enum{
    DISCHARGE_DISABLED,
    DISCHARGE_ENABLED,
    SPEED_CHECK,
    DISCHARGE_ACTIVE,
    DISCHARGE_COMPLETE 
} MC_DISCHARGE_STATE;

uint8_t hv_allowed();
uint8_t precharge_complete();
uint8_t precharge_ready();
int16_t get_current();
uint8_t hv_request();

/* [] END OF FILE */
