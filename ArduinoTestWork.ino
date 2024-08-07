//Hubbilling
//ArduinoTestWork.ino
//07.08.2024
//Board: Arduino UNO
//IDE: Arduino IDE

#include <EEPROM.h>

void workWithEEPROM(String input);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
  }
  Serial.println("Ready!");
}

void loop() {
  if (Serial.available() > 0) {
    String dataInput = Serial.readStringUntil('\n');
    workWithEEPROM(dataInput);
  }
}

void workWithEEPROM(String input) {
  input.trim();
  
  if (input.indexOf("eeprom") != -1) {
    if (input.indexOf("-w") != -1 && input.indexOf("-a") != -1 && input.indexOf("-v") != -1) {
      int startIndexAWrite = input.indexOf("-a") + 3;
      int endIndexAWrite = input.indexOf(" ", startIndexAWrite);
      if (endIndexAWrite == -1) {
        endIndexAWrite = input.length();
      }
      
      int startIndexVWrite = input.indexOf("-v") + 3;
      int endIndexVWrite = input.indexOf(" ", startIndexVWrite);
      if (endIndexVWrite == -1) {
        endIndexVWrite = input.length();
      }
      
      int address = input.substring(startIndexAWrite, endIndexAWrite).toInt();
      int value = input.substring(startIndexVWrite, endIndexVWrite).toInt();
      
      if (address >= 0 && address < EEPROM.length()) {
        EEPROM.update(address, value);
        Serial.println("Write Success!");
      } else {
        Serial.println("Error: Address out of range");
      }
      
    } else if (input.indexOf("-r") != -1 && input.indexOf("-a") != -1) {
      int startIndexA = input.indexOf("-a") + 3;
      int endIndexA = input.indexOf(" ", startIndexA);
      if (endIndexA == -1) {
        endIndexA = input.length();
      }
      
      int address = input.substring(startIndexA, endIndexA).toInt();
      
      if (address >= 0 && address < EEPROM.length()) {
        int value = EEPROM.read(address);
        Serial.println("Value: " + String(value));
      } else {
        Serial.println("Error: Address out of range");
      }
      
    } else if (input.indexOf("-e") != -1 && input.indexOf("-a") != -1) {
      int startIndexADelete = input.indexOf("-a") + 3;
      int endIndexADelete = input.indexOf(" ", startIndexADelete);
      if (endIndexADelete == -1) {
        endIndexADelete = input.length();
      }
      
      int address = input.substring(startIndexADelete, endIndexADelete).toInt();
      
      if (address >= 0 && address < EEPROM.length()) {
        EEPROM.update(address, 0);
        Serial.println("Delete Success!");
      } else {
        Serial.println("Error: Address out of range");
      }
      
    } else if (input.indexOf("-d") != -1) {
      Serial.println("EEPROM Dump:");
      for (int i = 0; i < EEPROM.length(); i += 8) {
        Serial.print(String(i, HEX));
        Serial.print(" : ");
        for (int j = 0; j < 8; ++j) {
          if (i + j < EEPROM.length()) {
            int value = EEPROM.read(i + j);
            if (value < 16) Serial.print("0");
            Serial.print(String(value, HEX));
            Serial.print(" ");
          }
        }
        Serial.println();
      }
    } else {
      Serial.println("Error: Invalid command format");
    }
  }
}
