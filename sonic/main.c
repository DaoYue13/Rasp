#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <pthread.h>

#define wPi_PWM1 23


// 외부 함수 선언
extern void calcRange();
extern void playSound(int um, int rhythm);
extern double Dist();

extern int song1[];
extern int rythm1[];

void initSound(int n, char *v[]) 
{
	double d1 = rate;
	if(n>1) sscanf(v[1], & "%lf",&d1) rate = d1;
	
	
    if (wiringPiSetup() == -1) {
        printf("프로그램을 초기화하지 못했습니다.\n");
        return 1;
    }

    pinMode(wPi_PWM1, PWM_OUTPUT); // PWM 출력 모드 설정
    calcRange(); // 주파수 범위 계산

    int i = 0;
    while (song1[i] != -1) {
        playSound(song1[i], rythm1[i]);
        i++;
    }
    
    wiringPiSetup(); //Pin umbering method : wPi(이 핀 번호로 하겠다)
	pinMode(TRIG, OUTPUT); //송신
	pinMode(ECHO, INPUT); //수신
	
	
	for(;;)
	{
	double d =Dist();
	printf("Distance : %.2f (cm) \n", d);
	double r = (d>100) ? 1.0 : (d < 50) ? 2.0 : 1.5;
	play(r);
	delay(500);
	}

    return 0;
}


