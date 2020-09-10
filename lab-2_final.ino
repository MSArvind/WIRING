#include"DHT.h"
#define sensor 3
#define DHTTYPE DHT11
float temp;
int pot=A5;
int settemp;
DHT dht(sensor, DHTTYPE);
int dt=500;
int motorpin=5;
int motorspeed;
int motorval;
int kp=5;

void setup() {
  // put your setup code here, to run once:
dht.begin();
pinMode(potmeter,INPUT);
pinMode(motorpin,OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
settemp=map(analogRead(potmeter),0,1023,0,50);
Serial.print("set temp =  ");
Serial.println(settemp);
delay(dt);
temp=dht.readTemperature();
Serial.print("temp in c =  ");
Serial.println(temp);
delay(dt);
motorval=-kp*(settemp-temp);
motorspeed=constrain(motorval,0,1023);
Serial.print("motor speed =  ");
Serial.println(motorspeed);
if(temp>settemp){
  analogWrite(motorpin,motorspeed);
}
else{
  analogWrite(motorpin,0);
}

}
