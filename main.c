#include <main.h>

void assert_failed(uint8_t *file, uint32_t line) {}

int main(void){
  Flash_Erase(EEPROM_START, EEPROM_SIZE);
  //Run();
  while(1){
    
  }
}