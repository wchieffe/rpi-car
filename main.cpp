// #include <unistd.h>
#include <iostream>
#include <wiringPi.h>
#include <chrono>

#include "libs/PCA9685.h"

#define ENCODER_FR 25

int main(void)
{
    wiringPiSetupGpio();
    pinMode(ENCODER_FR, INPUT);
    
    PCA9685 pwm(1, 0x40);
    pwm.setPWMFreq(50);

    int duty = 1500;

    pwm.setPWM(6, 0);
    pwm.setPWM(7, duty);

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    while(1)
    {
        std::cout << digitalRead(ENCODER_FR);
        if(std::chrono::steady_clock::now() - start > std::chrono::seconds(5))
            break;
        delay(500);
    }

    duty = 0;
    pwm.setPWM(6, 0);
    pwm.setPWM(7, duty);
    
    return 0;
}
