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
extern uint8_t hv_requested;
extern uint8_t vcu_state;
extern uint8_t vcu_attached;

//charger variables
extern uint8_t charger_attached;
extern uint8_t charger_status;

//loop counters
extern uint16_t loops_since_vcu_message;
extern uint16_t loops_since_bms_message;
extern uint16_t loops_since_mc_message;
extern uint16_t loops_since_charger_message;

extern uint8_t enable_commands;

uint8_t inverter_enable() {
    LCD_Position(1, 0);
    LCD_PrintInt8(enable_commands);
    
    return (enable_commands & 0x01) == 0x01;
}

uint8_t hv_request(){
    if(vcu_attached) return hv_requested;     
    else if(charger_attached) return GPIO1_ESD_Read();
    
    return 0;
} 

uint8_t hv_allowed(){
    
    //if(pei_status & SHUTDOWN) return 0;  //shutdown circuit open
    if(pei_status & BMS_TIMEOUT) return 0;
    if(pei_status & VCU_CHARGER_TIMEOUT) return 0;
    
    if(vcu_attached){
        if(pei_status & MC_FAULT) return 0;   //mc faults
        if(pei_status & MC_DISCHARGING) return 0;  //mc is trying to discharge
        //if(pei_status & MC_TIMEOUT) return 0;
        
        return 1;
        
    } else if(charger_attached){
        if(pei_status & CHARGER_FAULT) return 0;

        return 1;
    } 
    
    return 0;
}

uint8_t precharge_ready(){
    if(mc_vsm_state == PRECHARGE_INIT || mc_vsm_state == PRECHARGE_ACTIVE) return 1;
    
    return 0;                
}

uint8_t precharge_complete(){    
    uint16_t threshold = (uint16_t)(((float)bms_voltage)*0.95);
    return (mc_voltage > threshold);
}


void update_status(){
    pei_status = NORMAL;  //reset
      
    if(vcu_attached && (loops_since_vcu_message > CAN_TIMEOUT_LOOP_COUNT)) 
        add_status(VCU_CHARGER_TIMEOUT);
            
    if(charger_attached && (loops_since_charger_message > CAN_TIMEOUT_LOOP_COUNT))
        add_status(VCU_CHARGER_TIMEOUT);
    
    if(loops_since_mc_message > CAN_TIMEOUT_LOOP_COUNT) add_status(MC_TIMEOUT);
    if(mc_post_faults != 0 || mc_run_faults != 0) add_status(MC_FAULT);
    if(mc_discharge_state == DISCHARGE_ACTIVE) add_status(MC_DISCHARGING);
    if(loops_since_bms_message > CAN_TIMEOUT_LOOP_COUNT) add_status(BMS_TIMEOUT);
    if(SD_FINAL_Read() == 0) add_status(SHUTDOWN);     //shutdown circuit open
    if((charger_status & 0b1011) != 0) add_status(CHARGER_FAULT); //check charger fault bits
    
}

void add_status(uint8_t status){
    pei_status |= status;
}

/* [] END OF FILE */
