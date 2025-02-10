void Delay(int t){
    int i, j;
    for (i = 0; i < t; i++) {
        for (j = 0; j < 400; j++) {}  // Simple delay loop
    }
}
void Flash_Erase(uint16_t start_address, uint16_t length){
    // Unlock EEPROM (Data Memory)
    FLASH->DUKR = 0xAE;  // Key 1
    FLASH->DUKR = 0x56;  // Key 2

    // Wait until EEPROM is unlocked
    while ((FLASH->IAPSR & FLASH_IAPSR_DUL) == 0);

    // Erase EEPROM (write 0x00 or 0xFF depending on your needs)
    for (uint16_t i = 0; i < length; i++) {
        *(uint8_t *)(start_address + i) = 0x00;  // Erasing by writing 0x00
        
        // Wait for completion
        while ((FLASH->IAPSR & FLASH_IAPSR_EOP) == 0);
    }

    // Lock EEPROM again (disable writing)
    FLASH->IAPSR &= ~FLASH_IAPSR_DUL;
}
void Flash_Write_Struct_Array(uint16_t start_address, flashin *dataArray){
    //size_t dataSize = sizeof(flashin) * arraySize;

    // Unlock DATA area
    FLASH->DUKR = 0xAE;  // Key 1
    FLASH->DUKR = 0x56;  // Key 2

    // Wait until the Flash is unlocked
    while ((FLASH->IAPSR & FLASH_IAPSR_DUL) == 0);

    // _write each byte of the struct array to Flash
    for (size_t i = 0; i < 4; i++) {
        //*(uint8_t*)(start_address+i) = ((uint8_t*)dataArray + dataSize)[i];
        *(uint8_t*)(start_address + i) = ((uint8_t*)dataArray)[i];  // ? Correct memory access
        //start_address ;

        // Wait until the write operation is finished
        while ((FLASH->IAPSR & FLASH_IAPSR_EOP) == 0);
    }

    // Lock DATA area again
    FLASH->IAPSR &= ~FLASH_IAPSR_DUL;
   // flash_w[arraySize-1].next_address = start_address+1; 
}
void Flash_Read_Struct_Array(uint16_t start_address, flashin *dataArray, uint8_t arraySize){
  size_t dataSize = sizeof(flashin) * arraySize;
  
  for(size_t i = 0;i < dataSize;i++){
    ((uint8_t*)dataArray)[i] = *(uint8_t*)(start_address + i);
  }
}
void Add_New_Struct(port_e port, type_Sensor_e sensor, flashin *dataArray, uint8_t *current_count){
  if (*current_count < MAX_STRUCT_COUNT) {
    // Assign values to the new struct
    dataArray[*current_count].port = port;
    dataArray[*current_count].type_sensor = sensor;
    dataArray[*current_count].status = 1;   // Status: 1 (Saved)
    dataArray[*current_count].struct_count = *current_count + 1; // Increment struct count
  }
}
void Flash_Add_And_Write(uint16_t *start_address, port_e port, type_Sensor_e sensor, flashin *dataArray, uint8_t *current_count) {
    // Add the new struct to the array
    Add_New_Struct(port, sensor, dataArray, current_count);
    
    // Write the updated array to Flash memory
    Flash_Write_Struct_Array(*start_address, &dataArray[*current_count]);  
    
    // Update the address for the next write operation
    //*start_address += sizeof(flashin) * (*current_count);
    //flash_address += sizeof(flashin);
    flash_address += 4;  // ? Move by 4 bytes only
    (*current_count)++;  // Increase the current struct count
}
void Run(void){
    UART_Configuration(9600);  // Initialize UART with baud rate of 9600

    // Initialize GPIOB PIN_5 for controlling an LED
    GPIO_DeInit(GPIOB);
    GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);
    GPIO_WriteHigh(GPIOB, GPIO_PIN_5);  // Turn off LED initially
    
    // Load the current count from the first struct in Flash
    current_count = flash_w[0].struct_count;

    // Example of writing structs to Flash
    Flash_Add_And_Write(&flash_address, PORT_A, SENSOR_LUX, flash_w, &current_count);
    Flash_Add_And_Write(&flash_address, PORT_B, SENSOR_NTC, flash_w, &current_count);
  
    // Read the array of structs from Flash memory
    Flash_Read_Struct_Array(0x4000, flash_r, MAX_STRUCT_COUNT);
    
    // Check if the read data matches a specific condition
    for (uint8_t i = 0; i < MAX_STRUCT_COUNT; i++){
        if (flash_r[i].port == PORT_B &&
            flash_r[i].type_sensor == SENSOR_NTC &&
            flash_r[i].status == 1) {
            // If the data matches, turn on the LED
            GPIO_WriteLow(GPIOB, GPIO_PIN_5);
        }
    }
    // Infinite loop for checking and sending UART data
    while (1){
        UART1_SendData8(flash_r[2].port);  // Send port information via UART
        Delay(2000);  // Simple delay between sends
    }
}