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
#include "display.h"

//TODO: The state starts at 0
volatile uint32_t pei_state = 1;
volatile uint8_t e_stop;

#define max_Voltage 4976 //Change this later

uint16_t current;
uint16_t bms_status = 0;
uint16_t bms_voltage = 0;
uint8_t bms_soc = 0;
uint8_t bms_temp = 0;
uint8_t hv_requested = 0;
uint16_t mc_voltage;
uint8_t vcu_state;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    //Initialize and start CAN
    CAN_GlobalIntEnable();
    CAN_Init();
    CAN_Start();
    ADC_DelSig_1_Start();
    LCD_Start();
    
    for(;;)
    {   
        
        //We need read the e_stop status in from the Shutdown_IN pin.
        //If e_stop is hit, should be equal to 0.
        e_stop = SD_FINAL_Read();
        current = (uint16_t) ADC_DelSig_1_CountsTo_mVolts(ADC_DelSig_1_Read32());

        
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
        if (pei_state == 0) {
            clear_interlock(); // clears interlock, send a message to open AIRs          
            if((hv_requested == 1) && (e_stop != 0)) {
                pei_state = 1;
            }
        }
        else if (pei_state == 1) {
            //Todo: Capacitor (gotten value) >= 95% pack voltage (threshold that we measure in testing)
            //This if statement is incorrect
            if (mc_voltage > max_Voltage) {
                open_precharge();
            }
            else {
                close_precharge();
            }
            
            if(0){//get_RUN_FAULT_SUM() >0) {
                pei_state = 3;
            }    
            
            if(hv_requested == 0) {
               pei_state = 0;
            }
            
            else if (e_stop == 0) {
                pei_state = 3;   
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
        else if (pei_state == 3) {
            clear_interlock();
            if (hv_requested == 0) {
                pei_state = 0;
            }
        }
        
        

        update_display();
        CyDelay(1000);
    }
}
/* [] END OF FILE */
