#include <reg51.h>

sbit OUT1=P2^0;
sbit OUT2=P2^1;
sbit OUT3=P2^2;

unsigned char count_200=0;

void Device_Init() {
    OUT1=1; // 20ms  50%
    OUT2=1; // 200ms 25%
    OUT3=1; // 200ms 80%

    TMOD=0x01;
    TH0=(65535-10000)/256;
    TL0=(65535-10000)%256;

    ET0=1;
    EA=1;
		TR0=1;

}

int main() {
    Device_Init();
    while (1);
}

void TIM1_Sev() interrupt 1 
{   //10ms一次
    TH0=(65535-10000)/256;
    TL0=(65535-10000)%256;

    count_200++;
    OUT1=!OUT1;

    if(count_200>5)
    {
        OUT2=0;
    }

    if(count_200>16)
    {
        OUT3=0;
    }

    if(count_200>20)    //一个周期结束
    {
        OUT2=1;
        OUT3=1;
        count_200=0;
    }
}