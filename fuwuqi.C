#include <iom16v.h> 
#include <macros.h>   
#include "uart.h"//ÑÓÊ±º¯Êı
#include "delay.h"//ÑÓÊ±º¯Êı
#define uint  unsigned int 
#define uchar unsigned char



uchar jiaxianshi[5]="$00\0";

uchar  wupin_ming[5][13]={ 
"1.YuWen    \0",//
"2.ShuXue   \0",
"3.YingYu   \0",
"4.Wuli     \0",
"5.Huaxue   \0",

};

uchar xuhao;
char mode;
uchar ok;
uchar num;

uchar wupin[5]={5,5,5,5,5};

unsigned char com_in_buf[50];
unsigned char count;


uchar  jianshu_jilu[3][6];
uint   jiner_jilu[3];
uint jiner;
//¶Ë¿ÚÎ»¶¨Òå1602 Òı½ÅÏà¹Ø¿ØÖÆ
#define EN_CLR    PORTD&= ~(1 << PD6) 
#define EN_SET    PORTD |= (1 << PD6) 
#define RW_CLR    PORTD &= ~(1 << PD5) 
#define RW_SET    PORTD|= (1 << PD5) 
#define RS_CLR    PORTD &= ~(1 << PD4) 
#define RS_SET    PORTD |= (1 << PD4) 
#define LCD_BUS   PORTB

#define k1  ((PINC&0x01))
#define k2  ((PINC&0x02))
#define k3  ((PINC&0x04))
#define k4  ((PINC&0x08))

//#define lie2_0    PORTD&= ~(1 << PD5) 
//#define lie2_1    PORTD |= (1 << PD5) 

//#define lie4_0    PORTD&= ~(1 << PD7) 
//#define lie4_1    PORTD |= (1 << PD7) 

//#define BZ_CLR    PORTD&= ~(1 << PD0) 
//#define BZ_SET    PORTD |= (1 << PD0) 

#define LCD_BUS_Direction_REG    DDRB
#define LCD_BUS_READ_DATA        PINB
#define LCD_ControlPort_SET      DDRD |=((1<<PD4) | (1<<PD5) | (1<<PD6))
#define LCD_ControlPort_CLR      PORTD &=~((1<<PD4) | (1<<PD5) | (1<<PD6))

//LCD¶Ë¿Ú³õÊ¼»¯
void LCDPort_Init(void)
{    
   LCD_BUS = 0X00;
	 LCD_BUS_Direction_REG =0XFF;   //LCDÊı¾İ¶Ë¿ÚÉèÖÃÎªÊä³ö
	 LCD_ControlPort_CLR;          //RW RW ENµÍµçÆ½
	 LCD_ControlPort_SET;          //RS RW EN½Å¾ùÉèÖÃÎªÊä³ö	
}
//LCDĞ´Ö¸Áî
void Write_Com(unsigned char LCD_Com)
{
    // Check_Busy();
	 RW_CLR; //RW=0,Ğ´ÃüÁî
	 RS_CLR; //RS=0,Ğ´Ö¸Áî
	 EN_CLR;// E=0£¬ÏÂ½Ç  
	 LCD_BUS&=0x0f;
	 LCD_BUS|=(LCD_Com&0xf0);    //Êı¾İËÍÍùÊı¾İ¶Ë¿Ú? 
	 //delay_nus(10);    //Õâ¸öÑÓÊ±·Ç³£ÖØÒª£¬½áºÏÊ±ĞòÍ¼À´Àí½â£¬¿ÉÒÔ¸úËÍÊı¾İË³Ğòµ÷»»
	 EN_SET; //E=1,Ğ´²Ù×÷	
	 EN_CLR;// E=0£¬ÏÂ½Ç  

	 //while(1);
	 LCD_BUS&=0x0f;
	 LCD_BUS|=(LCD_Com<<4);    //Êı¾İËÍÍùÊı¾İ¶Ë¿Ú? 
	 delay_nus(10);    //Õâ¸öÑÓÊ±·Ç³£ÖØÒª£¬½áºÏÊ±ĞòÍ¼À´Àí½â£¬¿ÉÒÔ¸úËÍÊı¾İË³Ğòµ÷»»
 	 EN_SET; //E=1,Ğ´²Ù×÷	
	 EN_CLR;// E=0£¬ÏÂ½Ç  
	 delay_nms(5); 
}

