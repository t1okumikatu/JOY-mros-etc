#include <micro_ros_arduino.h>

#include <stdio.h>
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <std_msgs/msg/int32.h>

#if !defined(ESP32) && !defined(TARGET_PORTENTA_H7_M7) && !defined(ARDUINO_NANO_RP2040_CONNECT) && !defined(ARDUINO_WIO_TERMINAL)
#error This example is only avaible for Arduino Portenta, Arduino Nano RP2040 Connect, ESP32 Dev module and Wio Terminal
#endif

#define LED_PIN 16 //マイコン上の青いLEDを指定
#define AD_PIN 34 //ADCのピンを指定

//エラーハンドリング用のマクロ
#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}

//micro-ROS関連で必要となる変数を宣言しておく
rcl_publisher_t publisher;
std_msgs__msg__Int32 msg;
rcl_init_options_t init_options;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;

//micro-ROS関連でエラーが出るとマイコン上の青色LEDが点滅するように設定している
void error_loop(){
  while(1){
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(100);
  }
}

void setup() {
  /*
  wifiの設定を行う。
  マイコンが接続すべきWiFi(つまりmicro_ros_agentを立ち上げるPCが接続されているWiFi)のSSID，
  そのWiFiのパスワード，micro_ros_agentを立ち上げているPCのIPアドレス，port番号を
  指定する必要がある。PCのIPは事前に固定しておいた方が良い。
  */
  Serial.begin(115200);
  set_microros_wifi_transports("Buffalo-G-7900", "46uppwbxjnnnr", "192.168.11.25", 8888);

  //LEDの設定
  pinMode(LED_PIN, OUTPUT);
  //ADCの設定
  analogSetAttenuation(ADC_6db); //追加
  pinMode(AD_PIN, ANALOG); //追加

  delay(2000);

  //micro-ROSの設定
  allocator = rcl_get_default_allocator();
  init_options = rcl_get_zero_initialized_init_options();
  //初期化オプションの作成
  RCCHECK(rcl_init_options_init(&init_options, allocator));
  RCCHECK(rcl_init_options_set_domain_id(&init_options, 1)); //ROS_DOMAIN_IDを設定できる。今回は123としている。
  RCCHECK(rclc_support_init_with_options(&support, 0, NULL, &init_options, &allocator));
  //ノードの作成
  RCCHECK(rclc_node_init_default(&node, "micro_ros_arduino_wifi_node", "", &support));
  //publisherの作成
  RCCHECK(rclc_publisher_init_best_effort(
    &publisher,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
    "/ADC_data"));

  msg.data = 0;
  //セットアップが完了するとLEDが点灯する
  digitalWrite(LED_PIN, HIGH);
}

void loop() {
  msg.data = analogReadMilliVolts(AD_PIN);
  RCSOFTCHECK(rcl_publish(&publisher, &msg, NULL));
}
