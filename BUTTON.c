#include <stdio.h>
#include <wiringPi.h>
#include <signal.h>
#include <stdlib.h>

#define LED_A 0
#define LED_B 1
#define LED_C 2
#define BUTTON 3

void cleanup(int signum) {
    digitalWrite(LED_A, LOW);
    digitalWrite(LED_B, LOW);
    digitalWrite(LED_C, LOW);
    exit(0);
}

int main(void) 
{
    signal(SIGINT, cleanup);

    if(wiringPiSetup() == -1) {
        printf("프로그램을 초기화하지 못했습니다.\n");
        return 1;
    }

    pinMode(LED_A, OUTPUT);
    pinMode(LED_B, OUTPUT);
    pinMode(LED_C, OUTPUT);
    pinMode(BUTTON, INPUT);

    pullUpDnControl(BUTTON, PUD_UP);
   
    digitalWrite(LED_A, LOW);
    digitalWrite(LED_B, LOW);
    digitalWrite(LED_C, LOW);

    int arr[3] = {LED_A, LED_B, LED_C};
 
    while(1) {
        int buttonState = digitalRead(BUTTON);

        if(buttonState == LOW) {
            for(int i = 0; i < 3; i++) {
                digitalWrite(arr[i], HIGH);
                delay(300);
                digitalWrite(arr[i], LOW);
                delay(300);
            }
        }
    }

    return 0;
}

