#include <reg51.h>

sbit device=P3^1;
sbit led=P1^0;

unsigned char error_callback=0;
unsigned char error_flag=0;
unsigned char count=0;

unsigned char Display[9]={0x00,0x01,0x03,0x07,0x0f,0x1f,0x3f,0x7f,0xff};

void Device_Init();
void Delay(unsigned int time);
void Display_LED();

int main()
{
	Device_Init();
	
	while(1)
	{
		if(error_callback==0)
			Display_LED();
		else 
			P2=0x00;
	}

	
}

void Report_Error() interrupt 0
{
	count++;
	if(count>3)
	{
		error_callback=1;
		led=1;
	}
}

void Repair_Error() interrupt 2
{
	count=0;
	error_callback=0;
	led=0;
}

void Device_Init()
{
	led=0;
	IT0=1;
	EX0=1;
	IT1=1;
	EX1=1;
	EA=1;
}

void Display_LED()
{
	unsigned char i;
	for(i=0;i<9;i++)
	{
		P2=Display[i];
		Delay(50);
	}
	for(i=8;i>0;i--)
	{
		P2=Display[i];
		Delay(50);
	}
}

void Delay(unsigned int time)
{
	unsigned char i,j;
	for(i=0;i<time;i++)
		for(j=0;j<125;j++);
}