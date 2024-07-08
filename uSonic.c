#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>

#define TRIG 8  //나중에 수정할 때 더 편하게
#define ECHO 9

extern double Dist();

int main(int argc, char **argv )
{
	wiringPiSetup(); //Pin umbering method : wPi(이 핀 번호로 하겠다)
	pinMode(TRIG, OUTPUT); //송신
	pinMode(ECHO, INPUT); //수신
	
	
	for(;;)
	{
	printf("Distance : %f (cm) \n", Dist());
	delay(500);
	}
	
return 0;
}
