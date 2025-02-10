zuint8_t Message_Get_Port(frame_Message_t datain_frame)
{
  return datain_frame.Data[0];
}
uint8_t Message_Get_Type_Sensor(frame_Message_t datain_frame)
{
  return datain_frame.Data[1];
}
float Message_Get_Data_Sensor_Lux(frame_Message_t datain_frame)
{
  return Convert_bytes_into_float(datain_frame.Data[2], datain_frame.Data[3], datain_frame.Data[4], datain_frame.Data[5]);
}
uint16_t Message_Get_Data_Sensor_Res(frame_Message_t datain_frame)
{
  return Convert_bytes_into_uint16_t(datain_frame.Data[2], datain_frame.Data[3]);
}