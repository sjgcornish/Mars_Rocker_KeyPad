bool F2Menu(){
  readyStatus= "0";
  bool inSubmenu = true;
  //tell pico customKey pad in program mode
  u8g2.clear();
  bool changed = false;
  int position = 0;
  int menuoption = 0;
  displayF2Menu(0);
  menuoption = getMenuOption(1,5);
  u8g2.clear();
  u8g2.setCursor(0,40);
  u8g2.print("'ENT' to confirm");
  u8g2.setCursor(0,56);
  u8g2.print("'ESC' to cancel");
  u8g2.setCursor(0,7);
  u8g2.sendBuffer();
  //Serial.print("menuoption");  Serial.println(menuoption);
  //Serial.println("f2help");   
  switch (menuoption){   
    case 0:
      redisplayStartScreen();
      inSubmenu = false;
    break;
    case 1:
      systemsSettingsMenuHandler();
    break;
    case 2:
      driveSettingsMenuHandler();
    break;
    case 3:
      gimbalSettingsMenuHandler();
    break;
    case 4:
      autopanSettingsMenuHandler();
    break;
    case 5:
      servoTypeMenuHandler();
    break;
    case 10:
      EEPROMHandlerF2(0, 0); //Special case
  }
  return inSubmenu;
} //END F2Menu

void displayF2Menu(int option){
   u8g2.clear();
   u8g2.setCursor(0,7);
   u8g2.print("SETTINGS");
   if (option == 1) {invertText(1,0); }else{u8g2.setCursor(0,24);u8g2.print(F2MenuText[0]);}   
   if (option == 2) {invertText(1,1); }else{u8g2.setCursor(0,24);u8g2.print(F2MenuText[1]);}   
   if (option == 3) {invertText(1,2); }else{u8g2.setCursor(0,32);u8g2.print(F2MenuText[2]);}
   if (option == 4) {invertText(1,3); }else{u8g2.setCursor(0,40);u8g2.print(F2MenuText[3]);}
   if (option == 5) {invertText(1,4); }else{u8g2.setCursor(0,48);u8g2.print(F2MenuText[4]);}
  u8g2.setCursor(0,56);u8g2.print("Key '#' to Save");
  u8g2.setCursor(0,64);u8g2.print("Key 'Esc' to Exit");
  u8g2.sendBuffer();
} //END displayF2Menu

void systemsSettingsMenuHandler(){
    u8g2.clear();
    bool changed = false;
    int position = 0;
    int menuoption = 0;
    displaySystemSettingsMenu(0);
    menuoption = getMenuOption(5,3);
    u8g2CurrentValue(); 
    switch (menuoption){
    case 0:
      redisplayStartScreen();
      //inSubmenu = false;
    break;
    case 1:
      u8g2.print(systemSettingsText[0]);
      u8g2.setCursor(90,17);  u8g2.print(String(_mainSettings.avoidDistance));
      u8g2.sendBuffer();
      u8g2.setCursor(90,26);
      if (getCommandString(90) == true){
        _mainSettings.avoidDistance = atoi(keypad_receivedChars);
        changed = true;        
      }
    break;
    case 2:
      u8g2.print(systemSettingsText[2]);
      u8g2.setCursor(90,17);  u8g2.print(String(_mainSettings.minSpeed));
      u8g2.sendBuffer();
      u8g2.setCursor(90,26);
      if (getCommandString(90) == true){
        _mainSettings.minSpeed = atoi(keypad_receivedChars);
        changed = true;
      }
    break; 
    case 3:
      u8g2.print(systemSettingsText[3]);
      u8g2.setCursor(90,17);  u8g2.print(String(_mainSettings.maxSpeed));
      u8g2.sendBuffer();
      u8g2.setCursor(90,26);
      if (getCommandString(90) == true){
        _mainSettings.maxSpeed = atoi(keypad_receivedChars);
        changed = true;
      }
    break;   
    }
    if (changed == true){
      updateMainController(mainSettingsGroupType, SystemSettingsType, menuoption, 0);
   } 
} //END systemsSettingsMenuHandler

void displaySystemSettingsMenu(int option){
   u8g2.clear();
   u8g2.setCursor(0,7);
   u8g2.print("SYSTEM SETTINGS");
   Serial.println("SYSTEM SETTINGS");
   if (option == 1) {invertText(5,0); }else{u8g2.setCursor(0,16);u8g2.print(systemSettingsText[0]);};
   if (option == 2) {invertText(5,1); }else{u8g2.setCursor(0,24);u8g2.print(systemSettingsText[1]);};
   if (option == 3) {invertText(5,2); }else{u8g2.setCursor(0,32);u8g2.print(systemSettingsText[2]);};
   u8g2.sendBuffer();
} //END displaySystemSettingsMenu

