#define Kp 35
#define Ki 0
#define Kd 0
#define initial_motor_speed 150

#define trig 4
#define echo 3
#define sensorLeft A0
#define sensorCenter A1
#define sensorRight A2
#define Enable A3

int error = 0;
int I = 0;
int previous_error = 0;
int line = 800;
int PID_value;
bool enaMotor = true;

void read_sensor_values()
{
  int sensor[3];
  sensor[0] = analogRead(sensorLeft);
  sensor[1] = analogRead(sensorCenter);
  sensor[2] = analogRead(sensorRight);

  if ((sensor[0] < line) && (sensor[1] < line ) && (sensor[2] > line))
    error = 1;
  else if ((sensor[0] < line) && (sensor[1] > line ) && (sensor[2] < line))
    error = 0;
  else if ((sensor[0] > line) && (sensor[1] < line ) && (sensor[2] < line))
    error = -1;
}

void calculate_pid()
{
  int P = error;
  I = I + error;
  int D = error - previous_error;
  PID_value = (Kp * P) + (Ki * I) + (Kd * D);
  previous_error = error;
}

void motor_control(bool enable)
{
  // Calculating the effective motor speed:
  if (enable) {
    int left_motor_speed = initial_motor_speed + PID_value;
    int right_motor_speed = initial_motor_speed - PID_value;

    // The motor speed should not exceed the max PWM value
    constrain(left_motor_speed, 0, 255);
    constrain(right_motor_speed, 0, 255);

    analogWrite(5, left_motor_speed);  //Left Motor Speed
    analogWrite(9, right_motor_speed); //Right Motor Speed
    //following lines of code are to make the bot move forward
    /*The pin numbers and high, low values might be different
      depending on your connections */
    digitalWrite(6, LOW);
    digitalWrite(10, LOW);
  }
  else {
    digitalWrite(5, LOW);
    digitalWrite(9, LOW);
    digitalWrite(6, LOW);
    digitalWrite(10, LOW);
  }
}

int calculate_dis()
{
  digitalWrite(trig, 0);  // tắt chân trig
  delayMicroseconds(2);
  digitalWrite(trig, 1);  // phát xung từ chân trig
  delayMicroseconds(5);   // xung có độ dài 5 microSeconds
  digitalWrite(trig, 0);  // tắt chân trig
  int duration = pulseIn(echo, HIGH);
  int distance = int(duration / 2 / 29.412);
  return distance;
}

void setup() {
  pinMode(Enable, OUTPUT);
  pinMode(sensorRight, INPUT);
  pinMode(sensorCenter, INPUT);
  pinMode(sensorLeft, INPUT);
  pinMode(5 , OUTPUT);
  pinMode(6 , OUTPUT);
  pinMode(9 , OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(trig, OUTPUT);  // chân trig sẽ phát tín hiệu
  pinMode(echo, INPUT);
  // put your setup code here, to run once:
  Serial.begin(9600);
  digitalWrite(Enable, HIGH);
  line = analogRead(sensorCenter) - 100;
}

void loop() {
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 400) {
    int x = calculate_dis();
    if ( x > 7)
      enaMotor = true;
    else
      enaMotor = false;
  }
  read_sensor_values();
  calculate_pid();
  // Serial.println(PID_value);
  motor_control(enaMotor);
  // put your main code here, to run repeatedly:
}
