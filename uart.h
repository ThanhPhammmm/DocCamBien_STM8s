#define WAIT_RECEIVE 0
#define RECEIVING 1
#define END_RECEIVE 2

void UART_Configuration (uint32_t baudrate);
void UART_Send_Array (uint8_t* array, uint16_t length); 
void UART_Printf_String (char *message); 
void UART_Interrupt_Receive_String ();
void UART_Time_Out();

INTERRUPT_HANDLER(UART1_RX_IRQHandler,18);

#include <uart.c>