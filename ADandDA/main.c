#include <reg51.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
//ADC
sbit ALE=P3^5;	//一个脉冲 锁存地址
sbit START=P3^4;	//开始脉冲
sbit EOC=P3^2;	//转换完成为高 经过非门为低

unsigned char get_value;
const int VREF1=5; //参考电压+
const int VREF2=0; //参考电压-
double vin=0;//输入电压实际
//DAC
int num=0;

char str[20];
char recvbuff='1';

void Device_Init()
{
	TMOD=0x21;
	TH0=(65535-10)/256;
	TL0=(65535-10)%256;
	ET0=1;
	SCON=0x50;
	PCON=0;
	ES=1;
	TH1=0xfd;
	TL1=0xfd; //9600bps
	
	IT0=1;
	EX0=1;
	
	IT1=1;
	EX1=1;
	
	EA=1;
	
	TR1=1;
	TR0=1;
	
	ALE=0;
	START=0;
}

void Pluse()
{
	ALE=1;
	START=1;
	ALE=0;
	START=0;
}

void Send_Str(char *tx,int str_size)
{
	unsigned char i;
	if(str_size>1)
	{
		for(i=0;i<str_size;i++)
		{
			SBUF=*(tx+i);
			while(TI==0);
			TI=0;
		}
	}
	else
	{
		SBUF=*tx;
		while(TI==0);
		TI=0;
	}
}

int main()
{
	Device_Init();
	while(1)
	{
		
//		if(recvbuff=='1')
//		{
//			for(num=0;num<360;num++)
//			{
//				P1=127+127*sin((float)num/180*3.1415);
//			}
//		}
//		else if(recvbuff=='2')
//		{
//			for(num=0;num<255;num++)
//			{
//				P1=num;
//			}
//			for(num=255;num>0;num--)
//			{
//				P1=num;
//			}
//		}
//		else if(recvbuff=='3')
//		{
//			for(num=0;num<255;num++)
//			{
//				P1=num;
//			}
//		}
	}
}


void ADC_Begin() interrupt 2
{
	P2=0xff;
	Pluse();
}

void ADC() interrupt 0
{
	while(EOC==1);
	get_value=P2;
	vin=(get_value/256.0)*(VREF1-VREF2);
	sprintf(str,"   it is %f\n  ",vin);
	Send_Str(str,sizeof(str));
	memset(str,'\0',20);
}

void DAC() interrupt 1
{
	TH0=(65535-1000)/256;
	TL0=(65535-1000)%256;
	
	P1=num;
	
	num++;
	if(num>255)
		num=0;
}

void UART_Recv() interrupt 4
{
	if(RI)
	{
		recvbuff=SBUF;
		RI=0;
	}
}