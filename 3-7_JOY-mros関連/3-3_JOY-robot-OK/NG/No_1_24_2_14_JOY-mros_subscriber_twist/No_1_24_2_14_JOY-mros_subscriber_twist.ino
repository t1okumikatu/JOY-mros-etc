#include <micro_ros_arduino.h>
#include "motor.h"
#include <stdio.h>
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <geometry_msgs/msg/twist.h>

rcl_subscription_t subscriber;
geometry_msgs__msg__Twist msg;
rclc_executor_t executor;
rcl_allocator_t allocator;
rclc_support_t support;
rcl_node_t node;
int linear_velocity;
int angular_velocity;
int Lpwm=0;
int Rpwm=0;

#define LED_PIN 3
#define AIN1 2    //front
#define AIN2 4    //back
#define BIN1 12    //front
#define BIN2 13    //back
#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}

volatile double speed = 0.0;
double omega = 0;
void error_loop(){
  while(1){
    //digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(100);
  }
}

//twist message cb
void subscription_callback(const void *msgin) {
  const geometry_msgs__msg__Twist * msg = (const geometry_msgs__msg__Twist *)msgin;
  linear_velocity=msg->linear.x *  125 ;
  angular_velocity=msg->angular.z * 50;

  
  Lpwm=linear_velocity - (angular_velocity * 1);
  Rpwm=linear_velocity + (angular_velocity * 1);
  
   /*if(linear_velocity<0){
  angular_velocity=msg->angular.z * 50;
  LBpwm=linear_velocity - (angular_velocity * 1);
  RBpwm=linear_velocity + (angular_velocity * 1);
  }*/
  
  Serial.print("L ");
  Serial.print(Lpwm);
  Serial.print("  R ");
  Serial.println(Rpwm);
  //Lpwm=((msg->linear.x == 0) ? LOW : HIGH)*400;
  //digitalWrite(AIN1, (msg->linear.x == 0) ? LOW : HIGH);
  //digitalWrite(BIN1, (msg->linear.x == 0) ? LOW : HIGH);
  //digitalWrite(LED_PIN, (msg->linear.x == 0) ? LOW : HIGH);list
}
Motor motor = Motor();
void setup() {
  Serial.begin(115200);
  //set_microros_transports();
  set_microros_wifi_transports("Buffalo-G-7900", "46uppwbxjnnnr", "192.168.11.29", 8888);
   //set_microros_wifi_transports("KICK-event", "g6f5R9sP", "192.168.1.163", 8888);
  pinMode(LED_PIN, OUTPUT);
  /*pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);sour/
  pinMode(BIN2, OUTPUT);*/
  
  delay(2000);

  allocator = rcl_get_default_allocator();

   //create init_options１
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

  // create node２
  RCCHECK(rclc_node_init_default(&node, "micro_ros_arduino_node", "", &support));

  // create subscriber３
  RCCHECK(rclc_subscription_init_default(
    &subscriber,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
    "micro_ros_arduino_twist_subscriber"));

  // create executor４
  RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
  RCCHECK(rclc_executor_add_subscription(&executor, &subscriber, &msg, &subscription_callback, ON_NEW_DATA));

}

void loop() {
  motor.speed(Lpwm,Rpwm);
   //motor.Lpwm(Lpwm);
  // motor.Rpwm(Rpwm);
   //motor.LBpwm(LBpwm);
  // motor.RBpwm(RBpwm);
  delay(20);
 //Serial.println(Lpwm,Rpwm);
  RCCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
}
