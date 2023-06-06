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

#include "LCD.h"
#include "stdio.h"

#define NO_ERROR 0x0000
#define CHARGEMODE 0x0001
#define PACK_TEMP_OVER 0x0002
#define FUSE_BLOWN 0x0004
#define PACK_TEMP_UNDER 0x0008
#define LOW_SOC   0x0010
#define CRITICAL_SOC   0x0020
#define IMBALANCE   0x0040
#define COM_FAILURE   0x0080
#define NEG_CONT_CLOSED   0x0100
#define POS_CONT_CLOSED   0x0200 
#define ISO_FAULT   0x0400
#define SPI_FAULT   0x0400
#define CELL_VOLT_OVER   0x0800
#define CELL_VOLT_UNDER   0x1000
#define CHARGE_HAULT   0x2000
#define FULL   0x4000
#define PRECHARGE_CLOSED   0x8000

void update_display();

/* [] END OF FILE */
