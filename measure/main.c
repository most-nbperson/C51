#include <reg51.h>


sbit location1=P2^0;
sbit location2=P2^1;
sbit location3=P2^2;
sbit location4=P2^3;
sbit input=P3^2;

int count=0;
int time=0;
int show_flag=0;
int OKAY=0;

unsigned char num1=0;//千位
unsigned char num2=0;//百位
unsigned char num3=0;//十位
unsigned char num4=0;//个位

char num_tab[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

enum
{
	L1=1,
	L2=2,
	L3=3,
	L4=4
};

void Dispaly(unsigned char location,unsigned char num,unsigned char dp);
void Device_Init();
void Delay(int i);
void Show();


int main()
{
	Device_Init();
	while(1)
	{
		time = count*50 + ((TH0-0x3b)*256+(TL0-0xb0))/1000;
		Show();
	}
}

void Device_Init()
{
	TMOD=0x09;
	
	ET0=1;
	
	TH0=0x3c;
	TL0=0xb0;	//50ms
	
	TR0=1;
	EA=1;
}

void Delay(int i)
{
	while(i--);       
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

void Show()
{
		num4=(time/1000)%10;
		num3=(time/100)%10;
		num2=(time/10)%10;
		num1=time%10;
		
		Dispaly(L1,num4,0);
		Dispaly(L2,num3,0);
		Dispaly(L3,num2,0);
		Dispaly(L4,num1,0);	
}


void Timer1_Int() interrupt 1
{
	TH0=0x3c;   //timer0赋初值
	TL0=0xb0;   //50ms初值
	count++;
	
}

