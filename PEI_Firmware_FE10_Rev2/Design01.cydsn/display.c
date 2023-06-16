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
#include "display.h"
#include "fsm.h"

extern uint8_t bms_soc;
extern uint8_t bms_temp;
extern uint16_t bms_status;
extern uint16_t bms_voltage;
extern int16_t current;
extern uint8_t pei_status;
extern uint8_t pei_state;

void update_display(){
    LCD_Position(0,0);
    
    if(bms_status & (PACK_TEMP_OVER | PACK_TEMP_UNDER)){
        LCD_PrintString("BMS TEMP     ");
    }else if(bms_status & SPI_FAULT){
        LCD_PrintString("SPI FAULT    ");
    }else if(bms_status & CELL_VOLT_OVER){
        LCD_PrintString("OVERVOLT     ");
    }else if(bms_status & CELL_VOLT_UNDER){
        LCD_PrintString("UNDERVOLT    ");
    }else if(bms_status & IMBALANCE){
        LCD_PrintString("IMBALANCE    ");
    }else if(bms_status & LOW_SOC){
        LCD_PrintString("LOW SOC      ");
    }else if(pei_status & BMS_TIMEOUT){
        LCD_PrintString("BMS TIMEOUT  ");
    }else if(pei_status & MC_FAULT){
        LCD_PrintString("MC FAULT     ");
    }else if(pei_status & MC_TIMEOUT){
        LCD_PrintString("MC TIMEOUT   ");
    }else if(pei_status & VCU_CHARGER_TIMEOUT){
        LCD_PrintString("VCU TIMEOUT  ");
    }else if(pei_status & CHARGER_FAULT){
        LCD_PrintString("CHARGER FAULT");
    }else if(pei_status & MC_DISCHARGING){
        LCD_PrintString("MC DISCHARGE ");
    }else if(pei_status & SHUTDOWN){
        LCD_PrintString("SHUTDOWN OPEN");
    }else if(bms_status & CHARGEMODE){
        LCD_PrintString("CHARGE MODE  ");
    }else if(pei_state == PEI_LV){
        LCD_PrintString("LV           ");
    }else if(pei_state == PEI_PRECHARGE){
        LCD_PrintString("PRECHARGE    ");
    }else if(pei_state == PEI_HV){
        LCD_PrintString("HV           ");
    }else{
        LCD_PrintString("YO WTF?      ");
    }
    
    
    char str[8];
    
    LCD_Position(1, 0);
    sprintf(str, "%u%% ", bms_soc);
    LCD_PrintString(str);
    
    LCD_Position(1, 5);
    sprintf(str, "%uC ", bms_temp);
    LCD_PrintString(str);
    
    LCD_Position(1, 10);
    sprintf(str, "%dA  ", current/10);
    LCD_PrintString(str);
}

/* [] END OF FILE */
