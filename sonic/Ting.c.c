

#include <stdio.h>

int main(int argc, char **argv)
{

#define TRIG 8  //나중에 수정할 때 더 편하게
#define ECHO 9

void TriggerDist() //함수와 시키기
{
	//Trigger signal
	digitalWrite(TRIG, 1);   // 첫번째 파영이 만들어짐
	delayMicroseconds(10);
	digitalWrite(TRIG, 0);
	delayMicroseconds(200); //200 * 0.34 = 68mm -> 6.8cm 데이터는 무시 버스트 대기
	
	return 0;
}

