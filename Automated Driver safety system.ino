#include<Servo.h>
#include<HCSR04.h>
int sensor=A0;
int sensorread;
float beepstart=101.6;
float alert1=76.2;
float alert2=50.8;
float stopdistance=25.4;
Servo wheel;
int buzzerpin=5;
HCSR04 hc(10,11);
float distance;


void setup() {
  // put your setup code here, to run once:
pinMode(sensor,INPUT);
pinMode(buzzerpin,OUTPUT);
wheel.attach(6);
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
sensorread=analogRead(sensor);
Serial.print("sensor value=  ");
Serial.println(sensorread);
delay(500);
wheel.write(0);
distance=hc.dist();
Serial.print("distance of vehicle in front =  ");
Serial.println(distance);
delay(500);

if(sensorread>800&&distance>beepstart){
  Serial.println("Driver is looking at the road");
  delay(1000);
}
else if(sensorread<800&&alert1<distance&&distance<beepstart){
  slow();  
  Serial.println("slow down");
  delay(500);
}
else if(sensorread<800&&alert2<distance&&alert1>distance){
  fast();
  Serial.println("slow down warning 2 ");
  delay(500);
}
else if(sensorread<800&&stopdistance<distance&&alert2>distance){
  constant();
  Serial.println("slow down warning 3");
  delay(500);
}
else if(sensorread<800&&distance<=stopdistance){
  wheel.write(90);
  constant();
  Serial.print("vehicle stopped");
  delay(500);
  
}


}
void slow(){
  digitalWrite(buzzerpin,HIGH);
  delay(1000);
  digitalWrite(buzzerpin,LOW);
  
}
void fast(){
  digitalWrite(buzzerpin,HIGH);
  delay(100);
  digitalWrite(buzzerpin,LOW);
}
void constant(){
  digitalWrite(buzzerpin,HIGH);
}
