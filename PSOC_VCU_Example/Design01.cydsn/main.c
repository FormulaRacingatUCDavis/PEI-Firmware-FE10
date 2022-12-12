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

//The state starts at 0
volatile uint32_t state = 0;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    //Initialize and start CAN
    CAN_GlobalIntEnable();
    CAN_Start();

    for(;;)
    {
        //Interlock state machine
        if (state == 0) {
            if (get_ESTOP_Check() != 0 && get_HV_Requested() == 1) {
                //TODO: Set the state to 1;
            }
        }
        else if (state == 1) {
            if(get_HV_Requested() == 0) {
                //TODO: Set the state to 0;
            }
            //TODO: Set the state to 2 if there's an error
        }
        else if (state == 3) {
            if (get_HV_Requested() == 0) {
                //TODO: Set the state to 0;
            }
        }
            
    }
}

/* [] END OF FILE */
