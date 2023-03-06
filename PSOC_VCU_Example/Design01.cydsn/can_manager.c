/* ========================================
 * Can API for FRUCD
 * Schuyler Alschuler 2016 - 2017
 * ========================================
*/

/*******************************************
 * Used to interface dashboard with CAN bus
 * some functinality can be found in CAN_TX_RX_func.c
 * which is a generated source file
 * see the can component of the top design for specific mailboxes
 ******************************************/

#include "can_manager.h"
#include "CAN.h"
#include "Precharge.h"

extern volatile vcu_state state;

volatile uint8_t THROTTLE_HIGH = 0;
volatile uint8_t THROTTLE_LOW = 0;

volatile uint8_t ESTOP_MC = 0;
//VCU Data
volatile uint8_t HV_REQUEST_TR = 0;
volatile uint8_t VEHICLE_STATE = 0;

//MC_DEBG
volatile uint8_t THROTTLE = 0;
volatile uint8_t SET_INTERLOCK = 0;
volatile uint8_t STATE = 0;
volatile uint8_t HV_REQUEST_MC = 0;

//Return the hv_requested state from the VCU.
uint8_t get_HV_Requested()
{
    return HV_REQUEST_TR;   
}

//Returs the vehicle state from torque request CAN (different from state interlock machine)
uint8_t get_VEHICLE_STATE()
{
    return VEHICLE_STATE;   
}

//returns THROTTLE_HIGH
uint8_t get_THROTTLE_HIGH()
{
    return THROTTLE_HIGH;
}
//returns THROTTLE_LOW
uint8_t get_THROTTLE_LOW()
{
    return THROTTLE_LOW;
}
//returns THROTTLE
uint8_t get_THROTTLE()
{
    return THROTTLE;
}
//returns state
uint8_t get_STATE()
{
    return STATE;
}
// called from CAN_TX_RX_func.c in the generic RX func
// tldr: part of an interrupt service routine
void can_receive(uint8_t *msg, int ID)
{
    uint8 InterruptState = CyEnterCriticalSection();
    
    switch (ID) 
    {
        case TORQUE_REQUEST_COMMAND:
            HV_REQUEST_TR = msg[CAN_DATA_BYTE_1];
            VEHICLE_STATE = msg[CAN_DATA_BYTE_5];
            break;
        case MC_DEBUG:
            THROTTLE = msg[CAN_DATA_BYTE_7];
            STATE = msg[CAN_DATA_BYTE_3];
            SET_INTERLOCK = msg[CAN_DATA_BYTE_1];
            HV_REQUEST_MC = msg[CAN_DATA_BYTE_2];
            break;
        case MC_ESTOP:
            ESTOP_MC = msg[CAN_DATA_BYTE_1];
            break;
        case BSPD_FLAGS:
            THROTTLE_HIGH = msg[CAN_DATA_BYTE_2];
            THROTTLE_LOW = msg[CAN_DATA_BYTE_3];
            break;
    }
    
    CyExitCriticalSection(InterruptState);
}

void can_test_send()
{
    //CAN_1_DATA_BYTES_MSG msg;
    CAN_TX_MSG HeartB;
    
    HeartB.id = 0x300;
    HeartB.rtr = 0;
    HeartB.ide = 0;
    HeartB.dlc = 1;
    
    HeartB.irq = 0;
    
    HeartB.msg->byte[0] = (uint8) 1;
    HeartB.msg->byte[1] = (uint8) 1;
    HeartB.msg->byte[2] = (uint8) 1;
    HeartB.msg->byte[3] = (uint8) 1;
    HeartB.msg->byte[4] = (uint8) 1;
    HeartB.msg->byte[5] = (uint8) 1;
    HeartB.msg->byte[6] = (uint8) 1;
    HeartB.msg->byte[7] = (uint8) 1;
    
    CAN_SendMsg(&HeartB);
}

void can_send(uint8_t data[8], uint32_t ID)
{
    uint8_t i;
	CAN_TX_MSG message;
	CAN_DATA_BYTES_MSG payload;
	message.id = ID; 
	message.rtr = 0;
	message.ide = 0;
	message.dlc = 0x08;
	message.irq = 0;
	message.msg = &payload;
	for(i=0;i<8;i++)
		payload.byte[i] = data[i];
	CAN_SendMsg(&message); 
}

void can_send_cmd(
    uint8_t SetInterlock,
    uint16_t Throttle_High,
    uint16_t Throttle_Low,
    uint8_t E_Stop_Check
)
{
    //max and min voltage means the voltage of single cell
        
        uint8_t data[8];
        
        data[0] = SetInterlock;
        
        data[1] = Throttle_High;
        data[2] = Throttle_Low;
        
        data[3] = 0;
        data[4] = E_Stop_Check;
        
        data[5] = 0;
        data[6] = 0;
        data[7] = 0;

        can_send(data, 0x763);
        CyDelay(1); // Wtf is this shit?

} // can_send_cmd()

void can_send_state_and_throttle(uint8_t state, uint8_t throttle) {
    uint8_t data[8] = {0};
    data[2] = state;
    data[6] = throttle;
    can_send(data, MC_DEBUG_SEND);
}

void can_send_ESTOP(uint8_t estop) {
    uint8_t data[8] = {0};
    data[0] = estop;
    can_send(data, 0x363);
}

void set_interlock()
{
    AIR_NEG_Write(1);
    AIR_POS_Write(1);
    //can_send_interlock(1,1);
}    

void clear_interlock()
{
    AIR_NEG_Write(0);
    AIR_POS_Write(0);
    //can_send_interlock(0,0);
}

//temporarily reporting AIR NEG/POS state on 3rd and 4th bytes of PCAN PEI message
/* Used for debug purposes
void can_send_interlock(uint8_t air_neg, uint8_t air_pos)
{
    uint8_t data[8] = {0};
    data[3] = air_neg;
    data[4] = air_pos;
    can_send(data, 0x383); 
}
*/

void can_send_PEI(uint8_t current_upper, uint8_t current_lower, uint8_t shutdown_flags)
{
    uint8_t data[8] = {0};

    data[0] = current_upper;
    data[1] = current_lower;
    data[2] = shutdown_flags;
    can_send(data, 0x383); 
}
