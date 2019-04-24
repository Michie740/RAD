int maxVolt = 256;
int ledPin = 13;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < maxVolt; i++){
    analogWrite(ledPin, i);
    Serial.println("up by");
    delay(1);
  }
  for (int i = maxVolt - 1; i > 0; i--){
    analogWrite(ledPin, i);
    Serial.println("down by");

    delay(1);
  }
  
}
