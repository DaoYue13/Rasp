#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define ADC_ADDRESS 0x48 // ADC I2C 주소

// ADC 채널에서 값을 읽는 함수
int readADC(int fd, int channel) {
    wiringPiI2CWrite(fd, channel); // 채널 설정
    return wiringPiI2CRead(fd); // 값 읽기
}

int main(void) {
    int fd = wiringPiI2CSetup(ADC_ADDRESS);
    if (fd == -1) {
        printf("I2C 설정 실패!\n");
        return 1;
    }

    while (1) {
        int jodo = readADC(fd, 0); // 조도 센서 값을 0번 채널에서 읽기
        float jodof = (float)(jodo / 255.0 * 5.0);
        printf("Light sensor input level = %d (%.1fv)\n", jodo, jodof);
        delay(500);

        int ondo = readADC(fd, 1); // 온도 센서 값을 1번 채널에서 읽기
        float ondof = (float)(ondo / 255.0 * 5.0);
        printf("Temperature sensor input level = %d (%.1fv)\n", ondo, ondof);
        delay(500);
        
        int vr = readADC(fd, 3); // VR 값을 3번 채널에서 읽기   //p6 출력
        float vrf = (float)(vr / 255.0 * 5.0);
        printf("VR input level = %d (%.1fv)\n", vr, vrf);
        delay(500);
    }

    return 0;
}
