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

#include "relays.h"
extern uint8_t relay_flags;

//Closes the precharge relay, opens the positive relay
void start_precharge() {
    AIR_NEG_Write(1);
    AIR_POS_Write(0);
    Precharge_Write(1);
    
    relay_flags = 0b101;
}

//Opens the precharge relay, closese the positive relay
void finish_precharge()
{
    AIR_NEG_Write(1);
    AIR_POS_Write(1);
    Precharge_Write(0);
    
    relay_flags = 0b110;
}    

void clear_interlock()
{
    AIR_NEG_Write(0);
    AIR_POS_Write(0);
    Precharge_Write(0);
    
    relay_flags = 0b000;
}

/* [] END OF FILE */
