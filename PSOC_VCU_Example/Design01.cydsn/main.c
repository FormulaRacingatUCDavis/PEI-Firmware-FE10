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
            Clear_interlock(); //send a message to open AIRs
            if((get_Set_Interlock() > 0) && (get_ESTOP_Check() == 0)) {
                //TODO: Set the state to 1;
                
                state =1;
            }
        }
        else if (state == 1) {
            Set_interlock(); //?????
            if(((get_THROTTLE_HIGH()*255 + get_THROTTLE_LOW()) < 0) || ((get_THROTTLE_HIGH()*255 + get_THROTTLE_LOW()) > 32767)){
                can_send_VCL(0);
            }
            else
		    {
			can_send_VCL(get_THROTTLE_HIGH()*255 + get_THROTTLE_LOW());
			//the throttle signal is in bounds and is between 0 and 32767
	  	    }
            if(get_HV_Requested() == 0) {
                state = 0;
                //TODO: Set the state to 0;
            }
                state = 2;
            //TODO: Set the state to 2 if there's an error
            /*May or may not need to check status 3
            if(Status3 = 36) ; an OS defined variable that has info on driver faults
		        ; checks for 2 specific errors
    		; Bit2 = Coi12 Driver Open/Short (Code 32)
    		; Bit5 = PD Open/Short (Code 35)
    		{
    			state = 3
    			e_stop = 1
    			; sends CAN message saying that estop should activate
    			send_mailbox(eStop)
    		}
            else if(Status3 > 0) 
    		{
    			; trap state
    			state = 2
    		}
               */
        }
        else if(state == 2)	// Trap state. No exit conditions. DO NOT TOUCH!!!!!!!
	    // is entered when there are more errors than just estop (Status3 > 0). 
	    {
		Clear_interlock();
		// set EM Brake = 0
		
	     } 
        else if (state == 3) {
            if (get_ESTOP_Check() == 1) {
                state = 0;
                can_send_ESTOP(0);
                
         
            }
        }
        can_send_state(state);    
    }
}

/* [] END OF FILE */
