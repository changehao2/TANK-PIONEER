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
#define sRight A5  // Upgrade
#define sLeft A4 // Upgrade

#define motorLeft1 5 //PWM
#define motorLeft2 6 // check more
#define motorRight1 9 //PWM
#define motorRight2 10 // check more

int line = 100;
//int line[5] = {500,100,100,100,500}; // don't forget delete "line = 600"
int sensor[5];

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
  digitalWrite(Enable, HIGH);
}

void detectLine();
void checkSRF05();
void goStraight(int speed);
void goBack(int speed);
void turnLeft(int speed);
void turnRight(int speed);
void runRound(int speedLeft, int speedRight);

void loop() {
  // put your main code here, to run repeatedly:

  detectLine(); 
}

// Car follow white line
void detectLine(){

  sensor[0] = analogRead(sLeft);
  sensor[1] = analogRead(sensorLeft);
  sensor[2] = analogRead(sensorCenter);
  sensor[3] = analogRead(sensorRight);
  sensor[4] = analogRead(sRight);
  int error;

if((sensor[0]>line)&&(sensor[1]>line)&&(sensor[2]>line)&&(sensor[3]>line)&&(sensor[4]<line))           //0 0 0 0 1
  turnRight(150);// lech trai
  // else if((sensor[0]>line)&&(sensor[1]>line)&&(sensor[2]>line)&&(sensor[3]<line)&&(sensor[4]<line)) //0 0 0 1 1  
  // turnRight(80);// lech trai
  else if((sensor[0]>line)&&(sensor[1]>line)&&(sensor[2]>line)&&(sensor[3]<line)&&(sensor[4]>line))    //0 0 0 1 0
  // turnRight(100);
  runRound(50, 100);// lech trai
  // else if((sensor[0]>line)&&(sensor[1]>line)&&(sensor[2]<line)&&(sensor[3]<line)&&(sensor[4]>line)) //0 0 1 1 0
  // error=1;// lech trai
  else if((sensor[0]>line)&&(sensor[1]>line)&&(sensor[2]<line)&&(sensor[3]>line)&&(sensor[4]>line))    //0 0 1 0 0
  goStraight(120);// di thang
  // else if((sensor[0]>line)&&(sensor[1]<line)&&(sensor[2]<line)&&(sensor[3]<line)&&(sensor[4]>line)) //0 1 1 0 0
  // error=0;// line chu T
  else if((sensor[0]>line)&&(sensor[1]<line)&&(sensor[2]>line)&&(sensor[3]>line)&&(sensor[4]>line))    //0 1 0 0 0
  // turnLeft(100)
  runRound(100,50);// lech phai
  // else if((sensor[0]>line)&&(sensor[1]<line)&&(sensor[2]>line)&&(sensor[3]>line)&&(sensor[4]>line)) //1 1 0 0 0
  // error=-1.5; // lech phai
  else if((sensor[0]<line)&&(sensor[1]>line)&&(sensor[2]>line)&&(sensor[3]>line)&&(sensor[4]>line))    //1 0 0 0 0
  turnLeft(150);// lech phai
  // else if((sensor[0]<line)&&(sensor[1]>line)&&(sensor[2]>line)&&(sensor[3]>line)&&(sensor[4]>line))
  // error=-2.5;// lech phai 
  // else if((sensor[0]<line)&&(sensor[1]<line)&&(sensor[2]<line)&&(sensor[3]>line)&&(sensor[4]>line))
  // error=-3;// cua trai 90 do
  // else if((sensor[0]>line)&&(sensor[1]>line)&&(sensor[2]<line)&&(sensor[3]<line)&&(sensor[4]<line))
  // error=3;// cua phai 90 do
  else if((sensor[0]>line)&&(sensor[1]>line)&&(sensor[2]>line)&&(sensor[3]>line)&&(sensor[4]>line))     //0 0 0 0 0
  {
    // find line code something Bro :))
 //   runRound(150, 100);
 //   stop(); // Just for checking
  }
  
  
 // Serial.println(sensor[0],sensor[1],sensor[2],sensor[3],sensor[4]);
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

// FOR MOTOR
void goStraight(int speed){
  int temp = constrain(speed, 0, 255);
  analogWrite(motorLeft1, temp); // Motor left turn forward
  analogWrite(motorRight1, temp); // Motor right turn forward
  digitalWrite(motorLeft2, LOW);
  digitalWrite(motorRight2, LOW);
}
void goBack(int speed){
  int temp = constrain(speed, 0, 255); // ERROR: nothing change with speed
  analogWrite(motorLeft2, temp); // Reverse 
  analogWrite(motorRight2, temp); // Reverse
  digitalWrite(motorLeft1, LOW);
  digitalWrite(motorRight1, LOW);
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

void runRound(int speedLeft, int speedRight){
  int temp1 = constrain(speedLeft, 0, 255);
  int temp2 = constrain(speedRight, 0, 255);  
  analogWrite(motorLeft1, temp1);
  analogWrite(motorRight1, temp2);
  digitalWrite(motorLeft2, LOW);
  digitalWrite(motorRight2, LOW);
}



















