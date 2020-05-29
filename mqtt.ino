
void mqtt_init(){ 
  client.setServer(MQTT_SERVER, MQTT_PORT);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");  
    if (client.connect("Water_Counter", MQTT_USER, MQTT_PASSWORD )) {
       Serial.println("connected"); 
    } else { 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000); 
    }
  }
  client.setCallback(callback);
  client.subscribe(CONTROL_TOPIC);
  client.publish("home/online", "Water_Counter");
  client.publish("home/info", "Water_Counter can control (arguments): sensor - counter_hot, counter_cold, actor - neptun");
   
}

void callback(char* topic, byte *payload, unsigned int length) {
    // Установка значения холодной воды
    if (String(topic)== COLD_COMMAND_TOPIC){
      String s="";
        for (int i = 0; i < length; i++) {
            s=s+(char)payload[i];
        }
      d_cold=s.toFloat();
      EEPROM_float_write(addres_cold, d_cold);
      char result[8]; // Buffer big enough for 7-character float
      dtostrf(d_cold, 6, 2, result); // Leave room for too large numbers!
      client.publish(COLD_STATE_TOPIC, result, true); 
    }
    // Установка значения горячей воды
    if (String(topic)==HOT_COMMAND_TOPIC){
      String s="";
        for (int i = 0; i < length; i++) {
            s=s+(char)payload[i];
        }
      d_hot=s.toFloat();
      EEPROM_float_write(addres_hot, d_hot);
      char result[8]; // Buffer big enough for 7-character float
      dtostrf(d_hot, 6, 2, result); // Leave room for too large numbers!
      client.publish(HOT_STATE_TOPIC, result, true);
    }
    // Установка значения нептуна
    if (String(topic)== NEPTUN_COMMAND_TOPIC){
      String s="";
        for (int i = 0; i < length; i++) {
            s=s+(char)payload[i];
        }
       if (s=="ON"){
        d_state=1;
        digitalWrite(RELE, HIGH);
       }
       else if (s=="OFF"){
        d_state=0;
        digitalWrite(RELE, LOW);
       }

      char result[5]; // Buffer big enough for 7-character float
    s.toCharArray(result,5);
      client.publish(NEPTUN_STATE_TOPIC, result, true);
    }
 
}

void send_mqtt(){
 //Холодная вода
 char result[255]; // Buffer big enough for 7-character float
      dtostrf(d_cold, 6, 2, result); // Leave room for too large numbers!
      client.publish(COLD_STATE_TOPIC, result, true);
 // Горячая вода
      dtostrf(d_hot, 6, 2, result); // Leave room for too large numbers!
      client.publish(HOT_STATE_TOPIC, result, true);
}
