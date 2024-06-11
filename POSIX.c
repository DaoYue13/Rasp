#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <wiringPi.h>

// 핀 번호 정의
#define LED_PIN 0
#define BUTTON_PIN 1

// LED 제어 스레드 함수
void *ledControl(void *arg) {
    pinMode(LED_PIN, OUTPUT);
    while (1) {
        digitalWrite(LED_PIN, HIGH);
        delay(500); // 0.5초 대기
        digitalWrite(LED_PIN, LOW);
        delay(500); // 0.5초 대기
    }
    return NULL;
}

// 버튼 상태 읽기 스레드 함수
void *buttonRead(void *arg) {
    pinMode(BUTTON_PIN, INPUT);
    pullUpDnControl(BUTTON_PIN, PUD_UP); // 풀업 저항 설정
    while (1) {
        int buttonState = digitalRead(BUTTON_PIN);
        if (buttonState == LOW) {
            printf("Button pressed!\n");
            delay(200); // 디바운싱을 위해 200ms 대기
        }
    }
    return NULL;
}

int main(void) {
    // WiringPi 초기화
    if (wiringPiSetup() == -1) {
        printf("wiringPi 초기화 실패!\n");
        return 1;
    }

    // 스레드 ID
    pthread_t ledThread, buttonThread;

    // 스레드 생성
    if (pthread_create(&ledThread, NULL, ledControl, NULL) != 0) {
        printf("LED 스레드 생성 실패!\n");
        return 1;
    }

    if (pthread_create(&buttonThread, NULL, buttonRead, NULL) != 0) {
        printf("버튼 스레드 생성 실패!\n");
        return 1;
    }

    // 스레드가 종료될 때까지 대기
    pthread_join(ledThread, NULL);
    pthread_join(buttonThread, NULL);

    return 0;
}

