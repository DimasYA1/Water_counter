
boolean cold_flag =true;
boolean hot_flag= true;
boolean state_flag = false;


int16_t adc0=0;
int repeat=10;


// Измерение показаний счетчиков
void measure(){


  //Считывание данных со счетчика
// холодная вода
int i=0;
long sum=0;
for (i=0; i<repeat; i++){
    adc0 = ads.readADC_SingleEnded(COLD_PIN);
 sum=sum+ adc0;
 // Serial.println("COLD: "+String(ads.readADC_SingleEnded(COLD_PIN)));
 delay(100);
}
sum=sum/repeat;
 
if (cold_flag ==false && sum > porog_up){
  cold_flag=true;
   //Меняю значение счетчика   
   d_cold=d_cold+0.01;
   EEPROM_float_write(addres_cold, d_cold);         
   //MQTT
    char result[8]; // Buffer big enough for 7-character float
    dtostrf(d_cold, 6, 2, result); // Leave room for too large numbers!
    client.publish(COLD_STATE_TOPIC, result, true);
Serial.println("Холодная вода:"+ String(d_cold));  
}
else if (cold_flag ==true && sum < porog_down){
    cold_flag=false;
}

// Горячая вода
i=0;
sum=0;
for (i=0; i<repeat; i++){
    adc0 = ads.readADC_SingleEnded(HOT_PIN);
 sum=sum+ adc0;
  // Serial.println("HOT: "+String(ads.readADC_SingleEnded(HOT_PIN)));
 delay(100);
}
sum=sum/repeat;

if (hot_flag ==false && sum > porog_up){
  hot_flag=true;
   //Меняю значение счетчика   
   d_hot=d_hot+0.01;
   EEPROM_float_write(addres_hot, d_hot);         
   //MQTT
    char result[8]; // Buffer big enough for 7-character float
    dtostrf(d_hot, 6, 2, result); // Leave room for too large numbers!
    client.publish(HOT_STATE_TOPIC, result, true);
Serial.println("Горячая вода:"+ String(d_hot));  
}
else if (hot_flag ==true && sum < porog_down){
    hot_flag=false;
}




// Состояние Нептуна

Serial.println(digitalRead(STATE_PIN));
if (state_flag ==false && digitalRead(STATE_PIN)==1)
{
delay(500);
 if (digitalRead(STATE_PIN)==1)
{
  delay(500);
  if (digitalRead(STATE_PIN)==1)
  {
            state_flag=true;
            d_state = 1;

     //MQTT
client.publish(NEPTUN_STATE_TOPIC, "ON", true);
Serial.println("Нептун: "+String(d_state));
  }
}
}

else if (state_flag ==true && digitalRead(STATE_PIN)==0)
{
delay(500);
 if (digitalRead(STATE_PIN)==0)
{
  delay(500);
   if (digitalRead(STATE_PIN)==0)
   {
      state_flag=false;
      d_state = 0; 
      //MQTT
client.publish(NEPTUN_STATE_TOPIC, "OFF",true);
             Serial.println("Нептун: "+String(d_state));
}
}

}


}
