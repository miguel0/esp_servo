#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <NewPing.h>
#include <Servo.h>
#define maxDist 200
#define echoPin 4
#define trigPin 0
NewPing sonar(trigPin, echoPin, maxDist);

char auth[] = "40e063892ad34a6baa46ae29674e6f62";
char ssid[] = "FD-89";
char pass[] = "12345678";

Servo SERVO;
const int LED = 16;
const int VOZ = 14;
const int BUZZ = 5;

void Blynk_Delay(int milli){
   int end_time = millis() + milli;
   while(millis() < end_time){
       Blynk.run();
       yield();
   }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  SERVO.attach(2);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  // put your main code here, to run repeatedly:
    Blynk.run();
    digitalWrite(LED,HIGH);
    long distance;
  
    unsigned int uS = sonar.ping();
    
    pinMode(echoPin,OUTPUT);
    digitalWrite(echoPin,LOW);
    pinMode(echoPin,INPUT);
  
    distance = uS / US_ROUNDTRIP_CM;

    if ((digitalRead(VOZ) == 1)||((distance <= 15) && (distance != 0))){
      digitalWrite(LED,LOW);
      SERVO.write (30);
      Blynk_Delay(800);
      SERVO.write (170);
      digitalWrite(BUZZ, HIGH);
      Blynk_Delay(50);
      digitalWrite(BUZZ, LOW);
      Blynk_Delay(3500);
      digitalWrite(VOZ,LOW);
    }
    
    Blynk_Delay(50);
}
