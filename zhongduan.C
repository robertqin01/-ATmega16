#include <iom16v.h> 
#include <macros.h>   

#include <stdio.h>  
#include <stdlib.h>

#include "uart.h"//延时函数
#include "delay.h"//延时函数
#define uint  unsigned int 
#define uchar unsigned char

uchar  wupin[6]={10,15,20,25,30,35};
uchar  jianshu_jilu[3][6];
uint   jiner_jilu[3];
uchar jiaxianshi[5]="$00\0";

uchar  wupin_ming[6][13]={ 
"1.Tudousi  \0",//
"2.Huiguorou\0",
"3.Pijiuya  \0",
"4.Zhujiao  \0",
"5.Qingcai  \0",
"6.Huoguodi \0",
};



uchar xuhao;
uchar ok;
unsigned char com_in_buf[50];
unsigned char count;
char mode;
uchar jianshu;
uchar num;
//端口位定义1602 引脚相关控制

#define k1  ((PINC&0x01))
#define k2  ((PINC&0x02))
#define k3  ((PINC&0x04))
#define k4  ((PINC&0x08))


//端口位定义1602 引脚相关控制
#define EN_CLR    PORTD&= ~(1 << PD6) 
#define EN_SET    PORTD |= (1 << PD6) 
#define RW_CLR    PORTD &= ~(1 << PD5) 
#define RW_SET    PORTD|= (1 << PD5) 
#define RS_CLR    PORTD &= ~(1 << PD4) 
#define RS_SET    PORTD |= (1 << PD4) 
#define LCD_BUS   PORTB




//#define BZ_CLR    PORTD&= ~(1 << PD0) 
//#define BZ_SET    PORTD |= (1 << PD0) 

#define LCD_BUS_Direction_REG    DDRB
#define LCD_BUS_READ_DATA        PINB
#define LCD_ControlPort_SET      DDRD |=((1<<PD4) | (1<<PD5) | (1<<PD6))
#define LCD_ControlPort_CLR      PORTD &=~((1<<PD4) | (1<<PD5) | (1<<PD6))

//LCD端口初始化
void LCDPort_Init(void)
{    
   LCD_BUS = 0X00;
	 LCD_BUS_Direction_REG =0XFF;   //LCD数据端口设置为输出
	 LCD_ControlPort_CLR;          //RW RW EN低电平
	 LCD_ControlPort_SET;          //RS RW EN脚均设置为输出	
}
//LCD写指令
void Write_Com(unsigned char LCD_Com)
{
    // Check_Busy();
	 RW_CLR; //RW=0,写命令
	 RS_CLR; //RS=0,写指令
	 EN_CLR;// E=0，下角  
	 LCD_BUS&=0x0f;
	 LCD_BUS|=(LCD_Com&0xf0);    //数据送往数据端口? 
	 //delay_nus(10);    //这个延时非常重要，结合时序图来理解，可以跟送数据顺序调换
	 EN_SET; //E=1,写操作	
	 EN_CLR;// E=0，下角  

	 //while(1);
	 LCD_BUS&=0x0f;
	 LCD_BUS|=(LCD_Com<<4);    //数据送往数据端口? 
	 delay_nus(10);    //这个延时非常重要，结合时序图来理解，可以跟送数据顺序调换
 	 EN_SET; //E=1,写操作	
	 EN_CLR;// E=0，下角  
	 delay_nms(5); 
}

//LCD写字节数据
void Write_Data_Byte(unsigned char LCD_Data)
{
    // Check_Busy();
     RW_CLR;//RW=0,写入
     RS_SET; //RS=1,数据寄存器
     EN_CLR;// E=0，下角   
		 LCD_BUS&=0x0f;
	   LCD_BUS|=(LCD_Data&0xf0);//数据送数据端口  
     //delay_nus(10);   //这个延时非常重要	 
      EN_SET; //E=1,写操作	
	    EN_CLR;// E=0，下角   
		 LCD_BUS&=0x0f;
	   LCD_BUS|=(LCD_Data<<4);//数据送数据端口  
     //delay_nus(10);   //这个延时非常重要	 
      EN_SET; //E=1,写操作	
	    EN_CLR;// E=0，下角   
     delay_nms(5);
		// while(1);
}
   
//键盘扫描，无按键返回0
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
//LCD初始化
void LCD_Init(void)
{
   delay_nms(150);
	 delay_nms(15);
	 Write_Com(0x02);//显示模式设置 16*2，5*7点阵，4位数据接口

	 delay_nms(15);
	 Write_Com(0x28);//显示模式设置 16*2，5*7点阵，4位数据接口
	 delay_nms(15);
	 //Write_Com(0x28);//显示模式设置 16*2，5*7点阵，4位数据接口
	 //delay_nms(15);
   Write_Com(0x06);//光标设置，读或写一个字符后，地址指针加1，光标加1，整屏不移动
	 delay_nms(15);
	//Write_Com(0x0f);//显示开关控制，开显示，光标显示，光标闪烁
	 Write_Com(0x0c);//显示开关控制，开显示，光标不显示，光标不闪烁 
	 delay_nms(15);
	 Write_Com(0x01);;//清屏
	 delay_nms(15);
}