void driveSettingsMenuHandler(){
    u8g2.clear();
    bool changed = false;
    int position = 0;
    int menuoption = 0;
    displayDriveSettingsMenu(0);
    menuoption = getMenuOption(10,2);
    u8g2CurrentValue();
    switch (menuoption){
    case 0:
      redisplayStartScreen();
      //inSubmenu = false;
    break;
    case 1:
      u8g2.print(driveSettingsText[0]);
      u8g2.setCursor(90,17);  u8g2.print(String(_mainSettings.steeringServoStepSize));
      u8g2.sendBuffer();
      u8g2.setCursor(90,26);
      if (getCommandString(90) == true){
        _mainSettings.steeringServoStepSize = atoi(keypad_receivedChars);
        changed = true;        
      }
    break;
    case 2:
      u8g2.print(driveSettingsText[1]);
      u8g2.setCursor(90,17);  u8g2.print(String(_mainSettings.steeringServoStepDelay));
      u8g2.sendBuffer();
      u8g2.setCursor(90,26);
      if (getCommandString(90) == true){
        _mainSettings.steeringServoStepDelay = atoi(keypad_receivedChars);
        changed = true;
      }
    break; 
    }
    if (changed == true){
      updateMainController(mainDriveGroupType, DriveSettingsType, menuoption, 1);
   }  
} //END driveSettingsMenuHandler

void displayDriveSettingsMenu(int option){
   u8g2.clear();
   u8g2.setCursor(0,7);
   u8g2.print("DRIVE SETTINGS");
   if (option == 1) {invertText(10,0); }else{u8g2.setCursor(0,16);u8g2.print(driveSettingsText[0]);};
   if (option == 2) {invertText(10,1); }else{u8g2.setCursor(0,24);u8g2.print(driveSettingsText[1]);};
   u8g2.sendBuffer();
} //END displaySystemSettingsMenu

void unitsHandler(){
  u8g2.clear();
  bool changed = false;
  currentUnits = _gimbalSettings.units;
  int menuoption = 0;
  displayUnitsMenu(0);
  menuoption = getMenuOption(16,2);
  if (menuoption == 0){
    if (changed == true){
      //printConfig();
    }
  }else{
    _gimbalSettings.units = menuoption;
    if (currentUnits != _gimbalSettings.units){
      changed = true;
    }
  }
  if (changed == true){
    updateMainController(gimbalSettingsGroupType, gimbalDriveGroupType, UnitType, 0);  //packetID, type
  }
} //END unitsHandler

void stepModeHandler(){
  u8g2.clear();
  bool changed = false;
  currentStepMode = _gimbalSettings.stepMode;
  int menuoption = 0;
  displayStepModeMenu(0);
  menuoption = getMenuOption(17,2);
  if (menuoption == 0){  //when ENT pressed
    if (changed == true){
      //printConfig();
    }
  }else{
    _gimbalSettings.stepMode = menuoption;
    if (currentStepMode != _gimbalSettings.stepMode){
      changed = true;
    }
  }
  if (changed == true){
    updateMainController(gimbalSettingsGroupType, gimbalDriveGroupType, StepModeType, 0);  //packetID, type
  }
} //END stepModeHandler

void gimbalSettingsMenuHandler(){
   u8g2.clear();
   bool changed = false;
   int position = 0;
   int menuoption = 0;
   displayGimbalSettingsMenu(0);
   menuoption = getMenuOption(6,4);
   u8g2CurrentValue();
   switch (menuoption){
    case 0:
      redisplayStartScreen();
      //inSubmenu = false;
    break;
    case 1:
      unitsHandler();
    break;
    case 2:
      stepModeHandler();
    break;    
    case 3:
      u8g2.print(gimbalSettingsText[2]);
      u8g2.setCursor(90,17);  u8g2.print(String(_gimbalSettings.stepSize));
      u8g2.sendBuffer();
      u8g2.setCursor(90,26);
      if (getCommandString(90) == true){
        _gimbalSettings.stepSize = atoi(keypad_receivedChars);
        changed = true;        
      }
    break;
    case 4:
      u8g2.print(gimbalSettingsText[3]);
      u8g2.setCursor(90,17);  u8g2.print(String(_gimbalSettings.stepDelay));
      u8g2.sendBuffer();
      u8g2.setCursor(90,26);
      if (getCommandString(90) == true){
        _gimbalSettings.stepDelay = atof(keypad_receivedChars);
        changed = true;        
      }
    break;   
  }
  if (changed == true){
    updateGimbalController(gimbalSettingsGroupType, gimbalDriveGroupType, menuoption, 0);  
  } 
} //END gimbalSettingsMenuHandler

