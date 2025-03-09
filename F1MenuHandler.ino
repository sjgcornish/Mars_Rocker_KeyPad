void help(){
  u8g2.setCursor(0,64);
  u8g2.print("'ENT' Conf 'ESC' Cancel");
  u8g2.setCursor(0,7);
  u8g2.sendBuffer();
}

bool F1Menu(){
  readyStatus= "0";
  bool inSubmenu = true;
  //tell pico customKey pad in program mode
  u8g2.clear();
  int lastmenuItem = 0;
  bool changed = false;
  int position = 0;
  int menuoption = 0;
  displayF1Menu(0);
  menuoption = getMenuOption(0,5);
  Serial.print("menuoption");  Serial.println(menuoption);  
  switch (menuoption){
    case 0:
      redisplayStartScreen();
      inSubmenu = false;
    break;
    case 1:
      u8g2SteeringModeHandler();
      lastmenuItem = menuoption; 
    break;
    case 2:
      u8g2SteeringControlHandler();
      lastmenuItem = menuoption; 
      break;
    case 3:
      displayJoystickModeMenuHandler();
      lastmenuItem = menuoption; 
      break;
    case 4:
      operatingModeHandler();
      lastmenuItem = menuoption; 
      break;
    case 5:
      gimbalOperationHandler();
      lastmenuItem = menuoption; 
      break;
    case 10:
      UploadDownLoadHandler(lastmenuItem);
    break;
  }
  return inSubmenu;
} //END F1MENUE

void u8g2SteeringModeHandler(){
  u8g2.clear();
  bool changed = false;
  currentSteeringMode = _opModeMain.steeringMode;
  int menuoption = 0;
  displaySteeringModeMenu(0);
  menuoption = getMenuOption(2,4);
  if (menuoption == 0){
    if (changed == true){
    }
  }else{
    _opModeMain.steeringMode = menuoption;
    if (currentSteeringMode != _opModeMain.steeringMode){
      changed = true;
    }
  }
  if (changed == true){
    updateMainController(opModeMainGroupType, SteeringModeType, _opModeMain.steeringMode, 0);  //packetID, type
  }
} //END u8g2SteeringModeHandler

void u8g2SteeringControlHandler(){
  u8g2.clear();
  bool changed = false;
  currentSteeringControl = _opModeMain.steeringControl;
  int menuoption = 0;
  displaySteeringControlMenu(0);
  menuoption = getMenuOption(3,4);
  if (menuoption == 0){
    if (changed == true){
    }
  }else{
    _opModeMain.steeringControl = menuoption;
    if (currentSteeringControl != _opModeMain.steeringControl){
      changed = true;
    }
  }
  if (changed == true){
    updateMainController(opModeMainGroupType, SteeringControlType, _opModeMain.steeringControl, 0);  //packetID, type
  }
} //END u8g2SteeringControlHandler

void displayJoystickModeMenuHandler(){
  u8g2.clear();
  bool changed = false;
  currentjoystickMode = _opModeMain.joystickMode;
  int menuoption = 0;
  displayJoystickModeMenu(0);
  menuoption = getMenuOption(4,4);
  if (menuoption == 0){
    if (changed == true){
    }
  }else{
    _opModeMain.joystickMode = menuoption;
    if (currentSteeringControl != _opModeMain.joystickMode){
      changed = true;
    }
  }
  if (changed == true){
    updateMainController(opModeMainGroupType, JoystickModeType, _opModeMain.joystickMode, 0);  //packetID, type
  }
} //END displayJoystickModeMenuHandler


void operatingModeHandler(){
  bool inMenu = true; 
  while (inMenu == true){       
    inMenu = operatingModeMenu();
  }
} //END operatingModeHandler

bool operatingModeMenu(){
  bool inSubmenu = true;
  u8g2.clear();
  bool changed = false;
  int position = 0;
  int menuoption = 0;
  displaySystemOperatingModeMenu(0);
  menuoption = getMenuOption(11,3);
  u8g2.clear();
  u8g2.setCursor(0,40);
  u8g2.print("'ENT' to confirm");
  u8g2.setCursor(0,56);
  u8g2.print("'ESC' to cancel");
  u8g2.setCursor(0,7);
  u8g2.sendBuffer();
  Serial.print("menuoption");  Serial.println(menuoption);
  Serial.println("f1help");  
  switch (menuoption){
  case 0:
    redisplayStartScreen();
    inSubmenu = false;
  break;
  case 1:
    crashModeHandler();
    break;
  case 2:
    mirrorModeHandler();
    break;
  case 3:
    driveModeHandler();
    break;  
  }
  return inSubmenu;
} //END operatingModeMenu

