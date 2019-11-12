#include "reg51.h"

sbit KEY1=P3^2;	//��ʼ
sbit KEY2=P3^3;	//ֹͣ

sbit KEY3=P3^0;	//�л�ģʽ ��
sbit KEY4=P3^1;	//�л�ģʽ ��

sbit KEY5=P3^4;	//����
sbit KEY6=P3^5;	//����

sbit KEY7=P3^6;	//�ֶ����� ��/ʵ�ʿ���
sbit KEY8=P3^7; //�ֶ����� ��

char Run_Flag=0;//���б�־ 1��ʼ 0ֹͣ
char Mode=0;//ģʽѡ��
char Manual_Flag=0;//�ֶ���־ 1�ֶ� 0�Զ�
char Manual_Next=0;//�ֶ�״̬���л�LED״̬

char count=0;

unsigned char LED_Display1[9]={0x00,0x01,0x03,0x07,0x0f,0x1f,0x3f,0x7f,0xff};//��1����ʾ��ʽ
unsigned char LED_Display2[4]={0x03,0x0c,0x30,0xc0};//��2����ʾ��ʽ
unsigned char LED_Display3[8]={0x01,0x03,0x07,0x0e,0x1c,0x38,0x70,0xe0};//��3����ʾ��ʽ

void Display(char mode,char manual_flag);
void Manual_Control();
void Delay(unsigned time );
int Speed_Control(int speed);
void Change_Mode();
void Power_Control();

int main()
{
	int speed=50;
	while(1)
	{
		Power_Control();
		if(Run_Flag==1)
		{
			Manual_Control();
			Change_Mode();
			speed=Speed_Control(speed);
			Display(Mode,Manual_Flag);	//����led
			Delay(speed);

		}
		else if(Run_Flag==0)
		{
			P1=0x00;	//����ledȫ���õ�
		}
		
	}
}

void Power_Control()
{
	int i;
	if(KEY1==0)
	{
		Delay(50);
		if(KEY1==0)
		{
			Run_Flag=1;
		}
		
		for(i=0;i<3;i++)
		{
			P1=0xff;
			Delay(100);
			P1=0x00;
			Delay(100);
		}
	}
	
	if(KEY2==0)
	{
		Delay(50);
		if(KEY2==0)
		{
			Run_Flag=0;
		}
	}
}

void Display(char mode,char manual_flag)
{
	if(mode==0)	//ģʽ1
	{
		if(manual_flag==0)	//�ֶ����Ʊ�־
		{
			P1=LED_Display1[count];
			count++;
		}
		else if(manual_flag==1)
		{
			P1=LED_Display1[count];
			if(KEY7==0)
			{
				Delay(50);
				if(KEY7==0)
				{
					count++;
				}
			}
		}
		if(count>9)
		count=0;
	}
	else if(mode==1)	//ģʽ2
	{
		if(manual_flag==0)
		{
			P1=LED_Display2[count];
			count++;
		}
		else if(manual_flag==1)
		{
			P1=LED_Display2[count];
			if(KEY7==0)
			{
				Delay(50);
				if(KEY7==0)
				{
					count++;
				}
			}
		}
		if(count>4)
		count=0;
	}
	else if(mode==2)	//ģʽ3
	{
		if(manual_flag==0)
		{
			P1=LED_Display3[count];
			count++;
		}
		else if(manual_flag==1)
		{
			P1=LED_Display3[count];
			if(KEY7==0)
			{
				Delay(50);
				if(KEY7==0)
				{
					count++;
				}
			}
		}
		if(count>8)
		count=0;
	}
}

void Manual_Control()
{
	if(KEY7==0)
	{
		Delay(50);
		if(KEY7==0)
		{
			Manual_Flag=1;
		}
	}
	if(KEY8==0)
	{
		Delay(50);
		if(KEY8==0)
		{
			Manual_Flag=0;
		}
	}
}


void Change_Mode()
{
	if(KEY3==0)
	{
		Delay(50);
		if(KEY3==0)
		{
			Mode++;
		}
	}
	if(KEY4==0)
	{
		Delay(50);
		if(KEY4==0)
		{
			Mode--;
		}
	}
	if(Mode<0)
		Mode=2;
	if(Mode>2)
		Mode=0;
}

int Speed_Control(int speed)
{
	if(KEY5==0)
	{
		Delay(50);
		if(KEY5==0)
		{
			speed+=10;
		}
	}
	else if(KEY6==0)
	{
		Delay(50);
		if(KEY6==0)
		{
			speed-=10;
		}
	}
	if(speed<0)
		return speed=0;
	if(speed>225)
		return speed=225;
}

void Delay(unsigned int time)
{
	unsigned char i,j;
	for(i=0;i<time;i++)
		for(j=0;j<125;j++);
}

