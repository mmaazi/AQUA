//////////////////////////////// DEBUG

#define DEBUG_FUNCTIONS_SETUP 0
#define DEBUG_FUNCTIONS_LOOP 0
#define DEBUG_FUNCTIONS_NETWORK 0
#define DEBUG_FUNCTIONS_COMPONENTS 0

//////////////////////////////// SYSTEM

#define TYPE 1 // 1. AQUA, 2. BMS, 3. 

#if TYPE == 1

  #define USE_SERIAL 1
  #define USE_SOFTSERIAL 0
  #define USE_WIRE 1
  #define USE_ONEWIRE 1
  #define USE_SOFTSPI 0
  
  #define USE_ESP 1
    #define USE_ESP_WIFI 1
    #define USE_ESP_WEBSERVER 0
    #define USE_ESP_SYNCSERVER 1
    #define USE_ESP_OTA 0
    #define USE_ESP_UDP 0
    
  #define USE_RADIO 0
    #define USE_RADIO_MESH 0
    
  #define USE_MESSENGER 1
  
  #define USE_EEPROM 1
    #define USE_EEPROM_INT 1
    #define USE_EEPROM_EXT 0

  #define USE_SD 0
  
  #define USE_TAMPER 0
  
  #define USE_LED 0
  
  #define USE_BUZZER 0
  
  #define USE_RGB 0
    #define USE_RGB_CA 0
  
  #define USE_SEVSEG 0
    #define USE_SEVSEG_CA 0
  
  #define USE_LCD 0
    #define USE_LCD_LCD5110 0
  
  #define USE_BUTTONS 0
  
  #define USE_KEYPAD 0
    #define USE_KEYPAD_4x4 0
    #define USE_KEYPAD_I2C 0

  #define USE_RTC 1
    #define USE_RTC_DS1307 1

  #define USE_MULTIPLEXER 0
    #define USE_MULTIPLEXER_PCF8574 1
      #define USE_MULTIPLEXER_PCF8574_INTERRUPT 0

  #define USE_FINGER 0
  
  #define USE_RFID 0
    #define USE_RFID_MFRC522 0
  
  #define USE_RC 0
  
  #define USE_THERMOMETER 1
    #define USE_THERMOMETER_DS18B20 1
    
  #define USE_HUMIDITY 0
    #define USE_HUMIDITY_DHT11 0
  
  #define USE_PIR 0
  
  #define USE_GAS 0
  
  #define USE_LDR 0
  
  #define USE_MOTOR 0
    #define USE_MOTOR_SERVO 0
  
  #define USE_CURRENT 0
  
  #define USE_SIMCARD 0
    #define USE_SIMCARD_SIM800 0

#endif

#define _TASK_SLEEP_ON_IDLE_RUN
//#define _TASK_TIMECRITICAL

//////////////////////////////// PROTOCOLS

#if USE_SERIAL == 1
  #define SERIAL_BOUD 9600
#endif

#if USE_SOFTSERIAL == 1
  uint8_t SOFTSERIAL_PINS[2] = {0, 0};  // 1. RX, 2. TX
  SoftwareSerial SOFTSERIAL(SOFTSERIAL_PINS[0], SOFTSERIAL_PINS[1]);
  #define SOFTSERIAL_BOUD 9600
#endif

#if USE_WIRE == 1
  uint8_t WIRE_PINS[2] = {4, 5};  // 1. SDA, 2. SCL
#endif

#if USE_ONEWIRE == 1
  uint8_t ONEWIRE_PIN = 2;
  OneWire oneWire(ONEWIRE_PIN);
#endif

#if USE_SOFTSPI == 1
  uint8_t SOFTSPI_PINS[3] = {0, 0, 0};  // 1. MOSI, 2. MISO, 3. SCK
  SoftSPI SOFTSPI(SOFTSPI_PINS[0], SOFTSPI_PINS[1], SOFTSPI_PINS[2]);
#endif

//////////////////////////////// NETWORK

