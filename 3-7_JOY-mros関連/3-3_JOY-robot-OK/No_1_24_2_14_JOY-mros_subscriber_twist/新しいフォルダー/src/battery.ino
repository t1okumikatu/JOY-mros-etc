const int adcPin = 34;
const int R1 = 5100;
const int R2 = 2000;
//float value=0;
String voltage1;
void battery(){   // Serial.println(voltage);
 const int adcPin = 34;
// float value;
 float value = analogRead(adcPin);
 float voltage = value * (R1+R2)/R2*(3.43/4095);//3.43//6.25
//  for (int i = 0; i < (voltage.length()); i++){
//    SerialBT.write(voltage.charAt(i)); 
 // }
  // SerialBT.print(voltage);
  // SerialBT.println(" volt");
   Serial.print(voltage);
   Serial.println(" volt");
    while(voltage<7){
  float voltage;
   Serial.print("loop ");
   Serial.println(voltage);
  motor.brake(0);
 // bluetooth();
 for(;;){}
 }
}
