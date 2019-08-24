void ANALYZE_EEPROM(void) {
  
  #if USE_EEPROM == 1
  
    #if DEBUG_FUNCTIONS_COMPONENTS == 1
      Serial.println(F("ANALYZE_EEPROM"));
    #endif
      
    if (STATION_ALTERED) {
      #if EEPROM_DEBUG > 0
        Serial.println(F("Saving STATION."));
      #endif
      #if USE_EEPROM_INT == 1
        EEPROM.put(EEPROM_INT_ADDRESS_STATION, STATION);
        EEPROM.commit();
      #endif
      #if USE_EEPROM_EXT == 1
        EEPROM.put(EEPROM_INT_ADDRESS_STATION, STATION);
        EEPROM.commit();
      #endif
      STATION_ALTERED = false;
    }
    
    if (SETTINGS_ALTERED) {
      #if EEPROM_DEBUG > 0
        Serial.println(F("Saving SETTINGS."));
      #endif
      #if USE_EEPROM_INT == 1
        EEPROM.put(EEPROM_INT_ADDRESS_SETTINGS, SETTINGS);
        EEPROM.commit();
      #endif
      #if USE_EEPROM_INT == 1
        EEPROM.put(EEPROM_INT_ADDRESS_SETTINGS, SETTINGS);
        EEPROM.commit();
      #endif
      SETTINGS_ALTERED = false;
    }
    
  #endif
}

void ANALYZE_SD(void) {

  #if USE_SD == 1

    #if DEBUG_FUNCTIONS_COMPONENTS == 1
      Serial.println(F("ANALYZE_SD"));
    #endif
    
  #endif
}

void ANALYZE_TAMPER(void) {
  
  #if USE_TAMPER == 1
  
    #if DEBUG_FUNCTIONS_COMPONENTS == 1
      Serial.println(F("ANALYZE_TAMPER"));
    #endif
    
    if (digitalRead(TAMPER_PIN) != LOW) {
      TAMPER_ERROR = true;
      TAMPER_EVER_TRIGGERED = true;
    } else {
      TAMPER_ERROR = false;
    }

  #endif
}

void ANALYZE_LED(void) {
  
  #if USE_LED == 1
  
    #if DEBUG_FUNCTIONS_COMPONENTS == 1
      Serial.println(F("ANALYZE_LED"));
    #endif
  
  #endif
}

void ANALYZE_BUZZER(void) {
  
  #if USE_BUZZER == 1
  
    #if DEBUG_FUNCTIONS_COMPONENTS == 1
      Serial.println(F("ANALYZE_BUZZER"));
    #endif
  
  #endif
}

void ANALYZE_RGB(void) {

  #if USE_RGB == 1
  
    #if DEBUG_FUNCTIONS_COMPONENTS == 1
      Serial.println(F("ANALYZE_RGB"));
    #endif

    if (LUX_VALUE >= SETTINGS.RGB_LAMP_TRESHHOLD) {
      if (SETTINGS.RGB_LAMP_DAY_MODE == 1) {
        for (uint8_t i = 0; i < 3; i++) {
          RGB_LAMP_COLOR_GOAL[i] = 0;
        }
      } else if (SETTINGS.RGB_LAMP_DAY_MODE == 2) {
        for (uint8_t i = 0; i < 3; i++) {
          RGB_LAMP_COLOR_GOAL[i] = SETTINGS.RGB_LAMP_DAY_COLOR[i];
        }
      }
    } else {
      if (SETTINGS.RGB_LAMP_NIGHT_MODE == 1) {
        for (uint8_t i = 0; i < 3; i++) {
          RGB_LAMP_COLOR_GOAL[i] = 0;
        }
      } else if (SETTINGS.RGB_LAMP_NIGHT_MODE == 2) {
        for (uint8_t i = 0; i < 3; i++) {
          RGB_LAMP_COLOR_GOAL[i] = SETTINGS.RGB_LAMP_NIGHT_COLOR[i];
        }
      }
    }
  
    bool tmp_RGB_LAMP_STATION_ALTERED = false;
    for (uint8_t i = 0; i < 3; i++) {
      if (RGB_LAMP_COLOR_CURRENT[i] != RGB_LAMP_COLOR_GOAL[i]) {
        tmp_RGB_LAMP_STATION_ALTERED = true;
        if (RGB_LAMP_COLOR_CURRENT[i] > RGB_LAMP_COLOR_GOAL[i] + 10) {
          RGB_LAMP_COLOR_CURRENT[i] -= 10;
        } else if (RGB_LAMP_COLOR_CURRENT[i] < RGB_LAMP_COLOR_GOAL[i] - 10) {
          RGB_LAMP_COLOR_CURRENT[i] += 10;
        } else {
          RGB_LAMP_COLOR_CURRENT = RGB_LAMP_COLOR_GOAL;
        }
      }
    }
  
    if (tmp_RGB_LAMP_STATION_ALTERED) {
      if (LUX_VALUE >= SETTINGS.RGB_LAMP_TRESHHOLD) {
        RGB_LAMP.writeRGB(RGB_LAMP_COLOR_CURRENT[0], RGB_LAMP_COLOR_CURRENT[1], RGB_LAMP_COLOR_CURRENT[2]);
      } else {
        RGB_LAMP.writeRGB(RGB_LAMP_COLOR_CURRENT[0], RGB_LAMP_COLOR_CURRENT[1], RGB_LAMP_COLOR_CURRENT[2]);
      }
    }
    
  #endif
}

