
// адреса в постоянной памяти
int adr_init_eeprom = 500;
int addres_cold = 5;
int addres_hot = 20;



void EEPROM_float_write(int addr, float val) // запись в ЕЕПРОМ FLOAT 4 bite
{  
  byte *x = (byte *)&val;
  for(byte i = 0; i < 4; i++) EEPROM.write(i+addr, x[i]);
  EEPROM.commit();
}

float EEPROM_float_read(int addr) // чтение из ЕЕПРОМ
{    
  byte x[4];
  for(byte i = 0; i < 4; i++) x[i] = EEPROM.read(i+addr);
  float *y = (float *)&x;
  return y[0];
}

void EEPROM_string_write (int addr, int addr_length, String s)
{
    int charLength=s.length();
  
  Serial.println("writing eeprom ssid:");
          for (int i = 0; i < s.length(); ++i)
            {
              EEPROM.write(i+addr, s[i]);
            }
          EEPROM.write(addr_length,charLength);
         EEPROM.commit();
}

String EEPROM_string_read (int addr, int charLength)
{
 //  Serial.println("Reading EEPROM ssid");
  String s;
  for (int i = 0; i < charLength; ++i)
    {
      s += char(EEPROM.read(i+addr));
    }
  return s;
}





void EEPROM_init(void) {
 EEPROM.begin(512);
// При первом запуске в памяти пусто 
if (EEPROM.read(adr_init_eeprom)!=1)
{
  Serial.println("Write init value to EEPROM");
  EEPROM_float_write(addres_cold, 0);
  EEPROM_float_write(addres_hot, 0);
  EEPROM.write(adr_init_eeprom, 1);
  EEPROM.commit();
}

//Загрузка текущих показаний
d_cold = EEPROM_float_read(addres_cold);
d_hot = EEPROM_float_read(addres_hot);
}
