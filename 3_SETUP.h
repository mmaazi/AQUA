Scheduler SCHEDULER;

Task TASK_LOOP_100MILISECOND(100, TASK_FOREVER, &LOOP_100MILISECOND);
Task TASK_LOOP_PRINT(10000, TASK_FOREVER, &LOOP_PRINT);
#if USE_ESP_SYNCSERVER == 1
  Task TASK_SYNCSERVER(SYNCSERVER_INTERVAL, TASK_FOREVER, &ANALYZE_SYNCSERVER);
#endif
#if USE_ESP_OTA == 1
  Task TASK_OTA(OTA_INTERVAL, TASK_FOREVER, &ANALYZE_OTA);
#endif
#if USE_RADIO == 1
  Task TASK_RADIO(1000, TASK_FOREVER, &ANALYZE_RADIO);
#endif
#if USE_SIMCARD == 1
  Task TASK_SIMCARD(SIMCARD_INTERVAL, TASK_FOREVER, &ANALYZE_SIMCARD);
#endif
#if USE_EEPROM == 1
  Task TASK_EEPROM(EEPROM_INTERVAL, TASK_FOREVER, &ANALYZE_EEPROM);
#endif
#if USE_SD == 1
  Task TASK_SD(SD_INTERVAL, TASK_FOREVER, &ANALYZE_SD);
#endif
#if USE_TAMPER == 1
  Task TASK_TAMPER(TAMPER_INTERVAL, TASK_FOREVER, &ANALYZE_TAMPER);
#endif
#if USE_LED == 1
  Task TASK_LED(LED_INTERVAL, TASK_FOREVER, &ANALYZE_LED);
#endif
#if USE_BUZZER == 1
  Task TASK_BUZZER(BUZZER_INTERVAL, TASK_FOREVER, &ANALYZE_BUZZER);
#endif
#if USE_RGB == 1
  Task TASK_RGB(RGB_INTERVAL, TASK_FOREVER, &ANALYZE_RGB);
#endif
#if USE_SEVSEG == 1
  Task TASK_SEVSEG(SEVSEG_INTERVAL, TASK_FOREVER, &ANALYZE_SEVSEG);
#endif
#if USE_LCD == 1
  Task TASK_LCD(LCD_INTERVAL, TASK_FOREVER, &ANALYZE_LCD);
#endif
#if USE_BUTTONS == 1
  Task TASK_BUTTONS(BUTTONS_INTERVAL, TASK_FOREVER, &ANALYZE_BUTTONS);
#endif
#if USE_KEYPAD == 1
  Task TASK_KEYPAD(KEYPAD_INTERVAL, TASK_FOREVER, &ANALYZE_KEYPAD);
#endif
#if USE_RTC == 1
  Task TASK_RTC(RTC_INTERVAL, TASK_FOREVER, &ANALYZE_RTC);
#endif
#if USE_MULTIPLEXER == 1
  Task TASK_MULTIPLEXER(MULTIPLEXER_INTERVAL, TASK_FOREVER, &ANALYZE_MULTIPLEXER);
#endif
#if USE_FINGER == 1
  Task TASK_FINGER(FINGER_INTERVAL, TASK_FOREVER, &ANALYZE_FINGER);
#endif
#if USE_RFID == 1
  Task TASK_RFID(RFID_INTERVAL, TASK_FOREVER, &ANALYZE_RFID);
#endif
#if USE_RC == 1
  Task TASK_RC(RC_INTERVAL, TASK_FOREVER, &ANALYZE_RC);
#endif
#if USE_THERMOMETER == 1
  Task TASK_THERMOMETER(THERMOMETER_INTERVAL, TASK_FOREVER, &ANALYZE_THERMOMETER);
#endif
#if USE_HUMIDITY == 1
  Task TASK_HUMIDITY(HUMIDITY_INTERVAL, TASK_FOREVER, &ANALYZE_HUMIDITY);
#endif
#if USE_PIR == 1
  Task TASK_PIR(PIR_INTERVAL, TASK_FOREVER, &ANALYZE_PIR);
