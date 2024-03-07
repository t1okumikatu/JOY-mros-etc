#include "motor.h"

Motor::Motor() { 
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
  
  ledcSetup(CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_BIT);
  ledcSetup(CHANNEL_1, LEDC_BASE_FREQ, LEDC_TIMER_BIT);
  ledcSetup(CHANNEL_2, LEDC_BASE_FREQ, LEDC_TIMER_BIT);
  ledcSetup(CHANNEL_3, LEDC_BASE_FREQ, LEDC_TIMER_BIT);

  ledcAttachPin(AIN1, CHANNEL_0);//right motor pwm
  ledcAttachPin(AIN2, CHANNEL_1);
  ledcAttachPin(BIN1, CHANNEL_2);//left motor pwm
  ledcAttachPin(BIN2, CHANNEL_3);
}
void Motor::speed(int Lpwm, int Rpwm) {
  int Rplmi = 0;//0:正転  1:逆転
  int Lplmi = 0;//0:正転  1:逆転
  if (Rpwm > VALUE_MAX) {     // 右設定値異常修正(+)
    Rpwm = VALUE_MAX;
  }
  if (Lpwm > VALUE_MAX) {     // 左設定値異常修正(+)
    Lpwm = VALUE_MAX;
  }

  if(Rpwm < 0){               // 右設定値異常修正(-)
    if (-(Rpwm) > VALUE_MAX) {
      Rpwm = -(VALUE_MAX);
    }
  }
  if(Lpwm < 0){               // 左設定値異常修正(-)
    if (-(Lpwm) > VALUE_MAX) {
      Lpwm = -(VALUE_MAX);
    } 
  }
  
  if((Rpwm < 0) && (-(Rpwm) <= VALUE_MAX)){    // －値を＋値へ変換（右側）
    Rpwm = abs(Rpwm);
    Rplmi = 1; //逆転
  }
  if((Lpwm < 0) && (-(Lpwm) <= VALUE_MAX)){    // －値を＋値へ変換（左側）
    Lpwm = abs(Lpwm);
    Lplmi = 1; //逆転
 }
 if((Lplmi == 0) && (Rplmi == 0)){       // 前進     
    ledcWrite(0, Lpwm);
    ledcWrite(1, 0);
    ledcWrite(2, Rpwm);
    ledcWrite(3, 0);   
 }
 if((Lplmi == 1) && (Rplmi == 1)){       // 後進    
    ledcWrite(0, 0);
    ledcWrite(1, Lpwm);
    ledcWrite(2, 0);
    ledcWrite(3, Rpwm);   
 }
 if((Lplmi == 1) && (Rplmi == 0)){       // 左回転     
    ledcWrite(0, 0);
    ledcWrite(1, Lpwm);
    ledcWrite(2, Rpwm);
    ledcWrite(3, 0);   
 }
 if((Lplmi == 0) && (Rplmi == 1)){       // 右回転     
    ledcWrite(0, Lpwm);
    ledcWrite(1, 0);
    ledcWrite(2, 0);
    ledcWrite(3, Rpwm);   
 }
}
void Motor::brake(uint32_t){
  ledcWrite(0, 255);
  ledcWrite(1, 255);  
  ledcWrite(2, 255);
  ledcWrite(3, 255);  
}

