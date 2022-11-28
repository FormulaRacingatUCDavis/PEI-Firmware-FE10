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
# include"project.h"

typedef enum {
    VEHICLE_STATE = 0x0c0,
    SWITCHES = 0x0d0,
    TORQUE_REQUEST_COMMAND = 0x766,
    BMS_STATUS = 0x380,
    PEI_CURRENT = 0x387,
    BMS_VOLTAGES = 0x388,
    BMS_TEMPERATURES = 0x389
} CAN_ID;
    
// State machine
State			equals	User4

void Clear_interlock() {
    //TODO
    // trial
    // make change
}

void Set_Interlock() {
    //TODO   
}
// try to first initalize the state using Andrey publish in his VCL code
void initialization() {
    int SetInterlock = 0;
    int VCL_Throttle = 0;
    int VCL_Brake = 0;
    int state = 0;
    int DisplayState = 1;
    int Count_Low = 0
    int Count_High = 0
    int flashing_L = 0
    int flashing_H = 0
    int e_stop = 0
    int e_stop_check = 0
}

int main(void)
{
    initialization();
    // create a class similar to data type uCAN_MSG from FE9
    uCAN_MSG canCurrentData;
    // TODO: create the uCAN_MSG restruct it
    // might do the comparison for data0,1,2
    canCurrentData.frame.data0 = current >> 8; // upper bits
    canCurrentData.frame.data1 = current & 0xFF; // lower bits
    canCurrentData.frame.data2 = shutdown_flags;
    // TODO: create the function CAN_transmit, pass in the 
    // address of canCurrentData
    CAN_transmit(&canCurrentData);

    CyGlobalIntEnable; /* Enable global interrupts. */

    //The car is not moving yet
    int state = 0;
    
    //At first, there is no driver, so there shouldn't be any voltage moving the wheel.
    int setInterlock = 0;
    int VCL_Throttle = 0;
    
    //Why is the brake set to 0?
    int VCL_Brake = 0;
    
    int e_stop_check = 0;
    int e_stop = 0;
    
    //The 16-bit throttle is split across two 8-bit values
    //throttle = throttle_high * 255 + throttle_low
    int throttle_high = 0; //
    int throttle_low = 0; //
    
    int status3 = 0;
    int DisplayState = 1;
    
    /* Initialized to 0 in the VCL code, not sure if they will be of use here.
    int Count_Low = 0
    int Count_High = 0
    
    int flashing_L = 0
    int flashing_H = 0
    */

    for(;;)
    {
        if (state == 0) {
            Clear_interlock();
            //TODO: put PWM2 to 0
            
            if (setInterlock > 0 && e_stop_check == 0) {
                state = 1;
            }
        }
        else if (state == 1) {
            Set_Interlock();
            
            if (throttle_high*255 + throttle_low < 0 or throttle_high*255 + throttle_low > 32767) {
                VCL_Throttle = 0;
            }
            else {
                VCL_Throttle = (throttle_high * 255) + throttle_low;
            }
            
            if (setInterlock == 0) {
                state = 0;   
            }
            
            if (status3 == 36) {
                state = 3;
                e_stop = 1;
            }
            else if (status3 > 0) {
                state = 2;   
            }
        }
        else if (state == 2) {
            Clear_interlock();
            //put PWM2 to 0
        }
        else if (state == 3) {
            if (e_stop_check == 1) {
                state = 0;
                e_stop = 0;
                //send_mailbox(eStop);
            }
        }
            
    }
}

/* [] END OF FILE */
