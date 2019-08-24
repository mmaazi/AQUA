//
//
//uint8_t HELPERS_ENCRYPT(uint8_t arg1_DATA, uint8_t arg2_COUNT) {
//
//  return arg1_DATA + (arg2_COUNT + 7) + (arg2_COUNT * (arg2_COUNT + 11)) + 17;
//}
//
//uint8_t HELPERS_DECRYPT(uint8_t arg1_DATA, uint8_t arg2_COUNT) {
//
//  return arg1_DATA - (arg2_COUNT + 7) - (arg2_COUNT * (arg2_COUNT + 11)) - 17;
//}
//
//
//
//template <class T> uint32_t HELPERS_CHECKSUM(const T &arg1_INPUT) {
//
//  uint32_t tmp_HELPERS_CHECKSUM;
//  byte* p = (byte*)(void*)&arg1_INPUT;
//  for (uint32_t i = 0; i < sizeof(arg1_INPUT); i++) tmp_HELPERS_CHECKSUM += (((int)(*p++)) * (i + 1));
//  return tmp_HELPERS_CHECKSUM;
//}
//
//String HTML_HELPERS_URLCODE(String arg1_INPUT) {
//
//  char tmp_CHAR;
//  String tmp_RESULT = "";
//  for (uint8_t i = 0; i < arg1_INPUT.length(); i++) {
//    tmp_CHAR = arg1_INPUT[i];
//    if (tmp_CHAR == '+') tmp_CHAR = ' ';
//    if (tmp_CHAR == '%') {
//      i++;
//      tmp_CHAR = arg1_INPUT[i];
//      i++;
//      tmp_CHAR = (HELPERS_HEX2INT(tmp_CHAR) << 4) | HELPERS_HEX2INT(arg1_INPUT[i]);
//    }
//    tmp_RESULT.concat(tmp_CHAR);
//  }
//  return tmp_RESULT;
//}

