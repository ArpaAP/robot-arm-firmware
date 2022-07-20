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
    String r = bt.readString();
    Serial.print(r);
    r.trim();

    if (r == "init") {
      sv1.write(60);
      sv2.write(40);
      sv3.write(120);
      sv4.write(90);
    }
    if (r == "left") {
      sv4.write(180);
    }
    if (r == "right") {
      sv4.write(0);
    }
    
  }
  if (Serial.available()) {
    bt.write(Serial.read());
  } 
}
