void Delay_ms(uint32_t ticks){
  TIM4->CR1 |= (1 << 0);
  TIM4->EGR |= (1 << 0);
  TIM4->PSCR |= (0x3 << 0);
  //Ftim = 16Mhz/2^3 = 2Mhz
  //1Ttim = 1/Ftim = 1/2Mhz = 0.000 000 5
  //0.000 000 5s <-> 1T
  //0.001s = 1ms <->2000T
  while(ticks > 0){
    for(int i = 0;i < 2000;i++){
      //empty
    }
      ticks--;
  }
  TIM4->CR1 &= ~(1 << 0);  // Optionally disable Timer
}
void CLK_HSI_16Mhz_config(void) {
    CLK->ICKR |= (1 << 1);   
    while (!(CLK->ICKR & (1 << 0))); 
    CLK->SWR = 0xE1;
    CLK->CKDIVR = 0x00;
}
