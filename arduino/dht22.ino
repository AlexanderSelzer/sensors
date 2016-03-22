#include <Wire.h>
#include <Adafruit_BMP085.h>
#include "Adafruit_SI1145.h"
#include "SI7021.h"
#include <DHT.h>

#define FANPIN 6
#define DHTPIN 2

int fanState = 1;
int sendInterval = 1000; // 1s

DHT dht(DHTPIN, DHT22);
Adafruit_BMP085 bmp;
SI7021 si7021;
Adafruit_SI1145 si1132 = Adafruit_SI1145();
// had to modify the library according to https://hackaday.io/project/5684/logs

void setup() {
  Serial.begin(9600);
  dht.begin();

  if (!bmp.begin()) {
    Serial.println("Can't find BMP180");
  }

  if (!si1132.begin()) {
    Serial.println("Didn't find Si1145");
  }

  if (!si7021.begin()) {
    Serial.println("didn't find si7021");
  }

  pinMode(FANPIN, OUTPUT);

}

String line;

void loop() {
  while (Serial.available()) {
    delay(3);
    char c = Serial.read();
    line += c;
  }
  if (line.length()) {
    int spaceIndex = line.indexOf(' ');
    if (spaceIndex != -1) {
      String cmd = line.substring(0, spaceIndex);
      String value = line.substring(spaceIndex, line.length());

      if (cmd == "fan") {
        fanState = value.toInt();
      }
    }
    
    line = "";
  }
  
  digitalWrite(FANPIN, fanState);

  if (millis() % sendInterval == 0) {
  
    float h = dht.readHumidity();
    float t = dht.readTemperature();  
    
    uint32_t bmp_pressure = bmp.readPressure();
    float bmp_temp = bmp.readTemperature();

    int si1132_visible = si1132.readVisible();
    int si1132_ir = si1132.readIR();
    int si1132_uv = si1132.readUV();
    
    float si7021_temp = si7021.getCelsiusHundredths() / 100;
    float si7021_humidity = si7021.getHumidityPercent();

    Serial.print("temp: ");
    Serial.print(t);
    Serial.print(", humidity: ");
    Serial.print(h);
  
    Serial.print(", pressure: ");
    Serial.print(bmp_pressure);
    Serial.print(", bmp180temp: ");
    Serial.print(bmp_temp);

    Serial.print(", si1132_visible: ");
    Serial.print(si1132_visible);
    Serial.print(", si1132_ir: ");
    Serial.print(si1132_ir);
    Serial.print(", si1132_uv: ");
    Serial.print(si1132_uv);

    Serial.print(", si7021_temp: ");
    Serial.print(si7021_temp);
    Serial.print(", si7021_humidity: ");
    Serial.println(si7021_humidity);
  }
}
