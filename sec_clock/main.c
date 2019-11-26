#include <reg51.h>

enum
{
	L1,
	L2,
	L3,
	L4,
	L5,
	L6,
	L7,
	L8
};

sbit begin=P3^0;
sbit stop=P3^1;
sbit rst=P3^2;

unsigned char count=0;
unsigned char count_flag=0;
unsigned char show_flag=L1;

int clock_num_sec=0;
int clock_num_min=0;
int clock_num_hour=0;

unsigned char ms1=0;
unsigned char ms2=0;

unsigned char sec1=0;
unsigned char sec2=0;

unsigned char min1=0;
unsigned char min2=0;

unsigned char houer1=0;
unsigned char houer2=0;

char num_tab[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
char location_tab[10]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};

void Dispaly(unsigned char location,unsigned char num,unsigned char dp);
void Device_Init();
void Delay(int i);
void Show();

void main()
{
	Device_Init();
	while(1)
	{
		if(begin==0)
		{
			count_flag=1;
		}
		else if(stop==0)
		{
			count_flag=0;
		}
		
		if(rst==0)
		{
			count_flag=0;
			count=0;
			clock_num_sec=0;
			clock_num_min=0;
			clock_num_hour=0;
		}
		
		
		
		
		ms1=count/10;
		ms2=count%10;
		
		sec1=clock_num_sec/10;
		sec2=clock_num_sec%10;
		
		min1=clock_num_min/10;
		min2=clock_num_min%10;

		houer1=clock_num_hour/10;
		houer2=clock_num_hour%10;

//		Dispaly(L1,houer1,0);
//		Dispaly(L2,houer2,1);
//		Dispaly(L3,min1,0);
//		Dispaly(L4,min2,1);
//		Dispaly(L5,sec1,0);
//		Dispaly(L6,sec2,1);
//		Dispaly(L7,ms1,0);
//		Dispaly(L8,ms2,1);

			
	}


}

void Show()
{
	switch(show_flag)
	{
		case L1: {Dispaly(L1,houer1,0);	break;}
		case L2: {Dispaly(L2,houer2,1);	break;}
		case L3: {Dispaly(L3,min1,0);		break;}
		case L4: {Dispaly(L4,min2,1);		break;}
		case L5: {Dispaly(L5,sec1,0);		break;}
		case L6: {Dispaly(L6,sec2,1);		break;}
		case L7: {Dispaly(L7,ms1,0);		break;}
		case L8: {Dispaly(L8,ms2,1);		break;}

	}
}

void Dispaly(unsigned char location,unsigned char num,unsigned char dp)
{
	if(location==L1)
	{
		P2=location_tab[L1];
		
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
		
//		Delay(100);
//		P0=0x00;	//消隐
	}
	else if(location==L2)
	{
		P2=location_tab[L2];
		
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
		
//		Delay(100);
//		P0=0x00;	//消隐
	}
	else if(location==L3)
	{
		P2=location_tab[L3];
		
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
		
//		Delay(100);
//		P0=0x00;	//消隐
	}
	else if(location==L4)
	{
		P2=location_tab[L4];
		
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
		
//		Delay(100);
//		P0=0x00;	//消隐
	}
	else if(location==L5)
	{
		P2=location_tab[L5];
		
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
		
//		Delay(100);
//		P0=0x00;	//消隐
	}
	else if(location==L6)
	{
		P2=location_tab[L6];
		
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
		
//		Delay(100);
//		P0=0x00;	//消隐
	}
	else if(location==L7)
	{
		P2=location_tab[L7];
		
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
		
//		Delay(100);
//		P0=0x00;	//消隐
	}
	else if(location==L8)
	{
		P2=location_tab[L8];
		
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
		
//		Delay(100);
//		P0=0x00;	//消隐
	}
}

void Device_Init()
{
	P0=0x00;
	P2=0x00;
	
	TMOD=0x11;
	//计时
	ET1=1;
	TH1=(65535-10000)/256;
	TL1=(65535-10000)%256;	//10ms
	//显示
	ET0=1;
	TH0=(65535-1000)/256;
	TL0=(65535-1000)%256;	//10ms
	
	
//	IT0=1;
//	EX0=1;
//	PX0=1;
//	
//	IT1=1;
//	EX1=1;
//	PX1=1;
	
	EA=1;
	
	TR1=1;
	TR0=1;
}

void Timer1_Int()	interrupt 3
{
	TH1=(65535-10000)/256;
	TL1=(65535-10000)%256;
	
	if(count_flag)
	{
		count++;
		if(count>100)
		{
			count=0;
			
			clock_num_sec++;
			if(clock_num_sec>59)
			{
				clock_num_min++;
				clock_num_sec=0;
			}
				
			if(clock_num_min>59)
			{
				clock_num_hour++;
				clock_num_sec=0;
				clock_num_min=0;
			}
			
			if(clock_num_hour>23)
			{
				clock_num_hour=0;
				clock_num_sec=0;
				clock_num_min=0;
			}
		}
	}
}

void Timer0_Int()	interrupt 1
{
	TH0=(65535-1000)/256;
	TL0=(65535-1000)%256;
	
	show_flag++;
	if(show_flag>L8)
	{
		show_flag=L1;
	}
	Show();

}

void Delay(int i)
{
	while(i--);       
}

//void Stop_Int() interrupt 0
//{
//	count_flag=!count_flag;
//}

//void Rst_Int() interrupt 2
//{
//	count=0;
//	clock_num_sec=0;
//	clock_num_min=0;
//	clock_num_hour=0;
//}

