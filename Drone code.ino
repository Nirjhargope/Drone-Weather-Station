 #include "DHT.h"
 #define DHTPIN 2
 #define DHTTYPE DHT11
 DHT dht(DHTPIN, DHTTYPE);
 #include <Wire.h>
 #include <SFE_BMP180.h>
 SFE_BMP180 bmp180;
 void setup() {
 Serial.begin(9600);
 Serial.println("Initializing..");
 dht.begin();
 bool success = bmp180.begin();
 if (success) {
 Serial.println("BMP180 init success");
 Serial.println("DHT11 init success");
 }
 }
 void loop() {
 Serial.flush();
 delay(2000);
 // Reading temperature or humidity takes about 250
 milliseconds!
 // Sensor readings may also be up to 2 seconds 'old' (its a
 very slow sensor)
 float h = dht.readHumidity();
 // Read temperature as Celsius
 float t = dht.readTemperature();
 // Read temperature as Fahrenheit
 float f = dht.readTemperature(true);
 // Check if any reads failed and exit early (to try again).
 if (isnan(h) || isnan(t) || isnan(f)) {
 Serial.println("Failed to read from DHT sensor!");
return;
 }
 // Compute heat index
 // Must send in temp in Fahrenheit!
 float hi = dht.computeHeatIndex(f, h);
 char status;
 double T, P;
 bool success = false;
 status = bmp180.startTemperature();
 if (status != 0) {
 delay(1000);
 status = bmp180.getTemperature(T);
 if (status != 0) {
 status = bmp180.startPressure(3);
 if (status != 0) {
 delay(status);
 status = bmp180.getPressure(P, T);
 if (status != 0) {
 Serial.print("Pressure: ");
 Serial.print(P);
 Serial.println(" hPa");
 }
 }
 }
 }
 Serial.print("Humidity: ");
 Serial.print(h);
 Serial.println(" %\t");
 Serial.print("Temperature: ");
 Serial.print(t);
 Serial.print(" *C ");
 Serial.print(f);
 Serial.println(" *F\t");
Serial.print("Heat index: ");
 Serial.print(hi);
 Serial.println(" *F");
 }