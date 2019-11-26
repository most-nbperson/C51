#include <reg51.h>
#include <stdio.h>
#include <string.h>
enum
{
	L1,
	L2,
	L3,
	L4,
	L5,
	L6,
	L7,
	L8,
	
	L9,
	L10,
	L11,
	L12,
	L13,
	L14,
	L15,
	L16,
	
	L17,
	L18,
};

sbit last2=P3^6;
sbit last1=P3^7;


char num_tab[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
char location_tab[10]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};

char sendbuff[]="17150211 1715021103 WJM\n";
char getbuff[19];

unsigned char show_flag=L1;
unsigned char get_ready=0;

int ID_num[18];

void Dispaly(unsigned char location,unsigned char num,unsigned char dp)
{
	
	if(location==L1)
	{
		P2=location_tab[L1];
		P1=0xff;
		last2=1;
		last1=1;
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
	}
	else if(location==L2)
	{
		P2=location_tab[L2];
		P1=0xff;
		last2=1;
		last1=1;
		
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
	}
	else if(location==L3)
	{
		P2=location_tab[L3];
		P1=0xff;
		last2=1;
		last1=1;
		
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
	}
	else if(location==L4)
	{
		P2=location_tab[L4];
		P1=0xff;
		last2=1;
		last1=1;
		
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
	}
	else if(location==L5)
	{
		P2=location_tab[L5];
		P1=0xff;
		last2=1;
		last1=1;
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
	}
	else if(location==L6)
	{
		P2=location_tab[L6];
		P1=0xff;
		last2=1;
		last1=1;
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
	}
	else if(location==L7)
	{
		P2=location_tab[L7];
		P1=0xff;
		last2=1;
		last1=1;
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
	}
	else if(location==L8)
	{
		P2=location_tab[L8];
		P1=0xff;
		last2=1;
		last1=1;
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];

	}
	
	
	else if(location==L9)
	{
		P2=0xff;
		P1=location_tab[L1];
		last2=1;
		last1=1;
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
	}
	else if(location==L10)
	{
		P2=0xff;
		P1=location_tab[L2];
		last2=1;
		last1=1;
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
	}
	else if(location==L11)
	{
		P2=0xff;
		P1=location_tab[L3];
		last2=1;
		last1=1;
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
	}
	else if(location==L12)
	{
		P2=0xff;
		P1=location_tab[L4];
		last2=1;
		last1=1;
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
	}
	else if(location==L13)
	{
		P2=0xff;
		P1=location_tab[L5];
		last2=1;
		last1=1;
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
	}
	else if(location==L14)
	{
		P2=0xff;
		P1=location_tab[L6];
		last2=1;
		last1=1;
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
	}
	else if(location==L15)
	{
		P2=0xff;
		P1=location_tab[L7];
		last2=1;
		last1=1;
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
	}
	else if(location==L16)
	{
		P2=0xff;
		P1=location_tab[L8];
		last2=1;
		last1=1;
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
	}
	
	
	else if(location==L17)
	{
		P2=0xff;
		P1=0xff;
		last2=0;
		last1=1;
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
	}
	else if(location==L18)
	{
		P2=0xff;
		P1=0xff;
		last2=1;
		last1=0;
		if(dp)
			P0=num_tab[num]|0x80;
		else
			P0=num_tab[num];
	}
}

void Show()
{
	switch(show_flag)
	{
		case L1: {Dispaly(L1,ID_num[0],0);	break;}
		case L2: {Dispaly(L2,ID_num[1],0);	break;}
		case L3: {Dispaly(L3,ID_num[2],0);		break;}
		case L4: {Dispaly(L4,ID_num[3],0);		break;}
		case L5: {Dispaly(L5,ID_num[4],0);		break;}
		case L6: {Dispaly(L6,ID_num[5],0);		break;}
		case L7: {Dispaly(L7,ID_num[6],0);		break;}
		case L8: {Dispaly(L8,ID_num[7],0);		break;}
		case L9: {Dispaly(L9,ID_num[8],0);		break;}
		case L10: {Dispaly(L10,ID_num[9],0);		break;}
		case L11: {Dispaly(L11,ID_num[10],0);		break;}
		case L12: {Dispaly(L12,ID_num[11],0);		break;}
		case L13: {Dispaly(L13,ID_num[12],0);		break;}
		case L14: {Dispaly(L14,ID_num[13],0);		break;}
		case L15: {Dispaly(L15,ID_num[14],0);		break;}
		case L16: {Dispaly(L16,ID_num[15],0);		break;}
		case L17: {Dispaly(L17,ID_num[16],0);		break;}
		case L18: {Dispaly(L18,ID_num[17],0);		break;}
																								

	}
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

void Device_Init()
{
	P0=0x00;
	P2=0x00;
	P1=0x00;
	memset(getbuff,'\0',19);
	
	memset(ID_num,0,18);
	
	SCON=0x50;
	PCON=0;
	ES=1;
	
	TMOD=0x21;
	//ÏÔÊ¾
	ET0=1;
	TH0=(65535-1000)/256;
	TL0=(65535-1000)%256;	//10ms
	
	TH1=0xfd;
	TL1=0xfd; //9600bps
	
	EA=1;
	TR0=1;
	TR1=1;
}

int main()
{
	Device_Init();
	Send_Str(sendbuff,sizeof(sendbuff));
	
	
	while(1)
	{
		if(get_ready)
		{
			unsigned char i;
			for(i=0;i<18;i++)
			{
				ID_num[i]=getbuff[i]-'0';
			}
			memset(getbuff,'\0',19);
			get_ready=0;
		}
	}
}


void Timer0_Int()	interrupt 1
{
	TH0=(65535-1000)/256;
	TL0=(65535-1000)%256;
	
	show_flag++;
	if(show_flag>L18)
	{
		show_flag=L1;
	}
	Show();

}

void UART_Recv() interrupt 4
{
	static unsigned char rev_count=0;
	if(RI==1&&get_ready==0)
	{
		getbuff[rev_count]=SBUF;
		if(rev_count>17)
		{
			getbuff[18]='\0';
			rev_count=0;
			get_ready=1;
		}
		else
		{
			rev_count++;
		}
		RI=0;
	}
}