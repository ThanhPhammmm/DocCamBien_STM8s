void I2c_Init(void){
  I2C->FREQR = 16;
  
  I2C->CCRL = 0x80;
  I2C->CCRH &= ~(1 << 6);
  
  I2C->TRISER = 17;
  
  I2C->CR1 |= (1 << 0);
  
  I2C->CR2 |= (1 << 2);
  
  
  I2C->OARL |= (0x27 << 1);
  I2C->OARH &= ~(1 << 7);
  I2C->OARH |= (1 << 6);
  
  I2C->CR1 |= I2C_CR1_PE;
}
void I2c_generate_start(){
  I2C->CR2 |= (1 << 0);
}
void I2c_generate_stop(){
  I2C->CR2 |= (1 << 1);
}
void I2c_send_7bits_address(uint8_t address){
  I2C->DR = (uint8_t)address;
}
void I2c_send_data(uint8_t data){
  I2C->DR = data;
}
uint32_t Get_flag_status_of_bus(void){
  uint8_t tmp = (I2C->SR3 & (1 << 1));
  return tmp;
}
uint32_t Check_event_start(){
  uint8_t t1 = I2C->SR3 & (1 << 1);//busy
  uint8_t t2 = I2C->SR3 & (1 << 0);//msl
  uint8_t t3 = I2C->SR1 & (1 << 0);//sb
  return (t1 && t2 && t3);
}
uint32_t Check_event_send_7bits_address(){
  uint8_t t1 = I2C->SR3 & (1 << 1);//busy
  uint8_t t2 = I2C->SR3 & (1 << 0);//msl
//  uint8_t t3 = I2C->SR1 & (1 << 1);//adr
  uint8_t t4 = I2C->SR1 & (1 << 7);//txe
  uint8_t t5 = I2C->SR3 & (1 << 2);//tra
  return (t1 && t2  && t4 && t5);
}
uint32_t Check_event_send_data(){
  uint8_t t1 = I2C->SR3 & (1 << 2);//tra
  uint8_t t2 = I2C->SR3 & (1 << 1);//busy
  uint8_t t3 = I2C->SR3 & (1 << 0);//msl
  uint8_t t4 = I2C->SR1 & (1 << 7);//txe
  uint8_t t5 = I2C->SR1 & (1 << 2);//btf
  return (t1 && t2 && t3 && t4 && t5);
}
void I2c_write(uint8_t address, uint8_t data){
  while(Get_flag_status_of_bus());
  I2c_generate_start();
  while(!Check_event_start());
  
  I2c_send_7bits_address(address);
  while(!Check_event_send_7bits_address());
  
  I2c_send_data(data);
  while(!Check_event_send_data());

  I2c_generate_stop();
}




