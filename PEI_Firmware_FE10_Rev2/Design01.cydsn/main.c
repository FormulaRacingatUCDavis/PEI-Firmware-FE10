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

//pei parameters  
PEI_STATE_t pei_state = PEI_LV;
uint8_t pei_status = NORMAL;
int16_t current;
uint8_t relay_flags = 0;

//vcu parameters
VCU_STATE vcu_state = LV;
uint8_t enable_commands = 0;
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

//loop counters
uint16_t loop_counter = 0;
uint16_t loops_since_vcu_message = 0;
uint16_t loops_since_bms_message = 0;
uint16_t loops_since_mc_message = 0;
uint16_t loops_since_charger_message = 0;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    //Initialize and start CAN
    CAN_GlobalIntEnable();
    CAN_Init();
    CAN_Start();
    ADC_DelSig_1_Start();
    LCD_Start();
    
    uint8_t shutdown_flags = 0;
    uint8_t charge_start = 0;
    
    for(;;)
    {       
        for(uint8_t i = 0; i < CAN_MSG_INTERVAL; i++){
            // shutdown flags, current
            charge_start = 0;
            shutdown_flags = 0;
            
            shutdown_flags = relay_flags & 0x07;
            if (IMD_Fault_Read()) shutdown_flags |= (1 << 5);       
            if (BMS_Fault_Read()) shutdown_flags |= (1 << 4);  
            if (SD_FINAL_Read()) shutdown_flags |= (1 << 3);
            
            
            //Interlock state machine
            update_status();
            
            if(hv_allowed() == 0){
                pei_state = PEI_FAULT;
            }
              
            switch(pei_state){
                case PEI_LV:
                    clear_interlock(); // clears interlock, send a message to open AIRs   
                    
                    if(hv_request() && hv_allowed()) {
                        if(vcu_attached && precharge_ready()){
                            pei_state = PEI_PRECHARGE;
                        } else if(charger_attached){
                            pei_state = PEI_HV;   //charger doesn't need precharge
                        }
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
                    charge_start = 1;
                    
                    if(hv_request() == 0) {
                       pei_state = PEI_LV;
                    }
                    
                    break;
                    
                default:
                    clear_interlock();
                    pei_state = PEI_FAULT;
                    
                    if (hv_request() == 0 && hv_allowed()) {
                        pei_state = PEI_LV;
                    } 
            } //end switch
            
            CyDelay(1);
            
        } //end for loop
        
        
        check_can();
        current = get_current();
        update_display();
        
        //printState(pei_state);
        //printHV(inverter_enable());
        
        can_send_PEI(current, shutdown_flags);
        if(charger_attached) can_send_CHARGER(charge_start);
        
    }
}

/*
void printHV(bool request) {
    LCD_Position(1, 0);
    if (request) {
        LCD_PrintString("True");
    }
    else {
        LCD_PrintString("False");
    }
}

void printState(PEI_STATE_t state) {
    LCD_Position(0,0);
    
    switch(state) {
        case PEI_LV:
            LCD_PrintString("State 0");
            break;
        case PEI_PRECHARGE:
            LCD_PrintString("State 1");
            break;
        case PEI_HV:
            LCD_PrintString("State 3");
            break;
        case PEI_FAULT:
            LCD_PrintString("State 2");
            break;
        default:
            LCD_PrintString("Fault");
            break;
    }
}
*/

int16_t get_current(){
    double current_raw_mv = (double)ADC_DelSig_1_CountsTo_mVolts(ADC_DelSig_1_Read32());
    int16_t current = (int16_t)(((current_raw_mv*5.5/3.3) - 2500)/6.667)*10;
    return current;
}

/* [] END OF FILE */
