void LOOP_100MILISECOND(void) {

  #if DEBUG_FUNCTIONS_LOOP == 1
    Serial.println(F("LOOP_100MILISECOND"));
  #endif

  #if USE_ESP_WEBSERVER == 1
    WEBSERVER.handleClient();
  #endif
  
  #if USE_MESSENGER == 1
    while (Serial.available()) MESSENGER.process(Serial.read());
  #endif
}

void LOOP_PRINT(void) {
  
  #if DEBUG_FUNCTIONS_LOOP == 1
    Serial.println(F("LOOP_PRINT"));
  #endif

  Serial.println();
  Serial.println(F("STATUS>>>>>>>>>"));
  Serial.print(F("CUSTOMER NAME: "));
  Serial.print(CUSTOMER.NAME);
  Serial.print(F(" "));
  Serial.println(CUSTOMER.FNAME);
  Serial.print(F("CUSTOMER ID: "));
  Serial.println(CUSTOMER.ID);
  Serial.print(F("SYSTEM NAME: "));
  Serial.println(SETTINGS.NAME);
  #if USE_RTC == 1
    Serial.print(F("ACTIVATION DATE: "));
    DateTime tmp_ACTIVATION(STATION.ACTIVATION);
    printf("%u/%u/%u %u:%u:%u\n", tmp_ACTIVATION.year(), tmp_ACTIVATION.month(), tmp_ACTIVATION.day(), tmp_ACTIVATION.hour(), tmp_ACTIVATION.minute(), tmp_ACTIVATION.second());
    Serial.print(F("EXPIRATION DATE: "));
    DateTime tmp_EXPIRATION(STATION.EXPIRATION);
    printf("%u/%u/%u %u:%u:%u\n", tmp_EXPIRATION.year(), tmp_EXPIRATION.month(), tmp_EXPIRATION.day(), tmp_EXPIRATION.hour(), tmp_EXPIRATION.minute(), tmp_EXPIRATION.second());
    printf("CURRENT TIME (CH): %u/%u/%u %u:%u:%u\n", RTC_DATETIME.year(), RTC_DATETIME.month(), RTC_DATETIME.day(), RTC_DATETIME.hour(), RTC_DATETIME.minute(), RTC_DATETIME.second());
    printf("CURRENT TIME (JA): %u/%u/%u %u:%u:%u\n", RTC_CALENDAR.J_YEAR, RTC_CALENDAR.J_MONTH, RTC_CALENDAR.J_DAY, RTC_CALENDAR.J_HOUR, RTC_CALENDAR.J_MINUTE, RTC_CALENDAR.J_SECOND);
    Serial.print(F("UNIX TIME: "));
    Serial.println(RTC_DATETIME.unixtime());
    Serial.print(F("TOTAL RUNNING HOURS: "));
    Serial.println(RTC_TOTAL_TIMER);
  #endif
  Serial.println(F("*** ERRORS: "));
  #if USE_ESP == 1
    Serial.print(F("ESP_ERROR: "));
    Serial.println(ESP_ERROR);
  #endif
  #if USE_ESP_WIFI == 1
    Serial.print(F("WIFI_ERROR: "));
    Serial.println(WIFI_ERROR);
  #endif
  #if USE_ESP_SYNCSERVER == 1
    Serial.print(F("SYNCSERVER_ERROR: "));
    Serial.println(SYNCSERVER_ERROR);
  #endif
  #if USE_ESP_WEBSERVER == 1
    Serial.print(F("WEBSERVER_ERROR: "));
    Serial.println(WEBSERVER_ERROR);
  #endif
  #if USE_ESP_OTA == 1
    Serial.print(F("OTA_ERROR: "));
    Serial.println(OTA_ERROR);
  #endif
  #if USE_ESP_UDP == 1
    Serial.print(F("UDP_ERROR: "));
    Serial.println(UDP_ERROR);
  #endif
  #if USE_RADIO == 1
    Serial.print(F("ERROR_RADIO: "));
    Serial.println(ERROR_RADIO);
  #endif
  #if USE_SIMCARD == 1
    Serial.print(F("SIMCARD_ERROR: "));
    Serial.println(SIMCARD_ERROR);
  #endif
  #if USE_EEPROM_INT == 1
    Serial.print(F("EEPROM_ERROR: "));
    Serial.println(EEPROM_ERROR);
  #endif
  #if USE_SD == 1
    Serial.print(F("SD_ERROR: "));
    Serial.println(SD_ERROR);
  #endif
  #if USE_TAMPER == 1
    Serial.print(F("TAMPER_ERROR: "));
    Serial.println(TAMPER_ERROR);
    Serial.print(F("TAMPER_EVER_TRIGGERED: "));
    Serial.println(TAMPER_EVER_TRIGGERED);
    #if USE_RTC == 1
      Serial.print(F("TAMPER_EVER_TRIGGERED_EPOCH: "));
      Serial.println(TAMPER_EVER_TRIGGERED_EPOCH);
    #endif
  #endif
  #if USE_KEYPAD == 1
    Serial.print(F("ERROR_KEYPAD: "));
    Serial.println(ERROR_KEYPAD);
  #endif
  #if USE_RTC == 1
    Serial.print(F("RTC_ERROR: "));
    Serial.println(RTC_ERROR);
  #endif
  #if USE_MULTIPLEXER == 1
    Serial.print(F("MULTIPLEXER_ERROR: "));
    Serial.println(MULTIPLEXER_ERROR);
  #endif
  #if USE_FINGER == 1
    Serial.print(F("FINGER_ERROR: "));
    Serial.println(FINGER_ERROR);
  #endif
  #if USE_RFID == 1
    Serial.print(F("RFID_ERROR: "));
    Serial.println(RFID_ERROR);
  #endif
  #if USE_THERMOMETER == 1
    Serial.print(F("THERMOMETER_ERROR: "));
    Serial.println(THERMOMETER_ERROR);
  #endif
  #if USE_HUMIDITY == 1
    Serial.print(F("HUMIDITY_ERROR: "));
    Serial.println(HUMIDITY_ERROR);
  #endif
  Serial.println(F("*** I2C: "));
  HELPERS_I2C_SCAN();
  Serial.println(F("<<<<<<<<<STATUS"));
}

