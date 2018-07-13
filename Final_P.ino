/*  Five - One

     Karan, Jestin, Shrishti, Navya, Sachin
    We've created an obstacle avoiding robot which uses an ultrasonic sensor to detect obstacled in its path,
    It displays the distance of each route and also the turnings and the route color.
    It also has an color sensor which helps avoid unaccessiable routes by detecting its color convention.

    Our code uses:-
    functions
    global and local variables
    control statements like while, for and simple if loops.
*/



#include <Servo.h>

Servo servo1;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 90;    // variable to store the servo position

int trigPin = 11, echoPin = 12, vcc , gnd ; //US
long duration , cm ;


#define S0 4    // color sensor
#define S1 A1
#define S2 A2
#define S3 A3
#define sensorOut 2

int frequency = 0;
int r, b, g, c = 0;
String color = "";
String turn = "";


#include <SPI.h> //OLED
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);



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

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop()
{
  servo1.write(90);
  color_sensor();
  if (c == 1)
  {
    backward();
    rl();
  }
  else if (c == 3)
  {
    s();
    exit(0);
  }
  else
  {
    servo1.write(90);
    delay(100);
    ultrasonic();
    if (cm > 20)
    {
      forward();
    }
    else
    {
      rl();
    }
  }
}

void ultrasonic()
{
  digitalWrite(trigPin, LOW); delayMicroseconds(5);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = (duration / 2) / 29.1;
  Serial.print(cm); Serial.println("cm");
  delay(100);
}

void forward()
{
  digitalWrite(10, HIGH); //FORWARD DIRECTON
  digitalWrite(9, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(5, LOW);
  turn = "Forward";
}

void backward()
{
  for (int i = 0; i <= 4; i++)
  {
    digitalWrite(10, LOW); //BACKWARD DIRECTON
    digitalWrite(9, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(5, HIGH);
    delay(500);
    turn = "Backward";
  }
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

void right() {
  digitalWrite(10, LOW); //right
  analogWrite(9, 130);
  digitalWrite(8, HIGH);
  digitalWrite(7, HIGH);
  analogWrite(6, 130);
  digitalWrite(5, LOW);
  delay(1000);
  turn = "Right";
}

void left() {
  analogWrite(10, 130);
  digitalWrite(9, LOW);   //left
  digitalWrite(8, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(6, LOW);
  analogWrite(5, 130);
  delay(1000);
  turn = "Left";
}

void rl()
{
  servo1.write(0);
  delay(300);
  ultrasonic();
  if (cm > 20)
  {
    for (int i = 0; i <= 6; i++)
    {
      right();
    }
    servo1.write(90);
    delay(100);
    forward();
  }
  else
  {
    servo1.write(180);
    delay(300);
    ultrasonic();
    if (cm > 20)
    {
      for (int i = 0; i <= 7; i++)
      {
        left();
      }
      servo1.write(90);
      forward();
    }
    else
    {
      s();
    }
  }
}

void color_sensor()
{
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.clearDisplay();
  color_read();
  display.print("Color is: "); display.println(color);
  display.print("Turning : "); display.println(turn);
  display.print("Distance is: "); display.println(cm);
  display.display();
  
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);

  //Remap
  // frequency = map(frequency, 25, 70, 255, 0);

  // Printing the value on the serial monitor
  Serial.print("R = "); // printing name
  Serial.print(frequency); // printing RED color frequency
  Serial.print(" ");
  delay(10);

  // Setting green filtered photodoides to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);

  //Reading the output frequncy
  frequency = pulseIn(sensorOut, LOW);

  //Remap
  // frequency = map(frequency, 25, 70, 255, 0);

  //Printing the value on the serail monitor
  Serial.print("G =  "); // printing the name
  Serial.print(frequency); // printing GREEN color frequency
  Serial.print(" ");
  delay(10);

  //Setting blue filtered photodoide to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  //Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);

  //Remap
  //  frequency = map(frequency, 25, 70, 255, 0);

  //Printing the value on the serial monitor
  Serial.print(" B = "); //printing the name
  Serial.print(frequency); //printing BLUE color frrequency
  Serial.print(" ");
  delay(10);
  Serial.println();
}

void color_read() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);

  //Remap
  // frequency = map(frequency, 25, 70, 255, 0);

  r = frequency; // Printing the value on the serial monitor

  delay(100);

  // Setting green filtered photodoides to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);

  //Reading the output frequncy
  frequency = pulseIn(sensorOut, LOW);

  //Remap
  // frequency = map(frequency, 25, 70, 255, 0);

  //Printing the value on the serail monitor
  g = frequency;
  delay(100);

  //Setting blue filtered photodoide to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  //Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);

  //Remap
  //  frequency = map(frequency, 25, 70, 255, 0);

  //Printing the value on the serial monitor
  b = frequency;
  delay(100);
  /*
    if ((((r >= 45)) && (r <= 65)) && ((g >= 145) && (g <= 170)) && ((b >= 120) && (b <= 140)))
    {
      color = "RED";
    }
    else  if ((((r >= 100)) && (r <= 120)) && ((g >= 75) && (g <= 90)) && ((b >= 120) && (b <= 140)))
    {
      color = "GREEN";
    }
    else if ((((r >= 85)) && (r <= 100)) && ((g >= 80) && (g <= 100)) && ((b >= 55) && (b <= 70)))
    { color = "BLUE";
    }
    //else
      //color = "FLOOR";
  */
  /* if (r >= 30 && r <= 57)
    {
     color = "RED";
     c=1;
    }
    else if (g >= 45 && g <= 82)
    {
     color = "GREEN";
     c=2;
    }
    else if (b >= 40 && b <= 80)
    {
     color = "BLUE";
     c=3;
    }
    else
    {
     color="none";
    }*/
  if (r <= 44)
  {
    color = "RED";
    c = 1;
  }
  else if (g >= 45 && g <= 82)
  {
    color = "GREEN";
    c = 2;
  }
  else if (b >= 40 && b <= 90)
  {
    color = "BLUE";
    c = 3;
  }
  else
  {
    color = "none";
  }
}