//LCDĞ´×Ö½ÚÊı¾İ
void Write_Data_Byte(unsigned char LCD_Data)
{
    // Check_Busy();
     RW_CLR;//RW=0,Ğ´Èë
     RS_SET; //RS=1,Êı¾İ¼Ä´æÆ÷
     EN_CLR;// E=0£¬ÏÂ½Ç   
		 LCD_BUS&=0x0f;
	   LCD_BUS|=(LCD_Data&0xf0);//Êı¾İËÍÊı¾İ¶Ë¿Ú  
     //delay_nus(10);   //Õâ¸öÑÓÊ±·Ç³£ÖØÒª	 
      EN_SET; //E=1,Ğ´²Ù×÷	
	    EN_CLR;// E=0£¬ÏÂ½Ç   
		 LCD_BUS&=0x0f;
	   LCD_BUS|=(LCD_Data<<4);//Êı¾İËÍÊı¾İ¶Ë¿Ú  
     //delay_nus(10);   //Õâ¸öÑÓÊ±·Ç³£ÖØÒª	 
      EN_SET; //E=1,Ğ´²Ù×÷	
	    EN_CLR;// E=0£¬ÏÂ½Ç   
     delay_nms(5);
		// while(1);
}
   
//LCD³õÊ¼»¯
void LCD_Init(void)
{
   delay_nms(150);
	 delay_nms(15);
	 Write_Com(0x02);//ÏÔÊ¾Ä£Ê½ÉèÖÃ 16*2£¬5*7µãÕó£¬4Î»Êı¾İ½Ó¿Ú

	 delay_nms(15);
	 Write_Com(0x28);//ÏÔÊ¾Ä£Ê½ÉèÖÃ 16*2£¬5*7µãÕó£¬4Î»Êı¾İ½Ó¿Ú
	 delay_nms(15);
	 //Write_Com(0x28);//ÏÔÊ¾Ä£Ê½ÉèÖÃ 16*2£¬5*7µãÕó£¬4Î»Êı¾İ½Ó¿Ú
	 //delay_nms(15);
   Write_Com(0x06);//¹â±êÉèÖÃ£¬¶Á»òĞ´Ò»¸ö×Ö·ûºó£¬µØÖ·Ö¸Õë¼Ó1£¬¹â±ê¼Ó1£¬ÕûÆÁ²»ÒÆ¶¯
	 delay_nms(15);
	//Write_Com(0x0f);//ÏÔÊ¾¿ª¹Ø¿ØÖÆ£¬¿ªÏÔÊ¾£¬¹â±êÏÔÊ¾£¬¹â±êÉÁË¸
	 Write_Com(0x0c);//ÏÔÊ¾¿ª¹Ø¿ØÖÆ£¬¿ªÏÔÊ¾£¬¹â±ê²»ÏÔÊ¾£¬¹â±ê²»ÉÁË¸ 
	 delay_nms(15);
	 Write_Com(0x01);;//ÇåÆÁ
	 delay_nms(15);
}



//Ö¸¶¨µ±Ç°Ğ´×Ö·ûµÄÎ»ÖÃ
void Write_Place_xy(unsigned char x,unsigned char y)
{
     unsigned char address;
	 if(y==0)             //ĞĞÎ»ÖÃ
	 {
	      address=0x80+x; //ÁĞÎ»ÖÃ
     }
	 else 
	 {
	      address=0xc0+x;
	 }
	 Write_Com(address);  //Ğ´µØÖ·90 d0
	 
}


//ÔÚÖ¸¶¨µÄÎ»ÖÃĞ´×Ö·û´®
void Write_Data_String(unsigned char x,unsigned char y,unsigned char *data)
{
     unsigned char i;
	 unsigned char Length;
	 Write_Place_xy(x,y); //Ğ´µØÖ·
	 delay_nms(1);
     Length=strlen(data);//µ÷ÓÃ×Ö·û´®º¯ÊıËã³ö×Ö·ûµÄ³¤¶È,²¢¸³Öµ¸øLength
     for(i=0;i<Length;i++) //X×ø±êÓ¦Ğ¡ÓÚ0xF
      {
         Write_Data_Byte(*data); //ÏÔÊ¾µ¥¸ö×Ö·û
         
         data++;
				 delay_nms(1);
      }
 
}

//ÔÚÖ¸¶¨µÄÎ»ÖÃĞ´×Ö·û´
void Write_Data_char(unsigned char x,unsigned char y,unsigned char data)
{
     unsigned char i;
	 unsigned char Length;
	 Write_Place_xy(x,y); //Ğ´µØÖ·
	 delay_nms(1);
    Write_Data_Byte(data); //ÏÔÊ¾µ¥¸ö×Ö·û
	  delay_nms(1);
    
 
}

