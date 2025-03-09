bool EEPROMMenuF2(int groupType, int type){
  readyStatus= "0";
  bool inSubmenu = true;
  //tell pico customKey pad in program mode
  u8g2.clear();
  bool changed = false;
  int position = 0;
  int menuoption = 0;
  displayEEPROMModeMenu(0);
  menuoption = getMenuOption(20,4);
  u8g2.clear();
  u8g2.setCursor(0,40);
  u8g2.print("'ENT' to confirm");
  u8g2.setCursor(0,56);
  u8g2.print("'ESC' to cancel");
  u8g2.setCursor(0,7);
  u8g2.sendBuffer();
  //Serial.print("menuoption");  Serial.println(menuoption);  
  switch (menuoption){   //save
    case 0:
      inSubmenu = false;
    break;
    case 1: //Save gimbal changes locally
      if (type == 0){ //from top level menu applies to all
        saveToEEPROMAllGimbal();
        saveToEEPROMAllMain();
      }else if (type == opModeGimbalGroupType){
        EEPROM.put(16,  myGimbalStruct.myOpModeGimbal);
      }else if (type == gimbalSettingsGroupType){
        EEPROM.put(64,  myGimbalStruct.myGimbalSettings);
      }else if (type == autopanSettingsType){
        EEPROM.put(64,  myGimbalStruct.myAutopanSettings);
      }else if (type == servoGimbalGroupType){
        EEPROM.get(80,  myServoStruct.myPitchServoSettings); 
        EEPROM.get(96,  myServoStruct.myRollServoSettings);
        EEPROM.get(112, myServoStruct.myPanServoSettings);
      }else if (type == opModeMainGroupType){
        EEPROM.put(0,   myMainStruct.myOpModeMain);
      }else if (type == mainSettingsGroupType){
        EEPROM.put(32, myMainStruct.myMainSettings);
      }else if (type ==servoWheelGroupType){
        EEPROM.put(128, MyServoStructMain.myServoSettingsArray[1]);
        EEPROM.put(144, MyServoStructMain.myServoSettingsArray[2]);
        EEPROM.put(160, MyServoStructMain.myServoSettingsArray[3]);
        EEPROM.put(176, MyServoStructMain.myServoSettingsArray[4]);
        EEPROM.put(192, MyServoStructMain.myServoSettingsArray[5]);
        EEPROM.put(208, MyServoStructMain.myServoSettingsArray[6]);
      }
    break;
    case 2: //Upload Changes
      if (type ==0) {
         updateGimbalController(0, 0, 0, 2);
         updateMainController(0, 0, 0, 2); 
      }else if (type == opModeGimbalGroupType){
        updateGimbalController(opModeGimbalGroupType, SystemSettingsType, 0, 1);
      }else if (type == gimbalSettingsGroupType){
        updateGimbalController(gimbalSettingsGroupType, 0, 0, 1);
      }else if (type == autopanSettingsType){
        updateGimbalController(gimbalSettingsGroupType, autopanSettingsType, 0, 1);
      }else if (type == servoGimbalGroupType){
        updateGimbalController(gimbalSettingsGroupType, gimbalServoType, 0, 1);
      }else if (type == opModeMainGroupType){
        updateMainServoController(opModeMainGroupType, 0, 1);
      }else if (type == mainSettingsGroupType){
        updateMainServoController(mainSettingsGroupType, 0, 1);
      }else if (type ==servoWheelGroupType){
        updateMainServoController(servoWheelGroupType, 0, 1); 
      }
    break;
    case 3: //download gimbal      
    break; 
    case 4: //download main
    break;
  }
  return inSubmenu;
} // END operatingModeMenu

void updateMainController(uint16_t groupType, uint16_t type, uint16_t subType, uint16_t action){
  uint16_t sendSize = 0;
  myMainStruct.to = gimbalControllerID;
  myMainStruct.groupType = groupType;
  myMainStruct.type = type;
  myMainStruct.subType = subType;
  myMainStruct.action = action;
  myMainStruct.myOpModeMain = _opModeMain;
  myMainStruct.myMainSettings = _mainSettings;
  myMainStruct.myMainDrive = _mainDrive;
  printmyMainStruct();
  sendSize = loopTransfer.txObj(myMainStruct, sendSize);
  loopTransfer.sendData(sendSize, mainControllerID); //packetID is read by the receiver, to indicate which variables are coming through
  Serial.print("Sent Packet #"); Serial.println(mainControllerID);  
}