//指定当前写字符的位置
void Write_Place_xy(unsigned char x,unsigned char y)
{
     unsigned char address;
	 if(y==0)             //行位置
	 {
	      address=0x80+x; //列位置
     }
	 else 
	 {
	      address=0xc0+x;
	 }
	 Write_Com(address);  //写地址90 d0
	 
}


//在指定的位置写字符串
void Write_Data_String(unsigned char x,unsigned char y,unsigned char *data)
{
     unsigned char i;
	 unsigned char Length;
	 Write_Place_xy(x,y); //写地址
	 delay_nms(1);
     Length=strlen(data);//调用字符串函数算出字符的长度,并赋值给Length
     for(i=0;i<Length;i++) //X坐标应小于0xF
      {
         Write_Data_Byte(*data); //显示单个字符
         
         data++;
				 delay_nms(1);
      }
 
}


	 
	 
void main(void) 
{ 
  uchar z; 
	//uchar i;
	uchar keynum;
	
	
	
	
	CLI(); //disable all interrupts
  DDRC = 0X00;//IO 初始化  0是输入
  PORTC = 0XFF;//IO 初始化
	
  DDRD = 0X02;//IO 初始化
  PORTD=0XFF;
  LCDPort_Init(); //端口初始化
		
 LCD_Init();  // LCD初始化
 Write_Data_String(0,0,"Huan ying");//显示第一行数据
 uart0_init();
  MCUCR = 0x00;
 GICR  = 0x00;
 TIMSK = 0x00; //timer interrupt sources
 SEI(); //re-enable interrupts
 //all peripherals are now initialized
 while(ok==0);
 
 while(1)
 {  
	//ok=1;
 keynum=ScanKey();//扫描按键
	 if(keynum!=0xff)//有按键按下
	 {
	 	 if(keynum==1)//有按键按下
		 {
	      send_data('S');
		  send_data(jianshu_jilu[0][0]+0x30);
		  send_data(jianshu_jilu[0][1]+0x30);
		  send_data(jianshu_jilu[0][2]+0x30);
		  send_data(jianshu_jilu[0][3]+0x30); 
		  send_data(jianshu_jilu[0][4]+0x30);
		  send_data(jianshu_jilu[0][5]+0x30);

		  
		  send_data(jianshu_jilu[1][0]+0x30);
		  send_data(jianshu_jilu[1][1]+0x30);
		  send_data(jianshu_jilu[1][2]+0x30);
		  send_data(jianshu_jilu[1][3]+0x30); 
		  send_data(jianshu_jilu[1][4]+0x30);
		  send_data(jianshu_jilu[1][5]+0x30);
	  
		  
		  send_data(jianshu_jilu[2][0]+0x30);
		  send_data(jianshu_jilu[2][1]+0x30);
		  send_data(jianshu_jilu[2][2]+0x30);
		  send_data(jianshu_jilu[2][3]+0x30); 
		  send_data(jianshu_jilu[2][4]+0x30);
		  send_data(jianshu_jilu[2][5]+0x30);
  

		  send_data(0X0D);
		  send_data(0X0A); 		  
		
	     }
		 
		 if(keynum==2)//切换菜单
		 {
           xuhao++;
           if(xuhao>=6)
           xuhao=0;    
	     } 
		 
		 if(keynum==3)//切换用户
		 {
           num++;
           if(num>=3)
           num=0;    
	     } 
		 
		 if(keynum==4)//点菜数量
		 {
           jianshu_jilu[num][xuhao]++;
           if(jianshu_jilu[num][xuhao]>=9)
           jianshu_jilu[num][xuhao]=0;    
	     }  
		  
		 
	 }
	if(ok==1) 
	{
	  ok=0;
	  LCD_Init();  // LCD初始化  
  jiaxianshi[2]=wupin[0]/10+0x30;
  jiaxianshi[3]=wupin[0]%10+0x30;
  Write_Data_String(0,0,wupin_ming[0]);//显示第一行数据
  Write_Data_String(10,0,jiaxianshi);//显示第一行数据
  

  jiaxianshi[2]=wupin[1]/10+0x30;
  jiaxianshi[3]=wupin[1]%10+0x30;
  Write_Data_String(0,1,wupin_ming[1]);//显示第一行数据
  Write_Data_String(10,1,jiaxianshi);//显示第一行数据
  delay_nms(2000); 
  
  
  
  jiaxianshi[2]=wupin[2]/10+0x30;
  jiaxianshi[3]=wupin[2]%10+0x30;
  Write_Data_String(0,0,wupin_ming[2]);//显示第一行数据
  Write_Data_String(10,0,jiaxianshi);//显示第一行数据

  jiaxianshi[2]=wupin[3]/10+0x30;
  jiaxianshi[3]=wupin[3]%10+0x30;
  Write_Data_String(0,1,wupin_ming[3]);//显示第一行数据
  Write_Data_String(10,1,jiaxianshi);//显示第一行数据
  delay_nms(2000); 
  
  
  jiaxianshi[2]=wupin[4]/10+0x30;
  jiaxianshi[3]=wupin[4]%10+0x30;
  Write_Data_String(0,0,wupin_ming[4]);//显示第一行数据
  Write_Data_String(10,0,jiaxianshi);//显示第一行数据

  jiaxianshi[2]=wupin[5]/10+0x30;
  jiaxianshi[3]=wupin[5]%10+0x30;
  Write_Data_String(0,1,wupin_ming[5]);//显示第一行数据
  Write_Data_String(10,1,jiaxianshi);//显示第一行数据
  delay_nms(2000); 
  LCD_Init();  // LCD初始化
  }
  
  
if(ok==2) 
	{
	  ok=0;
	  LCD_Init();  // LCD初始化  

  Write_Data_String(0,0,"Zongjia:");//显示第一行数据
  Write_Data_Byte(jiner_jilu[num]/1000+0x30); //显示单个字符
  Write_Data_Byte(jiner_jilu[num]/100%10+0x30); //显示单个字符
  Write_Data_Byte(jiner_jilu[num]/10%10+0x30); //显示单个字符
  Write_Data_Byte(jiner_jilu[num]%10+0x30); //显示单个字符
 
  delay_nms(4000); 
  LCD_Init();  // LCD初始化
  }  


  //********显示菜单第一行*******
  jiaxianshi[2]=wupin[xuhao]/10+0x30;
  jiaxianshi[3]=wupin[xuhao]%10+0x30;
  Write_Data_String(0,0,wupin_ming[xuhao]);//显示第一行数据
  Write_Data_String(12,0,jiaxianshi);//显示第一行数据
  
  Write_Data_String(0,1,"ID:");//
  Write_Data_Byte((num+1)+0x30); //显示单个字符
  
   Write_Data_String(13,1,"S:");//
   Write_Data_Byte(jianshu_jilu[num][xuhao]+0x30); //显示单个字符
   
  //jianshu_jilu[4][6]

 } 
} 

