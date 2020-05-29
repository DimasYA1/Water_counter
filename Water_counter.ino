#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_ADS1015.h>

#include "config.h"
//#include "secret.h" // Для заполнения настроек подключения к WI-FI и MQTT. При заполнении настроек в config.h нужно закомментировать эту строчку

//----------------------------------------------------------------------- Переменные в ОЗУ
//Значение счетчика
// счетчики
float d_cold=0;
float d_hot = 0; 

//статус нептуна 
int d_state = 0;


//----------------------------------------------------------MQTT
WiFiClient espClient;
PubSubClient client(espClient);

// -------------------------------------------------------Время работы для прерывания loop
unsigned long times_1min =0;
unsigned long times_5sec =0;

//---------------------------------------------------------------------------------------Конец переменных



void setup() {
 Serial.begin(115200);
Serial.println("Serial ready");

ads.begin();

pinMode(RELE, OUTPUT);
digitalWrite(RELE, LOW);
d_state = digitalRead(STATE_PIN);
Serial.println("Neptun ready");


EEPROM_init();
Serial.println("EEPROM ready");
init_wifi();

ota_init();
Serial.println("OTA Ready");

mqtt_init();
Serial.println("MQTT Ready");

}

void loop() {
  
 if (WiFi.status() != WL_CONNECTED){
  init_wifi();
 }
    if (!client.connected()) {
    Serial.println("Attempting to reconnect MQTT...");
    mqtt_init();
  }
  
 ArduinoOTA.handle();
 
 //Обработка MQTT
 client.loop();
 
 
if ((millis()- times_5sec >5000)|| (times_5sec > millis())){
    times_5sec = millis();
 measure(); 
}
 // Отсылка данных каждую минуту
 
if ((millis()- times_1min >60000)|| (times_1min>millis())){
    times_1min = millis();
    
//----------------------------------------------------------KeepAlive

client.publish(ONLINE_TOPIC, "ON"); 
}



}