void updateGimbalController(uint16_t groupType, uint16_t type, uint16_t subType, uint16_t action){
  //NOTE if subtype = 0 then update applies to all subtypes in the type
  //NOTE if type = 0 then update applies to all types and subtypes inthe group type
  //Note if action = 1 then tells remote end to locally save accrding to type and subtype
  //If action = 2 then tells remote end to sace all gimbal commands regardless of types
  uint16_t sendSize = 0;
  myGimbalStruct.to = mainControllerID;
  myMainStruct.groupType = groupType;
  myMainStruct.type = type;
  myMainStruct.subType = subType;
  myMainStruct.action = action;
  myGimbalStruct.myOpModeGimbal = _opModeGimbal;                    
  myGimbalStruct.myGimbalSettings = _gimbalSettings;
  myGimbalStruct.myAutopanSettings = _autopanSettings;
  myGimbalStruct.myGimbalDrive = _gimbalDrive;
  printmyGimbalStruct();
  sendSize = loopTransfer.txObj(myGimbalStruct, sendSize);
  loopTransfer.sendData(sendSize, gimbalControllerID); //packetID is read by the receiver, to indicate which variables are coming through
  Serial.print("Sent Packet #"); Serial.println(gimbalControllerID);  
}

void updateGimbalServoController(uint16_t groupType, uint16_t servoID, uint16_t action){
  //NOTE if servoID = 0 then update applies to all servos in the group type
  //Note if action = 1 then tells remote end to locally save accrding to type and subtype
  //If action = 2 then tells remote end to sace all gimbal commands regardless of types
  uint16_t sendSize = 0;
  myServoStruct.to = gimbalControllerID;
  myServoStruct.groupType = groupType;
  myServoStruct.type = servoID;
  myServoStruct.action = action;
  switch(servoID){
  case servoPitch:
    myServoStruct.myPitchServoSettings = _servoPitchSettings;
    break; 
  case servoRoll:
    myServoStruct.myRollServoSettings = _servoRollSettings;
    break;
  case servoPan:
    myServoStruct.myPanServoSettings = _servoPanSettings;
    break;
  }                   
  sendSize = loopTransfer.txObj(myServoStruct, sendSize);
  loopTransfer.sendData(sendSize, gimbalControllerServoID); //packetID is read by the receiver, to indicate which variables are coming through
  Serial.print("Sent Packet #"); Serial.println(gimbalControllerServoID);  
}

void updateMainServoController(uint16_t groupType, uint16_t servoID, uint16_t action){
  uint16_t sendSize = 0;
  MyServoStructMain.to = mainControllerID;
  MyServoStructMain.groupType = groupType;
  MyServoStructMain.type = servoID;   //wheel control board ID use I2C address
  MyServoStructMain.action = action;
  switch (servoID){
    case 1: MyServoStructMain.myServoSettingsArray[1] = _servoSettings; break;
    case 2: MyServoStructMain.myServoSettingsArray[2] = _servoSettings; break;
    case 3: MyServoStructMain.myServoSettingsArray[3] = _servoSettings; break;
    case 4: MyServoStructMain.myServoSettingsArray[4] = _servoSettings; break;
    case 5: MyServoStructMain.myServoSettingsArray[5] = _servoSettings; break;
    case 6: MyServoStructMain.myServoSettingsArray[6] = _servoSettings; break;
  }                 
  sendSize = loopTransfer.txObj(myServoStruct, sendSize);
  loopTransfer.sendData(sendSize, mainControllerServoID); //packetID is read by the receiver, to indicate which variables are coming through
  Serial.print("Sent Packet #"); Serial.println(mainControllerServoID);  
}

void clearMovement(){
  _gimbalDrive.pitchUp = 0;
  _gimbalDrive.pitchDown = 0;
  _gimbalDrive.rollLeft = 0;
  _gimbalDrive.rollRight = 0;
  _gimbalDrive.panLeft = 0;
  _gimbalDrive.panRight = 0;
}

