#include <Servo.h>

Servo servo1;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 90;    // variable to store the servo position

int trigPin = 11, echoPin = 12, vcc , gnd ;
long duration , cm ;



void setup() {
  servo1.attach(3); //set pulse width range from 500 to 2500 microseconds(default value for Arduino servo library)
  pinMode(10, OUTPUT);  //in1
  pinMode(9, OUTPUT);    //in2
  pinMode(8, OUTPUT); //en1
  pinMode(7, OUTPUT); //en2
  pinMode(6, OUTPUT);     //in3
  pinMode(5, OUTPUT);  //in4
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);


}



void loop() {
/*  servo1.write(90);
  ultrasonic1();
  servo1.write(180); 
  ultrasonic();
  if(cm>15)
  {
    ultrasonic2();
  }
  else
  {
    servo1.write(0);
    ultrasonic3();
  }*/
  start();
 
}

void start()
{
  ultrasonic();
  while(cm>15)
  {
    forward();
    ultrasonic();
    
  while(cm<15)
  {
    s();
    ultrasonic();
    }
 }
}


void forward()
{
  digitalWrite(10, HIGH); //FORWARD DIRECTON
  digitalWrite(9, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(5, LOW);
}

void s()
{ digitalWrite(10, HIGH); //STOP
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
  digitalWrite(7, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(5, LOW);
  delay(2000);
}

void left() {
  digitalWrite(10, LOW); //LEFT
  analogWrite(9, 130);
  digitalWrite(8, HIGH);
  digitalWrite(7, HIGH);
  analogWrite(6, 130);
  digitalWrite(5, LOW);
  delay(2000);
}

void right() {
  analogWrite(10, 130);
  digitalWrite(9, LOW);   //RIGHT
  digitalWrite(8, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(6, LOW);
  analogWrite(5, 130);
  delay(2000);
}



void ultrasonic()
{
  digitalWrite(trigPin, LOW); delayMicroseconds(5);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = (duration / 2) / 29.1;
  Serial.print(cm); Serial.println("cm");
  delay(100);
 
  
}
