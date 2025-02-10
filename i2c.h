void I2c_Init(void);
void I2c_generate_start();
void I2c_generate_stop();
void I2c_send_7bits_address(uint8_t address);
void I2c_send_data(uint8_t data);
uint32_t Get_flag_status_of_bus(void);
uint32_t Check_event_start();
uint32_t Check_event_send_7bits_address();
uint32_t Check_event_send_data();
void I2c_write(uint8_t address, uint8_t data);

#include <i2c.c>