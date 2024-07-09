#include <stdio.h>
#include <wiringPi.h>

#define SERVO_PIN 1 // wPi number(12)

int main(int argc, char **argv)
{
	wiringPiSetup();
	pinMode(SERVO_PIN, OUTPUT);
	
	for(int j=0;j<10;j++){
	for(int i=1;i<10;i++)
	{
	digitalWrite(SERVO_PIN, 1);
	delayMicroseconds(1000); //PWM 전체 주파수 상승엣지 두번째 상승엣지 20이라는 뜻 그안에 펄스 폭을 1/20으로 된다
	
	digitalWrite(SERVO_PIN, 0);
	delayMicroseconds(1900); //첫번째 각도를 가져단다
	}
	
	for(int i=1;i<10;i++)
	{
	digitalWrite(SERVO_PIN, 1);
	delayMicroseconds(2000); //PWM 전체 주파수 상승엣지 두번째 상승엣지 20이라는 뜻 그안에 펄스 폭을 1/20으로 된다 20을 맞추기위함
	
	digitalWrite(SERVO_PIN, 0);
	delayMicroseconds(1800); //두번째 각도를 가져단다
	}
}
	
	return 0;
}

