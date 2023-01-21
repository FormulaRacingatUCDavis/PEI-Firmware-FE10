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
extern volatile uint32_t pedalOK;
extern volatile uint8_t PACK_TEMP;
extern volatile uint8_t BSPD_CATCH;
extern volatile uint16_t CURRENT;
//extern volatile int ERROR_NODE;
//extern volatile int ERROR_IDX;
extern volatile uint8_t soc;
extern volatile uint32_t voltage;
//extern volatile BMS_STATUS bms_status;
extern volatile uint8_t shutdown_flags;


volatile uint8_t CAPACITOR_VOLT = 0;
volatile uint8_t ACK_RX = 0;
volatile uint8_t ERROR_TOLERANCE = 0;
volatile uint8_t ABS_MOTOR_RPM = 0;
volatile uint8_t THROTTLE_HIGH = 0;
volatile uint8_t THROTTLE_LOW = 0;
volatile uint8_t THROTTLE = 0;

volatile uint8_t ESTOP;
//VCU Data
volatile uint8_t HV_REQUEST = 0;
volatile uint8_t E_STOP_CHECK = 0;


//Interlock States
volatile uint8_t SET_INTERLOCK = 0;

uint8 current_bytes[4] = {0};

// returns voltage of capacitor from motor controller
uint8_t getCapacitorVoltage()
{
    return CAPACITOR_VOLT;
}

// returns 1 always... not sure whats up in the motor controller
uint8_t getAckRx()
{
    return ACK_RX;
}

// true if break depressed more than 10%
// this value typically used for drive request
uint8_t getErrorTolerance()
{
    return ERROR_TOLERANCE;
}

// from motor controller
// look this one up in 1239E manual, im not super sure
uint8_t getABSMotorRPM()
{
    return ABS_MOTOR_RPM;
}

//Return the ESTOP state from the VCU.
uint8_t get_ESTOP_Check()
{
    return E_STOP_CHECK;  
}

//Return the hv_requested state from the VCU.
uint8_t get_HV_Requested()
{
    return HV_REQUEST;   
}

// returns setInterlock
uint8_t get_Set_Interlock()
{
    return SET_INTERLOCK;
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
// called from CAN_TX_RX_func.c in the generic RX func
// tldr: part of an interrupt service routine
void can_receive(uint8_t *msg, int ID)
{
    uint8 InterruptState = CyEnterCriticalSection();
    
    switch (ID) 
    {
        case TORQUE_REQUEST_COMMAND:
            HV_REQUEST = msg[CAN_DATA_BYTE_1];
            E_STOP_CHECK = msg[CAN_DATA_BYTE_4];
            break;
        case MC_PDO_SEND:
            CAPACITOR_VOLT = msg[CAN_DATA_BYTE_1];
            ABS_MOTOR_RPM = msg[CAN_DATA_BYTE_3];
            break;
        case MC_PDO_ACK:
            ACK_RX = msg[CAN_DATA_BYTE_1];
            break;
        case BMS_VOLTAGES:
            voltage = msg[CAN_DATA_BYTE_5] << 24;
            voltage |= msg[CAN_DATA_BYTE_6] << 16;
            voltage |= msg[CAN_DATA_BYTE_7] << 8;
            voltage |= msg[CAN_DATA_BYTE_8];
            break;
        case BMS_STATUS_MSG:
            soc = msg[CAN_DATA_BYTE_2];
            //bms_status = msg[CAN_DATA_BYTE_3] << 8;    // bms error flags
            //bms_status |= msg[CAN_DATA_BYTE_4];        // bms error flags
            break;
        case BMS_TEMPERATURES:
            PACK_TEMP = msg[CAN_DATA_BYTE_8];
            break;
        case PEI_CURRENT:
            CURRENT = msg[CAN_DATA_BYTE_1] << 8;
            CURRENT |= msg[CAN_DATA_BYTE_2];
            shutdown_flags = msg[CAN_DATA_BYTE_3];
            break;
        case MC_DEBUG:
            SET_INTERLOCK = msg[CAN_DATA_BYTE_1];
            THROTTLE = msg[CAN_DATA_BYTE_7];
            break;
        case 0x366:
            ESTOP = msg[CAN_DATA_BYTE_1];
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

void can_send_switches(
    uint8_t sw_status)
{
        //CAN_TX_DATA_BYTE1(CAN_TX_MAILBOX_DRIVER_SWITCHES) = sw_status; 
        //CAN_SendMsgDRIVER_SWITCHES(); 
    
        /*
        uint8_t data[8];
        
        data[0] = sw_status;
        data[1] = 0;
        
        data[2] = 0;
        data[3] = 0;
        
        data[4] = 0;
        data[5] = 0;
        data[6] = 0;
        data[7] = 0;

        can_send(data, DRIVER_SWITCHES);
*/
        
} // can_send_status()

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

        can_send(data, 0x766);
        CyDelay(1); // Wtf is this shit?

} // can_send_cmd()
void can_send_state(uint8_t state) {
    uint8_t data[8] = {0};
    data[2] = state;
    
    can_send(data, 0x466);
}
void can_send_throttle(uint8_t throttle) {
    uint8_t data[8] = {0};
    data[6] = throttle;
    can_send(data, 0x466);
}
void can_send_ESTOP(uint8_t estop) {
    uint8_t data[8] = {0};
    data[0] = estop;
    can_send(data, 0x366);
}
//temporarily reporting AIR NEG/POS state on 3rd and 4th bytes of PCAN PEI message
void can_send_interlock(uint8_t air_neg, uint8_t air_pos)
{
    uint8_t data[8] = {0};
    data[3] = air_neg;
    data[4] = air_pos;
    
    can_send(data, 0x387); 
}