void crashModeHandler(){
  u8g2.clear();
  bool changed = false;
  currentCrashMode = _opModeMain.crashMode;
  int menuoption = 0;
  displayCrashModeMenu(0);
  menuoption = getMenuOption(12,2);
  if (menuoption == 0){
    if (changed == true){
    }
  }else{
    _opModeMain.crashMode = menuoption;
    if (currentCrashMode != _opModeMain.crashMode){
      changed = true;
    }
  }
  if (changed == true){
    updateMainController(opModeMainGroupType, systemOperatingType, CrashModeType, 0);  //packetID, type
  }
} //END crashModeHandler

void mirrorModeHandler(){
  u8g2.clear();
  bool changed = false;
  currentMirrorMode = _opModeMain.mirrorMode;
  int menuoption = 0;
  displayMirrorModeMenu(0);
  menuoption = getMenuOption(13,2);
  if (menuoption == 0){
    if (changed == true){
    }
  }else{
    _opModeMain.mirrorMode = menuoption;
    if (currentMirrorMode != _opModeMain.mirrorMode){
      changed = true;
    }
  }
  if (changed == true){
    updateMainController(opModeMainGroupType, systemOperatingType, MirrorModeType, 0);  //packetID, type
  }
} //END mirrorModeHandler

void driveModeHandler(){
  u8g2.clear();
  bool changed = false;
  currentDriveMode = _opModeMain.driveMode;
  int menuoption = 0;
  displayDriveModeMenu(0);
  menuoption = getMenuOption(13,3);
  if (menuoption == 0){
    if (changed == true){
    }
  }else{
    _opModeMain.driveMode = menuoption;
    if (currentDriveMode != _opModeMain.driveMode){
      changed = true;
    }
  }
  if (changed == true){
    updateMainController(opModeMainGroupType, systemOperatingType, DriveModeType, 0);  //packetID, type
  }
} //END driveModeHandler

void gimbalOperationHandler(){
  bool inMenu = true; 
  while (inMenu == true){         
    inMenu = gimbalOperationMenu();
  }
} //END gimbalOperationHandler


bool gimbalOperationMenu(){
  readyStatus= "0";
  bool inSubmenu = true;
  //tell pico customKey pad in program mode
  u8g2.clear();
  bool changed = false;
  int position = 0;
  int menuoption = 0;
  displayGimbalOperatingModeMenu(0);
  menuoption = getMenuOption(14,3);
  u8g2.clear();
  u8g2.setCursor(0,40);
  u8g2.print("'ENT' to confirm");
  u8g2.setCursor(0,56);
  u8g2.print("'ESC' to cancel");
  u8g2.setCursor(0,7);
  u8g2.sendBuffer();
  Serial.print("menuoption");  Serial.println(menuoption);  
  switch (menuoption){
  case 0:
    //u8g2.clear();
    //u8g2.sendBuffer();
    inSubmenu = false;
  break;
    case 1:
    gimbalModeHandler();
    break;
  break;
  case 2:
    gimbalControlHandler();
    break;
  break;
  case 3:
    autopanModeHandler();
    break;
  }
  return inSubmenu;
} // END operatingModeMenu

void gimbalModeHandler(){
  u8g2.clear();
  bool changed = false;
  currentGimbalMode = _opModeGimbal.gimbalMode;
  int menuoption = 0;
  displayGimbalModeMenu(0);
  menuoption = getMenuOption(13,2);
  if (menuoption == 0){
    if (changed == true){
    }
  }else{
    _opModeGimbal.gimbalMode = menuoption;
    if (currentGimbalMode != _opModeGimbal.gimbalMode){
      changed = true;
    }
  }
  if (changed == true){
    updateGimbalController(opModeGimbalGroupType, GimbalModeType, _opModeGimbal.gimbalMode, 0);  //packetID, type
  }
} //END gimbalModeHandler

void gimbalControlHandler(){
  u8g2.clear();
  bool changed = false;
  currentGimbalControl = _opModeGimbal.gimbalControl;
  int menuoption = 0;
  displayGimbalControlMenu(0);
  menuoption = getMenuOption(8,3);
  if (menuoption == 0){
    if (changed == true){
    }
  }else{
    _opModeGimbal.gimbalControl = menuoption;
    if (currentGimbalControl != _opModeGimbal.gimbalControl){
      changed = true;
    }
  }
  if (changed == true){
    updateGimbalController(opModeGimbalGroupType, GimbalControlType, _opModeGimbal.gimbalControl, 0);  //packetID, type
  }
}  //END gimbalControlandler

