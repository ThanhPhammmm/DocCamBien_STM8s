void TIM1_IT_Config(uint8_t type, uint8_t state){
  if(state == ON){
    TIM1->IER |= (1 << type);
  }
  else if(state == OFF){
    TIM1->IER &= ~(1 << type);
  }
}
void TIM1_BaseInit(uint16_t prescaler, uint8_t type, uint16_t period, uint8_t repitition){
  TIM1->ARRH = (uint8_t)(period >> 8);
  
  TIM1->ARRL = (uint8_t)(period);
  
  TIM1->PSCRH = (uint8_t)(prescaler >> 8);
  
  TIM1->PSCRL = (uint8_t)(prescaler);
    
  TIM1->RCR = repitition;
  
  TIM1_IT_Config(UPDATE_EVENT, ON);
  
  TIM1->CR1 |= (1 << 7) | (type << 4);
  
  TIM1->CR1 |= (1 << 0);
}
void TIM1_CLEAR_IT_PENDING(uint8_t type){
  TIM1->SR1 &= ~(1 << type);
}