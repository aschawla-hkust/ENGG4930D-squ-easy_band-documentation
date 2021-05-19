int motorPin = 6;
//int led = 4;
int BUTTON = 13;
int BUTTONstate = 0;
int interval = 6000; //Vibrate after every 6 seconds
int led1 = 5;
int led2 = 4;
int led3 = 3;
int success = 1;

unsigned long previousMillis = 0; //Count time of last vibration

void setup(){ //Setup Devices
  pinMode(motorPin, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(BUTTON, INPUT);
  Serial.begin(9600);
}

void loop() {
   if (digitalRead(BUTTON)==HIGH){ //Detect button press
      digitalWrite(motorPin, LOW);
      if(success==3){
        digitalWrite(led1,HIGH);
        digitalWrite(led2,HIGH);
        digitalWrite(led3,HIGH);
      }
      else if(success==2){
        digitalWrite(led1,HIGH);
        digitalWrite(led2,HIGH);
      }
      else if(success==1){
        digitalWrite(led1,HIGH);
      }
      else{
        digitalWrite(led1,LOW);
        digitalWrite(led2,LOW);
        digitalWrite(led3,LOW);
        success = 0;
      }
      previousMillis = millis(); //Vibration timer starts from button press
      success += 1;
      delay(1000);
  }                            
  else{                        
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    unsigned long currentMillis = millis();
    Serial.print(currentMillis); Serial.print("   "); Serial.println(previousMillis);
    if (((currentMillis - previousMillis) >= interval) && ((currentMillis - previousMillis) <= (interval+3000))){ //Checks if long interval has passed between reminders and limits vibration to 3s
       digitalWrite(motorPin, 128);  
    }
    else{
       digitalWrite(motorPin, LOW);    
       if((currentMillis - previousMillis) >= (interval+3000)){ //Once finished vibrating, resets reminder by changing previousMillis to next vibration time
          previousMillis += interval; 
       } 
    }
  }
}
