void bluetooth(){
  float voltage;
  if (Serial.available()) {//ESP32からdata
    String sendData = Serial.readStringUntil(';');
    SerialBT.print("voltage ");
    SerialBT.println(voltage);
    //SerialBT.print("BTsendData");
    //SerialBT.println(sendData);
  }

  if (SerialBT.available()) {//スマホからdata
    String s = SerialBT.readStringUntil(';');
    char inkey= s.charAt(0);
    switch(inkey){
      case 's':       
         motor.brake(0);
        SerialBT.println("STOP");
        delay(3000);  
        break;
    }
  }
}
  /*
      case 'b': 
        servoClamp.gripclose150();//bすぐ閉める
        Serial.println("gripclose150");  
        break; 
       case 'c':                                                                            
        break;
       case 'd':
        servoClamp.shoulderclose();//5dショルダーゆっくりおろす
        Serial.println("shoulderclose");   
        delay(200);     
        break;
        case 'e': //ゆっくりあげる
        servoClamp.shoulderopen();//eショルダースロー開く
        Serial.println("shoulderopen");                    
        delay(200);                      
        break;
        case 'f':  
        servoClamp.shoulderopen130();//ショルダースロー少し開く
        Serial.println("shoulderopen130");   
        delay(2000);
         Motor();
        motor.brake(0);   
        delay(200);         
        break;
        case 'i': 
        servoClamp.gripopen40();//iすぐ開
        Serial.println("gripopen40");
        break;
         case 'j': 
        servoClamp.gripopen();//jゆっくり開
        Serial.println("gripopen");
        Motor();
        delay(200);
        motor.brake(0);
        delay(200);           
        break;
        case 'g'://forward 
        Motor();
        delay(100); 
        motor.forward(170);  
        delay(1200);                  
        break;
        default:
        break; 
        case 'k':
        Motor(); 
        delay(100); 
        motor.back(170);  
        delay(1000);
        break;       
        case 'h':   //stop
        mydetach();    
        Motor();
        motor.brake(0);   
        delay(200);                  
        break;
        case 'l':   //gripdetach   17  
        servoClamp.myservogrip.detach(); 
        delay(200);                 
        break;
        case 'm':   //sholderdetach  16
        servoClamp.myservoshou.detach();
        delay(200);                   
        break;
        case 'n':   //sholderclose150  16
        servoClamp.shoulderclose150();//nショルダーすぐおろす
        Serial.println("shoulderclose150");   
        delay(200);     
        break;
        case 'o':  
        servoClamp.shoulderopen40();//ショルダーすぐ上げる
        Serial.println("shoulderopen40");   
        delay(2000);
        case 't':   //TEST_Mode
         while(1){
         SerialBT.println("TEST_Mode"); 
         Serial.println("TEST_Mode");
          bluetooth();              
         }
        break;
    case 's':   //Start_Mode
         SerialBT.println("Start_Mode");  
         Serial.println("Start_Mode");                
        break;
       
       
  }     
    } 
    */              
  
