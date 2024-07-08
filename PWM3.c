#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define wPi_PWM1 23
int PSC = 19;                 //필요한 주파수를 뽑는 식   C / P * R 예) 299
const int RANGE = 100;        //R = C / 299 * P
int DUTY = RANGE / 2;

enum{DO=0, Do, RE, Re, MI, FA, Fa, SL, Sl, LA, La, CI}; //안에서 순서 대로 기호 대로 정수형 숫자 대입
int pitch[] = {262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494};
int range[12]; 
int song1[] = {SL,MI,MI,MI,SL,MI,SL,RE,SL,MI,
              SL,MI,RE,SL,MI,SL,MI,SL,MI,SL,
              RE,SL,FA,MI,FA,SL,-1}; //종료를 뜻하는것을 알리기 위해
              
int rythm1[] = {2,2,2,2,2,1,2,6,2,2,
               2,2,1,4,4,2,2,4,2,2,
               6,2,2,2,6,2};

void calcRange() // Calc Range values using Pitch data 주파수를 계산하기 위함
{
     for (int i = 0; i < 12; i++) 
     {
        range[i] = 1000000 / pitch[i]; // 19200000 / (PSC * pitch[i]);
     }
}

void playSound(int um, int rhythm) // um : pitch, rhythm
{
    pwmSetClock(PSC);  //Prescaler : ~ 1MHz 까지 컨트롤 가능한
    pwmSetRange(range[um]); //Range 10K = 19.2 M / 19 * x (x=100)
    pwmWrite(wPi_PWM1, range[um]/2); // compare 50% 까지 주면 된다 (거의 대부분 50이 디폴트라고 생각)
    //rythm......
    //delay(2000/rythm)
    delay(rhythm * 150);
    pwmWrite(wPi_PWM1, 0); // 음 사이에 짧은 간격 추가
    delay(50);
}

int main()
{
    if (wiringPiSetup() == -1) {
        printf("wiringPi 초기화 실패\n");
        return 1;
    }
    
    pinMode(wPi_PWM1, PWM_OUTPUT); //여기서 이미 소리는 나가고 있지만 소리가 없음
    pwmSetMode(PWM_MODE_MS);
    calcRange();
    
    for(int i=0; song1[i]!=-1; i++)
    {
        playSound(song1[i], rythm1[i]);
    }
    
    
    return 0;    
}
