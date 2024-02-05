#include "DHT.h"
#define DHTPIN 5
#define DHTTYPE DHT11 
const int analogPin = A0;     // Analog pin for MQ-2 sensor
const int redLEDPin = 07;      // Pin for the red LED
const int greenLEDPin = 03;    // Pin for the green LED
int sensorValue = 0;          // Variable to store the sensor value
int threshold = 90;          // Adjust this threshold based on your sensor and environment
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);         // Start the serial communication
  pinMode(redLEDPin, OUTPUT);  // Set red LED pin as output
  pinMode(greenLEDPin, OUTPUT);// Set green LED pin as output
  Serial.println(F("DHTxx test!"));
  dht.begin();
}

void loop() {
  sensorValue = analogRead(analogPin);  // Read the analog value from the sensor
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (sensorValue > threshold) {
    digitalWrite(redLEDPin, HIGH);    // Turn on the red LED
    digitalWrite(greenLEDPin, LOW);   // Turn off the green LED
    Serial.println("CO2 Gas Detected!");
  
  } else {
    digitalWrite(redLEDPin, LOW);     // Turn off the red LED
    digitalWrite(greenLEDPin, HIGH);  // Turn on the green LED
    Serial.println("No CO2 Gas Detected.");
    
  }
  
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  if(t<20) {
    Serial.println("Room Temperature is below Normal");
    digitalWrite(redLEDPin, LOW);
  
  }

  else  if(t>25) {
    Serial.println("Room Temperature is Above Normal");
    digitalWrite(redLEDPin, HIGH);
  }
  else {
    Serial.println("Room Temperature is Normal");
      
     
  }


  delay(1000);  // Delay for better readability (adjust as needed)
}
