#define FW_VERSION "10"

//////////////////////////////// INCLUDE LIBRARIES

//#include <avr/io.h>
//#include <avr/interrupt.h>

#include <TaskScheduler.h>

//#include <SoftwareSerial.h>
#include <Wire.h>
#include <OneWire.h>
//#include <SPI.h>
//#include <SoftSPI.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266Ping.h>
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <ESP8266httpUpdate.h>
#include <WiFiUdp.h>
//#include <RF24.h>
//#include <RF24Network.h>
//#include <RF24Mesh.h>
//#include <SIM800.h>

#include <Messenger.h>
#include <EEPROM.h>
#include <MYLIB_EXT_EEPROM.h>
//#include <SD.h>
#include <RGBLED.h>
//#include <SevSeg.h>
//#include <Adafruit_GFX.h>
//#include <Adafruit_PCD8544.h>
//#include <Keypad.h>
#include <RTClib.h>
#include <PCF8574.h>
//#include <Adafruit_Fingerprint.h>
//#include <MFRC522.h>
//#include <RCSwitch.h>
#include <DallasTemperature.h>
//#include <DHT.h>
#include <Servo.h>
//#include <EmonLib.h>

//////////////////////////////// PREDEFINE FUNCTIONS

void SETUP_SCHEDULER(void);
void SETUP_PROTOCOLS(void);
void SETUP_REGISTERS(void);
void SETUP_PINS(void);
void SETUP_INTERRUPTS(void);

void SETUP_ESP(void);
void SETUP_WIFI(void);
void SETUP_AP(void);
void SETUP_SYNCSERVER(void);
void SETUP_WEBSERVER(void);
void SETUP_RADIO(void);
void SETUP_SIMCARD(void);

void SETUP_MESSENGER(void);

void SETUP_EEPROM(void);
void SETUP_SD(void);
void SETUP_TAMPER(void);
void SETUP_LED(void);
void SETUP_BUZZER(void);
void SETUP_RGB(void);
void SETUP_SEVSEG(void);
void SETUP_LCD(void);
void SETUP_BUTTONS(void);
void SETUP_KEYPAD(void);
void SETUP_RTC(void);
void SETUP_MULTIPLEXER(void);
void SETUP_FINGER(void);
void SETUP_RFID(void);
void SETUP_RC(void);
void SETUP_THERMOMETER(void);
void SETUP_HUMIDITY(void);
void SETUP_PIR(void);
void SETUP_GAS(void);
void SETUP_LDR(void);
void SETUP_MOTOR(void);
void SETUP_CURRENT(void);
void SETUP_EXECS(void);
void SETUP_TEMPORARY(void);
void SETUP_START(void);

void LOOP_100MILISECOND(void);
void LOOP_PRINT(void);
void LOOP_MESSENGER(void);

void ANALYZE_SYNCSERVER(void);
void ANALYZE_OTA(void);
void ANALYZE_RADIO(void);
void ANALYZE_SIMCARD(void);
void HELPER_EXIP(void);
void HELPER_PING(void);

void ANALYZE_EEPROM(void);
void ANALYZE_SD(void);
void ANALYZE_TAMPER(void);
void ANALYZE_LED(void);
void ANALYZE_BUZZER(void);
void ANALYZE_RGB(void);
void ANALYZE_SEVSEG(void);
void ANALYZE_LCD(void);
void ANALYZE_BUTTONS(void);
void ANALYZE_KEYPAD(void);
void ANALYZE_RTC(void);
void ANALYZE_MULTIPLEXER(void);
void ANALYZE_FINGER(void);
void ANALYZE_RFID(void);
void ANALYZE_RC(void);
void ANALYZE_THERMOMETER(void);
void ANALYZE_HUMIDITY(void);
void ANALYZE_PIR(void);
void ANALYZE_GAS(void);
void ANALYZE_LDR(void);
void ANALYZE_MOTOR(void);
void ANALYZE_CURRENT(void);

uint16_t HELPERS_MEMORY(void);
bool HELPERS_GET_BIT(uint32_t arg1_DATA, uint8_t arg2_COUNT);
uint32_t HELPERS_SET_BIT(uint32_t arg1_DATA, uint8_t arg2_COUNT,  bool arg3_VALUE);
char HELPERS_HEX2INT(char arg1_HEX);
uint8_t HELPERS_BCD2BIN(uint8_t arg1_VALUE);
void HELPERS_I2C_SCAN(void);
bool HELPERS_I2C_CHECK(uint8_t arg1_ADDRESS);

//////////////////////////////// INCLUDE HEADERS

#include "1_SETTINGS.h"
#include "2_VARIABLES.h"
#include "3_SETUP.h"
#include "4_LOOP.h"
#include "5_NETWORK.h"
#include "6_COMPONENTS.h"
#include "7_HELPERS.h"

//////////////////////////////// SETUP

void setup (void) {

  SETUP_SCHEDULER();
  SETUP_ESP();
  SETUP_PROTOCOLS();
  SETUP_REGISTERS();
  SETUP_PINS();
  SETUP_INTERRUPTS();
  
  SETUP_MESSENGER();
  
  SETUP_EEPROM();
  SETUP_SD();
  SETUP_TAMPER();
  SETUP_LED();
  SETUP_BUZZER();
  SETUP_RGB();
  SETUP_SEVSEG();
  SETUP_LCD();
  SETUP_BUTTONS();
  SETUP_KEYPAD();
  SETUP_RTC();
  SETUP_MULTIPLEXER();
  SETUP_FINGER();
  SETUP_RFID();
  SETUP_RC();
  SETUP_THERMOMETER();
  SETUP_HUMIDITY();
  SETUP_PIR();
  SETUP_GAS();
  SETUP_LDR();
  SETUP_MOTOR();
  SETUP_CURRENT();
  SETUP_SIMCARD();
  
  SETUP_WIFI();
  SETUP_SYNCSERVER();
  SETUP_WEBSERVER();
  SETUP_RADIO();
  
  SETUP_EXECS();
  SETUP_TEMPORARY();
  SETUP_START();
}

//////////////////////////////// LOOP

void loop() {
  
  SCHEDULER.execute();
}
