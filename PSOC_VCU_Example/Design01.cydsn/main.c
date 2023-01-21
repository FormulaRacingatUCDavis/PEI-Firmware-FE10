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
void set_interlock();
void clear_interlock();
void interlock(uint8_t mode);

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
            interlock(0); // clears interlock, send a message to open AIRs
            if((get_Set_Interlock() > 0) && (get_ESTOP_Check() == 0)) {
                state =1;
            }
        }
        else if (state == 1) {
            interlock(1); //sets interlock, sends a message to close AIRs
            if(((get_THROTTLE_HIGH()*255 + get_THROTTLE_LOW()) < 0) || ((get_THROTTLE_HIGH()*255 + get_THROTTLE_LOW()) > 32767)){
                can_send_throttle(0);
            }
            else
		    {
			can_send_throttle(get_THROTTLE_HIGH()*255 + get_THROTTLE_LOW());
			//the throttle signal is in bounds and is between 0 and 32767
	  	    }
            if(get_HV_Requested() == 0) {
                state = 0;
            }
                state = 2;
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
        //Trap state
        // is entered when there are more errors than just estop (Status3 > 0). 
        else if(state == 2)
	    {
		    interlock(0); // clears interlock, send a message to open AIRs
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
void set_interlock()
{
    AIR_NEG_Write(1);
    AIR_POS_Write(1);
    can_send_interlock(1,1);
}    
void clear_interlock()
{
    AIR_NEG_Write(0);
    AIR_POS_Write(0);
    can_send_interlock(0,0);
}
void interlock(uint8_t mode)
{
    AIR_NEG_Write(mode);
    AIR_POS_Write(mode);
    can_send_interlock(mode, mode);
}
/* [] END OF FILE */