#endif
#if USE_GAS == 1
  Task TASK_GAS(GAS_INTERVAL, TASK_FOREVER, &ANALYZE_GAS);
#endif
#if USE_LDR == 1
  Task TASK_LDR(LDR_INTERVAL, TASK_FOREVER, &ANALYZE_LDR);
#endif
#if USE_MOTOR == 1
  Task TASK_MOTOR(MOTOR_INTERVAL, TASK_FOREVER, &ANALYZE_MOTOR);
#endif
#if USE_CURRENT == 1
  Task TASK_CURRENT(CURRENT_INTERVAL, TASK_FOREVER, &ANALYZE_CURRENT);
#endif

void SETUP_SCHEDULER(void) {

  SCHEDULER.init();

  SCHEDULER.addTask(TASK_LOOP_100MILISECOND);
  SCHEDULER.addTask(TASK_LOOP_PRINT);
  #if USE_ESP_SYNCSERVER == 1
    SCHEDULER.addTask(TASK_SYNCSERVER);
  #endif
  #if USE_ESP_OTA == 1
    SCHEDULER.addTask(TASK_OTA);
  #endif
  #if USE_RADIO == 1
    SCHEDULER.addTask(TASK_RADIO);
  #endif
  #if USE_SIMCARD == 1
    SCHEDULER.addTask(TASK_SIMCARD);
  #endif
  #if USE_EEPROM == 1
    SCHEDULER.addTask(TASK_EEPROM);
  #endif
  #if USE_SD == 1
    SCHEDULER.addTask(TASK_SD);
  #endif
  #if USE_TAMPER == 1
    SCHEDULER.addTask(TASK_TAMPER);
  #endif
  #if USE_LED == 1
    SCHEDULER.addTask(TASK_LED);
  #endif
  #if USE_BUZZER == 1
    SCHEDULER.addTask(TASK_BUZZER);
  #endif
  #if USE_RGB == 1
    SCHEDULER.addTask(TASK_RGB);
  #endif
  #if USE_SEVSEG == 1
    SCHEDULER.addTask(TASK_SEVSEG);
  #endif
  #if USE_LCD == 1
    SCHEDULER.addTask(TASK_LCD);
  #endif
  #if USE_BUTTONS == 1
    SCHEDULER.addTask(TASK_BUTTONS);
  #endif
  #if USE_KEYPAD == 1
    SCHEDULER.addTask(TASK_KEYPAD);
  #endif
  #if USE_RTC == 1
    SCHEDULER.addTask(TASK_RTC);
  #endif
  #if USE_MULTIPLEXER == 1
    SCHEDULER.addTask(TASK_MULTIPLEXER);
  #endif
  #if USE_FINGER == 1
    SCHEDULER.addTask(TASK_FINGER);
  #endif
  #if USE_RFID == 1
    SCHEDULER.addTask(TASK_RFID);
  #endif
  #if USE_RC == 1
    SCHEDULER.addTask(TASK_RC);
  #endif
  #if USE_THERMOMETER == 1
    SCHEDULER.addTask(TASK_THERMOMETER);
  #endif
  #if USE_HUMIDITY == 1
    SCHEDULER.addTask(TASK_HUMIDITY);
  #endif
  #if USE_PIR == 1
    SCHEDULER.addTask(TASK_PIR);
  #endif
  #if USE_GAS == 1
    SCHEDULER.addTask(TASK_GAS);
  #endif
  #if USE_LDR == 1
    SCHEDULER.addTask(TASK_LDR);
  #endif
  #if USE_MOTOR == 1
    SCHEDULER.addTask(TASK_MOTOR);
  #endif
  #if USE_CURRENT == 1
    SCHEDULER.addTask(TASK_CURRENT);
  #endif
}

