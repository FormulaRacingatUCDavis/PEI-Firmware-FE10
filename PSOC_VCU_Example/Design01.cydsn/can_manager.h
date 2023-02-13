/* ========================================
* Can manager for PEI
* ========================================
*/

#ifndef CAN_MANGA_H
#define CAN_MANGA_H

#include "project.h"
#include "CAN.h"
//#include "T6963C.h"
//#include "graphic.h"
    
typedef enum {
    TORQUE_REQUEST_COMMAND = 0x766,
    PEI_CURRENT = 0x387,
    MC_ESTOP = 0x366,
    MC_DEBUG = 0x466,
}CAN_ID;

typedef enum {
    LV,
    PRECHARGING,
    HV_ENABLED,
    DRIVE,
    FAULT = 0x80,
}vcu_state;

// Basic CAN functionality
void can_receive(uint8_t *msg, int ID);
void can_test_send();
void can_send(uint8_t data[8], uint32_t ID);

// Advanced CAN functionality
void can_send_cmd(uint8_t SetInterlock, uint16_t Throttle_High, uint16_t Throttle_Low, uint8_t E_Stop_Check);
void can_send_state(uint8_t state);
void can_send_throttle(uint8_t throttle);
void can_send_ESTOP(uint8_t estop);

//VCU state functions
uint8_t get_ESTOP_Check();
uint8_t get_HV_Requested();

//Throttle(HIGH/LOW), THROTTLE
uint8_t get_THROTTLE_HIGH();
uint8_t get_THROTTLE_LOW();
uint8_t get_THROTTLE();

uint8_t get_STATE();

//Interlock functionality
void set_interlock();
void clear_interlock();
void can_send_interlock(uint8_t air_pos, uint8_t air_neg);

//Current flags, shutdown circuit
void can_send_PEI(uint8_t current_upper, uint8_t current_lower, uint8_t shutdown_flags);




/* Not necessary at the moment
uint8_t getEStop(); //Tehya test
void tempAttenuate();
*/
#endif
