#include <elapsedMillis.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
#define R 6371
#define TO_RAD (3.1415926536 / 180)


  double dist(double th1, double ph1, double th2, double ph2) {
  double dx, dy, dz;
  ph1 -= ph2;
  ph1 *= TO_RAD, th1 *= TO_RAD, th2 *= TO_RAD;
 
  dz = sin(th1) - sin(th2);
  dx = cos(ph1) * cos(th1) - cos(th2);
  dy = sin(ph1) * cos(th1);
  return asin(sqrt(dx * dx + dy * dy + dz * dz) / 2) * 2 * R;
  }

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
      Serial.write("2");
    }
  }
  else{  
    digitalWrite(ledPin, HIGH);
    pressureTimeElapsed = 0;
  }

  
  if (Serial.available() > 0){ // if there is data
    state = Serial.read();
  }
  char myString[] = '';
  double coordinates[4];

  if (state.length() > 1){

  myString = strtok( state, ",\n");
  
  for (int i=0; i<4; i++){
    coordinates[i]= myString;
    myString = strtok(NULL, ",\n");
  }

  if (dist(coordinates[0], coordinates[2], coordinates[1], coordinates[3]) <76.2){
    Serial.write("0");
    delay(5000);
    Serial.write("1");
  }
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
