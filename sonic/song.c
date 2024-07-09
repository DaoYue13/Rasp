#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define wPi_PWM1 23
int PSC = 19;                 // 필요 주파수 계산식: C / P * R 예) 299
const int RANGE = 100;        // R = C / 299 * P
int DUTY = RANGE / 2;

enum { DO = 0, Do, RE, Re, MI, FA, Fa, SL, Sl, LA, La, CI }; // 각 음계에 정수값 매핑
int pitch[] = { 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494 };
int range[12]; // Range Register values
int song1[] = { SL, MI, MI, MI, SL, MI, SL, RE, SL, MI,
                SL, MI, RE, SL, MI, SL, MI, SL, MI, SL,
                RE, SL, FA, MI, FA, SL, -1 }; // -1, 종료를 뜻함

int rythm1[] = { 2, 2, 2, 2, 2, 1, 2, 6, 2, 2,
                 2, 2, 1, 4, 4, 2, 2, 4, 2, 2,
                 6, 2, 2, 2, 6, 2 }; // 4 = 0.5, 8 = 0.25

// 주파수 계산 함수
void calcRange() {
    for (int i = 0; i < 12; i++) {
        range[i] = 19200000 / (PSC * pitch[i]); // 주파수 계산
    }
}

void play(double r)
{
        if(!iFlag) initSound(); // iFlag == 0
        rate =r;
        for(int i=0; song[i] != -1, i++)
        {
            playSound(song[i], rythm1[i]);
        }
        pwmWrite()
}

double rate = 1;

// 음 재생 함수
void playSound(int um, int rhythm) {
    pwmSetClock(PSC); // 프리스케일러 설정
    pwmSetRange(range[um]); // 주파수 범위 설정
    pwmWrite(wPi_PWM1, range[um] / 2); // 50% 듀티 사이클 설정
    
    delay(2000/ (rhythm * rate)); // 리듬에 따른 딜레이
    pwmWrite(wPi_PWM1, 0); // 음 사이에 짧은 간격 추가
    delay(50);
}
int iFlag =0;
void initSound()
{
    wiringPiSetup();
    pinMode(wPi_PWM1)
}
