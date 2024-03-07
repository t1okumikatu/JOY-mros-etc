#ifndef _MOTORCTRL_H_
#define _MOTORCTRL_H_

#include "Arduino.h"

class Motor {
    public:
      Motor();
      void readSensor();
      void speed(int,int);
      void forward(uint32_t);
      void Rforward(uint32_t);
      void Lforward(uint32_t);
      void Rback(uint32_t);
      void Lback(uint32_t);
      void back(uint32_t);
      void brake();
      void coast(uint32_t);
    private :
      const int AIN1=2;
      const int AIN2=4;
      const int BIN1=12;
      const int BIN2=13;
      const int CHANNEL_0 = 0;
      const int CHANNEL_1 = 1;
      const int CHANNEL_2 = 2;
      const int CHANNEL_3 = 3;
      const int LEDC_TIMER_BIT =  8 ;  // PWMの範囲(8bitなら0〜255、9Bitなら0～512, 10bitなら0〜1023)
      const int LEDC_BASE_FREQ = 1000;  // 周波数(Hz)
      const int VALUE_MAX =  255;      // PWMの最大値
};
#endif