void LOOP_MESSENGER(void) {

  #if USE_MESSENGER == 1

    #if DEBUG_FUNCTIONS_COMPONENTS == 1
      Serial.println(F("LOOP_MESSENGER"));
    #endif
  
    if (!MESSENGER_LOGIN_A && !MESSENGER_LOGIN_B) {
      if (MESSENGER.checkString("LOGIN")) {
        if (MESSENGER.readInt() == MESSENGER_PASSWORD) {
          randomSeed(millis());
          uint16_t tmp_SEED = random(0, 4096);
          MESSENGER_OTP = (((tmp_SEED % 59) + (MESSENGER_PASSWORD % (tmp_SEED % 233)) % 157)) % 947;
          Serial.print(F("SEED is: "));
          Serial.print(tmp_SEED);
          Serial.print(F(" - "));
          Serial.println(MESSENGER_OTP);
          MESSENGER_LOGIN_A = true;
        } else {
          Serial.println(F("Wrong password."));
        }
      }
      return;
    }
    
    if (MESSENGER_LOGIN_A && !MESSENGER_LOGIN_B) {
      if (MESSENGER.readInt() == MESSENGER_OTP) {
        Serial.println(F("Welcome..."));
        MESSENGER_LOGIN_B = true;
      } else {
        Serial.println(F("Wrong MESSENGER_OTP."));
        MESSENGER_LOGIN_A = false;
        MESSENGER_OTP = 0;
      }
      return;
    }
    
    if (MESSENGER_LOGIN_A && MESSENGER_LOGIN_B) {
       if (MESSENGER.checkString("INIT")) {
        #if USE_EEPROM_INT == 1
          for (uint16_t i = EEPROM_INT_ADDRESS_STATION; i < EEPROM_INT_SIZE; i++) {
            EEPROM.write(i, 0);
          }
          Serial.println(F("Done."));
        #endif
        #if USE_EEPROM_EXT == 1
          // TBC
        #endif
      } else if (MESSENGER.checkString("EEPROM")) {
        #if USE_EEPROM_INT == 1
          Serial.println(F("______INT_EEPROM______"));
          for (uint16_t i = 0; i < EEPROM_INT_SIZE / 8; i++) {
            Serial.print(i);
            Serial.print(F("\t"));
            for (uint16_t j = 0; j < 8; j++) {
              uint8_t tmp_EEPROM_READING = EEPROM.read((8 * i) + j);
              Serial.print(tmp_EEPROM_READING, HEX);
              Serial.print(F("("));
              Serial.print(tmp_EEPROM_READING);
              Serial.print(F(")"));
              Serial.print(F("\t"));
            }
            Serial.println();
          }
          Serial.println(F("______INT_EEPROM______"));
        #endif
        #if USE_EEPROM_EXT == 1
          // TBC
        #endif
      } else if (MESSENGER.checkString("PRINT")) {
        if (MESSENGER.readInt() == 0) {
          TASK_LOOP_PRINT.disable();
        } else if (MESSENGER.readInt() == 1) {
          TASK_LOOP_PRINT.enable();
        }
      } else if (MESSENGER.checkString("WIFI")) {
        MESSENGER.copyString(SETTINGS.WIFI_SSID, 32);
        MESSENGER.copyString(SETTINGS.WIFI_PASSWORD, 32);
        SETTINGS.WIFI_DHCP = true;
        SETUP_WIFI();
//      } else if (MESSENGER.checkString("RGB")) {
//        bool tmp_IS_DAY = MESSENGER.readInt();
//        bool tmp_IS_LED = MESSENGER.readInt();
//        if (tmp_IS_DAY && tmp_IS_LED) {
//          SETTINGS.RGB_LED_STATE = true;
//          SETTINGS.RGB_LED_DAY_COLOR[0] = MESSENGER.readInt();
//          SETTINGS.RGB_LED_DAY_COLOR[1] = MESSENGER.readInt();
//          SETTINGS.RGB_LED_DAY_COLOR[2] = MESSENGER.readInt();
//          SETTINGS.RGB_LED_DAY_MODE = MESSENGER.readInt();
//          SETTINGS.RGB_LED_TRESHHOLD = MESSENGER.readInt();
//          SETTINGS_ALTERED = true;
//        } else if (!tmp_IS_DAY && tmp_IS_LED) {
//          SETTINGS.RGB_LED_STATE = true;
//          SETTINGS.RGB_LED_NIGHT_COLOR[0] = MESSENGER.readInt();
//          SETTINGS.RGB_LED_NIGHT_COLOR[1] = MESSENGER.readInt();
//          SETTINGS.RGB_LED_NIGHT_COLOR[2] = MESSENGER.readInt();
//          SETTINGS.RGB_LED_NIGHT_MODE = MESSENGER.readInt();
//          SETTINGS.RGB_LED_TRESHHOLD = MESSENGER.readInt();
//          SETTINGS_ALTERED = true;
//        }
      } else if (MESSENGER.checkString("SET1")) {
        SETTINGS.RELAY_1_MODE = 1;
        SETTINGS.RELAY_1_MODE_1_ENABLE[0] = 1;
        SETTINGS.RELAY_1_MODE_1_ACTIVATE = RTC_DATETIME.unixtime();
        SETTINGS.RELAY_1_MODE_1_DEACTIVATE = RTC_DATETIME.unixtime() + 60;
        SETTINGS.RELAY_1_MODE_1_ON[0] = (RTC_DATETIME.unixtime() % 86400) + 10;
        SETTINGS.RELAY_1_MODE_1_OFF[0] = (RTC_DATETIME.unixtime() % 86400) + 20;
      } else if (MESSENGER.checkString("SET21")) {
        SETTINGS.RELAY_1_MODE = 2;
        SETTINGS.RELAY_1_MODE_2_ACTIVATE = RTC_DATETIME.unixtime() + 10;
        SETTINGS.RELAY_1_MODE_2_DEACTIVATE = RTC_DATETIME.unixtime() + 100;
        SETTINGS.RELAY_1_MODE_2_DURATION = 4;
        SETTINGS.RELAY_1_MODE_2_INTERVAL = 1;
        SETTINGS.RELAY_1_MODE_2_COUNT = 0;
      } else if (MESSENGER.checkString("SET22")) {
        SETTINGS.RELAY_1_MODE = 2;
        SETTINGS.RELAY_1_MODE_2_ACTIVATE = RTC_DATETIME.unixtime() + 10;
        SETTINGS.RELAY_1_MODE_2_DEACTIVATE = RTC_DATETIME.unixtime() + 100;
        SETTINGS.RELAY_1_MODE_2_DURATION = 6;
        SETTINGS.RELAY_1_MODE_2_INTERVAL = 2;
        SETTINGS.RELAY_1_MODE_2_COUNT = 5;
      }
    }
    
  #endif
}
