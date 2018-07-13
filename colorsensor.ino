#define S0 7
#define S1 8
#define S2 9
#define S3 10
#define sensorOut 11

int frequency = 0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  
  Serial.begin(9600);

}

void loop() {
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
  delay(100);

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
  delay(100);

  //Setting blue filtered photodoide to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  //Reading the output frequency
  frequency = pulseIn(sensorOut,LOW);

  //Remap
//  frequency = map(frequency, 25, 70, 255, 0);

  //Printing the value on the serial monitor
  Serial.print(" B = "); //printing the name
  Serial.print(frequency); //printing BLUE color frrequency
  Serial.print(" ");
  delay(100);

  Serial.println();
}
