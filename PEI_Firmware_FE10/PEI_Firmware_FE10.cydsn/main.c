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

#include "main.h"

//TODO: The state starts at 0
volatile PEI_STATE_t pei_state = PEI_LV;
volatile uint8_t e_stop;

//pei parameters
int16_t current;
uint8_t relay_flags = 0;
uint16_t loop_counter = 0;

//vcu parameters
VCU_STATE vcu_state = LV;
uint8_t hv_requested = 0;
uint8_t vcu_attached = 0;

//bms parameters 
uint16_t bms_status = 0;
uint16_t bms_voltage = 0;
uint8_t bms_soc = 0;
uint8_t bms_temp = 0;

//mc parameters
int16_t mc_voltage = 0;
MC_VSM_STATE mc_vsm_state = VSM_START;
MC_DISCHARGE_STATE mc_discharge_state = DISCHARGE_DISABLED;
uint16_t mc_post_faults = 0;
uint16_t mc_run_faults = 0;

//charger parameters
uint8_t charger_attached = 0;
uint8_t charger_status = 0;


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
        // shutdown flags, current
        uint8_t shutdown_flags = 0;
        int16_t current = get_current();
        
        shutdown_flags = relay_flags & 0x07;
        if (IMD_Fault_Read()) shutdown_flags |= (1 << 5);       
        if (BMS_Fault_Read()) shutdown_flags |= (1 << 4);  
        if (SD_FINAL_Read()) shutdown_flags |= (1 << 3);
        
        
        //Interlock state machine
        if(hv_allowed() == 0){
            pei_state = PEI_FAULT;
        }
          
        switch(pei_state){
            case PEI_LV:
                clear_interlock(); // clears interlock, send a message to open AIRs   
                
                if(precharge_ready()) {
                    if(vcu_attached) pei_state = PEI_PRECHARGE;
                    else if(charger_attached) pei_state = PEI_HV;   //charger doesn't need precharge
                }
                break;
            
            case PEI_PRECHARGE:           
                start_precharge();
                
                //Todo: Capacitor (gotten value) >= 95% pack voltage (threshold that we measure in testing)
                //This if statement is incorrect
                if (precharge_complete()){
                    pei_state = PEI_HV;
                }

                if(hv_request() == 0) {
                   pei_state = PEI_LV;
                }
                
                break;
                
             case PEI_HV:
                finish_precharge();
                
                if(hv_requested == 0) {
                   pei_state = PEI_LV;
                }
                
                break;
                
            default:
                clear_interlock();
                pei_state = PEI_FAULT;
                
                if (hv_request() == 0 && hv_allowed()) {
                    pei_state = PEI_LV;
                } 
        }

        can_send_PEI(current, shutdown_flags);
        check_vcu_charger();
        update_display();
        loop_counter++;
        
        CyDelay(1000);
    }
}

uint8_t hv_request(){
    if(vcu_attached) return hv_requested;     
    else if(charger_attached) return GPIO1_ESD_Read();
    
    return 0;
} 

uint8_t hv_allowed(){
    if(SD_FINAL_Read() == 0) return 0;  //shutdown circuit open
    
    if(vcu_attached){
        if(mc_post_faults != 0) return 0;   //mc faults
        if(mc_run_faults != 0) return 0;
        if(mc_discharge_state == DISCHARGE_ACTIVE) return 0;  //mc is trying to discharge
        
        return 1;
        
    } else if(charger_attached){
        if((charger_status & 0b1011) != 0) return 0; //check charger fault bits

        return 1;
    } 
    
    return 0;
}

uint8_t precharge_ready(){
    if(hv_allowed() == 0) return 0;
    if(hv_request() == 0) return 0;
    
    if(vcu_attached){
        if(mc_vsm_state != PRECHARGE_INIT && mc_vsm_state != PRECHARGE_ACTIVE) return 0;
    }
    
    return 1;                
}

uint8_t precharge_complete(){    
    uint16_t threshold = (uint16_t)(((float)bms_voltage)*0.95);
    return (mc_voltage > threshold);
}

int16_t get_current(){
    double current_raw_mv = (double)ADC_DelSig_1_CountsTo_mVolts(ADC_DelSig_1_Read32());
    int16_t current = (int16_t)(((current_raw_mv*5.0/3.3) - 2500)/6.667)*10;
    return current;
}
/* [] END OF FILE */
