uint16_t Check_Sum(uint8_t *buffer, uint8_t len){//16-CRC calculation ModBus
  uint16_t CRC = 0xFFFF;
  for(uint16_t pos = 0;pos < len;pos++){
    CRC ^= (uint16_t)buffer[pos];
    for(uint16_t i = 8;i > 0;i--){
      if((CRC & 0x0001) != 0){
        CRC >>= 1;
        CRC ^= 0xA001;
      }
      else{
        CRC >>= 1;
      }
    }
  }
  return CRC;
}
uint16_t Message_Frame_Create_Set_Port( port_e datain_port, uint8_t *data_out){
  frame_Message_t frame_data_in;
  frame_data_in.StartFrame = START_BYTE;
  frame_data_in.TypeMessage = TYPE_MESSAGE_SET_PORT;
  frame_data_in.Length = LENGTH_MESSAGE_SET_PORT;
  frame_data_in.Data[0] = datain_port;
  
  uint8_t *arr_temp_out;
  uint16_t count_arr_data = 0;
  
  arr_temp_out = (uint8_t*)&frame_data_in;
  
  for(int count_arr_data = 0;count_arr_data < LENGTH_DEFAULT + LENGTH_MESSAGE_SET_PORT - 2;count_arr_data++){
    data_out[count_arr_data] = arr_temp_out[count_arr_data];
  }
  frame_data_in.CheckFrame = Check_Sum(data_out, LENGTH_DEFAULT + LENGTH_MESSAGE_SET_PORT - 2);
  
  data_out[count_arr_data] = (frame_data_in.CheckFrame & 0xFF);
  count_arr_data += 1;
  data_out[count_arr_data] = ((frame_data_in.CheckFrame >> 8) & 0xFF);
  count_arr_data += 1;
  
  return count_arr_data;
}

uint8_t Message_Frame_Create_Confirm_Port(uint8_t datain_port, uint8_t datain_sensor, uint8_t* dataout){
  frame_Message_t frame_confirm;
  frame_confirm.StartFrame = START_BYTE;
  frame_confirm.TypeMessage = TYPE_MESSAGE_CONFIRM_PORT;
  frame_confirm.Length = LENGTH_MESSAGE_CONFIRM;
  frame_confirm.Data[0] = datain_port;
  frame_confirm.Data[1] = datain_sensor;
  
  uint8_t* sensor_confirm = (uint8_t*)&frame_confirm;
  
  frame_confirm.CheckFrame = Check_Sum(sensor_confirm, (LENGTH_MESSAGE_CONFIRM + LENGTH_DEFAULT - 2));
  
  uint16_t count_confirm_data = 0;
  for(count_confirm_data = 0;count_confirm_data < (LENGTH_MESSAGE_CONFIRM + LENGTH_DEFAULT - 2);count_confirm_data++){
    dataout[count_confirm_data] = sensor_confirm[count_confirm_data];
  }
  
  dataout[count_confirm_data] = frame_confirm.CheckFrame & 0xFF;
  dataout[count_confirm_data + 1] = ((frame_confirm.CheckFrame >> 8) & 0xFF);
  
  count_confirm_data += 2;
  return count_confirm_data;
}
uint8_t Message_Frame_Create_Ask_Data_Sensor(port_e datain_port, type_Sensor_e datain_sensor, uint8_t* dataout){
  frame_Message_t frame_ask;
  frame_ask.StartFrame = START_BYTE;
  frame_ask.TypeMessage = TYPE_MESSAGE_ASK_DATA;
  frame_ask.Length = LENGTH_MESSAGE_ASK_DATA;
  frame_ask.Data[0] = datain_port;
  frame_ask.Data[1] = datain_sensor;
  
  uint8_t* data_ask = (uint8_t*)&frame_ask;
  
  frame_ask.CheckFrame = Check_Sum(data_ask, (LENGTH_MESSAGE_ASK_DATA + LENGTH_DEFAULT - 2));
  
  uint16_t count_ask_data = 0;
  
  for(count_ask_data = 0;count_ask_data < (LENGTH_MESSAGE_ASK_DATA + LENGTH_DEFAULT - 2);count_ask_data++){
    dataout[count_ask_data] = data_ask[count_ask_data];
  }
  dataout[count_ask_data] = frame_ask.CheckFrame & 0xFF;
  dataout[count_ask_data + 1] = ((frame_ask.CheckFrame >> 8 )& 0xFF);
  count_ask_data += 2;
  return count_ask_data;
}
//LUX
uint16_t Message_Frame_Response_LUX(port_e datain_port, type_Sensor_e datain_sensor, float datain_value, uint8_t* dataout){
  uint8_t *data_convert = Convert_float_to_bytes(datain_value);
  frame_Message_t frame_response;
  frame_response.StartFrame = START_BYTE;
  frame_response.TypeMessage = TYPE_MESSAGE_RESPOND_DATA;
  frame_response.Length = LENGTH_MESSAGE_RESPOND_LUX;
  frame_response.Data[0] = datain_port;
  frame_response.Data[1] = datain_sensor;
  
  for(int i = 0;i < 4;i++){
    frame_response.Data[i + 2] = data_convert[i];
  }
  uint8_t* data_temp = (uint8_t*)&frame_response;
  uint16_t count_response_data = 0;
  for(count_response_data = 0; count_response_data <(LENGTH_MESSAGE_RESPOND_LUX + LENGTH_DEFAULT - 2);count_response_data++){
    dataout[count_response_data] = data_temp[count_response_data];
  }
  frame_response.CheckFrame = Check_Sum(data_temp, (LENGTH_MESSAGE_RESPOND_LUX + LENGTH_DEFAULT - 2));
  dataout[count_response_data] = frame_response.CheckFrame & 0xFF;
  dataout[count_response_data + 1] = (frame_response.CheckFrame >> 8) & 0xFF;
  count_response_data += 2;
  return count_response_data;
}
//RES
uint16_t Message_Frame_Response_RES(port_e datain_port, type_Sensor_e datain_sensor, uint16_t datain_value, uint8_t* dataout){//not test unit yet
  uint8_t *data_convert = Convert_uint16_t_to_bytes(datain_value);
  frame_Message_t frame_response;
  frame_response.StartFrame = START_BYTE;
  frame_response.TypeMessage = TYPE_MESSAGE_RESPOND_DATA;
  frame_response.Length = LENGTH_MESSAGE_RESPOND_RES;
  frame_response.Data[0] = datain_port;
  frame_response.Data[1] = datain_sensor;
  
  for(int i = 0;i < 4;i++){
    frame_response.Data[i + 2] = data_convert[i];
  }
  uint8_t* data_temp = (uint8_t*)&frame_response;
  uint16_t count_response_data = 0;
  for(count_response_data = 0; count_response_data <(LENGTH_MESSAGE_RESPOND_RES + LENGTH_DEFAULT - 2);count_response_data++){
    dataout[count_response_data] = data_temp[count_response_data];
  }
  frame_response.CheckFrame = Check_Sum(data_temp, (LENGTH_MESSAGE_RESPOND_RES + LENGTH_DEFAULT - 2));
  dataout[count_response_data] = frame_response.CheckFrame & 0xFF;
  dataout[count_response_data + 1] = (frame_response.CheckFrame >> 8) & 0xFF;
  count_response_data += 2;
  return count_response_data;
}