//bool EEPROM_CHECK(void);
//void EEPROM_MAP(uint16_t arg1_START, uint16_t arg2_FINISH);
//
//uint8_t EEPROM_get(uint32_t address);
//uint8_t EEPROM_get_uint8_t(uint32_t address);
//long EEPROM_get_long(uint32_t address);
//String EEPROM_get_string32(uint32_t beginaddress);
//String EEPROM_get_string64(uint32_t beginaddress);
//template <class T> uint16_t EEPROM_get_struct(uint16_t beginaddress, T &value);
//
//void EEPROM_set(uint32_t address, uint8_t data);
//void EEPROM_set_uint8_t(uint32_t address, uint8_t value);
//void EEPROM_set_long(uint32_t address, long value);
//void EEPROM_set_string32(uint32_t beginaddress, String string);
//void EEPROM_set_string64(uint32_t beginaddress, String string);
//template <class T> uint16_t EEPROM_set_struct(int beginaddress, const T &value);
//
//////////////////////////////////
//
//bool EEPROM_CHECK(void) {
//
//  Wire.beginTransmission(EEPROM_ADDRESS);
//  if (Wire.endTransmission() == 0) {
//    return true;
//  } else {
//    return false;
//  }
//}
//
//void EEPROM_MAP(uint16_t arg1_START, uint16_t arg2_FINISH) {
//  
//  Serial.println(F("________EEPROM________"));
//  if (arg1_START % 8 != 0) arg1_START -= arg1_START % 8;
//  if (arg2_FINISH % 8 != 0) arg2_FINISH += 7;
//  for (uint32_t i = arg1_START; i < arg2_FINISH / 8; i++) {
//    Serial.print(i * 8);
//    Serial.print("\t");
//    for (uint8_t j = 0; j < 8; j++) {
//      Serial.print(EEPROM_get((8 * i) + j), HEX);
//      Serial.print(F(";"));
//      Serial.print(EEPROM_get((8 * i) + j));
//      Serial.print(F(";"));
//      Serial.print((char)EEPROM_get((8 * i) + j));
//      Serial.print("\t\t");
//
////        uint8_t tmp_RAW = EEPROM_get((8 * i) + j);
////        String tmp_STRING_1 = String(tmp_RAW, HEX);
////        String tmp_STRING_2 = String(tmp_RAW);
////        String tmp_STRING_3 = String((char)tmp_RAW);
////
////        char tmp_STRING[8];
////        strcpy(tmp_STRING, tmp_STRING_1.c_str());
////        strcpy(tmp_STRING, ";");
////        strcpy(tmp_STRING, tmp_STRING_2.c_str());
////        strcpy(tmp_STRING, ";");
////        strcpy(tmp_STRING, tmp_STRING_3.c_str());
////        Serial.print(tmp_STRING);
//    }
//    Serial.println();
//    Serial.flush();
//  }
//  Serial.println(F("________EEPROM________"));
//}
//
//uint8_t EEPROM_get(uint32_t address) {
//  
//  uint8_t data = 0;
//  Wire.beginTransmission(EXT_EEPROM_ADDRESS);
//  Wire.write((int)(address >> 8));   // MSB
//  Wire.write((int)(address & 0xFF)); // LSB
//  Wire.endTransmission();
//  Wire.requestFrom(EEPROM_ADDRESS, (uint8_t)1);
//  delay(5);
//  if (Wire.available()) data = Wire.read();
//  return data;
//}
//
//byte EEPROM_GET_BYTE(uint32_t address) {
//  
//  byte one = EEPROM_get(address);
//  return ((one << 0) & 0xFF);
//}
//  
//  long EEPROM_get_long(uint32_t address) {
//    
//    long four = EEPROM_get(address);
//    long three = EEPROM_get(address + 1);
//    long two = EEPROM_get(address + 2);
//    long one = EEPROM_get(address + 3);
//    return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
//  }
//  
//  String EEPROM_get_string32(uint32_t beginaddress) {
//    
//    byte counter = 0;
//    char rChar;
//    String retString = "";
//    while (counter < 32) {
//      rChar = EEPROM_get(beginaddress + counter);
//      if (rChar == 0) break;
//      counter++;
//      retString.concat(rChar);
//    }
//    return retString;
//  }
//  
//  String EEPROM_get_string64(uint32_t beginaddress) {
//    
//    byte counter = 0;
//    char rChar;
//    String retString = "";
//    while (counter < 64) {
//      rChar = EEPROM_get(beginaddress + counter);
//      if (rChar == 0) break;
//      counter++;
//      retString.concat(rChar);
//    }
//    return retString;
//  }
//
//  template <class T> uint16_t EEPROM_get_struct(uint16_t beginaddress, T& value) {
//
//    byte* p = (byte*)(void*)&value;
//    for (uint16_t i = 0; i < sizeof(value); i++) *p++ = EEPROM_get(beginaddress++);
//    return sizeof(value);
//  }
//
//  void EEPROM_set(uint32_t address, byte data) {
//
//    if (EEPROM_get(address) != data) {
//      Wire.beginTransmission(EXT_EEPROM_ADDRESS);
//      Wire.write((int)(address >> 8));   // MSB
//      Wire.write((int)(address & 0xFF)); // LSB
//      Wire.write(data);
//      Wire.endTransmission();
//    }
//  }
//  
//  void EEPROM_SET_BYTE(uint32_t address, byte value) {
//    
//    EEPROM_set(address, value);
//  }
//  
//  void EEPROM_set_long(uint32_t address, long value) {
//    
//    byte four = (value & 0xFF);
//    byte three = ((value >> 8) & 0xFF);
//    byte two = ((value >> 16) & 0xFF);
//    byte one = ((value >> 24) & 0xFF);
//    EEPROM_set(address, four);
//    EEPROM_set(address + 1, three);
//    EEPROM_set(address + 2, two);
//    EEPROM_set(address + 3, one);
//  }
//  
//  void EEPROM_set_string32(uint32_t beginaddress, String string) {
//    
//    char charBuf[string.length() + 1];
//    string.toCharArray(charBuf, string.length() + 1);
//    int s;
//    if (sizeof(charBuf) > 32) {
//      s = 32;
//    } else {
//      s = sizeof(charBuf);
//    }
//    for (byte t = 0; t < s; t++) {
//      EEPROM_set(beginaddress + t, charBuf[t]);
//    }
//  }
//  
//  void EEPROM_set_string64(uint32_t beginaddress, String string) {
//    
//    char charBuf[string.length() + 1];
//    string.toCharArray(charBuf, string.length() + 1);
//    int s;
//    if (sizeof(charBuf) > 64) {
//      s = 64;
//    } else {
//      s = sizeof(charBuf);
//    }
//    for (byte t = 0; t < s; t++) {
//      EEPROM_set(beginaddress + t, charBuf[t]);
//    }
//  }
//  
//  template <class T> uint16_t EEPROM_set_struct(int beginaddress, const T &value) {
//    
//    const byte* p = (const byte*)(const void*)&value;
//    for (uint16_t i = 0; i < sizeof(value); i++) EEPROM_set(beginaddress++, *p++);
//    return sizeof(value);
//  }
//  
////////////////////////////////// RTC
//
//  
//////////////////////////////////
//
//uint16_t RTC_Gregorian2Jalali(uint16_t tmp_YEAR, uint16_t tmp_MONTH, uint16_t tmp_DAY, uint8_t data) {
//     
//    int tt = 0, sD = 0;
//    int j_year = 0, j_month = 0, j_day = 0;
//    int dWM[12] = { 0,31,59,90,120,151,181,212,243,273,304,334 };
//    int dWKM[12] = { 0,31,60,91,121,152,182,213,244,274,305,335 };
//    int j_monthlist[12] = { 31,31,31,31,31,31,30,30,30,30,30,29 };
//    int tmp_MONTHlist[12] = { 31,31,31,31,31,31,30,30,30,30,30,30 };
//  
//    if (tmp_YEAR == ((tmp_YEAR / 4) * 4)){
//      if ((tmp_MONTH > 2 & tmp_DAY > 19) || tmp_MONTH > 3){
//        j_year = tmp_YEAR - 621;
//        tt = dWKM[tmp_MONTH - 1] + tmp_DAY - 80;
//      }
//      else{
//        j_year = tmp_YEAR - 622;
//        tt = dWKM[tmp_MONTH - 1] + tmp_DAY + 285;
//      }
//    }
//    else {
//      if ((tmp_MONTH > 2 & tmp_DAY > 20) || tmp_MONTH > 3){
//        j_year = tmp_YEAR - 621;
//        tt = dWM[tmp_MONTH - 1] + tmp_DAY - 80;
//      }
//      else {
//        j_year = tmp_YEAR - 622;
//        tt = dWM[tmp_MONTH - 1] + tmp_DAY + 285;
//      }
//    }
//    sD = tt;
//    if (sD > 185) {
//      j_month = 8 + ((sD - 186) / 30);
//      j_day = sD - (185 + (((sD - 186) / 30) * 30));
//      if ((tmp_YEAR - 1) == (((tmp_YEAR - 1) / 4) * 4) & tmp_MONTH < 4){
//        sD = sD;
//        j_month = 7 + ((sD - 186) / 30);
//        j_day = 1 + sD - (185 + (((sD - 186) / 30) * 30));
//      }
//    }
//    if (sD < 186) {
//      j_month = ((sD) / 31) + 1;
//      j_day = (1 + sD - ((j_month - 1) * 31));
//    }
//    if (data == 3){
//      return j_year;
//    }
//    else if (data == 2){
//      return j_month;
//    }
//    else if (data == 1){
//      return j_day;
//    }
//  }
//
////////////////////////////////// MELODY
//
//  #define NOTE_B0  31
//  #define NOTE_C1  33
//  #define NOTE_CS1 35
//  #define NOTE_D1  37
//  #define NOTE_THERMOMETER1 39
//  #define NOTE_E1  41
//  #define NOTE_F1  44
//  #define NOTE_FS1 46
//  #define NOTE_G1  49
//  #define NOTE_GS1 52
//  #define NOTE_A1  55
//  #define NOTE_AS1 58
//  #define NOTE_B1  62
//  #define NOTE_C2  65
//  #define NOTE_CS2 69
//  #define NOTE_D2  73
//  #define NOTE_THERMOMETER2 78
//  #define NOTE_E2  82
//  #define NOTE_F2  87
//  #define NOTE_FS2 93
//  #define NOTE_G2  98
//  #define NOTE_GS2 104
//  #define NOTE_A2  110
//  #define NOTE_AS2 117
//  #define NOTE_B2  123
//  #define NOTE_C3  131
//  #define NOTE_CS3 139
//  #define NOTE_D3  147
//  #define NOTE_THERMOMETER3 156
//  #define NOTE_E3  165
//  #define NOTE_F3  175
//  #define NOTE_FS3 185
//  #define NOTE_G3  196
//  #define NOTE_GS3 208
//  #define NOTE_A3  220
//  #define NOTE_AS3 233
//  #define NOTE_B3  247
//  #define NOTE_C4  262
//  #define NOTE_CS4 277
//  #define NOTE_D4  294
//  #define NOTE_THERMOMETER4 311
//  #define NOTE_E4  330
//  #define NOTE_F4  349
//  #define NOTE_FS4 370
//  #define NOTE_G4  392
//  #define NOTE_GS4 415
//  #define NOTE_A4  440
//  #define NOTE_AS4 466
//  #define NOTE_B4  494
//  #define NOTE_C5  523
//  #define NOTE_CS5 554
//  #define NOTE_D5  587
//  #define NOTE_THERMOMETER5 622
//  #define NOTE_E5  659
//  #define NOTE_F5  698
//  #define NOTE_FS5 740
//  #define NOTE_G5  784
//  #define NOTE_GS5 831
//  #define NOTE_A5  880
//  #define NOTE_AS5 932
//  #define NOTE_B5  988
//  #define NOTE_C6  1047
//  #define NOTE_CS6 1109
//  #define NOTE_D6  1175
//  #define NOTE_THERMOMETER6 1245
//  #define NOTE_E6  1319
//  #define NOTE_F6  1397
//  #define NOTE_FS6 1480
//  #define NOTE_G6  1568
//  #define NOTE_GS6 1661
//  #define NOTE_A6  1760
//  #define NOTE_AS6 1865
//  #define NOTE_B6  1976
//  #define NOTE_C7  2093
//  #define NOTE_CS7 2217
//  #define NOTE_D7  2349
//  #define NOTE_THERMOMETER7 2489
//  #define NOTE_E7  2637
//  #define NOTE_F7  2794
//  #define NOTE_FS7 2960
//  #define NOTE_G7  3136
//  #define NOTE_GS7 3322
//  #define NOTE_A7  3520
//  #define NOTE_AS7 3729
//  #define NOTE_B7  3951
//  #define NOTE_C8  4186
//  #define NOTE_CS8 4435
//  #define NOTE_D8  4699
//  #define NOTE_THERMOMETER8 4978
//////////////////////////////////
//
//
//
////////////////////////////////// RF
//
////  uint16_t RF_Address;
////  
////////////////////////////////////
////  
////  uint16_t RF_scan (void);
////  void RF_set_address (uint16_t address);
////  uint8_t RF_decode (void);
////  
////////////////////////////////////
////  
////  uint16_t RF_scan (void) {
////    
////    RF_Address = 65000;
////    for (uint16_t i = 0 ; i < 6561 ; i++) {
////      RF_set_address (i);
////      delay(80);
////      if (digitalRead (PIN_RF_DATA) == HIGH) {
////        RF_Address = i;
////        break;
////      }
////    }
////    return RF_Address;
////  }
////  
////  void RF_set_address (uint16_t address) {
////    
////    int base[8];
////    for (uint8_t i = 0 ; i < 8 ; i++) {
////      base[i] = 0;
////    }
////    if (address >= 2187) {
////      base[7] = (address - (address % 2187)) / 2187;
////      address -= 2187 * base[7];
////    }
////    if (address >= 729) {
////      base[6] = (address - (address % 729)) / 729;
////      address -= 729 * base[6];
////    }
////    if (address >= 243) {
////      base[5] = (address - (address % 243)) / 243;
////      address -= 243 * base[5];
////    }
////    if (address >= 81) {
////      base[4] = (address - (address % 81)) / 81;
////      address -= 81 * base[4];
////    }
////    if (address >= 27) {
////      base[3] = (address - (address % 27)) / 27;
////      address -= 27 * base[3];
////    }
////    if (address >= 9) {
////      base[2] = (address - (address % 9)) / 9;
////      address -= 9 * base[2];
////    }
////    if (address >= 3) {
////      base[1] = (address - (address % 3)) / 3;
////      address -= 3 * base[1];
////    }
////    base[0] = address;
////    if (base[0] == 0) {
////      pinMode(PIN_RF_A0, OUTPUT);
////      digitalWrite(PIN_RF_A0, LOW);
////    } else if (base[0] == 1) {
////      pinMode(PIN_RF_A0, OUTPUT);
////      digitalWrite(PIN_RF_A0, HIGH);
////    } else pinMode(PIN_RF_A0, INPUT);
////    if (base[1] == 0) {
////      pinMode(PIN_RF_A1, OUTPUT);
////      digitalWrite(PIN_RF_A1, LOW);
////    } else if (base[1] == 1) {
////      pinMode(PIN_RF_A1, OUTPUT);
////      digitalWrite(PIN_RF_A1, HIGH);
////    } else pinMode(PIN_RF_A1, INPUT);
////    if (base[2] == 0) {
////      pinMode(PIN_RF_A2, OUTPUT);
////      digitalWrite(PIN_RF_A2, LOW);
////    } else if (base[2] == 1) {
////      pinMode(PIN_RF_A2, OUTPUT);
////      digitalWrite(PIN_RF_A2, HIGH);
////    } else pinMode(PIN_RF_A2, INPUT);
////    if (base[3] == 0) {
////      pinMode(PIN_RF_A3, OUTPUT);
////      digitalWrite(PIN_RF_A3, LOW);
////    } else if (base[3] == 1) {
////      pinMode(PIN_RF_A3, OUTPUT);
////      digitalWrite(PIN_RF_A3, HIGH);
////    } else pinMode(PIN_RF_A3, INPUT);
////    if (base[4] == 0) {
////      pinMode(PIN_RF_A4, OUTPUT);
////      digitalWrite(PIN_RF_A4, LOW);
////    } else if (base[4] == 1) {
////      pinMode(PIN_RF_A4, OUTPUT);
////      digitalWrite(PIN_RF_A4, HIGH);
////    } else pinMode(PIN_RF_A4, INPUT);
////    if (base[5] == 0) {
////      pinMode(PIN_RF_A5, OUTPUT);
////      digitalWrite(PIN_RF_A5, LOW);
////    } else if (base[5] == 1) {
////      pinMode(PIN_RF_A5, OUTPUT);
////      digitalWrite(PIN_RF_A5, HIGH);
////    } else pinMode(PIN_RF_A5, INPUT);
////    if (base[6] == 0) {
////      pinMode(PIN_RF_A6, OUTPUT);
////      digitalWrite(PIN_RF_A6, LOW);
////    } else if (base[6] == 1) {
////      pinMode(PIN_RF_A6, OUTPUT);
////      digitalWrite(PIN_RF_A6, HIGH);
////    } else pinMode(PIN_RF_A6, INPUT);
////    if (base[7] == 0) {
////      pinMode(PIN_RF_A7, OUTPUT);
////      digitalWrite(PIN_RF_A7, LOW);
////    } else if (base[7] == 1) {
////      pinMode(PIN_RF_A7, OUTPUT);
////      digitalWrite(PIN_RF_A7, HIGH);
////    } else pinMode(PIN_RF_A7, INPUT);
////  }
////
////  uint8_t RF_decode (void) {
////
////    uint8_t data = 0 , d1 = 0, d2 = 0, d3 = 0, d4 = 0, hold = 0;
////    hold = 0;
////    while (digitalRead(PIN_RF_DATA) == HIGH && hold < 1000) {
////      d1 = digitalRead(PIN_RF_D1);
////      d2 = digitalRead(PIN_RF_D2);
////      d3 = digitalRead(PIN_RF_D3);
////      d4 = digitalRead(PIN_RF_D4);
////      hold++;
////    }
////    if (hold < 300) {
////      data = d1 + (2 * d2) + (4 * d3) + (8 * d4);
////    } else if (hold > 299 && hold < 700 ){
////      data = (16 * d1) + (32 * d2) + (64 * d3) + (128 * d4);
////    } else if (hold > 699){
////      data = (256 * d1) + (512 * d2) + (1024 * d3) + (2048 * d4);
////    }
////    if (data == 8 ) return 1;
////    if (data == 4 ) return 2;
////    if (data == 2 ) return 3;
////    if (data == 5 ) return 4;
////    if (data == 13 ) return 5;
////    if (data == 6 ) return 6;
////    if (data == 14 ) return 7;
////    if (data == 3 ) return 8;
////    if (data == 9 ) return 9;
////    if (data == 12 ) return 10;
////    if (data == 7 ) return 11;
////    if (data == 11 ) return 12;
////    if (data == 15 ) return 13;
////    if (data == 1 ) return 14;
////    if (data == 10 ) return 15;
////    if (data == 128 ) return 17;
////    if (data == 64 ) return 18;
////    if (data == 32 ) return 19;
////    if (data == 80 ) return 20;
////    if (data == 208 ) return 21;
////    if (data == 96 ) return 22;
////    if (data == 224 ) return 23;
////    if (data == 48 ) return 24;
////    if (data == 144 ) return 25;
////    if (data == 192 ) return 26;
////    if (data == 112 ) return 27;
////    if (data == 176 ) return 28;
////    if (data == 240 ) return 29;
////    if (data == 16 ) return 30;
////    if (data == 160 ) return 31;
////    return 0;
////  }
//
//////////////////////////////////HumiTemp
//
//  double heatIndex(double TMP, double RH);
//  double humidex(double TMP, double RH);
//  double dewPoint(double TMP, double RH);
//  
//////////////////////////////////
//  
//  double heatIndex(double TMP, double RH) {
//
//    double T = (9 / 5) * TMP + 32;
//    double c1 = -42.38, c2 = 2.049, c3 = 10.14, c4 = -0.2248, c5 = -6.838e-3, c6 = -5.482e-2, c7 = 1.228e-3, c8 = 8.528e-4, c9 = -1.99e-6  ;
//    double A = (( c5 * T) + c2) * T + c1;
//    double B = (((c7 * T) + c4) * T + c3) * RH;
//    double C = (((c9 * T) + c8) * T + c6) * RH * RH;
//    return double(int(((A + B + C - 32) * 5 / 9) * 10)) / 10;
//  }
//  
//  double humidex(double TMP, double RH) {
//  
//    double dew = dewPoint(TMP, RH);
//    double e = 19.833625 - 5417.753 / (273.16 + dew);
//    double h = TMP + 3.3941 * exp(e) - 5.555;
//    return h;
//  }
//  
//  double dewPoint(double TMP, double RH) {
//  
//    double A0 = 373.15 / (273.15 + TMP);
//    double SUM = -7.90298 * (A0 - 1);
//    SUM += 5.02808 * log10(A0);
//    SUM += -1.3816e-7 * (pow(10, (11.344 * (1 - 1 / A0))) - 1) ;
//    SUM += 8.1328e-3 * (pow(10, (-3.49149 * (A0 - 1))) - 1) ;
//    SUM += log10(1013.246);
//    double VP = pow(10, SUM - 3) * RH;
//    double T = log(VP / 0.61078);
//    return (241.88 * T) / (17.558 - T);
//  }


