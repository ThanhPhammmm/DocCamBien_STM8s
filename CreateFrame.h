/*Ban tin chung*/
typedef struct
{
    uint16_t StartFrame;
    uint16_t TypeMessage;
    uint16_t Length; // tính t? Length + Data
    uint8_t  Data[10];
    uint16_t CheckFrame;
} frame_Message_t;
// Gia tri enum
typedef enum
{
    TYPE_MESSAGE_SET_PORT             = 0x0001,
    TYPE_MESSAGE_CONFIRM_PORT         = 0x0002,
    TYPE_MESSAGE_ASK_DATA             = 0x0003,
    TYPE_MESSAGE_RESPOND_DATA         = 0x0004, 
} type_Message_e;
typedef enum
{
	PORT_A = 0x01,
	PORT_B = 0x02,		
} port_e;
typedef enum
{
    SENSOR_LUX      = 0x01,
    SENSOR_RTC      = 0x02,
    SENSOR_NTC      = 0x03,
    SENSOR_RES      = 0x04,
} type_Sensor_e;
#define START_BYTE                   0XAA55 /*Ban tin start */
#define LENGTH_DEFAULT               4      /* StartByte + TypeMsg*/
#define LENGTH_MESSAGE_SET_PORT      5      /* Length_data + Port + Checksum*/
#define LENGTH_MESSAGE_CONFIRM       6      /* Length_data + Port + TypeSensor + Checksum*/
#define LENGTH_MESSAGE_ASK_DATA      6      /* Length_data + Port + TypeSensor + Checksum*/
#define LENGTH_MESSAGE_RESPOND_LUX   10     /* Length_data + Port + TypeSensor + 4 byte Data + Checksum*/
#define LENGTH_MESSAGE_RESPOND_RTC   13     /* Length_data + Port + TypeSensor + 7 byte Data + Checksum*/
#define LENGTH_MESSAGE_RESPOND_NTC   10     /* Length_data + Port + TypeSensor + 4 byte Data + Checksum*/
#define LENGTH_MESSAGE_RESPOND_RES   8      /* Length_data + Port + TypeSensor + 2 byte Data + Checksum*/


uint16_t Check_Sum(uint8_t *buf, uint8_t len);
uint16_t Message_Frame_Create_Set_Port( port_e datain_port, uint8_t *data_out);
uint8_t Message_Frame_Create_Confirm_Port(uint8_t datain_port, uint8_t datain_sensor, uint8_t* dataout);
uint8_t Message_Frame_Create_Ask_Data_Sensor(port_e datain_port, type_Sensor_e datain_sensor, uint8_t* dataout);
uint16_t Message_Frame_Response_LUX(port_e datain_port, type_Sensor_e datain_sensor, float datain_value, uint8_t* dataout);
uint16_t Message_Frame_Response_RES(port_e datain_port, type_Sensor_e datain_sensor, uint16_t datain_value, uint8_t* dataout);

#include <CreateFrame.c>