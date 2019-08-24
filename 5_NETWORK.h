void ANALYZE_SYNCSERVER(void) {

  #if USE_SYNCSERVER == 1
  
    #if DEBUG_FUNCTIONS_NETWORK == 1
      Serial.println(F("ANALYZE_SYNCSERVER"));
    #endif
    
    if (!SYNCSERVER_DTR) {
      // Building sync request
      String tmp_SQL_COMMAND = String("key=");
      tmp_SQL_COMMAND += String(SYNCSERVER_SECRET);
      tmp_SQL_COMMAND += String("&query=");
      tmp_SQL_COMMAND += String("CALL+%60SYNC%60%28");
      tmp_SQL_COMMAND += String(ESP.getChipId());
      tmp_SQL_COMMAND += String("%2C%27");
      tmp_SQL_COMMAND += String(SYNCSERVER_PASSWORD);
      tmp_SQL_COMMAND += String("%27%2C");
      tmp_SQL_COMMAND += String(STATION.TIMESTAMP);
      tmp_SQL_COMMAND += String("%2C");
      tmp_SQL_COMMAND += String(SETTINGS.TIMESTAMP);
      tmp_SQL_COMMAND += String("%2C");
      tmp_SQL_COMMAND += String(TYPE);
      tmp_SQL_COMMAND += String("%2C");
      tmp_SQL_COMMAND += String(RTC_TOTAL_TIMER);
      tmp_SQL_COMMAND += String("%29");
      #if ESP_SYNCSERVER_DEBUG > 1
        Serial.print(F("Query: "));
        Serial.println(tmp_SQL_COMMAND);
      #endif
      // Sending sync request
      #if ESP_SYNCSERVER_DEBUG > 0
        Serial.print(F("Requesting sync from server: "));
      #endif
      CLIENT.setTimeout(50);
      if (CLIENT.connect(SYNCSERVER_HOME, 80)) {
        CLIENT.println(F("POST /systems/query.php HTTP/1.1"));
        CLIENT.print(F("Host: "));
        CLIENT.println(SYNCSERVER_HOME);
        CLIENT.println(F("User-Agent: Arduino/1.0"));
        CLIENT.println(F("Content-Type: application/x-www-form-urlencoded"));
        CLIENT.print(F("Content-Length: "));
        CLIENT.println(tmp_SQL_COMMAND.length());
        CLIENT.println();
        CLIENT.print(tmp_SQL_COMMAND);
        if (CLIENT.println() == 0) {
          #if ESP_SYNCSERVER_DEBUG > 0
            Serial.println(F("Failed."));
          #endif
          SYNCSERVER_ERROR = true;
        } else {
          #if ESP_SYNCSERVER_DEBUG > 0
            Serial.println(F("Successful."));
          #endif
          SYNCSERVER_ERROR = false;
        }
        SYNCSERVER_DTR = true;
        TASK_ANALYZE_SYNCSERVER.setInterval(500);
      } else {
        #if ESP_SYNCSERVER_DEBUG > 0
          Serial.println(F("Failed to connect to server."));
        #endif
        SYNCSERVER_ERROR = true;
        return;
      }
    } else {
      // Reading sync response
      #if ESP_SYNCSERVER_DEBUG > 0
        Serial.println(F("Reading sync response from server: "));
      #endif
      String tmp_SQL_RESULTS;
      while (CLIENT.available()) tmp_SQL_RESULTS = CLIENT.readString();
      CLIENT.flush();
      #if ESP_SYNCSERVER_DEBUG > 1
        Serial.println(F("Result: "));
        Serial.println(tmp_SQL_RESULTS);
      #endif
      CLIENT.stop();
      // Analyzing sync responsse
      if (tmp_SQL_RESULTS.length() > 0) {
        // Syncing time with server
        #if USE_RTC == 1
          uint16_t tmp_YEAR = tmp_SQL_RESULTS.substring(tmp_SQL_RESULTS.indexOf("Date") + 18, tmp_SQL_RESULTS.indexOf("Date") + 22).toInt();
          String tmp_MONTH_STRING = tmp_SQL_RESULTS.substring(tmp_SQL_RESULTS.indexOf("Date") + 14, tmp_SQL_RESULTS.indexOf("Date") + 17);
          uint8_t tmp_MONTH = 0;
          for (uint8_t i = 0; i < 12; i++) {
            if (tmp_MONTH_STRING == RTC_MONTH_NAMES[i]) tmp_MONTH = i + 1;
          }
          uint8_t tmp_DAY = tmp_SQL_RESULTS.substring(tmp_SQL_RESULTS.indexOf("Date") + 11, tmp_SQL_RESULTS.indexOf("Date") + 13).toInt();
          uint8_t tmp_HOUR = tmp_SQL_RESULTS.substring(tmp_SQL_RESULTS.indexOf("Date") + 23, tmp_SQL_RESULTS.indexOf("Date") + 25).toInt();
          uint8_t tmp_MINUTE = tmp_SQL_RESULTS.substring(tmp_SQL_RESULTS.indexOf("Date") + 26, tmp_SQL_RESULTS.indexOf("Date") + 28).toInt();
          uint8_t tmp_SECOND = tmp_SQL_RESULTS.substring(tmp_SQL_RESULTS.indexOf("Date") + 29, tmp_SQL_RESULTS.indexOf("Date") + 31).toInt();
          DS1307.adjust(DateTime(tmp_YEAR, tmp_MONTH, tmp_DAY, tmp_HOUR, tmp_MINUTE, tmp_SECOND));
        #endif
        // Analyzing sync response code
        if (tmp_SQL_RESULTS.indexOf("CODE_11") > 0) {
          #if ESP_SYNCSERVER_DEBUG > 0
            Serial.println(F("11. Sync succeed. STATION: EQUAL, SETTINGS = EQUAL."));
          #endif
        } else if (tmp_SQL_RESULTS.indexOf("CODE_12") > 0) {
          #if ESP_SYNCSERVER_DEBUG > 0
            Serial.println(F("12. Sync succeed. STATION: EQUAL, SETTINGS = SERVER."));
          #endif
        } else if (tmp_SQL_RESULTS.indexOf("CODE_13") > 0) {
          #if ESP_SYNCSERVER_DEBUG > 0
            Serial.println(F("13. Sync succeed. STATION: EQUAL, SETTINGS = SYSTEM."));
          #endif
        } else if (tmp_SQL_RESULTS.indexOf("CODE_21") > 0) {
          #if ESP_SYNCSERVER_DEBUG > 0
            Serial.println(F("21. Sync succeed. STATION: SERVER, SETTINGS = EQUAL."));
          #endif
        } else if (tmp_SQL_RESULTS.indexOf("CODE_22") > 0) {
          #if ESP_SYNCSERVER_DEBUG > 0
            Serial.println(F("22. Sync succeed. STATION: SERVER, SETTINGS = SERVER."));
          #endif
        } else if (tmp_SQL_RESULTS.indexOf("CODE_23") > 0) {
          #if ESP_SYNCSERVER_DEBUG > 0
            Serial.println(F("23. Sync succeed. STATION: SERVER, SETTINGS = SYSTEM."));
          #endif
        } else {
          #if ESP_SYNCSERVER_DEBUG > 0
            Serial.println(F("00. Illegal response."));
          #endif
        }
      }
      SYNCSERVER_DTR = false;
      TASK_ANALYZE_SYNCSERVER.setInterval(SYNCSERVER_INTERVAL);
    }



//              String tmp_SQL_COMMAND = String("key=");
//              tmp_SQL_COMMAND += String(SYNCSERVER_SECRET);
//              tmp_SQL_COMMAND += String("&query=");
//              tmp_SQL_COMMAND += String("CALL+%60SYNC_AQUA%60%28");
//              tmp_SQL_COMMAND += String(ESP.getChipId());
//              tmp_SQL_COMMAND += String("%2C%27");
//              tmp_SQL_COMMAND += String(SYNCSERVER_PASSWORD);
//              tmp_SQL_COMMAND += String("%27%2C%27");
//              tmp_SQL_COMMAND += String(SETTINGS.NAME);
//              tmp_SQL_COMMAND += String("%27%2C%27");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_SSID);
//              tmp_SQL_COMMAND += String("%27%2C%27");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_PASSWORD);
//              tmp_SQL_COMMAND += String("%27%2C");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_DHCP);
//              tmp_SQL_COMMAND += String("%2C");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_IP[0]);
//              tmp_SQL_COMMAND += String("%2C");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_IP[1]);
//              tmp_SQL_COMMAND += String("%2C");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_IP[2]);
//              tmp_SQL_COMMAND += String("%2C");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_IP[3]);
//              tmp_SQL_COMMAND += String("%2C");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_GATE[0]);
//              tmp_SQL_COMMAND += String("%2C");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_GATE[1]);
//              tmp_SQL_COMMAND += String("%2C");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_GATE[2]);
//              tmp_SQL_COMMAND += String("%2C");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_GATE[3]);
//              tmp_SQL_COMMAND += String("%2C");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_MASK[0]);
//              tmp_SQL_COMMAND += String("%2C");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_MASK[1]);
//              tmp_SQL_COMMAND += String("%2C");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_MASK[2]);
//              tmp_SQL_COMMAND += String("%2C");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_MASK[3]);
//              tmp_SQL_COMMAND += String("%29");
//              #if ESP_SYNCSERVER_DEBUG > 1
//                Serial.print(F("Query: "));
//                Serial.println(tmp_SQL_COMMAND);
//              #endif
//              #if ESP_SYNCSERVER_DEBUG > 0
//                Serial.print(F("Sending new settings to server... "));
//              #endif
//              if (CLIENT.connect(SYNCSERVER_HOME, 80)) {
//                CLIENT.println("POST /systems/query.php HTTP/1.1");
//                CLIENT.print("Host: ");
//                CLIENT.println(SYNCSERVER_HOME);
//                CLIENT.println("User-Agent: Arduino/1.0");
//                CLIENT.println("Content-Type: application/x-www-form-urlencoded");
//                CLIENT.print("Content-Length: ");
//                CLIENT.println(tmp_SQL_COMMAND.length());
//                CLIENT.println();
//                CLIENT.print(tmp_SQL_COMMAND);
//                SYNCSERVER_ERROR = false;
//                SYNCSERVER_DTR = false;
//              } else {
//                #if ESP_SYNCSERVER_DEBUG > 0
//                  Serial.println(F("Failed. Server not reachable."));
//                #endif
//                SYNCSERVER_ERROR = true;
//              }
//            } else if (tmp_SQL_RESULTS.indexOf("CODE_13") > 0) {
//              #if ESP_SYNCSERVER_DEBUG > 0
//                Serial.println(F("13. Sync succeed. No STATION changes detected. New SETTINGS on server."));
//              #endif
//              uint16_t tmp_START_INDEX = tmp_SQL_RESULTS.indexOf("|", tmp_SQL_RESULTS.indexOf("CODE_13"));
//              String tmp_SETTINGS_TIMESTAMP = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SETTINGS.TIMESTAMP = tmp_SETTINGS_TIMESTAMP.toInt();
//              tmp_START_INDEX += tmp_SETTINGS_TIMESTAMP.length() + 1;
//              String tmp_NAME = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(SETTINGS.NAME, tmp_NAME.c_str());
//              tmp_START_INDEX += tmp_NAME.length() + 1;
//              String tmp_WIFI_SSID = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(SETTINGS.WIFI_SSID, tmp_WIFI_SSID.c_str());
//              tmp_START_INDEX += tmp_WIFI_SSID.length() + 1;
//              String tmp_WIFI_PASSWORD = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(SETTINGS.WIFI_PASSWORD, tmp_WIFI_PASSWORD.c_str());
//              tmp_START_INDEX += tmp_WIFI_PASSWORD.length() + 1;
//              String tmp_WIFI_DHCP = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SETTINGS.WIFI_DHCP = tmp_WIFI_DHCP.toInt();
//              tmp_START_INDEX += tmp_WIFI_DHCP.length() + 1;
//              String tmp_WIFI_IP_0 = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SETTINGS.WIFI_IP[0] = tmp_WIFI_IP_0.toInt();
//              tmp_START_INDEX += tmp_WIFI_IP_0.length() + 1;
//              String tmp_WIFI_IP_1 = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SETTINGS.WIFI_IP[1] = tmp_WIFI_IP_1.toInt();
//              tmp_START_INDEX += tmp_WIFI_IP_1.length() + 1;
//              String tmp_WIFI_IP_2 = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SETTINGS.WIFI_IP[2] = tmp_WIFI_IP_2.toInt();
//              tmp_START_INDEX += tmp_WIFI_IP_2.length() + 1;
//              String tmp_WIFI_IP_3 = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SETTINGS.WIFI_IP[3] = tmp_WIFI_IP_3.toInt();
//              tmp_START_INDEX += tmp_WIFI_IP_3.length() + 1;
//              String tmp_WIFI_GATE_0 = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SETTINGS.WIFI_GATE[0] = tmp_WIFI_GATE_0.toInt();
//              tmp_START_INDEX += tmp_WIFI_GATE_0.length() + 1;
//              String tmp_WIFI_GATE_1 = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SETTINGS.WIFI_GATE[1] = tmp_WIFI_GATE_1.toInt();
//              tmp_START_INDEX += tmp_WIFI_GATE_1.length() + 1;
//              String tmp_WIFI_GATE_2 = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SETTINGS.WIFI_GATE[2] = tmp_WIFI_GATE_2.toInt();
//              tmp_START_INDEX += tmp_WIFI_GATE_2.length() + 1;
//              String tmp_WIFI_GATE_3 = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SETTINGS.WIFI_GATE[3] = tmp_WIFI_GATE_3.toInt();
//              tmp_START_INDEX += tmp_WIFI_GATE_3.length() + 1;
//              String tmp_WIFI_MASK_0 = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SETTINGS.WIFI_MASK[0] = tmp_WIFI_MASK_0.toInt();
//              tmp_START_INDEX += tmp_WIFI_MASK_0.length() + 1;
//              String tmp_WIFI_MASK_1 = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SETTINGS.WIFI_MASK[1] = tmp_WIFI_MASK_1.toInt();
//              tmp_START_INDEX += tmp_WIFI_MASK_1.length() + 1;
//              String tmp_WIFI_MASK_2 = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SETTINGS.WIFI_MASK[2] = tmp_WIFI_MASK_2.toInt();
//              tmp_START_INDEX += tmp_WIFI_MASK_2.length() + 1;
//              String tmp_WIFI_MASK_3 = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("<", tmp_START_INDEX + 1));
//              SETTINGS.WIFI_MASK[3] = tmp_WIFI_MASK_3.toInt();
//              SETTINGS_ALTERED = true;
//            } else if (tmp_SQL_RESULTS.indexOf("CODE_31") > 0) {
//              #if ESP_SYNCSERVER_DEBUG > 0
//                Serial.println(F("31. Sync succeed. New STATION on server. No SETTINGS changes detected."));
//              #endif
//              uint16_t tmp_START_INDEX = tmp_SQL_RESULTS.indexOf("|", tmp_SQL_RESULTS.indexOf("CODE_31"));
//              String tmp_TIMESTAMP = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              STATION.TIMESTAMP = tmp_TIMESTAMP.toInt();
//              tmp_START_INDEX += tmp_TIMESTAMP.length() + 1;
//              String tmp_ID = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(CUSTOMER.ID, tmp_ID.c_str());
//              tmp_START_INDEX += tmp_ID.length() + 1;
//              String tmp_NAME = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(CUSTOMER.NAME, tmp_NAME.c_str());
//              tmp_START_INDEX += tmp_NAME.length() + 1;
//              String tmp_FNAME = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(CUSTOMER.FNAME, tmp_FNAME.c_str());
//              tmp_START_INDEX += tmp_FNAME.length() + 1;
//              String tmp_TELEPHONE = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(CUSTOMER.TELEPHONE, tmp_TELEPHONE.c_str());
//              tmp_START_INDEX += tmp_TELEPHONE.length() + 1;
//              String tmp_MOBILE = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(CUSTOMER.MOBILE, tmp_MOBILE.c_str());
//              tmp_START_INDEX += tmp_MOBILE.length() + 1;
//              String tmp_CITY = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(CUSTOMER.CITY, tmp_CITY.c_str());
//              tmp_START_INDEX += tmp_CITY.length() + 1;
//              String tmp_ADDRESS = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(CUSTOMER.ADDRESS, tmp_ADDRESS.c_str());
//              tmp_START_INDEX += tmp_ADDRESS.length() + 1;
//              String tmp_ZIP = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(CUSTOMER.ZIP, tmp_ZIP.c_str());
//              tmp_START_INDEX += tmp_ZIP.length() + 1;
//              String tmp_ACTIVATION = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              STATION.ACTIVATION = tmp_ACTIVATION.toInt();
//              tmp_START_INDEX += tmp_ACTIVATION.length() + 1;
//              String tmp_EXPIRATION = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              STATION.EXPIRATION = tmp_EXPIRATION.toInt();
//              tmp_START_INDEX += tmp_EXPIRATION.length() + 1;
//              String tmp_ACTIVE = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              STATION.ACTIVE = tmp_ACTIVE.toInt();
//              tmp_START_INDEX += tmp_ACTIVE.length() + 1;
//              String tmp_SYSTEM_VERSION = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SYSTEM_VERSION = tmp_SYSTEM_VERSION.toInt();
//              tmp_START_INDEX += tmp_SYSTEM_VERSION.length() + 1;
//              String tmp_SYSTEM_VERSION_CRITICAL = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("<", tmp_START_INDEX + 1));
//              SYSTEM_VERSION_CRITICAL = tmp_SYSTEM_VERSION_CRITICAL.toInt();
//              STATION_ALTERED = true;
//            } else if (tmp_SQL_RESULTS.indexOf("CODE_32") > 0) {
//              #if ESP_SYNCSERVER_DEBUG > 0
//                Serial.println(F("32. Sync succeed. New STATION on server. New SETTINGS on system."));
//              #endif
//              uint16_t tmp_START_INDEX = tmp_SQL_RESULTS.indexOf("|", tmp_SQL_RESULTS.indexOf("CODE_32"));
//              String tmp_TIMESTAMP = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              STATION.TIMESTAMP = tmp_TIMESTAMP.toInt();
//              tmp_START_INDEX += tmp_TIMESTAMP.length() + 1;
//              String tmp_ID = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(CUSTOMER.ID, tmp_ID.c_str());
//              tmp_START_INDEX += tmp_ID.length() + 1;
//              String tmp_NAME = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(CUSTOMER.NAME, tmp_NAME.c_str());
//              tmp_START_INDEX += tmp_NAME.length() + 1;
//              String tmp_FNAME = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(CUSTOMER.FNAME, tmp_FNAME.c_str());
//              tmp_START_INDEX += tmp_FNAME.length() + 1;
//              String tmp_TELEPHONE = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(CUSTOMER.TELEPHONE, tmp_TELEPHONE.c_str());
//              tmp_START_INDEX += tmp_TELEPHONE.length() + 1;
//              String tmp_MOBILE = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(CUSTOMER.MOBILE, tmp_MOBILE.c_str());
//              tmp_START_INDEX += tmp_MOBILE.length() + 1;
//              String tmp_CITY = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(CUSTOMER.CITY, tmp_CITY.c_str());
//              tmp_START_INDEX += tmp_CITY.length() + 1;
//              String tmp_ADDRESS = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(CUSTOMER.ADDRESS, tmp_ADDRESS.c_str());
//              tmp_START_INDEX += tmp_ADDRESS.length() + 1;
//              String tmp_ZIP = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(CUSTOMER.ZIP, tmp_ZIP.c_str());
//              tmp_START_INDEX += tmp_ZIP.length() + 1;
//              String tmp_ACTIVATION = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              STATION.ACTIVATION = tmp_ACTIVATION.toInt();
//              tmp_START_INDEX += tmp_ACTIVATION.length() + 1;
//              String tmp_EXPIRATION = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              STATION.EXPIRATION = tmp_EXPIRATION.toInt();
//              tmp_START_INDEX += tmp_EXPIRATION.length() + 1;
//              String tmp_ACTIVE = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              STATION.ACTIVE = tmp_ACTIVE.toInt();
//              tmp_START_INDEX += tmp_ACTIVE.length() + 1;
//              String tmp_SYSTEM_VERSION = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SYSTEM_VERSION = tmp_SYSTEM_VERSION.toInt();
//              tmp_START_INDEX += tmp_SYSTEM_VERSION.length() + 1;
//              String tmp_SYSTEM_VERSION_CRITICAL = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("<", tmp_START_INDEX + 1));
//              SYSTEM_VERSION_CRITICAL = tmp_SYSTEM_VERSION_CRITICAL.toInt();
//              STATION_ALTERED = true;
//              #if ESP_SYNCSERVER_DEBUG > 0
//                Serial.print(F("Sending new settings to server... "));
//              #endif
//              String tmp_SQL_COMMAND = String("key=");
//              tmp_SQL_COMMAND += String(SYNCSERVER_SECRET);
//              tmp_SQL_COMMAND += String("&query=");
//              tmp_SQL_COMMAND += String("CALL+%60SYNC_AQUA%60%28");
//              tmp_SQL_COMMAND += String(ESP.getChipId());
//              tmp_SQL_COMMAND += String("%2C%27");
//              tmp_SQL_COMMAND += String(SYNCSERVER_PASSWORD);
//              tmp_SQL_COMMAND += String("%27%2C%27");
//              tmp_SQL_COMMAND += String(SETTINGS.NAME);
//              tmp_SQL_COMMAND += String("%27%2C%27");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_SSID);
//              tmp_SQL_COMMAND += String("%27%2C%27");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_PASSWORD);
//              tmp_SQL_COMMAND += String("%27%2C");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_DHCP);
//              tmp_SQL_COMMAND += String("%2C");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_IP[0]);
//              tmp_SQL_COMMAND += String("%2C");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_IP[1]);
//              tmp_SQL_COMMAND += String("%2C");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_IP[2]);
//              tmp_SQL_COMMAND += String("%2C");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_IP[3]);
//              tmp_SQL_COMMAND += String("%2C");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_GATE[0]);
//              tmp_SQL_COMMAND += String("%2C");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_GATE[1]);
//              tmp_SQL_COMMAND += String("%2C");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_GATE[2]);
//              tmp_SQL_COMMAND += String("%2C");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_GATE[3]);
//              tmp_SQL_COMMAND += String("%2C");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_MASK[0]);
//              tmp_SQL_COMMAND += String("%2C");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_MASK[1]);
//              tmp_SQL_COMMAND += String("%2C");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_MASK[2]);
//              tmp_SQL_COMMAND += String("%2C");
//              tmp_SQL_COMMAND += String(SETTINGS.WIFI_MASK[3]);
//              tmp_SQL_COMMAND += String("%29");
//              #if ESP_SYNCSERVER_DEBUG > 1
//                Serial.print(F("Query: "));
//                Serial.println(tmp_SQL_COMMAND);
//              #endif
//              if (CLIENT.connect(SYNCSERVER_HOME, 80)) {
//                CLIENT.println("POST /systems/query.php HTTP/1.1");
//                CLIENT.print("Host: ");
//                CLIENT.println(SYNCSERVER_HOME);
//                CLIENT.println("User-Agent: Arduino/1.0");
//                CLIENT.println("Content-Type: application/x-www-form-urlencoded");
//                CLIENT.print("Content-Length: ");
//                CLIENT.println(tmp_SQL_COMMAND.length());
//                CLIENT.println();
//                CLIENT.print(tmp_SQL_COMMAND);
//                SYNCSERVER_ERROR = false;
//                SYNCSERVER_DTR = false;
//                #if ESP_SYNCSERVER_DEBUG > 0
//                  Serial.println(F("Sent."));
//                #endif
//              } else {
//                #if ESP_SYNCSERVER_DEBUG > 0
//                  Serial.println(F("Failed. Server not reachable."));
//                #endif
//                SYNCSERVER_ERROR = true;
//              }
//            } else if (tmp_SQL_RESULTS.indexOf("CODE_33") > 0) {
//              #if ESP_SYNCSERVER_DEBUG > 0
//                Serial.println(F("33. Sync succeed. Reading new STATION from server. Reading new SETTINGS from server."));
//              #endif
//              uint16_t tmp_START_INDEX = tmp_SQL_RESULTS.indexOf("|", tmp_SQL_RESULTS.indexOf("CODE_33"));
//              String tmp_TIMESTAMP = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              STATION.TIMESTAMP = tmp_TIMESTAMP.toInt();
//              tmp_START_INDEX += tmp_TIMESTAMP.length() + 1;
//              String tmp_ID = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(CUSTOMER.ID, tmp_ID.c_str());
//              tmp_START_INDEX += tmp_ID.length() + 1;
//              String tmp_NAME = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(CUSTOMER.NAME, tmp_NAME.c_str());
//              tmp_START_INDEX += tmp_NAME.length() + 1;
//              String tmp_FNAME = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(CUSTOMER.FNAME, tmp_FNAME.c_str());
//              tmp_START_INDEX += tmp_FNAME.length() + 1;
//              String tmp_TELEPHONE = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(CUSTOMER.TELEPHONE, tmp_TELEPHONE.c_str());
//              tmp_START_INDEX += tmp_TELEPHONE.length() + 1;
//              String tmp_MOBILE = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(CUSTOMER.MOBILE, tmp_MOBILE.c_str());
//              tmp_START_INDEX += tmp_MOBILE.length() + 1;
//              String tmp_CITY = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(CUSTOMER.CITY, tmp_CITY.c_str());
//              tmp_START_INDEX += tmp_CITY.length() + 1;
//              String tmp_ADDRESS = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(CUSTOMER.ADDRESS, tmp_ADDRESS.c_str());
//              tmp_START_INDEX += tmp_ADDRESS.length() + 1;
//              String tmp_ZIP = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(CUSTOMER.ZIP, tmp_ZIP.c_str());
//              tmp_START_INDEX += tmp_ZIP.length() + 1;
//              String tmp_ACTIVATION = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              STATION.ACTIVATION = tmp_ACTIVATION.toInt();
//              tmp_START_INDEX += tmp_ACTIVATION.length() + 1;
//              String tmp_EXPIRATION = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              STATION.EXPIRATION = tmp_EXPIRATION.toInt();
//              tmp_START_INDEX += tmp_EXPIRATION.length() + 1;
//              String tmp_ACTIVE = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              STATION.ACTIVE = tmp_ACTIVE.toInt();
//              tmp_START_INDEX += tmp_ACTIVE.length() + 1;
//              String tmp_SYSTEM_VERSION = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SYSTEM_VERSION = tmp_SYSTEM_VERSION.toInt();
//              tmp_START_INDEX += tmp_SYSTEM_VERSION.length() + 1;
//              String tmp_SYSTEM_VERSION_CRITICAL = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("<", tmp_START_INDEX + 1));
//              SYSTEM_VERSION_CRITICAL = tmp_SYSTEM_VERSION_CRITICAL.toInt();
//              tmp_START_INDEX += tmp_SYSTEM_VERSION_CRITICAL.length() + 1;
//              STATION_ALTERED = true;
//              String tmp_SETTINGS_TIMESTAMP = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SETTINGS.TIMESTAMP = tmp_SETTINGS_TIMESTAMP.toInt();
//              tmp_START_INDEX += tmp_SETTINGS_TIMESTAMP.length() + 1;
//              String tmp_NAME = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(SETTINGS.NAME, tmp_NAME.c_str());
//              tmp_START_INDEX += tmp_NAME.length() + 1;
//              String tmp_WIFI_SSID = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(SETTINGS.WIFI_SSID, tmp_WIFI_SSID.c_str());
//              tmp_START_INDEX += tmp_WIFI_SSID.length() + 1;
//              String tmp_WIFI_PASSWORD = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              strcpy(SETTINGS.WIFI_PASSWORD, tmp_WIFI_PASSWORD.c_str());
//              tmp_START_INDEX += tmp_WIFI_PASSWORD.length() + 1;
//              String tmp_WIFI_DHCP = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SETTINGS.WIFI_DHCP = tmp_WIFI_DHCP.toInt();
//              tmp_START_INDEX += tmp_WIFI_DHCP.length() + 1;
//              String tmp_WIFI_IP_0 = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SETTINGS.WIFI_IP[0] = tmp_WIFI_IP_0.toInt();
//              tmp_START_INDEX += tmp_WIFI_IP_0.length() + 1;
//              String tmp_WIFI_IP_1 = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SETTINGS.WIFI_IP[1] = tmp_WIFI_IP_1.toInt();
//              tmp_START_INDEX += tmp_WIFI_IP_1.length() + 1;
//              String tmp_WIFI_IP_2 = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SETTINGS.WIFI_IP[2] = tmp_WIFI_IP_2.toInt();
//              tmp_START_INDEX += tmp_WIFI_IP_2.length() + 1;
//              String tmp_WIFI_IP_3 = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SETTINGS.WIFI_IP[3] = tmp_WIFI_IP_3.toInt();
//              tmp_START_INDEX += tmp_WIFI_IP_3.length() + 1;
//              String tmp_WIFI_GATE_0 = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SETTINGS.WIFI_GATE[0] = tmp_WIFI_GATE_0.toInt();
//              tmp_START_INDEX += tmp_WIFI_GATE_0.length() + 1;
//              String tmp_WIFI_GATE_1 = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SETTINGS.WIFI_GATE[1] = tmp_WIFI_GATE_1.toInt();
//              tmp_START_INDEX += tmp_WIFI_GATE_1.length() + 1;
//              String tmp_WIFI_GATE_2 = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SETTINGS.WIFI_GATE[2] = tmp_WIFI_GATE_2.toInt();
//              tmp_START_INDEX += tmp_WIFI_GATE_2.length() + 1;
//              String tmp_WIFI_GATE_3 = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SETTINGS.WIFI_GATE[3] = tmp_WIFI_GATE_3.toInt();
//              tmp_START_INDEX += tmp_WIFI_GATE_3.length() + 1;
//              String tmp_WIFI_MASK_0 = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SETTINGS.WIFI_MASK[0] = tmp_WIFI_MASK_0.toInt();
//              tmp_START_INDEX += tmp_WIFI_MASK_0.length() + 1;
//              String tmp_WIFI_MASK_1 = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SETTINGS.WIFI_MASK[1] = tmp_WIFI_MASK_1.toInt();
//              tmp_START_INDEX += tmp_WIFI_MASK_1.length() + 1;
//              String tmp_WIFI_MASK_2 = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("|", tmp_START_INDEX + 1));
//              SETTINGS.WIFI_MASK[2] = tmp_WIFI_MASK_2.toInt();
//              tmp_START_INDEX += tmp_WIFI_MASK_2.length() + 1;
//              String tmp_WIFI_MASK_3 = tmp_SQL_RESULTS.substring(tmp_START_INDEX + 1, tmp_SQL_RESULTS.indexOf("<", tmp_START_INDEX + 1));
//              SETTINGS.WIFI_MASK[3] = tmp_WIFI_MASK_3.toInt();
//              tmp_START_INDEX += tmp_WIFI_MASK_3.length() + 1;
//              SETTINGS_ALTERED = true;
//            } else if (tmp_SQL_RESULTS.indexOf("CODE_90") > 0) {
//              #if ESP_SYNCSERVER_DEBUG > 0
//                Serial.println(F("Sync failed. Invalid station."));
//              #endif
//            } else if (tmp_SQL_RESULTS.indexOf("CODE_91") > 0) {
//              #if ESP_SYNCSERVER_DEBUG > 0
//                Serial.println(F("Sync failed. Invalid authentication."));
//              #endif
//            } else {  // UNKNOWN ERROR
//              #if ESP_SYNCSERVER_DEBUG > 0
//                Serial.println(F("Sync failed. Illegal response from server."));
//              #endif
//            }
//          } else {
//            #if ESP_SYNCSERVER_DEBUG > 0
//              Serial.println(F("Sync failed. Invalid response from server."));
//            #endif
//          }
//          SYNCSERVER_DTR = false;
//        }
//      }
//    }
  #endif
}

