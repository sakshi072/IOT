#include<SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);
int relay = 7;
byte relay_state = LOW;
void Switchrelayon();
void Switchrelayoff();
float onTime = 1;
float cycleTime = 5;
//unsigned long startTime = millis();

void setup() {
  pinMode(relay, OUTPUT);
  // Since Normally Open Configuration used therefore relay output is INVERSED
  digitalWrite(relay, HIGH);
  Serial.begin(9600);
  mySerial.begin(9600);
}

void Switchrelayon() {
  if (relay_state == LOW) {
    digitalWrite(relay, LOW);
    relay_state = HIGH;
    Serial.println("Relay ON");
  }
  else {
    Serial.println("Relay already ON");
  }
}

void Switchrelayoff() {
  if (relay_state == HIGH) {
    digitalWrite(relay, HIGH);
    relay_state = LOW;
    Serial.println("Relay OFF");
  }
  else {
    Serial.println("Relay already OFF");
  }
}

void loop() {
  float startTime = millis();
  //Serial.println(startTime);
  //Serial.println(cycleTime * 60000);
  //Serial.println((startTime + (cycleTime * 60000)) - millis());
  while (startTime + (cycleTime * 60000) - millis() > 0) {
    if (startTime + (onTime * 60000) - millis() > 0) {
      //Serial.println(cycleTime);
      //Serial.println(startTime);
      //Serial.println(onTime);
      //Serial.println(onTime*60000);
      //Serial.println(millis());
      //Serial.println((startTime + (onTime * 60000)) - millis());
      Switchrelayon();
    }
    else {
      Switchrelayoff();
    }
  }
}
