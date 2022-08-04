#include <Servo.h>
#include <SoftwareSerial.h>

#define SV1 4
#define SV2 5
#define SV3 6
#define SV4 7
#define RX 10
#define TX 11

SoftwareSerial bt(TX, RX);

Servo sv1, sv2, sv3, sv4;

/*
 * SV1: 집게
 * SV2: 상단 관절
 * SV3: 하단 관절
 * SV4: 회전
 */

// 최대 집게 각도 68

String splitString(String string, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = string.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(string.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found > index ? string.substring(strIndex[0], strIndex[1]) : "";
}

void setup() {
  Serial.begin(9600);
  bt.begin(9600);
  
  sv1.attach(4);
  sv2.attach(5);
  sv3.attach(6);
  sv4.attach(7);

  sv1.write(60);
  sv2.write(40);
  sv3.write(120);
  sv4.write(90);

}

void loop() {
  if (bt.available()) {
    String data = bt.readStringUntil('\n');
    data.trim();

    String key = splitString(data, '=', 0);
    String value = splitString(data, '=', 1);

    Serial.print("KEY: ");
    Serial.println(key);
    Serial.print("VALUE: ");
    Serial.println(value);
    Serial.println();

    if (data == "init") {
      sv1.write(60);
      sv2.write(40);
      sv3.write(120);
      sv4.write(90);
    }
    if (data == "left") {
      sv4.write(180);
    }
    if (data == "right") {
      sv4.write(0);
    }

    if (key == "s1") {
      sv1.write(value.toInt());
    }
    if (key == "s2") {
      sv2.write(value.toInt());
    }
    if (key == "s3") {
      sv3.write(value.toInt());
    }
    if (key == "s4") {
      sv4.write(value.toInt());
    }

    bt.read();
    
  }
  if (Serial.available()) {
    bt.write(Serial.read());
  } 
}
