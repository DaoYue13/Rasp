#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define wPi_Pin 22

int main(int n, char *s[])
{
		if(n<2)
		{
				printf("usage : pwm2 [duty_rate(%%)] [[period]]\n\n");
				printf("	period = 10 ms if empty\n\n");
				return 1;
		}
		
		int dr, drh, drl, period = 10;          
		sscanf(s[1], "%d", &dr);             // 70
		if(n>2) sscanf(s[2], "%d", &period); // 10
		drh= (dr * period) / 100;        // 7 Mark time :7
		drl = period - drh;              // 3 Space time : 3
		
		wiringPiSetup();
		pinMode(wPi_Pin, OUTPUT); // 출력 모드로 설정
		
		pwmSetMode(PWM_MODE_MS); // marc& space -> MS BAL가 초기값으로 되어 있다 
		softPwmCreate(wPi_Pin, drh, period); //계속 루프를 돌리지 않아서 좋다
		//softPwmWrite(wPi_Pin, 70,);
		
		delay(5000);
		softPwmStop(wPi_Pin);
	
		return 0;
}
