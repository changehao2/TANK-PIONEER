#include <SoftwareSerial.h>

// SRF05
#define trig 4
#define echo 3
#define trigLeft 12 // Upgrade
#define echoLeft 2  // Upgrade
#define trigRight 7  // Upgrade 
#define echoRight 8  // Upgrade

//Hong ngoai
#define sensorLeft A0
#define sensorCenter A1
#define sensorRight A2
#define Enable A3
#define sLeft A5  // Upgrade
#define sRight A4 // Upgrade

#define motorLeft1 5 //PWM
#define motorLeft2 6 // check more
#define motorRight1 9 //PWM
#define motorRight2 10 // check more
// #define TX 7 // bluetooth pin RX
// #define RX 8 // bluetooth pin TX
// SoftwareSerial mySerial(RX, TX); // RX, TX

void setup() {
  // put your setup code here, to run once:
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trigLeft, OUTPUT);
  pinMode(echoLeft, INPUT);
  pinMode(trigRight, OUTPUT);
  pinMode(echoRight, INPUT);

  pinMode(motorLeft1, OUTPUT);
  pinMode(motorLeft2, OUTPUT);
  pinMode(motorRight1, OUTPUT);
  pinMode(motorRight2, OUTPUT);

  pinMode(Enable, OUTPUT);
  pinMode(sensorRight, INPUT);
  pinMode(sensorCenter, INPUT);
  pinMode(sensorLeft, INPUT);
  pinMode(sLeft, INPUT);
  pinMode(sRight, INPUT);
  
  Serial.begin(9600);

  // mySerial.begin(9600);
}
void goStraight(int speed);
void goBack(int speed);
void turnLeft(int speed);
void turnRight(int speed);
//void bluetooth();
void checkSRF05();
void loop() {
  // put your main code here, to run repeatedly:
//  goStraight(100);
//  goBack(100);
//    turnLeft(100);
//    turnRight(100);
  // if (mySerial.available()>0)
  // {
  // String app = mySerial.readString();
  // Serial.println(app);
  // }

  // bluetooth();
  // checkSRF05();
  Serial.println(analogRead(sensorLeft));
}
void checkSRF05(){
  digitalWrite(trigRight, LOW); // change trig pin
  delayMicroseconds(2);
  digitalWrite(trigRight, HIGH); // change trig pin
  delayMicroseconds(10);
  digitalWrite(trigRight, LOW); // change trig pin
  

 const unsigned long duration= pulseIn(echoRight, HIGH); // change echo pin
 int distance= duration/29/2;
 if(duration==0){
   Serial.println("Warning: no pulse from sensor");
   } 
  else{
      Serial.print("distance to nearest object:");
      Serial.println(distance);
      Serial.println(" cm");
  }
 delay(100);
 }

//void bluetooth(){
////   Serial.print("Bluetooth: ");
//    if (mySerial.available() > 0) {
//      char app = mySerial.read();
////     Serial.println(app);
//      switch (app) {
//          case 'U':
//            goStraight(100);
//            break;
//          case 'B':
//            goBack(100); // can't control motor
//            break;
//          case 'L':
//            turnLeft(150);
//            break;
//          case 'R':
//            turnRight(150);
//            break;           
//          default:
//            stop();
//      }
//  }
//}
void goStraight(int speed){
  int temp = constrain(speed, 0, 255);
  analogWrite(motorLeft1, temp); // Motor left turn forward
  analogWrite(motorRight1, temp); // Motor right turn forward
  digitalWrite(motorLeft2, LOW);
  digitalWrite(motorRight2, LOW);
}
void goBack(int speed){
  int temp = constrain(speed, 0, 255); // ERROR: nothing change with speed
  digitalWrite(motorLeft2, temp); // Reverse 
  digitalWrite(motorRight2, temp); // Reverse
  analogWrite(motorLeft1, LOW);
  analogWrite(motorRight1, LOW);
}
void turnLeft(int speed){
  int temp = constrain(speed, 0, 255);
  analogWrite(motorRight1, temp);
  analogWrite(motorLeft1, LOW);
  digitalWrite(motorLeft2, LOW);
  digitalWrite(motorRight2, LOW);
}
void turnRight(int speed){
  int temp = constrain(speed, 0, 255);
  analogWrite(motorLeft1, temp);
  analogWrite(motorRight1, LOW);
  digitalWrite(motorLeft2, LOW);
  digitalWrite(motorRight2, LOW);
}
void stop(){
  digitalWrite(motorLeft1, LOW);
  digitalWrite(motorRight1, LOW);
  digitalWrite(motorLeft2, LOW);
  digitalWrite(motorRight2, LOW);
}



