void autopanModeHandler(){
  u8g2.clear();
  bool changed = false;
  currentAutopanMode = _opModeGimbal.autopanMode;
  int menuoption = 0;
  displayAutopanMenu(0);
  menuoption = getMenuOption(9,2);
  if (menuoption == 0){
    if (changed == true){
    }
  }else{
    _opModeGimbal.autopanMode = menuoption;
    if (currentAutopanMode != _opModeGimbal.autopanMode){
      changed = true;
    }
  }
  if (changed == true){
    updateGimbalController(opModeGimbalGroupType, AutopanModeType,  _opModeGimbal.autopanMode, 0);  //packetID, type
  }
} //END autopanModeHandler

void UploadDownLoadHandler(int lastmenuSelected){
  bool inMenu = true; 
  while (inMenu == true){       
    inMenu = UploadDownLoadMenu(lastmenuSelected);
  }
} //END UploadDownLoadMenu

bool UploadDownLoadMenu(int lastmenu){
  readyStatus= "0";
  bool inSubmenu = true;
  //tell pico customKey pad in program mode
  u8g2.clear();
  bool havepacket = false;
  int position = 0;
  int menuoption = 0;
  displayUploadDownLoadMenu(0);
  menuoption = getMenuOption(21,4);
  u8g2.clear();
  u8g2.setCursor(0,40);
  u8g2.print("'ENT' to confirm");
  u8g2.setCursor(0,56);
  u8g2.print("'ESC' to cancel");
  u8g2.setCursor(0,7);
  u8g2.sendBuffer();
  Serial.print("menuoption");  Serial.println(menuoption);  
  switch (menuoption){
    case 0:
      inSubmenu = false;
    break;
    case 1: //Upload Main
      updateMainController(0, 0, 0, 0); 
    break;
    case 2: //Upload Gimbal
      updateGimbalController(0, 0, 0, 0);  //packetID, type
    break;
    case 3: //Download Main
      myKeypadStruct.to = gimbalControllerID;
      myKeypadStruct.type = 0;
      myKeypadStruct.subType = 0;
      myKeypadStruct.action = 4;
      sending(3);  //still in loop need to exit to recieve data
      havepacket = false;
      while (havepacket == false){
         havepacket = getSerialPacket();
      }
    break; 
      case 4: //DownLoad Gimbal
      myKeypadStruct.to = mainControllerID;
      myKeypadStruct.type = 0;
      myKeypadStruct.subType = 0;
      myKeypadStruct.action = 4;
      sending(3);  //still in loop need to exit to recieve data
      bool havepacket = false;
      while (havepacket == false){
         havepacket = getSerialPacket();
      }
    break;
  }  
  return inSubmenu;
} // END UploadDownLoadMenu


void displayF1Menu(int option){
  u8g2.clear();
  u8g2.setCursor(0,7);
  u8g2.print("RUNNING MODES");
  if (option == 1) {invertText(0,0); }else{u8g2.setCursor(0,16);u8g2.print(F1MenuText[0]);}   
  if (option == 2) {invertText(0,1); }else{u8g2.setCursor(0,24);u8g2.print(F1MenuText[1]);}   
  if (option == 3) {invertText(0,2); }else{u8g2.setCursor(0,32);u8g2.print(F1MenuText[2]);}
  if (option == 4) {invertText(0,3); }else{u8g2.setCursor(0,40);u8g2.print(F1MenuText[3]);}
  if (option == 5) {invertText(0,4); }else{u8g2.setCursor(0,48);u8g2.print(F1MenuText[4]);};
// if (option == 6) {invertText(0,5); }else{u8g2.setCursor(0,56);u8g2.print(F1MenuText[5]);};
  u8g2.setCursor(0,56);u8g2.print("Key '#' to Save");
  u8g2.setCursor(0,64);u8g2.print("Key 'Esc' to Exit");
  u8g2.sendBuffer();
} //END displayF1Menu

void displaySystemOperatingModeMenu(int option){
  u8g2.clear();
  u8g2.setCursor(0,7);
  u8g2.print("OPERATING MODE");
  if (option == 1) {invertText(11,0); }else{u8g2.setCursor(0,16);u8g2.print(systemOperatingText[0]);}   
  if (option == 2) {invertText(11,1); }else{u8g2.setCursor(0,24);u8g2.print(systemOperatingText[1]);}   
  if (option == 3) {invertText(11,2); }else{u8g2.setCursor(0,32);u8g2.print(systemOperatingText[2]);}
  help();
} //END displaySystemOperatingModeMenu

