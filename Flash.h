typedef struct
{
    uint8_t port;            // Port connection
    uint8_t type_sensor;     // Type of sensor
    uint8_t status;          // Status (saved or not)
    uint8_t struct_count;    // Number of structs created
} flashin;

#define MAX_STRUCT_COUNT 4
#define EEPROM_SIZE   128   // Adjust to your memory size
#define EEPROM_START  0x4000

flashin flash_w[MAX_STRUCT_COUNT];  // Array for storing structs to write to Flash
flashin flash_r[MAX_STRUCT_COUNT];  // Array for storing structs read from Flash
uint8_t current_count = 0;          // Current number of structs in the array
uint16_t flash_address = 0x4000;    // Starting address of Flash

void Delay(int t);
//void Flash_Write_Struct_Array(uint16_t startAddress, flashin *dataArray, uint8_t arraySize);
void Flash_Write_Struct_Array(uint16_t start_address, flashin *dataArray);
void Add_New_Struct(port_e port, type_Sensor_e sensor, flashin *dataArray, uint8_t *currentCount);
void Flash_Read_Struct_Array(uint16_t startAddress, flashin *dataArray, uint8_t arraySize);
void Flash_Add_And_Write(uint16_t *start_address, port_e port, type_Sensor_e sensor, flashin *dataArray, uint8_t *current_count);
void Flash_Erase(uint16_t start_address, uint16_t length);
void Run(void);

#include <Flash.c>