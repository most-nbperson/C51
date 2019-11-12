#include <reg51.h>

sbit RED=P2^0;
sbit GREEN=P2^1;
//unsigned char emergency_flag=0;
void Device_Init();
int count=0;

int main()
{
	Device_Init();
	GREEN=1;
	while(1);
}

void Device_Init()
{
	RED=0;
	GREEN=0;
	
	IT0=1;
	EX0=1;
	PX0=1;
	TMOD=0x01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	ET0=1;
	TR0=1;
	
	EA=1;
}

void Delay10s()	interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	count++;
	
	if(count==100)
	{
		if(RED==1&&GREEN==0)
		{
			RED=0;
			GREEN=1;
		}
		else if(GREEN==1&&RED==0)
		{
			RED=1;
			GREEN=0;
		}
		count=0;
	}
}

void Emergency_Situation() interrupt 0
{
	RED=1;
	GREEN=0;
	count=0;
}