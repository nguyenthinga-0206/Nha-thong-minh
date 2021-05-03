/*
-còi: nối D8 và GND.
-đèn: nối D5 và GND.
-DHT11: nối D6.
-DC: +12V nối 5V
     +GND: 2 dây 1 nối với GND của arduino, 1 nối GND của Wifi.
     +5V nối Vin của wifi.
     +DNA nối D2
     +IN3,In4 nối D3,D4
-Cảm biến cháy: nối với D7.

*/

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"           
#include <SimpleTimer.h>
#define DHTTYPE DHT11
#include <SoftwareSerial.h>

#define dht_dpin D6
DHT dht(dht_dpin, DHTTYPE); 
SimpleTimer timer;
int enA =D2;//chân  động  cơ
int in3=D3;
int in4=D4;
int led1=D5;
int led2=D1;
int cb=D7;
int coi=D8;
char auth[] = "BMpCQIZ_Y5q2DIlrlhJCagK6RjHrh4Q_";
char ssid[] = "abv";
char pass[] = "12345678";
float t;
float h;

void setup()
{
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);
    dht.begin();
    timer.setInterval(1000, sendUptime);
    Serial.begin(9600);
  
    pinMode(enA,OUTPUT);
    pinMode(in3,OUTPUT); 
    pinMode(in4,OUTPUT);
    pinMode(led1,OUTPUT);
    pinMode(led2,OUTPUT);
    pinMode(cb,INPUT);
    pinMode(coi,OUTPUT);
}

void sendUptime()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
  Serial.print("Current humidity = ");
  Serial.print(h);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(t);
  Serial.print("*C  "); 
  
  Blynk.virtualWrite(V6, t);
  Blynk.virtualWrite(V5, h);
}

BLYNK_WRITE(V0){
  int va=param.asInt();
  if(va==1){
    digitalWrite(led1,HIGH);
  }
  else{
    digitalWrite(led1,LOW);
  }
}

BLYNK_WRITE(V2){
  int va=param.asInt();
  if(va==1){
    digitalWrite(led2,HIGH);
  }
  else{
    digitalWrite(led2,LOW);
  }
}

BLYNK_WRITE(V1){
  int value=param.asInt();
  if(value==1){
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
  }
  else{
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);
  }
}

void loop()
{
  Blynk.run();
  timer.run(); 
  int valu = digitalRead(cb);
  Serial.println(valu);
  if(valu==1){
    tone(coi,2000);
    Blynk.notify("Có cháy!!!");
  }
  else{
    noTone(coi);
  }
  delay(1000);
  
}