void displayGimbalSettingsMenu(int option){
   u8g2.clear();
   u8g2.setCursor(0,7);
   u8g2.print("GIMBAL SETTINGS");
   if (option == 1) {invertText(6,0); }else{u8g2.setCursor(0,16);u8g2.print(gimbalSettingsText[0]);};
   if (option == 2) {invertText(6,1); }else{u8g2.setCursor(0,24);u8g2.print(gimbalSettingsText[1]);};
   if (option == 3) {invertText(6,2); }else{u8g2.setCursor(0,32);u8g2.print(gimbalSettingsText[2]);};
   if (option == 4) {invertText(6,3); }else{u8g2.setCursor(0,40);u8g2.print(gimbalSettingsText[3]);};
   help();
} //END displayGimbalSettingsMenu

void displayStepModeMenu(int option){
  u8g2.clear();
  u8g2.setCursor(0,7);
  u8g2.print("STEP MODE -");
  u8g2.setCursor(110,0);
  u8g2.print(currentStepMode);
  if (option == 1) {invertText(17,0); }else{u8g2.setCursor(0,16);u8g2.print(stepModeText[0]);};
  if (option == 2) {invertText(17,1); }else{u8g2.setCursor(0,24);u8g2.print(stepModeText[1]);};
  help();
} //END u8g2CrashModeMenu

void displayUnitsMenu(int option){
  u8g2.clear();
  u8g2.setCursor(0,7);
  u8g2.print("UNITS -");
  u8g2.setCursor(110,0);
  u8g2.print(currentUnits);
  if (option == 1) {invertText(16,0); }else{u8g2.setCursor(0,16);u8g2.print(unitsText[0]);};
  if (option == 2) {invertText(16,1); }else{u8g2.setCursor(0,24);u8g2.print(unitsText[1]);};
  help();
} //END u8g2CrashModeMenu


void autopanSettingsMenuHandler(){
   u8g2.clear();
   int lastmenuItem = 0;
   bool changed = false;
   int position = 0;
   int menuoption = 0;
   displayAutopanSettingsMenu(0);
   menuoption = getMenuOption(15,4);
   u8g2CurrentValue();
   switch (menuoption){
    case 0:
      redisplayStartScreen();
      //inSubmenu = false;
    break;
    case 1:
      u8g2.print(autopanSettingsText[0]);
      u8g2.setCursor(90,17);  u8g2.print(String(_autopanSettings.stepSize));
      u8g2.sendBuffer();
      u8g2.setCursor(90,26);
      if (getCommandString(90) == true){
        _autopanSettings.stepSize = atoi(keypad_receivedChars);
        changed = true;        
      }
    break;
    case 2:
      u8g2.print(autopanSettingsText[1]);
      u8g2.setCursor(90,17);  u8g2.print(String(_autopanSettings.stepDelay));
      u8g2.sendBuffer();
      u8g2.setCursor(90,26);
      if (getCommandString(90) == true){
        _autopanSettings.stepDelay = atoi(keypad_receivedChars);
        changed = true;        
      }
    break;    
    case 3:
      u8g2.print(autopanSettingsText[2]);
      u8g2.setCursor(90,17);  u8g2.print(String(_autopanSettings.autopanMin));
      u8g2.sendBuffer();
      u8g2.setCursor(90,26);
      if (getCommandString(90) == true){
        _autopanSettings.autopanMin = atoi(keypad_receivedChars);
        changed = true;        
      }
    break;
    case 4:
      u8g2.print(autopanSettingsText[3]);
      u8g2.setCursor(90,17);  u8g2.print(String(_autopanSettings.autopanMin));
      u8g2.sendBuffer();
      u8g2.setCursor(90,26);
      if (getCommandString(90) == true){
        _autopanSettings.autopanMax = atof(keypad_receivedChars);
        changed = true;        
      }
    break;   
    case 10:
      if (changed == true)
        EEPROMHandlerF2(gimbalSettingsGroupType, autopanSettingsType);
    break;
  }
  if (changed == true){
    updateGimbalController(gimbalSettingsGroupType, autopanSettingsType, menuoption, 1); 
  }
} //END autopanSettingsMenuHandler

