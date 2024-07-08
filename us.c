#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>

#define TRIG 8  //나중에 수정할 때 더 편하게
#define ECHO 9

double Dist() //함수와 시키기
{
	//Trigger signal
	digitalWrite(TRIG, 1);   // 첫번째 파영이 만들어짐
	delayMicroseconds(10);
	digitalWrite(TRIG, 0);
	delayMicroseconds(200); //200 * 0.34 = 68mm -> 6.8cm 데이터는 무시 버스트 대기
	
	//Wait for Echo signal
	while(digitalRead(ECHO) != 0); //wait for burst Stert (0이 될때 까지 잠시 기달리는거 초기화 작업이라고 생각)
	
	while(digitalRead(ECHO) != 1); //wait for Echo HIGH 신호 인지 세번째 옛지가 검출 t1이 카운터
	int t1 = micros(); // Get start time (in micro - second) 현제 타이머에 카운터값을 돌려준다
	while(digitalRead(ECHO) != 0); // Echo Low 하이 에서 내려오는것 감지 폴링옛지를 감지
	int t2 = micros(); // Get end time
	//double dist = (t2 - t1) * (((340 / 1000000) /2) *100);
	return  Dist  (t2 - t1) * 0.017;
}