void SETUP_PROTOCOLS(void) {

  #if USE_SERIAL == 1
    Serial.begin(SERIAL_BOUD);
  #endif
  
  #if USE_SOFTSERIAL == 1
    SOFTSERIAL.begin(SOFTSERIAL_BOUD);
  #endif
  
  #if USE_WIRE == 1
    Wire.begin(WIRE_PINS[0], WIRE_PINS[1]);
  #endif
  
  #if USE_ONEWIRE == 1
  #endif
  
  #if USE_SOFTSPI == 1
    SOFTSPI.begin();
  #endif
}

void SETUP_REGISTERS(void) {

  #if DEBUG_FUNCTIONS_SETUP == 1
    Serial.println(F("SETUP_REGISTERS"));
  #endif
}

void SETUP_PINS(void) {

  #if DEBUG_FUNCTIONS_SETUP == 1
    Serial.println(F("SETUP_PINS"));
  #endif
}

void SETUP_INTERRUPTS(void) {

  #if DEBUG_FUNCTIONS_SETUP == 1
    Serial.println(F("SETUP_INTERRUPTS"));
  #endif
}

void SETUP_ESP(void) {

  #if USE_ESP == 1
  
    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_ESP"));
    #endif
    
    if (ESP.eraseConfig()) {
      ESP_ERROR = false;
    } else {
      ESP_ERROR = true;
    }
    
  #endif
}

void SETUP_WIFI(void) {

  #if USE_ESP_WIFI == 1

    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_WIFI"));
    #endif

    if ((SETTINGS.WIFI_SSID != NULL) && (SETTINGS.WIFI_SSID[0] == '\0')) {
      #if ESP_WIFI_DEBUG > 0
        Serial.println(F("WiFi not enabled. SSID is not defined."));
      #endif
      WIFI_ERROR = true;
    } else {
      #if ESP_WIFI_DEBUG > 0
        Serial.print(F("Setting up Wifi with "));
        Serial.print(F("SSID: "));
        Serial.print(SETTINGS.WIFI_SSID);
        Serial.print(F(" and Password: "));
        Serial.println(SETTINGS.WIFI_PASSWORD);
      #endif
      WiFi.persistent(false);
      WiFi.mode(WIFI_STA);
      if (!SETTINGS.WIFI_DHCP) {
        WiFi.config(SETTINGS.WIFI_IP, SETTINGS.WIFI_GATE, SETTINGS.WIFI_MASK);
      }
      WiFi.begin(SETTINGS.WIFI_SSID, SETTINGS.WIFI_PASSWORD);
      uint8_t tmp_COUNTER = 0;
      while (WiFi.status() != WL_CONNECTED && tmp_COUNTER < 20) {
        #if ESP_WIFI_DEBUG > 0
          Serial.print(F("."));
        #endif
        tmp_COUNTER++;
        delay(500);
      }
      if (WiFi.status() == WL_CONNECTED) {
        #if ESP_WIFI_DEBUG > 0
          Serial.print(F("WiFi Connected. IP: "));
          Serial.println(WiFi.localIP());
        #endif
        if (SETTINGS.WIFI_DHCP) {
          SETTINGS.WIFI_IP = WiFi.localIP();
          SETTINGS.WIFI_GATE = WiFi.gatewayIP();
          SETTINGS.WIFI_MASK = WiFi.subnetMask();
        }
        SETTINGS.WIFI_DHCP = false;
        SETTINGS_ALTERED = true;
        WIFI_ERROR = false;
        HELPER_EXIP();
        HELPER_PING();
      } else {
        #if ESP_WIFI_DEBUG > 0
          Serial.println(F("Wifi failed to start. AP will be enabled forcibly."));
        #endif
        SETTINGS.WIFI_DHCP = true;
        WIFI_ERROR = true;
        SETUP_AP();
      }
    }

  #endif
}