void displayGimbalOperatingModeMenu(int option){
  u8g2.clear();
  u8g2.setCursor(0,7);
  u8g2.print("GIMBAL OPERATING");
  if (option == 1) {invertText(14,0); }else{u8g2.setCursor(0,16);u8g2.print(gimbalOperatingMenuText[0]);}   
  if (option == 2) {invertText(14,1); }else{u8g2.setCursor(0,24);u8g2.print(gimbalOperatingMenuText[1]);}   
  if (option == 3) {invertText(14,2); }else{u8g2.setCursor(0,32);u8g2.print(gimbalOperatingMenuText[2]);}
  help();
} //END displayGimbalOperatingModeMenu

void displaySteeringModeMenu(int option){
  u8g2.clear();
  u8g2.setCursor(0,7);
  u8g2.print("STEERING MODES - ");
  u8g2.setCursor(100,0);
  u8g2.print(currentSteeringMode);
  if (option == 1) {invertText(2,0); }else{u8g2.setCursor(0,16);u8g2.print(steeringModeMenuText[0]);};
  if (option == 2) {invertText(2,1); }else{u8g2.setCursor(0,24);u8g2.print(steeringModeMenuText[1]);};
  if (option == 3) {invertText(2,2); }else{u8g2.setCursor(0,32);u8g2.print(steeringModeMenuText[2]);};
  if (option == 4) {invertText(2,3); }else{u8g2.setCursor(0,40);u8g2.print(steeringModeMenuText[3]);};
  help();
} // END displaySteeringModeMenu

void displaySteeringControlMenu(int option){
  u8g2.clear();
  u8g2.setCursor(0,7);
  u8g2.print("STEERING CONTROL -");
  u8g2.setCursor(118,0);
  u8g2.print(currentSteeringControl);
  if (option == 1) {invertText(3,0); }else{u8g2.setCursor(0,16);u8g2.print(steeringControlMenuText[0]);};
  if (option == 2) {invertText(3,1); }else{u8g2.setCursor(0,24);u8g2.print(steeringControlMenuText[1]);};
  if (option == 3) {invertText(3,2); }else{u8g2.setCursor(0,32);u8g2.print(steeringControlMenuText[2]);};
  if (option == 4) {invertText(3,3); }else{u8g2.setCursor(0,40);u8g2.print(steeringControlMenuText[3]);};
  help();
} //END displaySteeringControlMenu

void displayJoystickModeMenu(int option){
  u8g2.clear();
  u8g2.setCursor(0,7);
  u8g2.print("JOYSTICK MODE -");
  u8g2.setCursor(110,0);
  u8g2.print(currentjoystickMode);
  if (option == 1) {invertText(4,0); }else{u8g2.setCursor(0,16);u8g2.print(joystickModeMenuText[0]);};
  if (option == 2) {invertText(4,1); }else{u8g2.setCursor(0,24);u8g2.print(joystickModeMenuText[1]);};
  if (option == 3) {invertText(4,2); }else{u8g2.setCursor(0,32);u8g2.print(joystickModeMenuText[2]);};
  if (option == 4) {invertText(4,3); }else{u8g2.setCursor(0,40);u8g2.print(joystickModeMenuText[3]);};
  help();
} //END displayJoystickModeMenu

void displayCrashModeMenu(int option){
  u8g2.clear();
  u8g2.setCursor(0,7);
  u8g2.print("CRASH MODE -");
  if (currentCrashMode == 1){u8g2.print("CRASH MODE is OFF");
  }else {u8g2.print("CRASH MODE is ON");}
  if (option == 1) {invertText(12,0); }else{u8g2.setCursor(0,16);u8g2.print(crashModeText[0]);};
  if (option == 2) {invertText(12,1); }else{u8g2.setCursor(0,24);u8g2.print(crashModeText[1]);};
  help();
} //END displayCrashModeMenu

void displayMirrorModeMenu(int option){
  u8g2.clear();
  u8g2.setCursor(0,7);
  if (currentMirrorMode == 1){u8g2.print("MIRROR MODE is OFF");
  }else {u8g2.print("MIRROR MODE is ON");}
  if (option == 1) {invertText(13,0); }else{u8g2.setCursor(0,16);u8g2.print(mirrorModeText[0]);};
  if (option == 2) {invertText(13,1); }else{u8g2.setCursor(0,24);u8g2.print(mirrorModeText[1]);};
  help();
} //END displayMirrorModeMenu

void displayDriveModeMenu(int option){
  u8g2.clear();
  u8g2.setCursor(0,7);
  if (currentDriveMode == 1){u8g2.print("DRIVE MODE is PWM");
  }else {u8g2.print("DRIVE MODE is PID");}
  if (option == 1) {invertText(13,0); }else{u8g2.setCursor(0,16);u8g2.print(driveModeText[0]);};
  if (option == 2) {invertText(13,1); }else{u8g2.setCursor(0,24);u8g2.print(driveModeText[1]);};
  if (option == 3) {invertText(13,1); }else{u8g2.setCursor(0,32);u8g2.print(driveModeText[1]);};
  help();
} //END displayDriveModeMenu

