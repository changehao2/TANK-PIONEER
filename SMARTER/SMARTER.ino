// sieu am
#define trig 4
#define echo 3
#define trigLeft 12 // Upgrade
#define echoLeft 2 // Upgrade
#define trigRight 7 // Upgrade
#define echoRight 8 // Upgrade
// Hong ngoai
#define sensorLeft A0
#define sensorCenter A1
#define sensorRight A2
#define Enable A3
#define sRight A5 // Upgrade
#define sLeft A4 // Upgrade
// motor
#define motorLeft1 5 // PWM
#define motorLeft2 6 // check more
#define motorRight1 9 // PWM
#define motorRight2 10 // check more
int line = 100;
// int line[5] = {1000,100,100,100,1000}; // don't forget delete "line = 600"
int sensor[5];
boolean check=true;
boolean CheckBarrie = true;
void setup()
{
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
void detectWall();
void checkSRF05();
void goStraight(int speed);
void goBack(int speed);
void turnLeft(int speed);
void turnRight(int speed);
void runRound(int speedLeft, int speedRight);
int dataSRF05();
void detectBarrie();
void loop()
{
  // put your main code here, to run repeatedly:
   detectLine();
  //detectWall();
  // turnRight(100,100);
}

// Car follow white line
void detectLine()
{
  sensor[0] = analogRead(sLeft);
  sensor[1] = analogRead(sensorLeft);
  sensor[2] = analogRead(sensorCenter);
  sensor[3] = analogRead(sensorRight);
  sensor[4] = analogRead(sRight);
  int error;
  // if((sensor[0]>line)&&(sensor[1]>line)&&(sensor[2]>line)&&(sensor[3]>line)&&(sensor[4]>line))   //0 0 0 0 0
  // find line code something Bro :))
  // runRound(150, 100);
  // goStraight(150);
  if ((sensor[0] > line) && (sensor[1] > line) && (sensor[2] < line) && (sensor[3] < line) && (sensor[4] < line))
  // 0 0 1 1 1
  //turnRight(220, 50);
  checkLr();
   else if((sensor[0]>line)&&(sensor[1]>line)&&(sensor[2]<line)&&(sensor[3]>line)&&(sensor[4]<line))   //0 0 1 0 1
   //turnRight(150,50);
   checkLr();
  else
    if ((sensor[0] > line) && (sensor[1] > line) && (sensor[2] > line) && (sensor[3] < line) && (sensor[4] < line))
    // 0 0 0 1 1
    turnRight(210, 30);
  //checkLr();
  else
    if ((sensor[0] > line) && (sensor[1] > line) && (sensor[2] > line) && (sensor[3] > line) && (sensor[4] < line))
    // 0 0 0 0 1
    turnRight(222, 100);
  else
    if ((sensor[0] > line) && (sensor[1] > line) && (sensor[2] > line) && (sensor[3] < line) && (sensor[4] > line))
    // 0 0 0 1 0
    turnRight(150, 10);
  else
    if ((sensor[0] > line) && (sensor[1] > line) && (sensor[2] < line) && (sensor[3] < line) && (sensor[4] > line))
    // 0 0 1 1 0
    turnRight(180, 20);
  else
    if ((sensor[0] < line) && (sensor[1] < line) && (sensor[2] < line) && (sensor[3] > line) && (sensor[4] > line))
    // 1 1 1 0 0
    //turnLeft(100, 220);
    checkLl();
   else if((sensor[0]<line)&&(sensor[1]>line)&&(sensor[2]<line)&&(sensor[3]>line)&&(sensor[4]>line))   //1 0 1 0 0
   //turnRight(50,150);
   checkLl();
   else
    if ((sensor[0] < line) && (sensor[1] < line) && (sensor[2] > line) && (sensor[3] > line) && (sensor[4] > line))
    // 1 1 0 0 0
   turnLeft(100, 180);
 //7checkLl();
  else
    if ((sensor[0] < line) && (sensor[1] > line) && (sensor[2] > line) && (sensor[3] > line) && (sensor[4] > line))
    // 1 0 0 0 0
    turnLeft(100, 150);
  else
    if ((sensor[0] > line) && (sensor[1] < line) && (sensor[2] > line) && (sensor[3] > line) && (sensor[4] > line))
    // 0 1 0 0 0
    turnLeft(100, 180);
  else
    if ((sensor[0] > line) && (sensor[1] < line) && (sensor[2] < line) && (sensor[3] > line) && (sensor[4] > line))
    // 0 1 1 0 0
    turnLeft(100, 180);
  else
    if ((sensor[0] > line) && (sensor[1] > line) && (sensor[2] < line) && (sensor[3] > line) && (sensor[4] > line))
    // 0 0 1 0 0
    goStraight(255); // di thang
  else
    if ((sensor[0] > line) && (sensor[1] < line) && (sensor[2] < line) && (sensor[3] < line) && (sensor[4] > line))
    // 0 1 1 1 0
    goStraight(255); // di thang
  // stop(); // Just for checking
}

void checkLr()
{
  detectBarrie(); // Have barrie
    if (CheckBarrie) // If have barrie -> CheckBarrie = false, else CheckBarrie = true
    {
      turnRight(200,100);
      delay(1111);
    }
      CheckBarrie = true;

}

void checkLl()
{
  detectBarrie(); // Have barrie
    if (CheckBarrie) // If have barrie -> CheckBarrie = false, else CheckBarrie = true
    {
      turnLeft(100,200);
      delay(1111);
    }
      CheckBarrie = true;
}
void detectBarrie(){
      stop();
      // delay(2000);
      while(dataSRF05() < 100){
          CheckBarrie = false; // Make tank don't turn away
          do{
            stop();
          }while(dataSRF05() <20);
        goStraight(100); // change PWM here :))) and delay__ 
      delay(500);
      } 
}
void detectWall()
{
  long durationFront, front, durationLeft, left, durationRight, right;
  // sensorFront
  digitalWrite(trig, LOW); //
  delayMicroseconds(2); //
  digitalWrite(trig, HIGH); //
  delayMicroseconds(5); //
  digitalWrite(trig, LOW); //
  durationFront = pulseIn(echo, HIGH); //
  front = durationFront/29.412/2;
  // sensorLeft
  digitalWrite(trigLeft, LOW);
  delayMicroseconds(2);
  digitalWrite(trigLeft, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigLeft, LOW);
  durationLeft = pulseIn(echoLeft, HIGH);
  left = durationLeft/29.412/2;
  // sensorRight
  digitalWrite(trigRight, LOW);
  delayMicroseconds(2);
  digitalWrite(trigRight, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigRight, LOW);
  durationRight = pulseIn(echoRight, HIGH);
  right = durationRight/29.412/2;
  // run
  if (front >= 8 && left <= 16 && right <= 16 && front > left)
  {
    goStraight(80);
     delay(1000);}
   else if (front <= 8 && left >=30 && right <=16 )
  {turnLeft(200,150);
   delay(1000);}
   else if (front <= 8 && left <=16 && right >=30 )
  {turnRight(200,200);
   delay(1000);}
   else if (front >= 8 && front <= 65 && left >=16 && right >=16 ){turnRight(150,100);
    delay(1000);}
   else if (front <= 8 && left <=35 && right <=35 ){turnLeft(100,200);
    delay(1000);}
    // else if (front <= 8 && left <=16 && right >=16 ){turnRight(150,100);
    // delay(1000);}
    // else if (front <= 8 && left >=16 && right <=16 ){turnLeft(100,150);
    // delay(1000);}
  //else if (front > 8 && front < 65)
     // {runRound(200, 100);
       // delay(1000);}
    else
      if (front > 8 && front < 35)
        runRound(120, 255);
    else
      if (front > 8)
      {
        if (left > 0 && left < 13)
        {
          goStraight(80);
          delay(1000);
        }
        else
          if (left >= 15)
          {
            turnLeft(100, 250);
            delay(1000);
          }
        else
          if (left <= 10)
          {
            turnRight(250, 100);
            delay(1000);
          }
      }
    else
      if (left >= 15 && right <= 15 && front <= 10)
      {
        turnLeft(150, 250);
        delay(1000);
      }
    else
      if (left <= 15 && right >= 15 && front <= 10)
      {
        turnRight(250, 150);
        delay(1000);
      }
    else
      if (left >= 15 && right >= 15 && front <= 10)
      {
        turnLeft(150, 250);
        delay(1000);
      }
    else
      if (right <= 15 && left <= 15 && front <= 10)
      {
        turnLeft(150, 250);
        delay(1000);
      }
    else
    {
      goStraight(80);
      delay(1000);
    }
  }
  int dataSRF05(){
    unsigned long time = millis();
    digitalWrite(trig, LOW); // change trig pin
    delayMicroseconds(2);
    digitalWrite(trig, HIGH); // change trig pin
    delayMicroseconds(10);
    digitalWrite(trig, LOW); // change trig pin
    const unsigned long duration = pulseIn(echo, HIGH); // change echo pin
    int distance = duration/29/2;
    return distance;
    // while(time - millis() < 2000){
    // }

  }
  void checkSRF05()
  {
    digitalWrite(trigRight, LOW); // change trig pin
    delayMicroseconds(2);
    digitalWrite(trigRight, HIGH); // change trig pin
    delayMicroseconds(10);
    digitalWrite(trigRight, LOW); // change trig pin
    const unsigned long duration = pulseIn(echoRight, HIGH); // change echo pin
    int distance = duration/29/2;
    if (duration == 0)
    {
      Serial.println("Warning: no pulse from sensor");
    }
    else
    {
      Serial.print("distance to nearest object:");
      Serial.println(distance);
      Serial.println(" cm");
    }
    delay(100);
  }
  // FOR MOTOR
  void goStraight(int speed)
  {
    int temp = constrain(speed, 0, 255);
    analogWrite(motorLeft1, temp); // Motor left turn forward
    analogWrite(motorRight1, temp); // Motor right turn forward
    digitalWrite(motorLeft2, LOW);
    digitalWrite(motorRight2, LOW);
  }
  void goBack(int speed)
  {
    int temp = constrain(speed, 0, 255); // ERROR: nothing change with speed
    analogWrite(motorLeft2, temp); // Reverse
    analogWrite(motorRight2, temp); // Reverse
    digitalWrite(motorLeft1, LOW);
    digitalWrite(motorRight1, LOW);
  }
  void stop()
  {
    digitalWrite(motorLeft1, LOW);
    digitalWrite(motorRight1, LOW);
    digitalWrite(motorLeft2, LOW);
    digitalWrite(motorRight2, LOW);
  }
  void runRound(int speedLeft, int speedRight)
  {
    int temp1 = constrain(speedLeft, 0, 255);
    int temp2 = constrain(speedRight, 0, 255);
    analogWrite(motorLeft1, temp1);
    analogWrite(motorRight1, temp2);
    digitalWrite(motorLeft2, LOW);
    digitalWrite(motorRight2, LOW);
  }
  void turnLeft(int speedLeft, int speedRight)
  {
    int temp1 = constrain(speedLeft, 0, 255);
    int temp2 = constrain(speedRight, 0, 255);
    digitalWrite(motorLeft1, LOW);
    analogWrite(motorRight1, temp2);
    analogWrite(motorLeft2, temp1);
    digitalWrite(motorRight2, LOW);
  }
  void turnRight(int speedLeft, int speedRight)
  {
    int temp1 = constrain(speedLeft, 0, 255);
    int temp2 = constrain(speedRight, 0, 255);
    analogWrite(motorLeft1, temp1);
    digitalWrite(motorRight1, LOW);
    digitalWrite(motorLeft2, LOW);
    analogWrite(motorRight2, temp2);
  }
