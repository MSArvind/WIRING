#include<Servo.h>
int echopin = 6;
int trigerpin = 5;
float distance, duration;
Servo leftservo;
Servo rightservo;
int motorval;
int motorspeed;
float maxrange =400;
float reverserange = 38.1;
float stoprange = 20.32;
float reversedistance;
int dt = 100;
int kp=2;






void setup() {
  // put your setup code here, to run once:
  pinMode(echopin, INPUT);
  pinMode(trigerpin, OUTPUT);
  leftservo.attach(10);
  rightservo.attach(11);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigerpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigerpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigerpin, LOW);
  duration = pulseIn(echopin, HIGH);
  distance = duration / 58.2;
  Serial.print("distance of object in cm =  ");
  Serial.println(distance);
  delay(dt);
  if (distance > reverserange) {
    forward();
  }
  else if (distance <= reverserange && distance > stoprange) {
    for (distance;distance <=50.8;) {
      reverse();
      digitalWrite(trigerpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigerpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigerpin, LOW);
  duration = pulseIn(echopin, HIGH);
  distance = duration / 58.2;
      Serial.println(distance);
    }
    stop();
    turn();
  }

  else if (distance <= stoprange) {
    stop();
  }



}
void forward() {

  leftservo.write(0);
  rightservo.write(180);
  Serial.println("Forward direction");
  delay(dt);
}
void reverse() {

  leftservo.write(180);
  rightservo.write(0);
  Serial.println("reverse direction");
  delay(dt);

}
void stop() {
  leftservo.write(90);
  rightservo.write(90);
  Serial.println("stopped");
  delay(dt);
}
void turn() {
  leftservo.write(90);
  rightservo.write(180);
  Serial.println("left turn");
  delay(dt);
  if (distance >= maxrange) {
    forward();
  }
}