void displayOperatingModeMenu(int option){
   u8g2.clear();
   u8g2.setCursor(0,7);
   u8g2.print("OPERATING MODES");
   if (option == 1) {invertText(11,0); }else{u8g2.setCursor(0,16);u8g2.print(systemOperatingText[0]);};
   if (option == 2) {invertText(11,1); }else{u8g2.setCursor(0,24);u8g2.print(systemOperatingText[1]);};
   help();
} //END displayOperatingModeMenu

void displayGimbalModeMenu(int option){
  u8g2.clear();
  u8g2.setCursor(0,7);
  u8g2.print("GIMBAL MODE -");
  u8g2.setCursor(110,0);
  u8g2.print(currentGimbalMode);
  if (option == 1) {invertText(7,0); }else{u8g2.setCursor(0,16);u8g2.print(gimbalModeText[0]);};
  if (option == 2) {invertText(7,1); }else{u8g2.setCursor(0,24);u8g2.print(gimbalModeText[1]);};
  if (option == 3) {invertText(7,2); }else{u8g2.setCursor(0,32);u8g2.print(gimbalModeText[2]);};
  if (option == 4) {invertText(7,3); }else{u8g2.setCursor(0,40);u8g2.print(gimbalModeText[3]);};
  help();
} //END displayGimbalModeMenu

void displayGimbalControlMenu(int option){
  u8g2.clear();
  u8g2.setCursor(0,7);
  u8g2.print("GIMBAL MODE -");
  u8g2.setCursor(110,0);
  u8g2.print(currentGimbalControl);
  if (option == 1) {invertText(8,0); }else{u8g2.setCursor(0,16);u8g2.print(gimbalControlText[0]);};
  if (option == 2) {invertText(8,1); }else{u8g2.setCursor(0,24);u8g2.print(gimbalControlText[1]);};
  if (option == 2) {invertText(8,2); }else{u8g2.setCursor(0,32);u8g2.print(gimbalControlText[2]);};
  help();
} //END displayGimbalControlMenu

void displayAutopanMenu(int option){
  u8g2.clear();
  u8g2.setCursor(0,7);
  u8g2.print("AUTOPAN MODE -");
  u8g2.setCursor(110,0);
  u8g2.print(currentAutopanMode);
  if (option == 1) {invertText(9,0); }else{u8g2.setCursor(0,16);u8g2.print(autopanControlText[0]);};
  if (option == 2) {invertText(9,1); }else{u8g2.setCursor(0,24);u8g2.print(autopanControlText[1]);};
  if (option == 3) {invertText(9,2); }else{u8g2.setCursor(0,32);u8g2.print(autopanControlText[2]);};
  help();
} //END displayAutopanMenu

void displayUploadDownLoadMenu(int option){
  u8g2.clear();
  u8g2.setCursor(0,7);
  u8g2.print("SAVE & TRANSFER ALL!");
  u8g2.setCursor(110,0);
  if (option == 1) {invertText(21,0); }else{u8g2.setCursor(0,16);u8g2.print(EEPROMText[0]);};
  if (option == 2) {invertText(21,1); }else{u8g2.setCursor(0,24);u8g2.print(EEPROMText[1]);};
  if (option == 3) {invertText(21,2); }else{u8g2.setCursor(0,32);u8g2.print(EEPROMText[2]);};
  if (option == 4) {invertText(21,3); }else{u8g2.setCursor(0,40);u8g2.print(EEPROMText[3]);};
 help();
}

void displayEEPROMModeMenu(int option){
  u8g2.clear();
  u8g2.setCursor(0,7);
  u8g2.print("SAVE & UPLOAD");
  u8g2.setCursor(110,0);
  u8g2.print(currentAutopanMode);
  if (option == 1) {invertText(9,0); }else{u8g2.setCursor(0,16);u8g2.print(EEPROMText[0]);};
  if (option == 2) {invertText(9,1); }else{u8g2.setCursor(0,24);u8g2.print(EEPROMText[1]);};
  if (option == 3) {invertText(9,2); }else{u8g2.setCursor(0,32);u8g2.print(EEPROMText[2]);};
  if (option == 3) {invertText(9,2); }else{u8g2.setCursor(0,32);u8g2.print(EEPROMText[2]);};
  help();
} //END u8g2EEPROMMenu
