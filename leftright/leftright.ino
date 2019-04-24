#include <elapsedMillis.h>
int ledleft = 12;
int ledright = 8;
int state = 0;
elapsedMillis timeElapsed;
void setup() {
  pinMode(ledleft, OUTPUT);
  pinMode(ledright, OUTPUT);
  digitalWrite(ledleft, LOW);
  digitalWrite(ledright, LOW);
  Serial.begin(9600);
  //default for bluetooth module
}

void loop() {
  timeElapsed = 0;
  if (Serial.available() > 0){ // if there is data
    state = Serial.read();
  }

  if (state == '1'){
    digitalWrite(ledright, LOW);
    digitalWrite(ledleft, HIGH);
    Serial.println("LEFT SIDE VIBRATE"); // send back to phone
    if (timeElapsed > 180){
      digitalWrite(ledleft, LOW);
      state = 0;
    }    
    //state = 1;
  }

  else if (state == '2'){
    digitalWrite(ledleft, LOW);
    digitalWrite(ledright, HIGH);
    Serial.println("RIGHT SIDE VIBRATE");
    if (timeElapsed > 180){
      digitalWrite(ledright, LOW);
      state = 0;
    }
    //state = 2;

  }
  else if (state == 0){
    digitalWrite(ledleft, LOW);
    digitalWrite(ledright, LOW);
  }
}
