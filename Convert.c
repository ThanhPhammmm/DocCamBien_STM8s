//Chuyen doi int sang byte
uint8_t *Convert_int_to_bytes(int n){
  static union Int_to_bytes_format tmp;
  tmp.data = n;
  return tmp.bytes;//tra ve dia chi cua mang(dia chi cua gia tri dau tien cua mang)
}
//Chuyen doi byte sang int
uint32_t Convert_bytes_into_int(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4){
  static union Int_to_bytes_format tmp;
  tmp.bytes[0] = data1;//byte be nhat
  tmp.bytes[1] = data2;
  tmp.bytes[2] = data3;
  tmp.bytes[3] = data4;
  return tmp.data;
}
uint8_t *Convert_float_to_bytes(float n){
  static union Float_to_bytes_format tmp;//tra ve dia chi cua mang(dia chi cua gia tri dau tien cua mang)
  tmp.data = n;
  return tmp.bytes;
}
float Convert_bytes_into_float(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4){
  static union Float_to_bytes_format tmp;
  tmp.bytes[0] = data1;//byte be nhat
  tmp.bytes[1] = data2;
  tmp.bytes[2] = data3;
  tmp.bytes[3] = data4;
  return tmp.data;
}
uint8_t *Convert_uint16_t_to_bytes(uint16_t n){
  static union Unit16_t_to_bytes_format tmp;
  tmp.data = n;
  return tmp.bytes;
}
uint16_t Convert_bytes_into_uint16_t(uint8_t data1, uint8_t data2){
  static union Unit16_t_to_bytes_format tmp;
  tmp.bytes[0] = data1;//byte be nhat
  tmp.bytes[1] = data2;
  return tmp.data;
}