#if USE_ESP == 1
  bool ESP_ERROR = false;
  
  #if USE_ESP_WIFI == 1
    #define ESP_WIFI_DEBUG 1
    WiFiClient CLIENT;
    bool WIFI_ERROR = false;
  #endif
  
  #if USE_ESP_SYNCSERVER == 1
    #define ESP_SYNCSERVER_DEBUG 1
    //StaticJsonDocument<2048> SYNCSERVER_JSON_BUFFER;
    DynamicJsonDocument SYNCSERVER_JSON_BUFFER(200);
    #define SYNCSERVER_INTERVAL 2000
    uint8_t SYNCSERVER_ERROR = 0;
    #define SYNCSERVER_SECRET "secret"
    #define SYNCSERVER_HOME "192.168.1.3"
    #define SYNCSERVER_PASSWORD "password"
    bool SYNCSERVER_DTR = false;
  #endif
  
  #if USE_ESP_WEBSERVER == 1
    #define ESP_WEBSERVER_DEBUG 0
    ESP8266WebServer WEBSERVER(80);
  #endif
  
  #if USE_ESP_OTA == 1
    #define ESP_OTA_DEBUG 1
    #define OTA_INTERVAL 600000
    bool OTA_ERROR = false;
  #endif
  
  #if USE_ESP_UDP == 1
    #define ESP_UDP_DEBUG 1
    WiFiUDP UDP;
    bool UDP_ERROR = false;
  #endif
#endif

#if USE_RADIO == 1
  #define ESP_RADIO_DEBUG 1
  uint8_t RADIO_PINS[2] = {0, 0};  // 1. CE, 2. CS
  RF24 RADIO(RADIO_PINS[0], RADIO_PINS[1]);
  bool RADIO_ERROR = false;

  #if USE_RADIO_MESH == 1
    RF24Network NETWORK(RADIO);
    RF24Mesh MESH(RADIO, NETWORK);
  #endif
#endif

#if USE_SIMCARD == 1
  #define SIMCARD_INTERVAL 5000
  bool SIMCARD_ERROR = false;

  #if USE_SIMf_SIM800 == 1
    uint8_t SIM800_PIN = 0;
  #endif
#endif

//////////////////////////////// COMPONENTS

#if USE_MESSENGER == 1
  Messenger MESSENGER = Messenger();
  #define MESSENGER_INTERVAL 500
  #define MESSENGER_PASSWORD 3495
  bool MESSENGER_LOGIN_A = false;
  bool MESSENGER_LOGIN_B = false;
  uint16_t MESSENGER_OTP = 0;
#endif

#if USE_EEPROM == 1
  #define EEPROM_DEBUG 1
  #define EEPROM_INTERVAL 500
  bool EEPROM_ERROR = false;

  #if USE_EEPROM_INT == 1
    #define EEPROM_INT_SIZE 4096
    #define EEPROM_INT_FLAG 80
    #define EEPROM_INT_ADDRESS_EVER_TAMPERED 100  // 1 Byte
    #define EEPROM_INT_ADDRESS_RTC_TOTAL_TIMER 101  // 4 Byte
    #define EEPROM_INT_ADDRESS_FLAG 110  // 1 Byte * 10 copies
    #define EEPROM_INT_ADDRESS_STATION 150
    #define EEPROM_INT_ADDRESS_CUSTOMER 170
    #define EEPROM_INT_ADDRESS_SETTINGS 450
  #endif
  
  #if USE_EEPROM_EXT == 0
    #define EEPROM_EXT_ADDRESS = 0x50;
    #define EEPROM_EXT_SIZE 4096
    #define EEPROM_EXT_FLAG 80
    #define EEPROM_EXT_ADDRESS_EVER_TAMPERED 100  // 1 Byte
    #define EEPROM_EXT_ADDRESS_RTC_TOTAL_TIMER 101  // 4 Byte
    #define EEPROM_EXT_ADDRESS_FLAG 110  // 1 Byte * 10 copies
    #define EEPROM_EXT_ADDRESS_STATION 150
    #define EEPROM_EXT_ADDRESS_CUSTOMER 170
    #define EEPROM_EXT_ADDRESS_SETTINGS 450
  #endif
#endif

#if USE_SD == 1
  #define SD_PIN 0
  #define SD_INTERVAL 500
  bool SD_ERROR = false;
#endif

#if USE_TAMPER == 1
  #define TAMPER_PIN 0
  #define TAMPER_INTERVAL 500
  bool TAMPER_ERROR = false;
  bool TAMPER_EVER_TRIGGERED = false;
  uint32_t TAMPER_EVER_TRIGGERED_EPOCH;
#endif

#if USE_LED == 1
  #define LED_PIN 0
  #define LED_INTERVAL 1000
  bool LED_STATE = false;
  uint16_t LED_OFF_INTERVAL = 25;
  uint16_t LED_ON_INTERVAL = 1000;
