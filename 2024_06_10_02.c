#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    // WiringPi 라이브러리 초기화
    if (wiringPiSetup() == -1) {
        printf("WiringPi setup failed!\n");
        return 1;
    }

    pinMode(0, OUTPUT);
    pinMode(1, INPUT);

    while (1)
    {
        digitalWrite(0, HIGH);
        delay(1000); // 1초 대기
        digitalWrite(0, LOW);
        delay(1000); // 1초 대기
    }

    return 0;
}

