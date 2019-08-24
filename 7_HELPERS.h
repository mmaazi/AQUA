void (*resetFunc)(void) = 0;

uint16_t HELPERS_MEMORY(void) {
  
  extern int __heap_start, *__brkval; 
  uint16_t v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

bool HELPERS_GET_BIT(uint32_t arg1_DATA, uint8_t arg2_COUNT) {

  return (arg1_DATA & ( 1 << arg2_COUNT )) >> arg2_COUNT;
}

uint32_t HELPERS_SET_BIT(uint32_t arg1_DATA, uint8_t arg2_COUNT,  bool arg3_VALUE) {

  return arg1_DATA |= arg3_VALUE << arg2_COUNT;
}

char HELPERS_HEX2INT(char arg1_HEX) {
  
  if (arg1_HEX >= '0' && arg1_HEX <= '9') return ((char)arg1_HEX - '0');
  if (arg1_HEX >= 'a' && arg1_HEX <= 'f') return ((char)arg1_HEX - 'a' + 10);
  if (arg1_HEX >= 'A' && arg1_HEX <= 'F') return ((char)arg1_HEX - 'A' + 10);
  return (0);
}

uint8_t HELPERS_BCD2BIN(uint8_t arg1_VALUE) {
  
  return arg1_VALUE - 6 * (arg1_VALUE >> 4);
}

uint8_t HELPERS_BIN2BCD (uint8_t arg1_VALUE) {
  
  return arg1_VALUE + 6 * (arg1_VALUE / 10); 
}

void HELPERS_I2C_SCAN(void) {
  
  uint8_t tmp_ERROR;
  uint16_t tmp_COUNT = 0;
  for(uint8_t i = 0; i < 127; i++ ) {
    Wire.beginTransmission(i);
    tmp_ERROR = Wire.endTransmission();
    if (tmp_ERROR == 0) {
      Serial.print("I2C device found at address 0x");
      if (i < 16) Serial.print("0");
      Serial.print(i, HEX);
      Serial.print(" (");
      Serial.print(i);
      Serial.println(")");
      tmp_COUNT++;
    } else if (tmp_ERROR == 4) {
      Serial.print("Unknown error at address 0x");
      if (i < 16) Serial.print("0");
      Serial.println(i, HEX);
    }    
  }
  if (tmp_COUNT == 0) {
    Serial.println("No I2C devices found.");
  } else {
  }
}

bool HELPERS_I2C_CHECK(uint8_t arg1_ADDRESS) {
  
  Wire.beginTransmission(arg1_ADDRESS);
  uint8_t tmp_ERROR = Wire.endTransmission();
  if (tmp_ERROR == 0) return true; else return false;
}
