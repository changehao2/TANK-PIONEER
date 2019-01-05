#define sensorLeft A0
#define sensorCenter A1
#define sensorRight A2
#define Enable A3

void setup() {
  // put your setup code here, to run once:
  pinMode(Enable, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);

  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  digitalWrite(Enable, HIGH);
  Serial.begin(9600);
}
int sensor[5];
void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(analogRead(A4));
  Serial.print("  ");
  Serial.print(analogRead(A0));
  Serial.print("  ");
  Serial.print(analogRead(A1));
  Serial.print("  ");
  Serial.print(analogRead(A2));
  Serial.print("  ");
  Serial.print(analogRead(A5));
  Serial.println("");
  delay(500);

}
