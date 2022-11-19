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

typedef enum {
    VEHICLE_STATE = 0x0c0,
    SWITCHES = 0x0d0,
    TORQUE_REQUEST_COMMAND = 0x766,
    BMS_STATUS = 0x380,
    PEI_CURRENT = 0x387,
    BMS_VOLTAGES = 0x388,
    BMS_TEMPERATURES = 0x389
} CAN_ID;

void Clear_interlock() {
    //TODO
}

void Set_Interlock() {
    //TODO   
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    int state = 0;
    int setInterlock = 0;
    int e_stop_check = 0;
    int e_stop = 0;
    int throttle_high = 0;
    int throttle_low = 0;
    int VCL_Throttle = 0;
    int VCL_Brake = 0
    int status3 = 0;
    int DisplayState = 1
    int Count_Low = 0
    int Count_High = 0
    int flashing_L = 0
    int flashing_H = 0
    
    //---------------- CAN Variables -----------------------------
    // need to revise later according to PEI pins?
    pdoSend equals can1
    pdoRecv equals can2
    debug   equals can3
    pdoAck	equals can4
    eStop   equals can5

    
    // shutdown flags
    
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
