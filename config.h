//Unique name of device
#define CLIENT_ID        "water" // Must be unique!

//----------------------------------------------------------------------Настройка пинов                     
int RELE = 12;
int COLD_PIN = 0; //ads
int HOT_PIN = 1;  //ads
int STATE_PIN = 13;
Adafruit_ADS1115 ads(0x48);

// wifi settings from secret.h 
#define WIFI_SSID        wifi_ssid
#define WIFI_PASSWORD    wifi_password

// mqtt server settings from secret.h
#define MQTT_SERVER       mqtt_server
#define MQTT_PORT         mqtt_port
#define MQTT_USER         mqtt_user
#define MQTT_PASSWORD     mqtt_password

#define MAIN_TOPIC              "home"
#define ROOM                    "bathroom"
#define DEVICE_TYPE             "sensor"
#define HOME_ASSISTANT_TOPIC    "homeassistant"

//Топики                     
#define CONTROL_TOPIC            MAIN_TOPIC "/" ROOM "/" DEVICE_TYPE "/" CLIENT_ID "/#"  //"home/hall/cover/Roller_NG_1/#"
#define HA_CONFIG_TOPIC          HOME_ASSISTANT_TOPIC "/" DEVICE_TYPE "/" CLIENT_ID "/config"
#define ONLINE_TOPIC             MAIN_TOPIC "/" ROOM "/" DEVICE_TYPE "/" CLIENT_ID "/online"
#define COLD_COMMAND_TOPIC            MAIN_TOPIC "/" ROOM "/" DEVICE_TYPE "/" CLIENT_ID "/counter_cold/set"
#define HOT_COMMAND_TOPIC            MAIN_TOPIC "/" ROOM "/" DEVICE_TYPE "/" CLIENT_ID "/counter_hot/set"
#define NEPTUN_COMMAND_TOPIC            MAIN_TOPIC "/" ROOM "/" DEVICE_TYPE "/" CLIENT_ID "/neptun/set"
#define COLD_STATE_TOPIC              MAIN_TOPIC "/" ROOM "/" DEVICE_TYPE "/" CLIENT_ID "/counter_cold/state"
#define HOT_STATE_TOPIC              MAIN_TOPIC "/" ROOM "/" DEVICE_TYPE "/" CLIENT_ID "/counter_hot/state"
#define NEPTUN_STATE_TOPIC              MAIN_TOPIC "/" ROOM "/" DEVICE_TYPE "/" CLIENT_ID "/counter_hot/state"
#define DEBUG_TOPIC              MAIN_TOPIC "/" ROOM "/" DEVICE_TYPE "/" CLIENT_ID "/debug"


//Пороги срабатывания геркона счетчика
int16_t porog_up = 19800;
int16_t porog_down = 19650;
