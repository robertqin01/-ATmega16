//包含所需头文件
#include <iom16v.h> 
#include <macros.h>

//UART0 initialize
// desired baud rate: 9600
// actual: baud rate:9615 (0.2%)
void uart0_init(void)
{
 UCSRB = 0x00; //disable while setting baud rate
 UCSRA = 0x00;
 UCSRC = BIT(URSEL) | 0x06;
 UBRRL = 0x33; //set baud rate lo
 UBRRH = 0x00; //set baud rate hi
 UCSRB = 0x98;//发送使能
}


void send_data(unsigned char back)
{
  while( !( UCSRA & (1<<UDRE)) ) ;
  UDR=back;
}