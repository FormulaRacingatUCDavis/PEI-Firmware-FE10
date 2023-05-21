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
#include "Precharge.h"


//Closes the precharge relay, opens the positive relay
void close_precharge() {
    AIR_NEG_Write(1);
    AIR_POS_Write(0);
    Precharge_Write(1);
}

//Opens the precharge relay, closese the positive relay
void open_precharge()
{
    AIR_NEG_Write(1);
    Precharge_Write(0);
    AIR_POS_Write(1);
}    

void clear_interlock()
{
    AIR_NEG_Write(0);
    AIR_POS_Write(0);
    //can_send_interlock(0,0);
}

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

void can_send_PEI(uint8_t current_upper, uint8_t current_lower, uint8_t shutdown_flags)
{
    uint8_t data[8] = {0};

    data[0] = current_upper;
    data[1] = current_lower;
    data[2] = shutdown_flags;
    //can_send(data, 0x383); 
}
