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

extern uint8_t bms_soc;
extern uint8_t bms_temp;
extern uint16_t bms_status;
extern uint16_t bms_voltage;
extern uint16_t current;

void update_display(){
    LCD_Position(0,0);
    
    if(bms_status & (PACK_TEMP_OVER | PACK_TEMP_UNDER)){
        LCD_PrintString("BMS TEMP");
    }else if(bms_status & SPI_FAULT){
        LCD_PrintString("SPI FAULT");
    }else if(bms_status & CELL_VOLT_OVER){
        LCD_PrintString("OVERVOLT");
    }else if(bms_status & CELL_VOLT_UNDER){
        LCD_PrintString("UNDERVOLT");
    }else if(bms_status & IMBALANCE){
        LCD_PrintString("IMBALANCE");
    }else if(bms_status & LOW_SOC){
        LCD_PrintString("LOW SOC");
    }else if(bms_status & CHARGEMODE){
        LCD_PrintString("CHARGE MODE");
    }else{
        LCD_PrintString("NORMAL");
    }
    
    LCD_Position(1, 0);
    char str[8];
    sprintf(str, "%u%%", bms_soc);
    LCD_PrintString(str);
    
    LCD_Position(1, 5);
    sprintf(str, "%uC", bms_temp);
    LCD_PrintString(str);
    
    LCD_Position(1, 10);
    sprintf(str, "%uA", current);
    LCD_PrintString(str);
}

/* [] END OF FILE */