void displayAutopanSettingsMenu(int option){
   u8g2.clear();
   u8g2.setCursor(0,7);
   u8g2.print("AUTOPAN SETTINGS");
   if (option == 1) {invertText(15,0); }else{u8g2.setCursor(0,16);u8g2.print(autopanSettingsText[0]);};
   if (option == 2) {invertText(15,1); }else{u8g2.setCursor(0,24);u8g2.print(autopanSettingsText[1]);};
   if (option == 3) {invertText(15,2); }else{u8g2.setCursor(0,32);u8g2.print(autopanSettingsText[2]);};
   if (option == 4) {invertText(15,3); }else{u8g2.setCursor(0,40);u8g2.print(autopanSettingsText[3]);};
   help();
} //END displayAutopanSettingsMenu

void servoTypeMenuHandler(){
  bool inMenu = true; 
  while (inMenu == true){       
    inMenu = servoTypeMenu();
  }
} //END operatingModeHandler


bool servoTypeMenu(){
  u8g2.clear();
  bool inSubmenu = true;
  int lastmenuItem = 0;
  bool changed = false;
  int position = 0;
  int menuoption = 0;
  displayServoTypeMenu(0);
  menuoption = getMenuOption(19,4);
  Serial.print("option: "); Serial.println(menuoption);
  if (menuoption == 0){
    //redisplayStartScreen();
    Serial.println("servoTypeMenu Exit");
    inSubmenu = false;
  }else if (menuoption == 3){
    u8g2CurrentValue();
    u8g2.print("Enter Servo number: ");
    u8g2.sendBuffer();
    u8g2.setCursor(90,26);
    if (getCommandString(90) == true){
      servoID = atoi(keypad_receivedChars);
      servoTypeHandler(servoGimbalGroupType, menuoption);   
      } 
  }else{
    servoTypeHandler(servoGimbalGroupType, menuoption);
  }
  return inSubmenu;
} //END servoTypeMenu

void displayServoTypeMenu(int option){
   u8g2.clear();
   u8g2.setCursor(0,7);
   u8g2.print("SERVO TYPE");
   if (option == 1) {invertText(19,0); }else{u8g2.setCursor(0,16);u8g2.print(servoTypeText[0]);};
   if (option == 2) {invertText(19,1); }else{u8g2.setCursor(0,24);u8g2.print(servoTypeText[1]);};
   if (option == 3) {invertText(19,2); }else{u8g2.setCursor(0,32);u8g2.print(servoTypeText[2]);};
   if (option == 4) {invertText(19,3); }else{u8g2.setCursor(0,31);u8g2.print(servoTypeText[3]);};
   help();
} //END displayAutopanSettingsMenu

void servoTypeHandler(int type, int option){
  Serial.println("servoTypeHandler");
  bool inMenu = true; 
  while (inMenu == true){       
    inMenu = servoSettingsMenuSelection(type, option);
  }
}

bool servoSettingsMenuSelection(int type, int option){
  Serial.println("servoSettingsMenuSelection");
  bool inMenu = true; 
  while (inMenu == true){       
    inMenu = servoSettingsInputHandler(type, option);   
  }
  return inMenu;
}