#endif

#if USE_BUZZER == 1
  #define BUZZER_PIN 0
  #define BUZZER_INTERVAL 1000
  bool BUZZER_STATE = false;
  uint16_t BUZZER_OFF_INTERVAL = 25;
  uint16_t BUZZER_ON_INTERVAL = 1000;
#endif

#if USE_RGB == 1
  //uint8_t RGB_LED_PINS[3] = {0, 0, 0};
  uint8_t RGB_LAMP_PINS[3] = {13, 12, 14};
  #define RGB_INTERVAL 1000
  bool RGB_LED_STATE = false;
  uint32_t RGB_LED_COLOR;
  bool RGB_LAMP_STATE = false;
  uint32_t RGB_LAMP_COLOR_CURRENT;
  uint32_t RGB_LAMP_COLOR_GOAL;
  uint16_t RGB_LAMP_COLOR_HUE = 0;

  #if USE_RGB_CA == 1
    //RGBLED RGB_LED(RGB_LED_PINS[0], RGB_LED_PINS[1], RGB_LED_PINS[2], COMMON_ANODE);
    RGBLED RGB_LAMP(RGB_LAMP_PINS[0], RGB_LAMP_PINS[1], RGB_LAMP_PINS[2], COMMON_ANODE);
  #else
    RGBLED RGB_LED(RGB_LED_PINS[0], RGB_LED_PINS[1], RGB_LED_PINS[2], COMMON_CATHODE);
    RGBLED RGB_LAMP(RGB_LAMP_PINS[0], RGB_LAMP_PINS[1], RGB_LAMP_PINS[2], COMMON_CATHODE);
  #endif
#endif

#if USE_SEVSEG == 1
  SevSeg SEVSEG;
  #define SEVSEG_INTERVAL 100

  #if USE_SEVSEG_CA == 1
    uint8_t SEVSEG_CA_DIGIT_COUNT = 4;
    uint8_t SEVSEG_CA_DIGIT_PINS[] = {0, 0, 0, 0};
    uint8_t SEVSEG_CA_SEGMENT_PINS[] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t SEVSEG_CA_STATION = COMMON_ANODE;
    uint8_t SEVSEG_CA_BRIGHTNESS = 90;
    bool SEVSEG_CA_RESISTOR = false;
    bool SEVSEG_CA_DELAY = false;
    bool SEVSEG_CA_LEADING_ZERO = false;
    bool SEVSEG_CA_NO_DECIMAL = false;
  #else
    uint8_t SEVSEG_CC_DIGIT_COUNT = 4;
    uint8_t SEVSEG_CC_DIGIT_PINS[] = {0, 0, 0, 0};
    uint8_t SEVSEG_CC_SEGMENT_PINS[] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t SEVSEG_CC_STATION = COMMON_CATHODE;
    uint8_t SEVSEG_CC_BRIGHTNESS = 90;
    bool SEVSEG_CC_RESISTOR = false;
    bool SEVSEG_CC_DELAY = false;
    bool SEVSEG_CC_LEADING_ZERO = false;
    bool SEVSEG_CC_NO_DECIMAL = false;
  #endif
#endif

#if USE_LCD == 1
  #define LCD_INTERVAL 100

  #if USE_LCD_LCD5110 == 1
    uint8_t LCD5110_PINS[5] = {0, 0, 0, 0, 0};
    Adafruit_PCD8544 LCD5110 = Adafruit_PCD8544(LCD5110_PINS[0], LCD5110_PINS[1], LCD5110_PINS[2], LCD5110_PINS[3], LCD5110_PINS[4]);
  #endif
#endif

#if USE_BUTTONS == 1
  #define BUTTONS_INTERVAL 100
#endif

#if USE_KEYPAD == 1
  #define KEYPAD_INTERVAL 100
  bool KEYPAD_ERROR = false;

  #if USE_KEYPAD_4x4 == 1
    char KEYPAD_4x4_KEYS[4][4] = {{'1','2','3' ,'U'}, {'4','5','6','D'}, {'7','8','9','C'}, {'L','0','R','O'}};
    uint8_t KEYPAD_4x4_ROW_PINS[4] = {0, 0, 0, 0};
    uint8_t KEYPAD_4x4_COLUMN_PINS[4] = {0, 0, 0, 0};
    Keypad KEYPAD_4x4 = Keypad(makeKeymap(KEYPAD_KEYS), KEYPAD_ROW_PINS, KEYPAD_COLUMN_PINS, 4, 4);
  #endif
  
  #if USE_KEYPAD_I2C == 1
    uint8_t KEYPAD_I2C_ERROR = 0;
  #endif
