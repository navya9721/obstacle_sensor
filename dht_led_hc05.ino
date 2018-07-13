/*
  command             Response    Description
  AT+NAME="IoT_Lab"   OK          Sets the name to EE Blue.
  AT+PSWD="1234"      OK          Sets the pairing key.
  DHT           Bluetooth HC-05
  SIGNAL - 7    RX - 11
  VCC - 5V      TX - 10
  GND - GND     GND - GND
                VCC - 5V
*/
#include <DHT.h>;
#include <SoftwareSerial.h>
SoftwareSerial EEBlue(10, 11); // RX | TX
#define DHTPIN 3     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino
float hum;  //Stores humidity value
float temp; //Stores temperature value
#define ledPin 13
String state = "";
int i = 0;

void setup() {
  EEBlue.begin(38400);
  Serial.begin(38400);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(2, LOW);
  digitalWrite(4, HIGH);
  dht.begin();
}

void loop()
{
  if (EEBlue.available() > 0) { // Checks whether data is comming from the serial port
    state = EEBlue.readString(); // Reads the data from the serial port
    Serial.print(state);
  }
  if (state == "0" || state == "off") {
    digitalWrite(ledPin, LOW); // Turn LED OFF
    EEBlue.println("LED: OFF"); // Send back, to the phone, the String "LED: ON"
    Serial.println("\tLED: OFF");
    state = "2";
  }
  else if (state == "1" || state == "on") {
    digitalWrite(ledPin, HIGH);
    Serial.print("\tLED: ON");
    EEBlue.print("LED: ON");
    Serial.print("\tTemperature = ");
    Serial.print(dht.readTemperature());
    delay(100);
    EEBlue.print("\tTemperature = ");
    EEBlue.print(dht.readTemperature());
    delay(100);
    Serial.print("\tHumidity = ");
    Serial.println(dht.readHumidity());
    delay(100);
    EEBlue.print("\tHumidity = ");
    EEBlue.println(dht.readHumidity());
    delay(100);
    state = "1";
  }
}
