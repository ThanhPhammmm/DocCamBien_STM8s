fsm_List_State_e fsm_state = FSM_STATE_START_FRAME;

uint16_t count_element_arr = 0;
uint16_t type_mess_fsm = 0;
uint16_t length_fsm = 0;
uint8_t flag_fsm_new_message = 0;

void Clear_All_State_Fsm(void){
    count_element_arr = 0;
    length_fsm = 0;
    flag_fsm_new_message = 0;
    fsm_state = FSM_STATE_START_FRAME;
}
void FSM_Get_Message(uint8_t datain, uint8_t *dataout){
  switch(fsm_state){
  case FSM_STATE_START_FRAME:
    dataout[count_element_arr] = datain;
    count_element_arr++;
    if(count_element_arr == FSM_STATE_CHANGE_VALUE_TYPE_MESS){
      if(Convert_bytes_into_uint16_t(dataout[0], dataout[1]) != 0xAA55){
        Clear_All_State_Fsm();
      }
      else{
        fsm_state = FSM_STATE_TYPE_MESS;
      }
    }
    break;
  case FSM_STATE_TYPE_MESS:
    dataout[count_element_arr] = datain;
    count_element_arr++;
    if(count_element_arr == FSM_STATE_CHANGE_VALUE_LENGTH){
      type_mess_fsm = Convert_bytes_into_uint16_t(dataout[2], dataout[3]);
      if(type_mess_fsm == TYPE_MESSAGE_SET_PORT 
         || type_mess_fsm == TYPE_MESSAGE_CONFIRM_PORT 
         || type_mess_fsm == TYPE_MESSAGE_ASK_DATA 
         || type_mess_fsm == TYPE_MESSAGE_RESPOND_DATA){
        fsm_state = FSM_STATE_LENGTH;
      }
      else{
        Clear_All_State_Fsm();
      }
    }
    break;
  case FSM_STATE_LENGTH:
    dataout[count_element_arr] = datain;
    count_element_arr++;
    if(count_element_arr == FSM_STATE_CHANGE_VALUE_DATA){
      length_fsm = Convert_bytes_into_uint16_t(dataout[4], dataout[5]);
      fsm_state = FSM_STATE_DATA; 
    }
    break;
  case FSM_STATE_DATA:
    dataout[count_element_arr] = datain;
    count_element_arr++;
    if(count_element_arr == 7){
      if(dataout[6] != PORT_A && dataout[6] != PORT_B){
        Clear_All_State_Fsm();        
      }
    }
    else if(count_element_arr == 8){
      if( dataout[7] != SENSOR_LUX && dataout[7] != SENSOR_RTC && dataout[7] != SENSOR_NTC && dataout[7] != SENSOR_RES )
      {
        Clear_All_State_Fsm();
      }
    }
    switch(type_mess_fsm){
      case TYPE_MESSAGE_SET_PORT:
        fsm_state = FSM_STATE_END;
        break;
      case TYPE_MESSAGE_CONFIRM_PORT:
        if(count_element_arr == FSM_STATE_CHANGE_VALUE_END_TYPE_SENSOR){
          fsm_state = FSM_STATE_END;          
        }
        break;
      case TYPE_MESSAGE_ASK_DATA:
        if(count_element_arr == FSM_STATE_CHANGE_VALUE_END_TYPE_SENSOR){
          fsm_state = FSM_STATE_END;          
        }
        break;
      case TYPE_MESSAGE_RESPOND_DATA:
        if(count_element_arr > FSM_STATE_CHANGE_VALUE_END_TYPE_SENSOR){
          switch(dataout[FSM_STATE_CHANGE_VALUE_END_TYPE_SENSOR - 1]){
            case SENSOR_LUX:
              if(count_element_arr == FSM_STATE_CHANGE_VALUE_END_DATA_LUX){
                fsm_state = FSM_STATE_END;
              }
              break;
            case SENSOR_RES:
              if(count_element_arr == FSM_STATE_CHANGE_VALUE_END_DATA_RES){
                fsm_state = FSM_STATE_END;
              }
              break;
          }
        }
        break;
    }
    break;
  case FSM_STATE_END:
    dataout[count_element_arr] = datain;
    count_element_arr++;
    if(count_element_arr == (length_fsm + LENGTH_DEFAULT)){
      uint16_t Check_Sum_From_Arr = Convert_bytes_into_uint16_t( dataout[count_element_arr - 2], dataout[count_element_arr - 1]);
      uint16_t Check_Sum_Fsm = Check_Sum( dataout, count_element_arr - 2);
      if( Check_Sum_From_Arr == Check_Sum_Fsm)
      {
          Clear_All_State_Fsm();
      }
      else 
      {
          Clear_All_State_Fsm();
      }
    }
    break;
  }
}