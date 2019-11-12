#include <reg51.h>

sbit RED=P2^0;
sbit GREEN=P2^1;
unsigned char show_flag=1;
int count=0;
int time=20;

const char num_tab[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

void Device_Init();
void Delay(int i);

int main()
{
	Device_Init();
	while(1)
	{
		if(time<10)
		{
			P0=num_tab[time];
			Delay(100);
		}
		else 
			P0=0x00;
	
		if(show_flag)
		{
			RED=0;
			GREEN=1;
		}	
		else
		{
			RED=1;
			GREEN=0;
		}
	}

	
}

void Device_Init()
{
	RED=0;
	GREEN=0;
	
	TMOD=0x01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	ET0=1;
	TR0=1;
	
	EA=1;
}

void Delay(int i)
{
	while(i--);       
}

void Delay20s()	interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	count++;
	
	if(count%20==0)
		time--;
	
	if(count>400)
	{
		show_flag=!show_flag;
		time=20;
		count=0;
	}
}