bool servoSettingsInputHandler(int type, int option){
  Serial.print("servoMin " );Serial.println(myServoStruct.myPitchServoSettings.servoMin);
  u8g2.clear();
  bool inSubmenu = true;
  int lastmenuItem = 0;
  bool changed = false;
  int position = 0;
  int menuoption = 0;
  displayServoSettingsMenu(0);
  getCurrentSetting(type, option);
  menuoption = getMenuOption(18,6);
  u8g2CurrentValue();
  switch (menuoption){
    case 0:
      //redisplayStartScreen();
      inSubmenu = false;
    break;
    case 1: //servoType
      u8g2.print(servoSettingsText[0]);
      u8g2.setCursor(90,17);  u8g2.print(String(_servoSettings.servoType));
      u8g2.sendBuffer(); u8g2.setCursor(90,26);
      if (getCommandString(90) == true){_servoSettings.servoType = atoi(keypad_receivedChars);changed = true;}
    break;
    case 2:
  
      u8g2.print(servoSettingsText[1]);
      u8g2.setCursor(90,17);   u8g2.print(String(_servoSettings.servoMin));
      Serial.println(myServoStruct.myPitchServoSettings.servoMin); //u8g2.print(String(_servoSettings.servoMin));
      u8g2.sendBuffer(); u8g2.setCursor(90,26);
      if (getCommandString(90) == true){_servoSettings.servoMin = atoi(keypad_receivedChars);changed = true;}
    break;    
    case 3:
      u8g2.print(servoSettingsText[2]);
      u8g2.setCursor(90,17);  u8g2.print(String(_servoSettings.servoMax));
      u8g2.sendBuffer(); u8g2.setCursor(90,26);
      if (getCommandString(90) == true){_servoSettings.servoMax = atoi(keypad_receivedChars);changed = true;}
    break;    
    case 4:
      u8g2.print(servoSettingsText[3]);
      u8g2.setCursor(90,17);  u8g2.print(String(_servoSettings.servoCTR));
      u8g2.sendBuffer(); u8g2.setCursor(90,26);
      if (getCommandString(90) == true){_servoSettings.servoCTR = atoi(keypad_receivedChars);changed = true;}
    break;
    case 5:
      u8g2.print(servoSettingsText[4]);
      u8g2.setCursor(90,17);  u8g2.print(String(_servoSettings.sweepMin));
      u8g2.sendBuffer(); u8g2.setCursor(90,26);
      if (getCommandString(90) == true){_servoSettings.sweepMin = atoi(keypad_receivedChars);changed = true;}
    break;   
   case 6:
      u8g2.print(servoSettingsText[5]);
      u8g2.setCursor(90,17);  u8g2.print(String(_servoSettings.sweepMax));
      u8g2.sendBuffer(); u8g2.setCursor(90,26);
      if (getCommandString(90) == true){_servoSettings.sweepMax = atoi(keypad_receivedChars);changed = true;}
    break;   
  }
  if (changed == true && servoOption == servoGimbalGroupType){
    if (option = 1){_servoPitchSettings = _servoSettings;
    }else if (option = 2){_servoRollSettings = _servoSettings;
    }else if (option = 3){_servoPanSettings = _servoSettings;
    }
    updateGimbalServoController(servoGimbalGroupType, option, 0);
  }else if (changed == true && servoOption == servoWheelGroupType){
    updateMainServoController(servoWheelGroupType, servoID, 0);
  }
  return inSubmenu; 
} //END servoSettingsInputHandler
     

void displayServoSettingsMenu(int option){
   u8g2.clear();
   u8g2.setCursor(0,7);
   u8g2.print("SERVO SETTINGS");
   if (option == 1) {invertText(18,0); }else{u8g2.setCursor(0,16);u8g2.print(servoSettingsText[0]);};
   if (option == 2) {invertText(18,1); }else{u8g2.setCursor(0,24);u8g2.print(servoSettingsText[1]);};
   if (option == 3) {invertText(18,2); }else{u8g2.setCursor(0,32);u8g2.print(servoSettingsText[2]);};
   if (option == 4) {invertText(18,3); }else{u8g2.setCursor(0,40);u8g2.print(servoSettingsText[3]);};
   if (option == 5) {invertText(18,4); }else{u8g2.setCursor(0,48);u8g2.print(servoSettingsText[4]);};
  if (option == 6) {invertText(18,5); }else{u8g2.setCursor(0,56);u8g2.print(servoSettingsText[5]);};
  help();
} //END servoSettingsInputMenu


void EEPROMHandlerF2(int groupType, int lastmenuSelected){
  bool inMenu = true; 
  while (inMenu == true){       
    inMenu = EEPROMMenuF2(groupType, lastmenuSelected);
  }
} //END EEPROMHandlerF1



void u8g2CurrentValue(){
  u8g2.clear();
  u8g2.setCursor(0,24);
  u8g2.print("Current Value: ");
  u8g2.setCursor(0,26);
  u8g2.print("New Value: ");
  u8g2.setCursor(0,40);
  u8g2.print("'Ent' to confirm");
  u8g2.setCursor(0,56);
  u8g2.print("'Esc' to cancel");
  u8g2.sendBuffer(); 
  u8g2.setCursor(0,7);
}

void getCurrentSetting(int type, int option){
  if (type == servoGimbalGroupType){
    switch (option){
      case 1:
        _servoSettings = myServoStruct.myPitchServoSettings;
      break;
      case 2:
        _servoSettings = _servoRollSettings;
      break;
      case 3:
        _servoSettings = _servoPanSettings;
      break;
    }
  }else{
    _servoSettings = MyServoStructMain.myServoSettingsArray[option];
  }
}

//myServoStruct.myPitchServoSettings = _servoPitchSettings;