void ANALYZE_OTA(void) {

  #if USE_ESP_OTA == 1
  
    #if DEBUG_FUNCTIONS_NETWORK > 0
      Serial.println(F("ANALYZE_OTA"));
    #endif
  
    if (!WIFI_ERROR && !SYNCSERVER_ERROR) {
      #if ESP_OTA_DEBUG > 0
        Serial.print(F("Checking for updates: "));
      #endif
      t_httpUpdate_return tmp_ANALYZE_OTA_RESPONSE = ESPhttpUpdate.update(SYNCSERVER_HOME, 80, "/SYSTEMS/AQUA.php", FW_VERSION);
      switch (tmp_ANALYZE_OTA_RESPONSE) {
        case HTTP_UPDATE_FAILED:
          #if ESP_OTA_DEBUG > 0
            Serial.printf("failed. Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
            Serial.println();
          #endif
        break;
        case HTTP_UPDATE_NO_UPDATES:
          #if ESP_OTA_DEBUG > 0
            Serial.println(F("succeed. No new updates."));
          #endif
        break;
        case HTTP_UPDATE_OK:
          #if ESP_OTA_DEBUG > 0
            Serial.println(F("succeed. Updated."));
          #endif
        break;
      }
    } else {
      #if ESP_OTA_DEBUG > 0
        Serial.println(F("failed. Server not reachable."));
      #endif
    }
    
  #endif
}

void ANALYZE_RADIO(void) {
  
  #if USE_RADIO == 1
  
    #if DEBUG_FUNCTIONS_NETWORK > 0
      Serial.println(F("ANALYZE_RADIO"));
    #endif
  
  #endif
}

void ANALYZE_SIMCARD(void) {
  
  #if USE_SIMCARD
  
    #if DEBUG_FUNCTIONS_NETWORK == 1
      Serial.println(F("ANALYZE_SIMCARD"));
    #endif
  
  #endif
}

void HELPER_EXIP(void) {

  #if USE_ESP_WIFI == 1
  
    #if DEBUG_FUNCTIONS_NETWORK == 1
      Serial.println(F("HELPER_EXIP"));
    #endif

    #if ESP_WIFI_DEBUG > 1
      Serial.print(F("Getting external IP: "));
    #endif
    if (CLIENT.connect("api.ipify.org", 80)) {
      CLIENT.print("GET /?format=text HTTP/1.1\r\nHost: api.ipify.org\r\n\r\n");
      uint32_t tmp_TIMEOUT = millis();
      while (CLIENT.available() == 0) {
        if (millis() - tmp_TIMEOUT > 10000) {
          #if DEBUG_FUNCTIONS_HELPER_EXIP == 1
            Serial.print(F("failed. Timeout."));
          #endif
          return;
        }
      }
      uint16_t tmp_MESSAGE_SIZE;
      while ((tmp_MESSAGE_SIZE = CLIENT.available()) > 0) {
        uint8_t* msg = (uint8_t*)malloc(tmp_MESSAGE_SIZE);
        tmp_MESSAGE_SIZE = CLIENT.read(msg, tmp_MESSAGE_SIZE);
        Serial.write(msg, tmp_MESSAGE_SIZE);
        free(msg);
      }
    } else {
      #if ESP_WIFI_DEBUG > 1
        Serial.println(F("failed. IP Server not reachable."));
      #endif
    }

  #endif
}

void HELPER_PING(void) {

  #if USE_ESP_WIFI == 1
  
    #if DEBUG_FUNCTIONS_NETWORK == 0
      Serial.println(F("PINGING"));
    #endif
    
    #if DEBUG_FUNCTIONS_PINGING == 1
      Serial.print(F("Pinging server... "));
    #endif
  
    if (!WIFI_ERROR) {
      if (Ping.ping(SYNCSERVER_HOME, 3)) {
        #if DEBUG_FUNCTIONS_PINGING == 1
          Serial.println(F("succeed."));
        #endif
        SYNCSERVER_ERROR = false;
      } else {
        #if DEBUG_FUNCTIONS_PINGING == 1
          Serial.println(F("failed. Server not reachable."));
        #endif
        SYNCSERVER_ERROR = true;
      }
    } else {
      #if DEBUG_FUNCTIONS_PINGING == 1
        Serial.println(F("failed. WiFi not available."));
      #endif
      SYNCSERVER_ERROR = true;
    }
    
  #endif
}
