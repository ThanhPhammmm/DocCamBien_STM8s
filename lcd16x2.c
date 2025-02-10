//D7D6D5D4BLERwRs
//xxxx10x1
//MSB -> LSB
void LCD_SendCommand(uint8_t cmd) {
    uint8_t highNibble, lowNibble;
    
    highNibble = (cmd & 0xF0);  // Get high nibble
    lowNibble = ((cmd << 4) & 0xF0);  // Get low nibble
    
    // Send high nibble
    I2c_write(0x27 << 1, highNibble | 0x0C);  // Set enable bit (E=1)
    I2c_write(0x27 << 1, highNibble | 0x08);         // Clear enable bit (E=0)
    
    // Send low nibble
    I2c_write(0x27 << 1, lowNibble | 0x0C);  // Set enable bit (E=1)
    I2c_write(0x27 << 1, lowNibble | 0x08);         // Clear enable bit (E=0)
}
void LCD_SendData(uint8_t data) {
    uint8_t highNibble, lowNibble;
    
    highNibble = (data & 0xF0);  // Get high nibble
    lowNibble = ((data << 4) & 0xF0);  // Get low nibble
    
    // Send high nibble
    I2c_write(0x27 << 1, highNibble | 0x0D);  // Set RS=1 (data mode), E=1
    I2c_write(0x27 << 1, highNibble | 0x09);  // Set RS=1, E=0
    
    // Send low nibble
    I2c_write(0x27 << 1, lowNibble | 0x0D);  // Set RS=1 (data mode), E=1
    I2c_write(0x27 << 1, lowNibble | 0x09);  // Set RS=1, E=0
}
void LCD_SendString(char* str){
  while(*str){
    LCD_SendData((uint8_t)*str);
    str++;
  }
}
void LCD_Init(void) {
    Delay_ms(50);  // Wait for LCD to power up
    
    // Initialize in 4-bit mode
    LCD_SendCommand(0x30);  // Function set: 8-bit mode (called three times)
    Delay_ms(5);
    LCD_SendCommand(0x30);  
    Delay_ms(10);
    LCD_SendCommand(0x30);
    
    // Switch to 4-bit mode
    LCD_SendCommand(0x20);  // Function set: 4-bit mode
    
    // Configure display (2-line, 5x8)
    LCD_SendCommand(0x28);
    Delay_ms(1);

    //Display on, Cursor on
    LCD_SendCommand(0x0E);
    Delay_ms(1);

    //Display off
//    LCD_SendCommand(0x08);
//    Delay_ms(1);
    
    //Display clear
    LCD_SendCommand(0x01);
    Delay_ms(2);
    
    //Entry mode set
    LCD_SendCommand(0x06);
}
void LCD_set_cursor(uint32_t row, uint32_t column){
  column -= 1;
  switch(row){
    case 1:
      column |= 0x80;
      LCD_SendCommand(column);
      break;
    case 2:
      column |= 0xC0;
      LCD_SendCommand(column);
      break;
    default:
        break;
  }
}
void LCD_Light_BackGround(uint8_t State){
  uint8_t highNibble;

  highNibble = (State & 0xF0);  // Get high nibble
//  lowNibble = ((State << 4) & 0xF0);  // Get low nibble
  if(State == 1){
    I2c_write(0x27 << 1, highNibble | 0x0C);  // E=1, Backlight=1
    I2c_write(0x27 << 1, highNibble | 0x08);  // E=0, Backlight=1
  }
  else{
    I2c_write(0x27 << 1, highNibble | 0x04);  // E=1, Backlight=1
    I2c_write(0x27 << 1, highNibble | 0x00);  // E=0, Backlight=1
}
}