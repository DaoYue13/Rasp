#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <signal.h>

#define RED 0
#define GREEN 1
#define YELLOW 2
#define SW 3
#define SSW 4

int mode = 0;
int intv = 0;
int tim;
int ps[40] = {0}; // 모든 요소를 0으로 초기화

void Toggle(int pin) {
    ps[pin] = !ps[pin];  // 상태 토글
    digitalWrite(pin, ps[pin]);
}

// 인터럽트 처리기
void gpioisr_1() {
    if (++intv > 8) intv = 0;
    tim = (9 - intv) * 100;
    printf("GPIO interrupt occurred... : %d\n", tim);
}

void gpioisr_2() {
    digitalWrite(RED, 0);
    digitalWrite(GREEN, 0);
    digitalWrite(YELLOW, 0);
    exit(0);
}

// SIGINT 신호 처리기 설정 (Ctrl+C)
void cleanup(int signum) {
    digitalWrite(RED, 0);
    digitalWrite(GREEN, 0);
    digitalWrite(YELLOW, 0);
    printf("프로그램 종료\n");
    exit(0);
}

int main() {
    signal(SIGINT, cleanup); // SIGINT 신호 처리기 설정 (Ctrl+C)

    if (wiringPiSetup() == -1) {
        printf("프로그램 초기화 실패\n");
        return 1;
    }

    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(YELLOW, OUTPUT);
    pinMode(SW, INPUT);
    pinMode(SSW, INPUT);

    wiringPiISR(SW, INT_EDGE_FALLING, gpioisr_1); // GPIO ISR 등록
    wiringPiISR(SSW, INT_EDGE_FALLING, gpioisr_2); // GPIO ISR 등록

    for (;;) { // 무한 루프
        if (mode) {
            Toggle(RED); delay(tim);
            Toggle(GREEN); delay(tim);
            Toggle(YELLOW); delay(tim);
        } else {
            Toggle(RED); delay(tim);
            Toggle(GREEN); delay(tim);
            Toggle(YELLOW); delay(tim);
        }
    }

    return 0;
}
