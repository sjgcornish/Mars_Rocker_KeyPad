void invertText(int menuType, int menuindex){
   int cursorY = ((menuindex+1) * 8) + 7; //set cursor y starts at bottpm of character hence +7
   if (menuType == 0){u8g2.setCursor(10, cursorY); u8g2.print(F1MenuText[menuindex]);}
   if (menuType == 1){u8g2.setCursor(10, cursorY); u8g2.print(F2MenuText[menuindex]);}
   if (menuType == 2){u8g2.setCursor(10, cursorY); u8g2.print(steeringModeMenuText[menuindex]);}
   if (menuType == 3){u8g2.setCursor(10, cursorY); u8g2.print(steeringControlMenuText[menuindex]);}
   if (menuType == 4){u8g2.setCursor(10, cursorY); u8g2.print(joystickModeMenuText[menuindex]);}
   if (menuType == 5){u8g2.setCursor(10, cursorY); u8g2.print(systemSettingsText[menuindex]);}
   if (menuType == 6){u8g2.setCursor(10, cursorY); u8g2.print(gimbalSettingsText[menuindex]);}
   if (menuType == 7){u8g2.setCursor(10, cursorY); u8g2.print(gimbalModeText[menuindex]);}
   if (menuType == 8){u8g2.setCursor(10, cursorY); u8g2.print(gimbalControlText[menuindex]);}
   if (menuType == 9){u8g2.setCursor(10, cursorY); u8g2.print(autopanControlText[menuindex]);}
   if (menuType == 10){u8g2.setCursor(10, cursorY); u8g2.print(driveSettingsText[menuindex]);}
   if (menuType == 11){u8g2.setCursor(10, cursorY); u8g2.print(systemOperatingText[menuindex]);}
   if (menuType == 12){u8g2.setCursor(10, cursorY); u8g2.print(crashModeText[menuindex]);}
   if (menuType == 13){u8g2.setCursor(10, cursorY); u8g2.print(mirrorModeText[menuindex]);}
   if (menuType == 14){u8g2.setCursor(10, cursorY); u8g2.print(gimbalOperatingMenuText[menuindex]);}
   if (menuType == 15){u8g2.setCursor(10, cursorY); u8g2.print(autopanSettingsText[menuindex]);}
   if (menuType == 16){u8g2.setCursor(10, cursorY); u8g2.print(unitsText[menuindex]);}
   if (menuType == 17){u8g2.setCursor(10, cursorY); u8g2.print(stepModeText[menuindex]);}
   if (menuType == 18){u8g2.setCursor(10, cursorY); u8g2.print(servoSettingsText[menuindex]);}
   if (menuType == 19){u8g2.setCursor(10, cursorY); u8g2.print(servoTypeText[menuindex]);}
   if (menuType == 20){u8g2.setCursor(10, cursorY); u8g2.print(EEPROMText[menuindex]);}
   if (menuType == 20){u8g2.setCursor(10, cursorY); u8g2.print(uploadDownTextF1[menuindex]);}
   if (menuType == 21){u8g2.setCursor(10, cursorY); u8g2.print(driveModeText[menuindex]);}
}//END invertText

int getMenuOption(int menuType, int menuCount){
  //get button
  int pos = 0;
  char key = NO_KEY;
  bool getkey = true;
  while (getkey == true){
    key = keypad.getKey();
    if (key != NO_KEY){ 
      if (key == 'D'){
        if (pos < menuCount){
          pos++;
          getMenuTree(menuType, pos);
        }else if (pos = menuCount){  
          pos = 1;
          getMenuTree(menuType, pos);
        }
      }else if (key == 'U'){
        if (pos > 0){ 
          pos--;
          if (pos == 0){pos = menuCount;}
          getMenuTree(menuType, pos);
        }
      }else if (key == 'E'){
        getkey = false;
      }else if (key == 'C'){
        pos = 0;
        getkey = false;
      }else if (key == '#'){
        pos = 10;
        getkey = false;         
      }
    }
  }
  Serial.print("pos");  Serial.println(pos);  
  return pos;  
} //END getMenuOption

void getMenuTree(int menuType, int pos){
  if (menuType == 0){displayF1Menu(pos);}
  if (menuType == 1){displayF2Menu(pos);}
  if (menuType == 2){displaySteeringModeMenu(pos);}
  if (menuType == 3){displaySteeringControlMenu(pos);}
  if (menuType == 4){displayJoystickModeMenu(pos);}
  if (menuType == 5){displaySystemSettingsMenu(pos);}
  if (menuType == 6){displayGimbalSettingsMenu(pos);}  
  if (menuType == 7){displayGimbalModeMenu(pos);}
  if (menuType == 8){displayGimbalControlMenu(pos);}
  if (menuType == 9){displayAutopanMenu(pos);}
  if (menuType == 10){displayDriveSettingsMenu(pos);}
  if (menuType == 11){displaySystemOperatingModeMenu(pos);}
  if (menuType == 12){displayCrashModeMenu(pos);}
  if (menuType == 13){displayMirrorModeMenu(pos);}
  if (menuType == 14){displayGimbalOperatingModeMenu(pos);}
  if (menuType == 15){displayAutopanSettingsMenu(pos);}
  if (menuType == 16){displayUnitsMenu(pos);}
  if (menuType == 17){displayStepModeMenu(pos);}
  if (menuType == 18){displayServoSettingsMenu(pos);}
  if (menuType == 19){displayServoTypeMenu(pos);}
  if (menuType == 20){displayEEPROMModeMenu(pos);}
  if (menuType == 21){displayUploadDownLoadMenu(pos);}
} //END getMenuTree