void SETUP_AP(void) {
  
  #if USE_ESP_WIFI == 1
  
    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_AP"));
    #endif
  
    #if ESP_WIFI_DEBUG > 0
        Serial.print(F("Setting up AP: "));
    #endif
    if (WIFI_ERROR) {
      WiFi.mode(WIFI_AP);
    } else {
      WiFi.mode(WIFI_AP_STA);
    }
    IPAddress tmp_AP_IP(192, 168, 2, 110);
    IPAddress tmp_AP_GATE(192, 168, 2, 1);
    IPAddress tmp_AP_MASK(255, 255, 255, 0);
    WiFi.softAPConfig(tmp_AP_IP, tmp_AP_GATE, tmp_AP_MASK);
    char tmp_AP_SSID[32];
    char tmp_AP_PASSWORD[32];
    sprintf(tmp_AP_SSID, "AQUA_%lu", (long unsigned int)ESP.getChipId());
    strcpy(tmp_AP_PASSWORD, "12344321");
    WiFi.softAP(tmp_AP_SSID, tmp_AP_PASSWORD);
    #if ESP_WIFI_DEBUG > 0
      Serial.println(F(" Successful."));
    #endif

  #endif
}

void SETUP_SYNCSERVER(void) {
  
  #if USE_ESP_SYNCSERVER == 1
  
    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_SYNCSERVER"));
    #endif
    
  #endif
}

void SETUP_WEBSERVER(void) {
  
  #if USE_ESP_WEBSERVER == 1

    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_WEBSERVER"));
    #endif
  
    WEBSERVER.begin();
    
  #endif
}

void SETUP_RADIO(void) {

  #if USE_RADIO == 1

    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_RADIO"));
    #endif

    #if USE_RADIO_MESH == 1
      MESH.setNodeID(1);
      MESH.begin();
      RADIO.printDetails();
    #endif
    
  #endif
}

void SETUP_SIMCARD(void) {
  
  #if USE_SIMCARD == 1

    #if DEBUG_FUNCTIONS == 1
      Serial.println(F("SETUP_SIMCARD"));
    #endif
    
    #if USE_SIMCARD_SIM800 == 1

      SIM800.begin(9600);
      SIM800.setTimeout(3000);
      SIM800.monSpeakerVol("9");

    #endif
    
  #endif
}

void SETUP_MESSENGER(void) {

  #if USE_MESSENGER == 1

    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_MESSENGER"));
    #endif
    
    MESSENGER.attach(LOOP_MESSENGER);

  #endif
}

void SETUP_EEPROM(void) {

  #if USE_EEPROM == 1
  
    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_EEPROM"));
    #endif
  
    #if USE_EEPROM_INT == 1
    
      EEPROM.begin(EEPROM_INT_SIZE);
      #if EEPROM_DEBUG > 0
          Serial.println(F("Accessing ESP EEPROM."));
      #endif  
      uint8_t tmp_EEPROM_INT_FLAG_ERROR = false;
      uint8_t tmp_EEPROM_INT_FLAG_APPROVE = false;
      // Checking EEPROM flags
      for (uint8_t i = EEPROM_INT_ADDRESS_FLAG; i < EEPROM_INT_ADDRESS_FLAG + 10; i++) {
        if (EEPROM.read(i) == (uint8_t)EEPROM_INT_FLAG) {
          tmp_EEPROM_INT_FLAG_APPROVE = true;
        } else {
          tmp_EEPROM_INT_FLAG_ERROR = true;
        }
      }
      // Repairing corrupted EEPROM
      if (tmp_EEPROM_INT_FLAG_ERROR && tmp_EEPROM_INT_FLAG_APPROVE) {
        #if EEPROM_DEBUG > 0
            Serial.println(F("ESP eeprom corrupted. Repairing by syncing from server."));
        #endif
        EEPROM_ERROR = true;
        // TBC
      // Reading EEPROM
      } else if (!tmp_EEPROM_INT_FLAG_ERROR && tmp_EEPROM_INT_FLAG_APPROVE) {
        #if EEPROM_DEBUG > 0
          Serial.print(F("ESP eeprom OK. Reading..."));
        #endif
        #if USE_TAMPER == 1
          EEPROM.get(EEPROM_INT_ADDRESS_EVER_TAMPERED, ERROR_EVER_TAMPERED);
        #endif
        #if USE_RTC == 1
          EEPROM.get(EEPROM_INT_ADDRESS_RTC_TOTAL_TIMER, RTC_TOTAL_TIMER);
        #endif
        EEPROM.get(EEPROM_INT_ADDRESS_STATION, STATION);
        EEPROM.get(EEPROM_INT_ADDRESS_CUSTOMER, CUSTOMER);
        EEPROM.get(EEPROM_INT_ADDRESS_SETTINGS, SETTINGS);
        #if EEPROM_DEBUG > 0
          Serial.println(F("Done."));
        #endif
        
      // Initializing EEPROM
      } else {
        #if EEPROM_DEBUG > 0
          Serial.print(F("ESP eeprom is not initialized. Initializing... "));
        #endif
        for (uint16_t i = 0; i < EEPROM_INT_SIZE; i++) {
          EEPROM.write(i, 0);
        }
        for (uint8_t i = EEPROM_INT_ADDRESS_FLAG; i < EEPROM_INT_ADDRESS_FLAG + 10; i++) {
          EEPROM.write(i, EEPROM_INT_FLAG);
    
        }
        EEPROM.commit();
        #if EEPROM_DEBUG > 0
          Serial.println(F("Done."));
        #endif
      }
  
    #endif
  
    #if USE_EEPROM_EXT
    
      // TBC
      
    #endif
    
  #endif
}