#endif

#if USE_RTC == 1
  #define RTC_INTERVAL 1000
  bool RTC_ERROR = false;
  DateTime RTC_DATETIME;
  uint32_t RTC_TOTAL_TIMER;
  uint32_t RTC_EPOCH_LAST;
  struct STRUCT_CALENDAR {
    uint16_t J_YEAR;
    uint8_t J_MONTH;
    uint8_t J_DAY;
    uint8_t J_HOUR;
    uint8_t J_MINUTE;
    uint8_t J_SECOND;
    int16_t J_ZONE = 210;
  } RTC_CALENDAR;

  #if USE_RTC_DS1307 == 1
    #define DS1307_ADDRESS 0x68
    RTC_DS1307 DS1307;
  #endif
#endif

#if USE_MULTIPLEXER == 1
  #define MULTIPLEXER_DEBUG 1
  #define MULTIPLEXER_INTERVAL 100
  bool MULTIPLEXER_ERROR = false;
  
  #if USE_MULTIPLEXER_PCF8574 == 1
    uint8_t PCF8574_ADDRESS = 0x20;
    PCF8574 PCF8574;
    #if USE_MULTIPLEXER_PCF8574_INTERRUPT == 1
      uint8_t PCF8574_INTERRUPT_PIN = 0;
    #endif
  #endif
#endif

#if USE_FINGER == 1
  Adafruit_Fingerprint FINGER = Adafruit_Fingerprint(&SOFTSERIAL);
  //Adafruit_Fingerprint FINGER = Adafruit_Fingerprint(&SOFTSERIAL, 0000);
  #define FINGER_INTERVAL 1000
  bool FINGER_ERROR = false;
#endif

#if USE_RFID == 1
  #define RFID_INTERVAL 1000
  bool RFID_ERROR = false;

  #if USE_RFID_MFRC522 == 1
    uint8_t MFRC522_PINS[2] = {0, 0};  // 1. SS, 2. RST
    MFRC522 MFRC522(MFRC522_PINS[0], MFRC522_PINS[1]);
  #endif
#endif

#if USE_RC == 1
  uint8_t RC_RECEIVE_PIN = 0;
  uint8_t RC_SEND_PIN = 0;
  RCSwitch RC = RCSwitch();
  #define RC_INTERVAL 1000
#endif

#if USE_THERMOMETER == 1
  #define THERMOMETER_INTERVAL 5000
  bool THERMOMETER_ERROR = false;

  #if USE_THERMOMETER_DS18B20 == 1 && USE_ONEWIRE == 1
    DallasTemperature DS18B20(&oneWire);
    DeviceAddress DS18B20_IN_ADDRESS;
    DeviceAddress DS18B20_OUT_ADDRESS;
    float DS18B20_TEMP_IN;
    float DS18B20_TEMP_OUT;
  #endif
#endif

#if USE_HUMIDITY == 1
  #define HUMIDITY_INTERVAL 5000
  bool HUMIDITY_ERROR = false;

  #if USE_HUMIDITY_DHT11 == 1
    uint8_t DHT11_PIN = 0;
    DHT DHT11(DHT11_PIN, DHT11);
  #endif
#endif

#if USE_PIR == 1
  uint8_t PIR_PIN = 0;
  #define PIR_INTERVAL 5000
#endif

#if USE_GAS == 1
  uint8_t GAS_PIN = 0;
  #define GAS_INTERVAL 5000
#endif

#if USE_LDR == 1
  uint8_t LDR_PIN = A0;
  #define LDR_INTERVAL 5000
  uint8_t LUX_VALUE;
#endif

#if USE_MOTOR == 1
  #define MOTOR_INTERVAL 5000
  bool MOTOR_ERROR = false;

  #if USE_MOTOR_SERVO == 1
    uint8_t SERVO_PIN = 15;
    Servo SERVO;
  #endif
#endif

#if USE_CURRENT == 1
  uint8_t CURRENT_PIN = 0;
  uint8_t CURRENT_ZEROCROSS_PIN = 0;
  EnergyMonitor CURRENT;
  #define CURRENT_INTERVAL 5000
  float CURRENT_CONSTANT = 2.83;
#endif
