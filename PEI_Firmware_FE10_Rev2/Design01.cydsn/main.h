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
#include "can_manager.h"
#include "display.h"
#include "relays.h"
#include "fsm.h"

#define CAN_MSG_INTERVAL 100

#define CHARGE_STOP 1
#define CHARGE_START 0

int16_t get_current();

void printState(PEI_STATE_t state);
#include <stdbool.h>
void printHV(bool request);

/* [] END OF FILE */