void SETUP_SD(void) {
  
  #if USE_SD == 1
  
    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_SD"));
    #endif
  
    SD.begin(SD_PIN);
  
  #endif
}

void SETUP_TAMPER(void) {

  #if USE_TAMPER == 1
  
    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_TAMPER"));
    #endif
    
    pinMode(TAMPER_PIN, INPUT_PULLUP);
    
  #endif
}

void SETUP_LED(void) {

  #if USE_LED == 1

    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_LED"));
    #endif
    
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

  #endif
}

void SETUP_BUZZER(void) {

  #if USE_BUZZER == 1

    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_BUZZER"));
    #endif
    
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, HIGH);

  #endif
}

void SETUP_RGB(void) {

  #if USE_RGB == 1

    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_RGB"));
    #endif
    
//    RGB_LED.writeRGB(0, 0, 0);
    RGB_LAMP.writeRGB(0, 0, 0);
    
    for (uint8_t i = 0; i < 3; i++) {
      RGB_LAMP_COLOR_CURRENT[i] = 0;
    }

  #endif
}

void SETUP_SEVSEG(void) {

  #if USE_SEVSEG == 1

    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_SEVSEG"));
    #endif
  
    SEVSEG.begin(SEVSEG_STATION, SEVSEG_DIGIT_COUNT, SEVSEG_DIGIT_PINS, SEVSEG_SEGMENT_PINS, SEVSEG_RESISTOR, SEVSEG_DELAY, SEVSEG_LEADING_ZERO, SEVSEG_NO_DECIMAL);
    SEVSEG.setBrightness(SEVSEG_BRIGHTNESS);
    
  #endif
}

void SETUP_LCD(void) {
  
  #if USE_LCD == 1

    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_LCD"));
    #endif
    
    #if USE_LCD_LCD5110 == 1
      LCD5110.begin();
    #endif
    
  #endif
}

void SETUP_BUTTONS(void) {
  
  #if USE_BUTTONS == 1
  
    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_BUTTONS"));
    #endif
    
  #endif
}

void SETUP_KEYPAD(void) {
  
  #if USE_KEYPAD == 1
  
    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_KEYPAD"));
    #endif
    
    #if USE_KEYPAD_4x4 == 1
      KEYPAD_4x4.addEventListener(ANALYZE_KEYPAD);
    #endif    

  #endif
}

void SETUP_RTC(void) {

  #if USE_RTC == 1

    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_RTC"));
    #endif
    
    #if USE_RTC_DS1307 == 1
      if (HELPERS_I2C_CHECK(DS1307_ADDRESS) && DS1307.begin()) {
        RTC_EPOCH_LAST = RTC_DATETIME.unixtime();
        RTC_ERROR = false;
      } else {
        RTC_ERROR = true;
      }

    #endif
    
  #endif
}

