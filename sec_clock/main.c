#include <reg51.h>

sbit location1=P2^0;
sbit location2=P2^1;
sbit location3=P2^2;
sbit location4=P2^3;

enum
{
	L1=1,
	L2=2,
	L3=3,
	L4=4
};

unsigned char count=0;
unsigned char count_flag=1;

int clock_num_sec=0;
int clock_num_min=0;

unsigned char num1=0;//千位
unsigned char num2=0;//百位
unsigned char num3=0;//十位
unsigned char num4=0;//个位

char num_tab[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

void Dispaly(unsigned char location,unsigned char num,unsigned char dp);
void Device_Init();
void Delay(int i);

void main()
{
	Device_Init();
	while(1)
	{
		num4=clock_num_min/10;
		num3=clock_num_min%10;
		
		num2=clock_num_sec/10;
		num1=clock_num_sec%10;
		
		Dispaly(L1,num4,0);
		Dispaly(L2,num3,0);
		Dispaly(L3,num2,0);
		Dispaly(L4,num1,0);		

	}


}

void Dispaly(unsigned char location,unsigned char num,unsigned char dp)
{
	if(location==L1)
	{
		location1=0;
		location2=1;
		location3=1;
		location4=1;
		
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
		
		Delay(100);
		P0=0x00;	//消隐
	}
	else if(location==L2)
	{
		location1=1;
		location2=0;
		location3=1;
		location4=1;
		
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
		
		Delay(100);
		P0=0x00;	//消隐
	}
	else if(location==L3)
	{
		location1=1;
		location2=1;
		location3=0;
		location4=1;
		
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
		
		Delay(100);
		P0=0x00;	//消隐
	}
	else if(location==L4)
	{
		location1=1;
		location2=1;
		location3=1;
		location4=0;
		
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
		
		Delay(100);
		P0=0x00;	//消隐
	}

}

void Device_Init()
{
	P0=0x00;
	
	location1=0;
	location2=0;
	location3=0;
	location4=0;
	
	TMOD=0x10;
	ET1=1;
	TH1=(65535-50000)/256;
	TL1=(65535-50000)%256;	//50ms
	
	IT0=1;
	EX0=1;
	PX0=1;
	
	IT1=1;
	EX1=1;
	PX1=1;
	
	EA=1;
	TR1=1;

	

	
	
}

void Timer1_Int()	interrupt 3
{
	TH1=(65535-50000)/256;
	TL1=(65535-50000)%256;	//50ms
	if(count_flag)
	{
		count++;
		if(count>20)
		{
			count=0;
			
			clock_num_sec++;
			if(clock_num_sec>60)
			{
				clock_num_min++;
				clock_num_sec=0;
			}
				
			if(clock_num_min>99)
			{
				clock_num_sec=0;
				clock_num_min=0;
			}

				
			
		}
	}

}

void Delay(int i)
{
	while(i--);       
}

void Stop_Int() interrupt 0
{
	count_flag=!count_flag;
}

void Rst_Int() interrupt 2
{
	clock_num_sec=0;
	clock_num_min=0;
}