//¼üÅÌÉ¨Ãè£¬ÎŞ°´¼ü·µ»Ø0
uchar ScanKey()
{
  uchar ret = 0xff;

	// lie4_0;
	 delay_nms(5);
	 if(!k1)
	 {
	  ret=1;
	  while(!k1);
	 }
	 if(!k2)
	 {
	  ret=2;
	  while(!k2);
	 } 
	 if(!k3)
	 {
	  ret=3;
	  while(!k3);
	 } 
	 if(!k4)
	 {
	  ret=4;
	  while(!k4);
	 } 
	// lie4_1;
	return ret;
}



void main(void) 
{ 
  uchar z; 
  uchar shu;
	uchar i;
	uchar keynum;
	CLI(); //disable all interrupts
  DDRC = 0X00;//IO ³õÊ¼»¯  0ÊÇÊäÈë
  PORTC = 0XFF;//IO ³õÊ¼»¯
	
  DDRD = 0X02;//IO ³õÊ¼»¯
  PORTD=0XFF;
  LCDPort_Init(); //¶Ë¿Ú³õÊ¼»¯
		
 LCD_Init();  // LCD³õÊ¼»¯
 Write_Data_String(0,0,"OK");//ÏÔÊ¾µÚÒ»ĞĞÊı¾İ
 uart0_init();
  MCUCR = 0x00;
 GICR  = 0x00;
 TIMSK = 0x00; //timer interrupt sources
 SEI(); //re-enable interrupts
 //all peripherals are now initialized
 while(1)
 {  

   keynum=ScanKey();//É¨Ãè°´¼ü
	 if(keynum!=0xff)//ÓĞ°´¼ü°´ÏÂ
	 {
	 	 if(keynum==1)//ÓĞ°´¼ü°´ÏÂ
		 {
	      send_data('S');
		  send_data('A');
		  send_data(wupin[0]/10+0x30);
	      send_data(wupin[0]%10+0x30);
		  send_data('B');
		  send_data(wupin[1]/10+0x30);
	      send_data(wupin[1]%10+0x30);
		  send_data('C');
		  send_data(wupin[2]/10+0x30);
	      send_data(wupin[2]%10+0x30);	
		  send_data('D');
		  send_data(wupin[3]/10+0x30);
	      send_data(wupin[3]%10+0x30);		  
		  send_data('E');
		  send_data(wupin[4]/10+0x30);
	      send_data(wupin[4]%10+0x30);	  
		  //send_data('F');
		  //send_data(wupin[5]/10+0x30);
	      //send_data(wupin[5]%10+0x30);	
		  send_data(0X0D);
		  send_data(0X0A); 		  
	     }
		 
		  if(keynum==2)//ÇĞ»»²Ëµ¥
		 {
           xuhao++;
           if(xuhao>=5)
           xuhao=0;    
	     } 
		 
		 if(keynum==3)//ÇĞ»»ÓÃ»§
		 {
           num++;
           if(num>=3)
           num=0;    
	     } 
		 
	 }
	 
	 if(ok==1)// ÊÕµ½ÕËµ¥  ¼ÆËã×Ü¼Û·µ»Ø
	 {
	  ok=0;
	  
	  jiner=jianshu_jilu[0][0]*wupin[0];
	  jiner+=jianshu_jilu[0][1]*wupin[1];
	  jiner+=jianshu_jilu[0][2]*wupin[2];
	  jiner+=jianshu_jilu[0][3]*wupin[3];
	  jiner+=jianshu_jilu[0][4]*wupin[4];
	  //jiner+=jianshu_jilu[0][5]*wupin[5];
	  jiner_jilu[0]=jiner;    

	  jiner=jianshu_jilu[1][0]*wupin[0];
	  jiner+=jianshu_jilu[1][1]*wupin[1];
	  jiner+=jianshu_jilu[1][2]*wupin[2];
	  jiner+=jianshu_jilu[1][3]*wupin[3];
	  jiner+=jianshu_jilu[1][4]*wupin[4];
	  //jiner+=jianshu_jilu[1][5]*wupin[5];
	  jiner_jilu[1]=jiner;  
	  
	  jiner=jianshu_jilu[2][0]*wupin[0];
	  jiner+=jianshu_jilu[2][1]*wupin[1];
	  jiner+=jianshu_jilu[2][2]*wupin[2];
	  jiner+=jianshu_jilu[2][3]*wupin[3];
	  jiner+=jianshu_jilu[2][4]*wupin[4];
	  //jiner+=jianshu_jilu[2][5]*wupin[5];
	 jiner_jilu[2]=jiner;  
	  

		  send_data('J');
		  send_data(jiner_jilu[0]/1000+0x30);
		  send_data(jiner_jilu[0]/100%10+0x30);
		  send_data(jiner_jilu[0]/10%10+0x30);
		  send_data(jiner_jilu[0]%10+0x30);
		  
		  send_data(jiner_jilu[1]/1000+0x30);
		  send_data(jiner_jilu[1]/100%10+0x30);
		  send_data(jiner_jilu[1]/10%10+0x30);
		  send_data(jiner_jilu[1]%10+0x30);
		  
		  send_data(jiner_jilu[2]/1000+0x30);
		  send_data(jiner_jilu[2]/100%10+0x30);
		  send_data(jiner_jilu[2]/10%10+0x30);
		  send_data(jiner_jilu[2]%10+0x30);  
		  
		  send_data(0X0D);
		  send_data(0X0A); 	  
	  
	  
	  
	 }


	 
	
  //********ÏÔÊ¾²Ëµ¥µÚÒ»ĞĞ*******
  jiaxianshi[2]=wupin[xuhao]/10+0x30;
  jiaxianshi[3]=wupin[xuhao]%10+0x30;
  Write_Data_String(0,0,wupin_ming[xuhao]);//ÏÔÊ¾µÚÒ»ĞĞÊı¾İ
  Write_Data_String(12,0,jiaxianshi);//ÏÔÊ¾µÚÒ»ĞĞÊı¾İ
  
  Write_Data_String(0,1,"MZ:");//
  Write_Data_Byte((num+1)+0x30); //ÏÔÊ¾µ¥¸ö×Ö·û
  
   Write_Data_String(13,1,"M:");//
   Write_Data_Byte(jianshu_jilu[num][xuhao]+0x30); //ÏÔÊ¾µ¥¸ö×Ö·û 
	 
	 
  Write_Place_xy(5,1);
  Write_Data_Byte(jiner_jilu[num]/1000+0x30); //ÏÔÊ¾µ¥¸ö×Ö·û
  Write_Data_Byte(jiner_jilu[num]/100%10+0x30); //ÏÔÊ¾µ¥¸ö×Ö·û
  Write_Data_Byte(jiner_jilu[num]/10%10+0x30); //ÏÔÊ¾µ¥¸ö×Ö·û
  Write_Data_Byte(jiner_jilu[num]%10+0x30); //ÏÔÊ¾µ¥¸ö×Ö·û
	 
 } 
} 
#pragma interrupt_handler uart0_rx_isr:12
void uart0_rx_isr(void)
{
uchar i;
uchar temp;
 //uart has received a character in UDR
 //UCSRB&=~BIT(RXCIE); //¹Ø±Õ½ÓÊÕÖĞ¶Ï 
 com_in_buf[count++]=UDR;//
 if((com_in_buf[count-2]==0x0d)&&(com_in_buf[count-1]==0x0a))//½ÓÊÜÊÕµ½½øĞĞ½âÂë
 {
 //S000000000000000000

   if(com_in_buf[count-21]=='S')
   {
	temp=com_in_buf[count-20]-0x30;
    jianshu_jilu[0][0]=temp;
	temp=com_in_buf[count-19]-0x30;
    jianshu_jilu[0][1]=temp;
	temp=com_in_buf[count-18]-0x30;
    jianshu_jilu[0][2]=temp;
	temp=com_in_buf[count-17]-0x30;
    jianshu_jilu[0][3]=temp;
	temp=com_in_buf[count-16]-0x30;
    jianshu_jilu[0][4]=temp;
	 //temp=com_in_buf[count-15]-0x30;
    //jianshu_jilu[0][5]=temp;
	
	
    temp=com_in_buf[count-14]-0x30;
    jianshu_jilu[1][0]=temp;
	temp=com_in_buf[count-13]-0x30;
    jianshu_jilu[1][1]=temp;
	temp=com_in_buf[count-12]-0x30;
    jianshu_jilu[1][2]=temp;
	temp=com_in_buf[count-11]-0x30;
    jianshu_jilu[1][3]=temp;
	temp=com_in_buf[count-10]-0x30;
    jianshu_jilu[1][4]=temp;
	//temp=com_in_buf[count-9]-0x30;
    //jianshu_jilu[1][5]=temp;
	
	
    temp=com_in_buf[count-8]-0x30;
    jianshu_jilu[2][0]=temp;
	temp=com_in_buf[count-7]-0x30;
    jianshu_jilu[2][1]=temp;
	temp=com_in_buf[count-6]-0x30;
    jianshu_jilu[2][2]=temp;
	temp=com_in_buf[count-5]-0x30;
    jianshu_jilu[2][3]=temp;
	temp=com_in_buf[count-4]-0x30;
    jianshu_jilu[2][4]=temp;
	// temp=com_in_buf[count-3]-0x30;
    //jianshu_jilu[2][5]=temp;
    ok=1;
   }
   
   
   
	count=0;
 }
 //UCSRB|=BIT(RXCIE); //Ê¹ÄÜ½ÓÊÕÖĞ¶Ï

}