#pragma interrupt_handler uart0_rx_isr:12
void uart0_rx_isr(void)
{
uchar i,temp;
 //uart has received a character in UDR
// UCSRB&=~BIT(RXCIE); //关闭接收中断 
 com_in_buf[count++]=UDR;//
 // SA10B15C20D25E30F35
 if((com_in_buf[count-2]==0x0d)&&(com_in_buf[count-1]==0x0a))//接受收到进行解码
 {
  if(com_in_buf[count-21]=='S')
   {
   
    temp=com_in_buf[count-19]-0x30;
    temp=temp*10;
	temp+=com_in_buf[count-18]-0x30;
	wupin[0]=temp;//物品A 价格
	
	
    temp=com_in_buf[count-16]-0x30;
    temp=temp*10;
	temp+=com_in_buf[count-15]-0x30;
	wupin[1]=temp;//物品A 价格
	
	temp=com_in_buf[count-13]-0x30;
    temp=temp*10;
	temp+=com_in_buf[count-12]-0x30;
	wupin[2]=temp;//物品A 价格
	
	 temp=com_in_buf[count-10]-0x30;
     temp=temp*10;
	 temp+=com_in_buf[count-9]-0x30;
	 wupin[3]=temp;//物品A 价格
	 
	 temp=com_in_buf[count-7]-0x30;
     temp=temp*10;
	 temp+=com_in_buf[count-6]-0x30;
	 wupin[4]=temp;//物品A 价格	 
	 
	 temp=com_in_buf[count-4]-0x30;
     temp=temp*10;
	 temp+=com_in_buf[count-3]-0x30;
	 wupin[5]=temp;//物品A 价格 
	 
	 ok=1;
   }
   
   
   if(com_in_buf[count-15]=='J')
   {
  
    temp=com_in_buf[count-14]-0x30;
    jiner_jilu[0]=temp*1000;
	temp=com_in_buf[count-13]-0x30;
    jiner_jilu[0]+=temp*100;
	temp=com_in_buf[count-12]-0x30;
    jiner_jilu[0]+=temp*10;
    temp=com_in_buf[count-11]-0x30;
    jiner_jilu[0]+=temp;

    temp=com_in_buf[count-10]-0x30;
    jiner_jilu[1]=temp*1000;
	temp=com_in_buf[count-9]-0x30;
    jiner_jilu[1]+=temp*100;
	temp=com_in_buf[count-8]-0x30;
    jiner_jilu[1]+=temp*10;
    temp=com_in_buf[count-7]-0x30;
    jiner_jilu[1]+=temp;	
	
	
	 temp=com_in_buf[count-6]-0x30;
    jiner_jilu[2]=temp*1000;
	temp=com_in_buf[count-5]-0x30;
    jiner_jilu[2]+=temp*100;
	temp=com_in_buf[count-4]-0x30;
    jiner_jilu[2]+=temp*10;
    temp=com_in_buf[count-3]-0x30;
    jiner_jilu[2]+=temp;

	 ok=2;
   } 
  count=0;
 }
// UCSRB|=BIT(RXCIE); //使能接收中断

}