void SETUP_MULTIPLEXER(void) {

  #if USE_MULTIPLEXER == 1
  
    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_MULTIPLEXER"));
    #endif
    
    #if USE_MULTIPLEXER_PCF8574 == 1
      if (HELPERS_I2C_CHECK(PCF8574_ADDRESS)) {
        #if USE_MULTIPLEXER_PCF8574_INTERRUPT == 1
          pinMode(PCF8574_INTERRUPT_PIN, INPUT_PULLUP);
          PCF8574.enableInterrupt(PCF8574_INTERRUPT_PIN, ANALYZE_MULTIPLEXER);
          attachInterrupt(digitalPinToInterrupt(PCF8574_INTERRUPT_PIN), ANALYZE_MULTIPLEXER, FALLING);
        #endif
        PCF8574.begin(PCF8574_ADDRESS);
        PCF8574.pinMode(0, INPUT_PULLUP);
        PCF8574.pinMode(1, INPUT_PULLUP);
        PCF8574.pinMode(2, INPUT_PULLUP);
        PCF8574.pinMode(3, INPUT_PULLUP);
        PCF8574.pinMode(4, OUTPUT);
        PCF8574.digitalWrite(4, HIGH);
        PCF8574.pinMode(5, OUTPUT);
        PCF8574.digitalWrite(5, HIGH);
        PCF8574.pinMode(6, OUTPUT);
        PCF8574.digitalWrite(6, HIGH);
        PCF8574.pinMode(7, OUTPUT);
        PCF8574.digitalWrite(7, HIGH);
      } else {
        MULTIPLEXER_ERROR = true;
      }
  
    #endif
    
  #endif
}

void SETUP_FINGER(void) {
  
  #if USE_FINGER == 1
  
    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_FINGER"));
    #endif
    
  #endif  
}

void SETUP_RFID(void) {

  #if USE_RFID == 1
  
    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_RFID"));
    #endif

  #endif
}

void SETUP_RC(void) {

  #if USE_RC == 1
  
    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_RC"));
    #endif
  
    RC.enableReceive(RC_RECEIVE_PIN);
    RC.enableTransmit(RC_SEND_PIN);

  #endif
}

void SETUP_THERMOMETER(void) {

  #if USE_THERMOMETER == 1
  
    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_THERMOMETER"));
    #endif
    
    #if USE_THERMOMETER_DS18B20 == 1
      DS18B20.begin();
      DS18B20.getAddress(DS18B20_IN_ADDRESS, 0);
      DS18B20.setResolution(DS18B20_IN_ADDRESS, 10);
      DS18B20.getAddress(DS18B20_OUT_ADDRESS, 1);
      DS18B20.setResolution(DS18B20_OUT_ADDRESS, 10);
      DS18B20.setWaitForConversion(false);
    #endif
    
  #endif
}

void SETUP_HUMIDITY(void) {
  
  #if USE_HUMIDITY == 1

    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_HUMIDITY"));
    #endif
      
    #if USE_HUMIDITY_DHT11 == 1
      DHT11.begin();
    #endif
  
  #endif
}

void SETUP_PIR(void) {
  
  #if USE_PIR == 1
  
    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_PIR"));
    #endif
    
    pinMode(PIR_PIN, INPUT_PULLUP);
    
  #endif
}

void SETUP_GAS(void) {
  
  #if USE_GAS == 1
  
    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_GAS"));
    #endif
  
  #endif
}

void SETUP_LDR(void) {
  
  #if USE_LDR == 1
  
    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_LDR"));
    #endif

  #endif
}

void SETUP_MOTOR(void) {
  
  #if USE_MOTOR == 1
  
    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_MOTOR"));
    #endif
  
    #if USE_MOTOR_SERVO == 1
      SERVO.attach(SERVO_PIN);
      while (SERVO.read() > 0) {
        SERVO.write(SERVO.read() - 1);
        delay(15);
      }
      pinMode(SERVO_PIN, INPUT);
    #endif
    
  #endif
}

