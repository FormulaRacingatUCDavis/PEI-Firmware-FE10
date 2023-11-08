/* ========================================
 * Can API for FRUCD
 * Schuyler Alschuler 2016 - 2017
 * ========================================
*/

/*******************************************
 * Used to interface dashboard with CAN bus
 * some functinality can be found in CAN_TX_RX_func.c
 * which is a generated source file
 * see the can component of the top design for specific mailboxes
 ******************************************/

#include "can_manager.h"
#include "CAN.h"

extern uint8_t vcu_attached;
extern uint8_t charger_attached;
uint8_t baud = 0;

extern uint16_t loops_since_vcu_message;
extern uint16_t loops_since_bms_message;
extern uint16_t loops_since_mc_message;
extern uint16_t loops_since_charger_message;
extern uint16_t loop_counter;

//temporarily reporting AIR NEG/POS state on 3rd and 4th bytes of PCAN PEI message
/* Used for debug purposes
void can_send_interlock(uint8_t air_neg, uint8_t air_pos)
{
    uint8_t data[8] = {0};
    data[3] = air_neg;
    data[4] = air_pos;
    can_send(data, 0x383); 
}
*/

void can_send_PEI(int16_t current, uint8_t shutdown_flags)
{
    CAN_TX_DATA_BYTE1(CAN_TX_MAILBOX_PEI_CURRENT) = HI8(current);
    CAN_TX_DATA_BYTE2(CAN_TX_MAILBOX_PEI_CURRENT) = LO8(current);
    CAN_TX_DATA_BYTE3(CAN_TX_MAILBOX_PEI_CURRENT) = shutdown_flags;
    
    CAN_SendMsgPEI_CURRENT();   
}

void can_send_CHARGER(uint8_t charge_start){
    CAN_TX_DATA_BYTE1(CAN_TX_MAILBOX_PEI_CHARGER) = HI8(CHARGER_MAX_VOLTAGE);
    CAN_TX_DATA_BYTE2(CAN_TX_MAILBOX_PEI_CHARGER) = LO8(CHARGER_MAX_VOLTAGE);
    CAN_TX_DATA_BYTE3(CAN_TX_MAILBOX_PEI_CHARGER) = HI8(CHARGER_MAX_CURRENT);
    CAN_TX_DATA_BYTE4(CAN_TX_MAILBOX_PEI_CHARGER) = LO8(CHARGER_MAX_CURRENT);
    
    CAN_TX_DATA_BYTE5(CAN_TX_MAILBOX_PEI_CHARGER) = charge_start;
    
    CAN_SendMsgPEI_CHARGER();  
}

//checks to see if a can timout has occured and toggles can bus if so
void check_can(){
    //update timeout counters
    loop_counter++;
    loops_since_bms_message++;
    loops_since_charger_message++;
    loops_since_mc_message++;
    loops_since_vcu_message++;
    
    
    if(charger_attached || vcu_attached){
        return;
    }
    
    if(loop_counter > CAN_BAUD_TOGGLE_LOOP_COUNT){
        //CAN_toggle_baud();
        loop_counter = 0;
    }
}
        

//switches PCAN between 125kb/s (vehicle) and 500kb/s (charger)
void CAN_toggle_baud(){
    if(baud == 0){
        CAN_to_500KB();
        baud = 1;
    } else {
        CAN_to_125KB();
        baud = 0;
    }
}

void CAN_to_125KB(){
    CAN_Stop();
    CAN_Init();
    CAN_SetPreScaler(11);
    CAN_Enable();
}

void CAN_to_500KB(){
    CAN_Stop();
    CAN_Init();
    CAN_SetPreScaler(2);
    CAN_Enable();
}
