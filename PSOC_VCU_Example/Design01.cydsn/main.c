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
    ///
    
    
    //
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    //Initialize and start CAN
    CAN_GlobalIntEnable();
    CAN_Init();
    CAN_Start();
    ADC_DelSig_1_Start();
    
    for(;;)
    {
        state = get_STATE();
        
        //PEI board PICDUINO
        // get current sensor data (RA6/RC0 ???)
        // TODO: acquiring this conversion will need to change for current sensor; need 2 ADC channels
        uint32_t current = (int32_t)ADC_DelSig_1_CountsTo_mVolts(ADC_DelSig_1_Read16());
        
       
        
        // shutdown flags, current
        uint8_t shutdown_flags = 0;
        uint8_t current_upper = 0;
        uint8_t current_lower = 0;
        
        if (IMD_Fault_Read()) { shutdown_flags |= (1 << 5); }
        else { shutdown_flags &= (0b011111); }
        
        if (BMS_Fault_Read()) { shutdown_flags |= (1 << 4); }
        else { shutdown_flags &= (0b101111); }
        
        if (SD_FINAL_Read()) { shutdown_flags |= (1 << 3); }
        else { shutdown_flags &= (0b110111); }
        
        
        /* For debug purposes
        if (AIR_POS_Read()) { shutdown_flags |= (1 << 2); }
        else { shutdown_flags &= (0b111011); }
        
        if (AIR_NEG_Read()) { shutdown_flags |= (1 << 1); }
        else { shutdown_flags &= (0b111101); }
        
        if (Precharge_Read()) { shutdown_flags |= (1 << 0); }
        else { shutdown_flags &= (0b111110); }
        */
        
        // send data via PCAN to BMS main
        // note: uses 2's complement
        current_upper = current >> 8; // upper bits
        current_lower = current & 0xFF; // lower bits
        can_send_PEI(current_upper, current_lower, shutdown_flags);
        
        
        //Interlock state machine
        if (state == 0) {
            clear_interlock(); // clears interlock, send a message to open AIRs          
            if((get_HV_Requested() > 0) && (get_ESTOP_Check() == 0)) {
                state = 1;
            }
        }
        
        
        else if (state == 1) {
            
            
            set_interlock(); //sets interlock, sends a message to close AIRs
            uint8 throttle_high = get_THROTTLE_HIGH();
            uint8 throttle_low = get_THROTTLE_LOW();
            
            if(((throttle_high * 255 + throttle_low) < 0) || ((throttle_high * 255 + throttle_low) > 32767)){
                can_send_throttle(0);
            }
            else {
    			can_send_throttle(throttle_high * 255 + throttle_low);
    			//the throttle signal is in bounds and is between 0 and 32767
	  	    }
            
            if(get_HV_Requested() == 0) {
                state = 0;
            }
            
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
        else if(state == 2) {

		    clear_interlock(); // clears interlock, send a message to open AIRs
		    // set EM Brake = 0
		
	    }
        else if (state == 3) {
            
            if (get_ESTOP_Check() == 1) {
                state = 0;
                can_send_ESTOP(0);
            }
        }
        
        can_send_state(state);    
        
        CyDelay(1000);
    }
}
/* [] END OF FILE */