void SETUP_CURRENT(void) {
  
  #if USE_CURRENTRENT == 1
  
    #if DEBUG_FUNCTIONS_SETUP == 1
      Serial.println(F("SETUP_CURRENT"));
    #endif
    
    CURRENT.current(1, CURRENT_CONSTANT);
    pinMode(CURRENT_ZEROCROSS_PIN, INPUT);
    digitalWrite(CURRENT_ZEROCROSS_PIN, HIGH);
    attachInterrupt(0, COMPONENT_ANALYZE_CURRENT, RISING);

  #endif
}

void SETUP_EXECS(void) {

  #if DEBUG_FUNCTIONS_SETUP == 1
    Serial.println(F("SETUP_EXECS"));
  #endif
}

void SETUP_TEMPORARY(void) {
  
  #if DEBUG_FUNCTIONS_SETUP == 1
    Serial.println(F("SETUP_TEMPORARY"));
  #endif

  MESSENGER_LOGIN_A = true;
  MESSENGER_LOGIN_B = true;
}

void SETUP_START(void) {

  #if DEBUG_FUNCTIONS_SETUP == 1
    Serial.println(F("SETUP_START"));
  #endif

  TASK_LOOP_100MILISECOND.enable();
  TASK_LOOP_PRINT.enable();
  #if USE_ESP_SYNCSERVER == 1
    TASK_SYNCSERVER.enable();
  #endif
  #if USE_ESP_OTA == 1
    TASK_OTA.enable();
  #endif
  #if USE_RADIO == 1
    TASK_RADIO.enable();
  #endif
  #if USE_EEPROM == 1
    TASK_EEPROM.enable();
  #endif
  #if USE_SD == 1
    TASK_SD.enable();
  #endif
  #if USE_TAMPER == 1
    TASK_TAMPER.enable();
  #endif
  #if USE_LED == 1
    TASK_LED.enable();
  #endif
  #if USE_BUZZER == 1
    TASK_BUZZER.enable();
  #endif
  #if USE_RGB == 1
    TASK_RGB.enable();
  #endif
  #if USE_SEVSEG == 1
    TASK_SEVSEG.enable();
  #endif
  #if USE_LCD == 1
    TASK_LCD.enable();
  #endif
  #if USE_BUTTONS == 1
    TASK_BUTTONS.enable();
  #endif
  #if USE_KEYPAD == 1
    TASK_KEYPAD.enable();
  #endif
  #if USE_RTC == 1
    TASK_RTC.enable();
  #endif
  #if USE_MULTIPLEXER == 1
    TASK_MULTIPLEXER.enable();
  #endif
  #if USE_FINGER == 1
    TASK_FINGER.enable();
  #endif
  #if USE_RFID == 1
    TASK_RFID.enable();
  #endif
  #if USE_RC == 1
    TASK_RC.enable();
  #endif
  #if USE_THERMOMETER == 1
    TASK_THERMOMETER.enable();
  #endif
  #if USE_HUMIDITY == 1
    TASK_HUMIDITY.enable();
  #endif
  #if USE_PIR == 1
    TASK_PIR.enable();
  #endif
  #if USE_GAS == 1
    TASK_GAS.enable();
  #endif
  #if USE_LDR == 1
    TASK_LDR.enable();
  #endif
  #if USE_MOTOR == 1
    TASK_MOTOR.enable();
  #endif
  #if USE_CURRENT == 1
    TASK_CURRENT.enable();
  #endif
  #if USE_SIMCARD == 1
    TASK_SIMCARD.enable();
  #endif

  Serial.print(F("System ID: "));
  Serial.println(ESP.getChipId());
  Serial.print(F("Firmware version: "));
  Serial.println(FW_VERSION);
  Serial.printf("Built: %s %s\n", __DATE__, __TIME__);
  Serial.println(F("Created by Mehdi Maazi\n"));
}
