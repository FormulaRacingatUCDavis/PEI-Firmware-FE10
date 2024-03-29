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

#include "fsm.h"

extern uint8_t pei_status;

//BMS Varialbes
extern uint8_t bms_temp;
extern uint16_t bms_status;
extern uint8_t bms_soc;
extern uint16_t bms_voltage;

//MC varialbes
extern int16_t mc_voltage;
extern uint8_t mc_vsm_state;
extern uint8_t mc_discharge_state;
extern uint16_t mc_post_faults;
extern uint16_t mc_run_faults;

//VCU variables
extern uint8_t vcu_state;
extern uint8_t vcu_attached;
extern uint8_t enable_commands;
extern uint8_t hv_requested;

//charger variables
extern uint8_t charger_attached;
extern uint8_t charger_status;

//loop counters
extern uint16_t loops_since_vcu_message;
extern uint16_t loops_since_bms_message;
extern uint16_t loops_since_mc_message;
extern uint16_t loops_since_charger_message;

uint8_t hv_lockout = 1; 

uint8_t hv_request(){
    if(vcu_attached) return hv_requested;   
    else if(charger_attached) return !(pei_status & SHUTDOWN);
        
    return 0;
} 

uint8_t hv_allowed(){
    
    if(hv_lockout){
        if(!hv_request()) hv_lockout = 0;  //make sure we cannot go directly to HV
        return 0; 
    }
    
    if(pei_status & SHUTDOWN) return 0;  //shutdown circuit open
    if(pei_status & BMS_TIMEOUT) return 0;
    if(pei_status & VCU_CHARGER_TIMEOUT) return 0;
    
    if(vcu_attached){
        if(pei_status & MC_FAULT) return 0;   //mc faults
        if(pei_status & MC_DISCHARGING) return 0;  //mc is trying to discharge
        if(pei_status & MC_TIMEOUT) return 0;
        
        return 1;
        
    } else if(charger_attached){
        if(pei_status & CHARGER_FAULT) return 0;

        return 1;
    } 
    
    return 0;
}

uint8_t precharge_ready(){
    if(mc_vsm_state == PRECHARGE_INIT || 
       mc_vsm_state == PRECHARGE_ACTIVE ||
       mc_vsm_state == VSM_WAIT) return 1;
    
    return 0;                
}

uint8_t precharge_complete(){    
    uint16_t threshold = (uint16_t)(((float)(bms_voltage/10))*PRECHARGE_RATIO);
    return (mc_voltage > threshold);
}


void update_status(){
    pei_status = NORMAL;  //reset
      
    if(vcu_attached){
        if (loops_since_vcu_message > CAN_TIMEOUT_LOOP_COUNT) add_status(VCU_CHARGER_TIMEOUT);
        if(loops_since_mc_message > CAN_TIMEOUT_LOOP_COUNT) add_status(MC_TIMEOUT);
        if(mc_post_faults != 0 || mc_run_faults != 0) add_status(MC_FAULT);
        if(mc_discharge_state == DISCHARGE_ACTIVE) add_status(MC_DISCHARGING);
    }
            
    if(charger_attached){
        if (loops_since_charger_message > CAN_TIMEOUT_LOOP_COUNT) add_status(VCU_CHARGER_TIMEOUT);
        if((charger_status & 0b10111) != 0) add_status(CHARGER_FAULT); //check charger fault bits
    }
    
    if(loops_since_bms_message > CAN_TIMEOUT_LOOP_COUNT) add_status(BMS_TIMEOUT);
    if(SD_FINAL_Read() == 0) add_status(SHUTDOWN);     //shutdown circuit open
 
}

void add_status(uint8_t status){
    pei_status |= status;
}

/* [] END OF FILE */
