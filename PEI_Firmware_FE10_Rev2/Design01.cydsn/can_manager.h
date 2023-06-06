/* ========================================
* Can manager for PEI
* ========================================
*/

#ifndef CAN_MANGA_H
#define CAN_MANGA_H

#include "project.h"
    
#define CHARGER_MAX_CURRENT 26     //1300W/504V = 2.6A
#define CHARGER_MAX_VOLTAGE 5040   //504V
    
#define CAN_BAUD_TOGGLE_LOOP_COUNT 5
#define CAN_TIMEOUT_LOOP_COUNT 10

//Current flags, shutdown circuit
void can_send_PEI(int16_t current, uint8_t shutdown_flags);
void can_send_CHARGER(uint8_t charge_start);

void check_can();
void CAN_toggle_baud();
void CAN_to_125KB();
void CAN_to_500KB();

#endif