void displayValue(int xpos, int ypos, int value){
   u8g2.setCursor(xpos,ypos);
   u8g2.print("    ");
   u8g2.sendBuffer(); 
   u8g2.setCursor(xpos,ypos);
   u8g2.print(value); 
   u8g2.sendBuffer();
} //END displayValue

void displayCharStr(int xpos, int ypos, char value[]){
   u8g2.setCursor(xpos,ypos);
   u8g2.print("    ");
   u8g2.sendBuffer(); 
   u8g2.setCursor(xpos,ypos);
   u8g2.print(value); 
   u8g2.sendBuffer();
} //END displayCharStr


bool getCommandString(int ypos){
  char key;
  byte ndx = 0;
  bool newString = false;
  bool inputEnded = false;
  while (inputEnded == false){
    key = keypad.getKey();
    if (key != NO_KEY){
      if (key == '*'){
        key = '.';
      }
      Serial.println(key);
      if (key == '<' && ndx >0){
        ndx--;
        byte lastChar = strlen(keypad_receivedChars)-1;
        if (strlen > 0){
          keypad_receivedChars[lastChar] = '\0';
          displayCharStr(90, 26,keypad_receivedChars);
          Serial.println(keypad_receivedChars);
        }
      }else if (key == 'E'){ //Enter
        ndx++;
        keypad_receivedChars[ndx] = '\0';
        newString = true;
        inputEnded = true;
      }else if (key == 'C'){  //Cancel
        newString = false;
        inputEnded = true;
      }else{  
        u8g2.print(key);
        u8g2.sendBuffer();
        keypad_receivedChars[ndx] = key;
        Serial.println(keypad_receivedChars);
        ndx++;
      }      
    }
  }
  //u8g2Startup(false);
  return newString; 
} //END getCommand


bool getNumberString(){
  char key;
  byte ndx = 0;
  bool newString = false;
  bool inputEnded = false;
  while (inputEnded == false){
    key = keypad.getKey();
    if (key != NO_KEY){
      Serial.println(key);
      if (key == '*'){
        key = '.';
        Serial.println(key);
      }else if (key == 'E'){ //Enter
        ndx++;
        keypad_receivedChars[ndx] = '\0';
        newString = true;
        inputEnded = true;
      }else if (key == 'C'){  //Cancel
        newString = false;
        inputEnded = true;
      }else{  
        u8g2.print(key);
        u8g2.sendBuffer();
        keypad_receivedChars[ndx] = key;
        ndx++;
      }      
    }
  }
  return newString; 
} //END getNumberString

char getgimbalControlKey(){
  char key;
  byte ndx = 0;
  bool newString = false;
  bool inputEnded = false;
  while (inputEnded == false){
    key = keypad.getKey();
    if (key != NO_KEY){
      if (key == 'C' || key == '2' || key == '4' || key == '6' || key == '8' ||key == '5' ||key == '0' ||key == '3' || key == '<' || key == '>'){ 
        newString = false;
        inputEnded = true;
      }   
    }
  }
  return key; 
} //END getgimbalControlKey

char getControlKey(){
  char key;
  byte ndx = 0;
  bool newString = false;
  bool inputEnded = false;
  while (inputEnded == false){
    key = keypad.getKey();
    if (key != NO_KEY){
      if (key == 'C' || key == '0' || key == 'U' || key == 'D' || key == '<' || key == '>' || key == '*'){ 
        newString = false;
        inputEnded = true;
      }   
    }
  }
  return key; 
} //getControlKey

char waitforENTorESCKey(){
  char key;
  byte ndx = 0;
  bool newString = false;
  bool inputEnded = false;
  while (inputEnded == false){
    key = keypad.getKey();
    if (key != NO_KEY){
      if (key == 'E'){ //Enter
        ndx++;
        inputEnded = true;
      }else if (key == 'C'){
        inputEnded = true;
      }
    }
  }
  return key;
} //END getESCKey

void waitforESCKey(){
  char key;
  byte ndx = 0;
  bool newString = false;
  bool inputEnded = false;
  while (inputEnded == false){
    key = keypad.getKey();
    if (key != NO_KEY){
      if (key == 'C'){
        inputEnded = true;
      }
    }
  }
} //END getESCKey

void getSystemSettings(int option){
  u8g2.clear();
  u8g2.setCursor(0,12);
  switch(option){
    case 1:
    u8g2.print("Avoid Distance = "); u8g2.print(_mainSettings.avoidDistance);
    u8g2.setCursor(0,21);
    u8g2.print("New Value = ");
    u8g2.sendBuffer();
    Serial.println(getNumberString());
    break;
  }
}
