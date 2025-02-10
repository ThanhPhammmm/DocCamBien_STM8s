uint8_t *Convert_int_to_bytes(int n);
uint32_t Convert_bytes_into_int(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4);
uint8_t *Convert_float_to_bytes(float n);
float Convert_bytes_into_float(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4);
uint8_t *Convert_uint16_t_to_bytes(uint16_t n);
uint16_t Convert_bytes_into_uint16_t(uint8_t data1, uint8_t data2);

union Int_to_bytes_format{
  int data;
  unsigned char bytes[4];
};
union Float_to_bytes_format{
  float data;
  unsigned char bytes[4];
};
union Unit16_t_to_bytes_format{
  uint16_t data;
  unsigned char bytes[2];
};
enum STATUS{
  True = 1,
  False = 0
};
enum COLOUR{
  RED,
  BLUE,
  GREEN
};

#include <Convert.c>
