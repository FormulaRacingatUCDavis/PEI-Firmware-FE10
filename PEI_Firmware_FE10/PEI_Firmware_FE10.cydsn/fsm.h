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

#ifndef FSM_H
#define FSM_H

#include "project.h"
#include "can_manager.h"

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

#define NORMAL 0x00
#define BMS_TIMEOUT 0x01
#define VCU_CHARGER_TIMEOUT 0x02
#define MC_TIMEOUT 0x08
#define MC_FAULT 0x10
#define SHUTDOWN 0x20
#define MC_DISCHARGING 0x40
#define CHARGER_FAULT 0x80

uint8_t hv_request();
uint8_t hv_allowed();
uint8_t precharge_complete();
uint8_t precharge_ready();

void update_status();
void add_status(uint8_t status);

#endif

/* [] END OF FILE */