void ANALYZE_SEVSEG(void) {
  
  #if USE_SEVSEG == 1
  
    #if DEBUG_FUNCTIONS_COMPONENTS == 1
      Serial.println(F("ANALYZE_SEVSEG"));
    #endif
  
  #endif
}

void ANALYZE_LCD(void) {

  #if USE_LCD == 1
  
    #if DEBUG_FUNCTIONS_COMPONENTS == 1
      Serial.println(F("ANALYZE_LCD"));
    #endif
  
  #endif
}

void ANALYZE_BUTTONS(void) {

  #if USE_BUTTONS == 1
  
    #if DEBUG_FUNCTIONS_COMPONENTS == 1
      Serial.println(F("ANALYZE_BUTTONS"));
    #endif
  
  #endif
}

void ANALYZE_KEYPAD(void) {

  #if USE_KEYPAD == 1
  
    #if DEBUG_FUNCTIONS_COMPONENTS == 1
      Serial.println(F("ANALYZE_KEYPAD"));
    #endif
  
  #endif
}

void ANALYZE_RTC(void) {
  
  #if USE_RTC == 1
  
    #if DEBUG_FUNCTIONS_COMPONENTS == 1
      Serial.println(F("ANALYZE_RTC"));
    #endif
  
    if (HELPERS_I2C_CHECK(DS1307_ADDRESS) && DS1307.isrunning()) {
      
      RTC_ERROR = false;
      RTC_DATETIME = DS1307.now();
      
      // Set total timer
      if (RTC_DATETIME.unixtime() - RTC_EPOCH_LAST >= 3600) {
        RTC_TOTAL_TIMER++;
        RTC_EPOCH_LAST = RTC_DATETIME.unixtime();
        #if USE_EEPROM_INT == 1
          EEPROM.put(EEPROM_INT_ADDRESS_RTC_TOTAL_TIMER, RTC_TOTAL_TIMER);
          EEPROM.commit();
        #endif
        #if USE_EEPROM_EXT == 1
          // TBC
        #endif
      }

      // Calculate Jalali Date
      uint16_t tmp_YEAR = RTC_DATETIME.year();
      uint8_t tmp_MONTH = RTC_DATETIME.month();
      uint8_t tmp_DAY = RTC_DATETIME.day();
      uint16_t tt = 0, sD = 0;
      uint16_t j_year = 0, j_month = 0, j_day = 0;
      uint16_t dWM[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
      uint16_t dWKM[12] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
//      int tmp_MONTHlist[12] = {31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 30};
      if (tmp_YEAR == ((tmp_YEAR / 4) * 4)) {
        if ((tmp_MONTH > 2 && tmp_DAY > 19) || (tmp_MONTH > 3)) {
          j_year = tmp_YEAR - 621;
          tt = dWKM[tmp_MONTH - 1] + tmp_DAY - 80;
        } else {
          j_year = tmp_YEAR - 622;
          tt = dWKM[tmp_MONTH - 1] + tmp_DAY + 285;
        }
      } else {
        if ((tmp_MONTH > 2 && tmp_DAY > 20) || (tmp_MONTH > 3)) {
          j_year = tmp_YEAR - 621;
          tt = dWM[tmp_MONTH - 1] + tmp_DAY - 80;
        } else {
          j_year = tmp_YEAR - 622;
          tt = dWM[tmp_MONTH - 1] + tmp_DAY + 285;
        }
      }
      sD = tt;
      if (sD > 185) {
        j_month = 7 + ((sD - 186) / 30);
        j_day = sD - (185 + (((sD - 186) / 30) * 30));
        if ((tmp_YEAR - 1) == (((tmp_YEAR - 1) / 4) * 4) && (tmp_MONTH < 4)) {
          sD = sD;
          j_month = 8 + ((sD - 186) / 30);
          j_day = 1 + sD - (185 + (((sD - 186) / 30) * 30));
        }
      }
      if (sD < 186) {
        j_month = ((sD) / 31) + 1;
        j_day = (1 + sD - ((j_month - 1) * 31));
      }
      RTC_CALENDAR.J_YEAR = j_year;
      RTC_CALENDAR.J_MONTH = j_month;
      RTC_CALENDAR.J_DAY = j_day;
    } else {
      RTC_ERROR = true;
    }

  #endif
}

void ANALYZE_MULTIPLEXER(void) {
  
  #if USE_MULTIPLEXER == 1
  
    #if DEBUG_FUNCTIONS_COMPONENTS == 1
      Serial.println(F("ANALYZE_MULTIPLEXER"));
    #endif

    #if USE_MULTIPLEXER_PCF8574 == 1
    
      // Check if botton is pressed
      if (HELPERS_I2C_CHECK(PCF8574_ADDRESS)) {
        MULTIPLEXER_ERROR = false;
        byte tmp_PCF8574_READINGS = (byte)~PCF8574.read();
        uint8_t tmp_PCF8574_READINGS_BUTTONS = tmp_PCF8574_READINGS & 15;
//        uint8_t tmp_PCF8574_READINGS_RELAYS = (tmp_PCF8574_READINGS & 240) >> 4;
  
        if (tmp_PCF8574_READINGS_BUTTONS > 0) {
          #if MULTIPLEXER_PCF8574_DEBUG == 1
            Serial.print(F("MULTIPLEXER button press detected: "));
            Serial.println(tmp_PCF8574_READINGS_BUTTONS, BIN);
          #endif
          if (PCF8574_READINGS_BUTTONS_LAST == tmp_PCF8574_READINGS_BUTTONS) {
            PCF8574_READINGS_BUTTONS_TURNS++;
          } else {
            PCF8574_READINGS_BUTTONS_LAST = tmp_PCF8574_READINGS_BUTTONS;
            PCF8574_READINGS_BUTTONS_TURNS = 0;
          }
          return;
        // Check if button is released
        } else if (PCF8574_READINGS_BUTTONS_LAST > 0) {
          #if MULTIPLEXER_PCF8574_DEBUG == 1
            Serial.print(F("MULTIPLEXER release detected: "));
            Serial.print(PCF8574_READINGS_BUTTONS_LAST);
            Serial.print(F(", duration: "));
            Serial.println(PCF8574_READINGS_BUTTONS_TURNS);
          #endif
          if (PCF8574_READINGS_BUTTONS_LAST == 1) {
            if (PCF8574_READINGS_BUTTONS_TURNS < 3) {
              SETTINGS.RELAY_1_MODE_0_STATE = !SETTINGS.RELAY_1_MODE_0_STATE;
              SETTINGS.RELAY_1_MODE = 0;
            } else {
              SETTINGS.RELAY_1_MODE++;
              if (SETTINGS.RELAY_1_MODE > 2) SETTINGS.RELAY_1_MODE = 1;
            }
          } else if (PCF8574_READINGS_BUTTONS_LAST == 2) {
            if (PCF8574_READINGS_BUTTONS_TURNS < 3) {
              SETTINGS.RELAY_2_MODE_0_STATE = !SETTINGS.RELAY_2_MODE_0_STATE;
              SETTINGS.RELAY_2_MODE = 0;
            } else {
              SETTINGS.RELAY_2_MODE++;
              if (SETTINGS.RELAY_2_MODE > 2) SETTINGS.RELAY_2_MODE = 1;
            }
          } else if (PCF8574_READINGS_BUTTONS_LAST == 4) {
            if (PCF8574_READINGS_BUTTONS_TURNS < 3) {
              SETTINGS.RELAY_3_MODE_0_STATE = !SETTINGS.RELAY_3_MODE_0_STATE;
              SETTINGS.RELAY_3_MODE = 0;
            } else {
              SETTINGS.RELAY_3_MODE++;
              if (SETTINGS.RELAY_3_MODE > 2) SETTINGS.RELAY_3_MODE = 1;
            }
          } else if (PCF8574_READINGS_BUTTONS_LAST == 8) {
            if (PCF8574_READINGS_BUTTONS_TURNS < 3) {
              SETTINGS.RELAY_TEMP_MODE_0_STATE = !SETTINGS.RELAY_TEMP_MODE_0_STATE;
              SETTINGS.RELAY_TEMP_MODE = 0;
            } else {
              SETTINGS.RELAY_TEMP_MODE = 1;
            }            
          }
          PCF8574_READINGS_BUTTONS_LAST = 0;
          PCF8574_READINGS_BUTTONS_TURNS = 0;
          SETTINGS_ALTERED = true;
        }
        
      #endif

      #if USE_RTC == 1
        uint32_t tmp_UNIX = RTC_DATETIME.unixtime();
        // Manage manual mode
        if (SETTINGS.RELAY_1_MODE == 0) {
          PCF8574_RELAY_1_STATE = SETTINGS.RELAY_1_MODE_0_STATE;
        // Manage absolute time (of day) mode
        } else if (SETTINGS.RELAY_1_MODE == 1) {
          if (SETTINGS.RELAY_1_MODE_1_ACTIVATE <= tmp_UNIX && tmp_UNIX <= SETTINGS.RELAY_1_MODE_1_DEACTIVATE) {
            for (uint8_t i = 0; i < 10; i++) {
              if (SETTINGS.RELAY_1_MODE_1_ENABLE[i]) {
                if (SETTINGS.RELAY_1_MODE_1_ON[i] <= (tmp_UNIX % 86400) && (tmp_UNIX % 86400) <= SETTINGS.RELAY_1_MODE_1_OFF[i]) {
                  PCF8574_RELAY_1_STATE = true;
                } else {
                  PCF8574_RELAY_1_STATE = false;
                }
              }
            }
          } else {
            PCF8574_RELAY_1_STATE = false;
          }
        // Manage interval mode
        } else if (SETTINGS.RELAY_1_MODE == 2) {
          if (SETTINGS.RELAY_1_MODE_2_ACTIVATE <= tmp_UNIX && tmp_UNIX <= SETTINGS.RELAY_1_MODE_2_DEACTIVATE) {
            uint32_t tmp_ELAPSED = tmp_UNIX % (SETTINGS.RELAY_1_MODE_2_DURATION + SETTINGS.RELAY_1_MODE_2_INTERVAL);
            if (tmp_ELAPSED < SETTINGS.RELAY_1_MODE_2_DURATION) {
              if (SETTINGS.RELAY_1_MODE_2_COUNT == 0) {
                PCF8574_RELAY_1_STATE = true;
              } else if (SETTINGS.RELAY_1_MODE_2_COUNT - SETTINGS.RELAY_1_MODE_2_COUNT_ELAPSED > 0) {
                PCF8574_RELAY_1_STATE = true;
                SETTINGS.RELAY_1_MODE_2_COUNT_ELAPSED++;
              }
            } else {
              PCF8574_RELAY_1_STATE = false;
            }
          } else {
            PCF8574_RELAY_1_STATE = false;
          }
        }
      #endif

      // Manage temp relay 
      if (SETTINGS.RELAY_TEMP_MODE == 0) {
        PCF8574_RELAY_TEMP_STATE = SETTINGS.RELAY_TEMP_MODE_0_STATE;
      } else if (SETTINGS.RELAY_TEMP_MODE == 1) {
        if (DS18B20_TEMP_IN > SETTINGS.TEMP_TRESHHOLD + 0.5) {
          PCF8574_RELAY_TEMP_STATE = 0;
        } else if (DS18B20_TEMP_IN < SETTINGS.TEMP_TRESHHOLD - 0.5) {
          PCF8574_RELAY_TEMP_STATE = 1;
        }
      }

      // Check and set if relay state changed
      uint8_t tmp_PCF8574_RELAYS = PCF8574_RELAY_1_STATE + (PCF8574_RELAY_2_STATE * 2) + (PCF8574_RELAY_3_STATE * 4) + (PCF8574_RELAY_TEMP_STATE * 8);
      if (PCF8574_READINGS_RELAYS_LAST != tmp_PCF8574_RELAYS) {
        #if MULTIPLEXER_PCF8574_DEBUG == 1
          Serial.printf("Relays set from %i to %i\n", PCF8574_READINGS_RELAYS_LAST, tmp_PCF8574_RELAYS);
        #endif
        PCF8574_READINGS_RELAYS_LAST = tmp_PCF8574_RELAYS;
        PCF8574.write((byte)~(tmp_PCF8574_RELAYS << 4));
      }
    } else {
      #if MULTIPLEXER_PCF8574_DEBUG == 1
        Serial.println(F("PCF8574 not found."));
      #endif
      MULTIPLEXER_ERROR = true;
    }
  
  #endif
}

void ANALYZE_FINGER(void) {
  
  #if USE_FINGER == 1
  
    #if DEBUG_FUNCTIONS_COMPONENTS == 1
      Serial.println(F("ANALYZE_FINGER"));
    #endif
  
  #endif
}

void ANALYZE_RFID(void) {
  
  #if USE_RFID == 1
  
    #if DEBUG_FUNCTIONS_COMPONENTS == 1
      Serial.println(F("ANALYZE_RFID"));
    #endif
  
  #endif
}

void ANALYZE_RC(void) {
  
  #if USE_RC == 1
  
    #if DEBUG_FUNCTIONS_COMPONENTS == 1
      Serial.println(F("ANALYZE_RC"));
    #endif
    
  #endif
}

void ANALYZE_THERMOMETER(void) {
  
  #if USE_THERMOMETER == 1
  
    #if DEBUG_FUNCTIONS_COMPONENTS == 1
      Serial.println(F("ANALYZE_THERMOMETER"));
    #endif

    #if USE_THERMOMETER_DS18B20 == 1
      DS18B20.requestTemperatures();
      float tmp_TEMP_0 = DS18B20.getTempCByIndex(0);
      float tmp_TEMP_1 = DS18B20.getTempCByIndex(1);
      if (SETTINGS.DS18B20_TEMP_INVERT) {
        if (abs(DS18B20_TEMP_IN - tmp_TEMP_1) < 30) DS18B20_TEMP_IN = tmp_TEMP_1;
        if (abs(DS18B20_TEMP_OUT - tmp_TEMP_0) < 30) DS18B20_TEMP_OUT = tmp_TEMP_0;
      } else {
        if (abs(DS18B20_TEMP_IN - tmp_TEMP_0) < 30) DS18B20_TEMP_IN = tmp_TEMP_0;
        if (abs(DS18B20_TEMP_OUT - tmp_TEMP_1) < 30) DS18B20_TEMP_OUT = tmp_TEMP_1;
      }
    #endif
    
  #endif
}

void ANALYZE_HUMIDITY(void) {
  
  #if USE_HUMIDITY == 1
  
    #if DEBUG_FUNCTIONS_COMPONENTS == 1
      Serial.println(F("ANALYZE_HUMIDITY"));
    #endif
  
  #endif
}

void ANALYZE_PIR(void) {
  
  #if USE_MOT

    #if DEBUG_FUNCTIONS_COMPONENTS == 1
      Serial.println(F("ANALYZE_PIR"));
    #endif
    
  #endif
}

void ANALYZE_GAS(void) {
  
  #if USE_GAS

    #if DEBUG_FUNCTIONS_COMPONENTS == 1
      Serial.println(F("ANALYZE_GAS"));
    #endif
  
  #endif
}

void ANALYZE_LDR(void) {
  
  #if USE_LDR

    #if DEBUG_FUNCTIONS_COMPONENTS == 1
      Serial.println(F("ANALYZE_LDR"));
    #endif
  
    LUX_VALUE = analogRead(LDR_PIN);
  
  #endif
}

void ANALYZE_MOTOR(void) {
  
  #if USE_MOTOR
  
    #if DEBUG_FUNCTIONS_COMPONENTS == 1
      Serial.println(F("ANALYZE_MOTOR"));
    #endif
    
    #if USE_MOTOR_SERVO == 1

//      pinMode(PIN_MOTOR, OUTPUT);
//      while (SERVO.read() < 180) {
//        SERVO.write(SERVO.read() + 1);
//        delay(5);
//      }
//      while (SERVO.read() > 0) {
//        SERVO.write(SERVO.read() - 1);
//        delay(5);
//      }
//      pinMode(PIN_MOTOR, INPUT);
    
    #endif
    
  #endif
}

void ANALYZE_CURRENT(void) {
  
  #if USE_CURRENT
  
    #if DEBUG_FUNCTIONS_COMPONENTS == 1
      Serial.println(F("ANALYZE_CURRENT"));
    #endif
  
  #endif
}
