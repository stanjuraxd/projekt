#include "DHT.h"
#define DHTPIN D8  
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // senzor data posílá každých 10 sekund
  delay(10000);

  float vlhkost = dht.readHumidity();
  // vrací teplotu ve stupních Celsia (defaultně nastaveno)
  float teplotaC = dht.readTemperature();
  // pomocí "true" vrací teplotu ve stupních Fahrenheit
  float teplotaF = dht.readTemperature(true);

  // kontrola
  if (isnan(vlhkost) || isnan(teplotaC) || isnan(teplotaF)) {
    Serial.println("Nepodařilo se dostat data ze senzoru.");
    return;
  }

  // výpočet teplotního indexu ve stupních Fahrenheit (defaultně nastaveno)
  float indexF = dht.computeHeatIndex(teplotaF, vlhkost);
  // výpočet teplotního indexu ve stupních Celsia (pomocí false)
  float indexC = dht.computeHeatIndex(teplotaC, vlhkost, false);

  Serial.print("Vlhkost: ");
  Serial.print(vlhkost);
  Serial.print(" %\t");
  Serial.print("Teplota: ");
  Serial.print(teplotaC);
  Serial.print(" *C ");
  Serial.print(teplotaF);
  Serial.print(" *F\t");
  Serial.print("Teplotní index: ");
  Serial.print(indexC);
  Serial.print(" *C ");
  Serial.print(indexF);
  Serial.println(" *F");
}