//  if (WEBSERVER.args() > 0) {
//    for (uint8_t i = 0; i < WEBSERVER.args(); i++) {
//      Serial.print(WEBSERVER.argName(i));
//      Serial.print(": ");
//      Serial.println(WEBSERVER.arg(i));
//    }
//    if (WEBSERVER.argName(0) == "SETTING_TYPE" && WEBSERVER.arg(0) == "SETUP") {
//      for (uint8_t i = 0; i < WEBSERVER.args(); i++) {
//        if (WEBSERVER.argName(i) == "SYSTEM_NAME") strcpy(SETTINGS.SYSTEM_NAME, HTML_HELPERS_URLCODE(WEBSERVER.arg(i)).c_str());
//        if (WEBSERVER.argName(i) == "SYSTEM_PASSWORD") strcpy(SETTINGS.SYSTEM_PASSWORD, HTML_HELPERS_URLCODE(WEBSERVER.arg(i)).c_str());
//        if (WEBSERVER.argName(i) == "WIFI_SSID") strcpy(SETTINGS.WIFI_SSID, HTML_HELPERS_URLCODE(WEBSERVER.arg(i)).c_str());
//        if (WEBSERVER.argName(i) == "WIFI_PASSWORD") strcpy(SETTINGS.WIFI_PASSWORD, HTML_HELPERS_URLCODE(WEBSERVER.arg(i)).c_str());
//      }
//      if (!WIFI_ERROR) WEBSERVER.send(200, "text/plain", WiFi.localIP().toString().c_str());
//    } else if (WEBSERVER.argName(0) == "SETTING_TYPE" && WEBSERVER.arg(0) == "RGB") {
//      for (uint8_t i = 0; i < WEBSERVER.args(); i++) {
//        if (WEBSERVER.argName(i) == "RGB_STATE") SETTINGS.RGB_STATE = WEBSERVER.arg(i).toInt();
//        if (WEBSERVER.argName(i) == "RGB_TRESHHOLD") SETTINGS.RGB_TRESHHOLD = WEBSERVER.arg(i).toInt();
//        if (WEBSERVER.argName(i) == "RGB_DAY_MODE") SETTINGS.RGB_DAY_MODE = WEBSERVER.arg(i).toInt();
//        if (WEBSERVER.argName(i) == "RGB_DAY_COLOR_0") SETTINGS.RGB_DAY_COLOR[0] = WEBSERVER.arg(i).toInt();
//        if (WEBSERVER.argName(i) == "RGB_DAY_COLOR_1") SETTINGS.RGB_DAY_COLOR[1] = WEBSERVER.arg(i).toInt();
//        if (WEBSERVER.argName(i) == "RGB_DAY_COLOR_2") SETTINGS.RGB_DAY_COLOR[2] = WEBSERVER.arg(i).toInt();
//        if (WEBSERVER.argName(i) == "RGB_NIGHT_MODE") SETTINGS.RGB_NIGHT_MODE = WEBSERVER.arg(i).toInt();
//        if (WEBSERVER.argName(i) == "RGB_NIGHT_COLOR_0") SETTINGS.RGB_NIGHT_COLOR[0] = WEBSERVER.arg(i).toInt();
//        if (WEBSERVER.argName(i) == "RGB_NIGHT_COLOR_1") SETTINGS.RGB_NIGHT_COLOR[1] = WEBSERVER.arg(i).toInt();
//        if (WEBSERVER.argName(i) == "RGB_NIGHT_COLOR_2") SETTINGS.RGB_NIGHT_COLOR[2] = WEBSERVER.arg(i).toInt();
//      }
//    }
