#include <elapsedMillis.h>
int ledleft = 12;
int ledright = 8;
int state = 0;

int sensorpin = A0;
int ledPin = 9;
int force;
elapsedMillis pressureTimeElapsed;
elapsedMillis ledTimeElapsed;
void setup() {
  pinMode(ledleft, OUTPUT);
  pinMode(ledright, OUTPUT);  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledleft, HIGH);
  digitalWrite(ledright, HIGH);
  Serial.begin(9600);
  //default for bluetooth module
}

void loop() {
  force = analogRead(sensorpin);
//  Serial.println("force: ");
//  Serial.println(force);
  if (force < 100){
    if (pressureTimeElapsed > 2000){
      digitalWrite(ledPin, LOW);  
    }
    else{
      digitalWrite(ledPin, HIGH);
    }
  }
  else{  
    digitalWrite(ledPin, HIGH);
    pressureTimeElapsed = 0;
  }

  
  if (Serial.available() > 0){ // if there is data
    state = Serial.read();
  }
  if (state == 0){
    digitalWrite(ledleft, LOW);
    digitalWrite(ledright, LOW);
    ledTimeElapsed = 0;
    
    //Serial.println("OFF"); // send back to phone
  }
  else if (state == '1'){
    digitalWrite(ledright, LOW);
    digitalWrite(ledleft, HIGH);
    if (ledTimeElapsed > 2000){
      digitalWrite(ledleft, HIGH);
      Serial.println("LEFT SIDE VIBRATE"); // send back to phone
      state = 0;
      ledTimeElapsed = 0;
    }
  }  //works

  else if (state == '2'){
    digitalWrite(ledleft, LOW);
    digitalWrite(ledright, HIGH);
    if (ledTimeElapsed > 2000){
      digitalWrite(ledright, HIGH);
      Serial.println("RIGHT SIDE VIBRATE");
      state = 0;
      ledTimeElapsed = 0;
  }


}
}
