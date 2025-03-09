#include <EEPROM.h>
#include "declarations.h"
#include "SerialTransfer.h"

SerialTransfer loopTransfer;

/* SSD1306/Serial Initialisation */
#include <Wire.h>
#include <U8g2lib.h>
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

//#define DEBUGPRINT

#define DEBUG   //If you comment this line, the DPRINT & DPRINTLN lines are defined as blank.
#ifdef DEBUG    //Macros are usually in all capital letters.
   #define DPRINT(...)    Serial.print(__VA_ARGS__)     //DPRINT is a macro, debug print
   #define DPRINTLN(...)  Serial.println(__VA_ARGS__)   //DPRINTLN is a macro, debug print with new line
#else
   #define DPRINT(...)     //now defines a blank line
   #define DPRINTLN(...)   //now defines a blank line
#endif


/* Keypad Initialisation */
#include <Keypad.h>

const byte ROWS = 5; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char keys[ROWS][COLS] = {
  {'<','0','>','E'},
  {'7','8','9','C'},
  {'4','5','6','D'},
  {'1','2','3','U'},
  {'Y','Z','#','*'}
};

byte rowPins[ROWS] = {6, 7, 8, 9, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {2, 3, 4, 5}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


//Serial variables
const byte numChars = 32;
char serial_receivedChars[numChars];
boolean newSerialData = false;
char *strings[16];
char keypad_receivedChars[6];

/* Other Variable */
String picoID = "0:";
int myID = 1;
int fromID = 0;
String fromStr = "0";
String myStr = String(myID);
String readyStatus = "0";
bool allReady = false;
String txString = "";
String leftArrow = "<";
String rightArrow = ">";
int controlMode;
int controlModeState = -1;
#define manual 1
#define radio  0

void displayStartScreen(){ 
   controlMode = digitalRead(A3); 
   if (controlModeState != controlMode){
    u8g2.setCursor(0, 7); 
    u8g2.sendBuffer();
    if (controlMode == 1){
      Serial.println("Manual Operation");
      u8g2.print("Manual Operation");
    }else{
      Serial.println("Radio Operation");
      u8g2.print("Radio Operation");
    }
    controlModeState = controlMode;
    _opModeMain.runMode = controlMode;
    //EEPROM.put(0,_opMode);

    u8g2.setCursor(0,19);
    if (_opModeMain.steeringMode >0)u8g2.print(steeringModeMenuText[_opModeMain.steeringMode-1]);
    u8g2.setCursor(0,27);
    if (_opModeMain.steeringControl >0){u8g2.print(steeringControlMenuText[_opModeMain.steeringControl-1]);}
    u8g2.setCursor(0,35);
    if (_opModeMain.joystickMode >0)u8g2.print(joystickModeMenuText[_opModeMain.joystickMode-1]);
    u8g2.setCursor(0,43);
    if (_opModeGimbal.gimbalMode >0){u8g2.print(gimbalModeText[_opModeGimbal.gimbalMode-1]);}
    u8g2.setCursor(64,43);
    if (_opModeGimbal.gimbalControl >0){u8g2.print(gimbalControlText[_opModeGimbal.gimbalControl-1]);}
    u8g2.setCursor(0,51);
    if (_opModeGimbal.autopanMode >0){u8g2.print(autopanControlText[_opModeGimbal.autopanMode-1]);}
    u8g2.setCursor(0,64);
    u8g2.print("Select F1, F2, #, *");    
    u8g2.sendBuffer();
    }
} //END displayStartScreen

void redisplayStartScreen(){  
    u8g2.clear();
    u8g2.setCursor(0, 7);    
    if (controlMode == 1){
      //in Manual mode the keyPad sends not ready and the control mode to the pico
      u8g2.print("Manual Operation");
    }else{
      u8g2.print("Radio Operation");
      //in Radio mode the keyPad sends Ready and the control mode to the pico
      //The assumption being that if program got this far then the keypad MCU must be operational
    }
    u8g2.setCursor(0,19);
    if (_opModeMain.steeringMode >0)u8g2.print(steeringModeMenuText[_opModeMain.steeringMode-1]);
    u8g2.setCursor(0,27);
    if (_opModeMain.steeringControl >0){u8g2.print(steeringControlMenuText[_opModeMain.steeringControl-1]);}
    u8g2.setCursor(0,35);
    if (_opModeMain.joystickMode >0)u8g2.print(joystickModeMenuText[_opModeMain.joystickMode-1]);
    u8g2.setCursor(0,43);
    if (_opModeGimbal.gimbalMode >0){u8g2.print(gimbalModeText[_opModeGimbal.gimbalMode-1]);}
    u8g2.setCursor(64,43);
    if (_opModeGimbal.gimbalControl >0){u8g2.print(gimbalControlText[_opModeGimbal.gimbalControl-1]);}
    u8g2.setCursor(0,51);
    if (_opModeGimbal.autopanMode >0){u8g2.print(autopanControlText[_opModeGimbal.autopanMode-1]);}
    u8g2.setCursor(0,64);
    u8g2.print("Select F1, F2, #, *");
    u8g2.sendBuffer();
} //END redisplayStartScreen

void setup(){

  Serial.begin(115200);
  unsigned long start = millis();
  while(!Serial)  //Wait until the serial port is opened with a 3 second timeout
  {if (millis() - start > 3000){break;}}

  Serial1.begin(115200);
  loopTransfer.begin(Serial1);

  u8g2.begin();
  //u8g2.enableUTF8Print();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_spleen5x8_mf);  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A3, INPUT_PULLUP);
 
  u8g2.print("Hello From Mars");
  u8g2.sendBuffer();
  u8g2.clear();


  Serial.println("Hello From Mars");

  //restEEPROM();
  //fillmyGimbalStruct();
  initialiseEEPROM();
  //sending(1);

#ifdef DEBUGPRINT
  printmyMainStruct();
  printmyGimbalStruct();
  printServoStruct(1);
  printServoStruct(2);
  printServoStruct(3);
#endif


  neg_minSpeed = _mainSettings.minSpeed*-1;
  pos_minSpeed = _mainSettings.minSpeed; 
  pos_maxSpeed = _mainSettings.maxSpeed;
  neg_maxSpeed = _mainSettings.maxSpeed*-1;
  
  displayStartScreen();

  allReady = true;
  myMainStruct.to = 1;
  //sending(3);
 
} //END setup
 
void loop(){
       
  if (allReady == true){
    displayStartScreen();  //also checks radio/manual switch state
    if (controlMode == manual){
      char key = keypad.getKey(); 
      if (key != NO_KEY){
        DPRINTLN(key);
        bool inMenu = true; 
        switch (key){
          case 'Y': //F2
            while (inMenu == true){              
              inMenu = F1Menu();
            }
            break;
          case 'Z': //F1
            while (inMenu == true){
              inMenu = F2Menu();
            }
            break;
          break;
        case '#':  //gimbal and pan settings on to pages use # key to swap between pages when in menu
          roverDrive();
          redisplayStartScreen();
          break;
         case '*':
          autopanState = false;
          gimbalDrive();
          redisplayStartScreen();
          break;
        }
      }      
    }
  }
    
  getSerialPacket();

Serial_recvWithStartEndMarkers();
  if (newSerialData == true){
      processTerminalString();
      newSerialData = false;
  }


} //END Loop

bool getSerialPacket(){
  bool haveSerialHacket = false;
  if(loopTransfer.available()>0){
    int recSize = 0;
    packetID = loopTransfer.currentPacketID();
    DPRINT("recieved packet: ");DPRINTLN(packetID);
    switch(packetID){
      case 1:  // main board - not for me
        recSize = loopTransfer.rxObj(myTempMainStruct, recSize);
        if (myTempMainStruct.to = keypadControllerID){
          DPRINTLN("main struct recieved");
          myMainStruct = myTempMainStruct;
        }else{resend(packetID);}           
      break;
      case 2:  //gimbal Controller - not for me
        recSize = loopTransfer.rxObj(myTempGimbalStruct, recSize);
        if (myTempGimbalStruct.to = keypadControllerID){
          DPRINTLN("gimbal struct recieved");
          myGimbalStruct = myTempGimbalStruct;
        }else{resend(packetID);} 
      break;
      case 3:  //Keypad
        recSize = loopTransfer.rxObj(myKeypadStruct, recSize);
        process_myKeypadStruct(); 
      break;
      case 10:  //main controller servo   not for me
        recSize = loopTransfer.rxObj(myTempServoStruct, recSize);
        //Key pad does not receive and commands or settings only sends
        resend(packetID);  
      break;
        case 20:  //gimbal controller servo - not for me
        recSize = loopTransfer.rxObj(myTempServoStruct, recSize);
        //Key pad does not receive and commands or settings only sends
        resend(packetID); 
      break;
    }
    haveSerialHacket = true;
  }
  return haveSerialHacket;
} //END getSerialPacket

void sending(uint8_t ID) {
  uint16_t sendSize = 0;
  switch (ID) {//selector byte chooses the variable(s) to send.
    case 1:
      sendSize = loopTransfer.txObj(myMainStruct, sendSize);
      break;
    case 2:
      sendSize = loopTransfer.txObj(myGimbalStruct, sendSize);
      break;
    case 3:
      sendSize = loopTransfer.txObj(myKeypadStruct, sendSize);
      break;
    case 10:
      sendSize = loopTransfer.txObj(myServoStruct, sendSize);
      break;
    case 20:
      sendSize = loopTransfer.txObj(myServoStruct, sendSize);
      break;
    }
  loopTransfer.sendData(sendSize, ID); //packetID is read by the receiver, to indicate which variables are coming through
  DPRINT("sent Packet #"); DPRINT(ID);
} //END sending

void resend(uint8_t ID){
  Serial.print("Resend Packet");
  uint16_t sendSize = 0;
  switch (ID) {//selector byte chooses the variable(s) to send.
    case 1:
      sendSize = loopTransfer.txObj(myTempMainStruct, sendSize);
      break;
    case 2:
      sendSize = loopTransfer.txObj(myTempGimbalStruct, sendSize);
      break;
    case 3:
      //sendSize = loopTransfer.txObj(myTempKeypadStruct, sendSize);
      break;
    case 10:
      sendSize = loopTransfer.txObj(myTempServoStruct, sendSize);
      break;
    case 20:
      sendSize = loopTransfer.txObj(myTempServoStruct, sendSize);
      break;
  }
  loopTransfer.sendData(sendSize, ID); //packetID is read by the receiver, to indicate which variables are coming through
  DPRINT("Resent Packet #"); DPRINT(ID);
} //END resend;


void restEEPROM() {
  uint16_t a = 10000;
  for (int i = 0; i < EEPROM.length(); i=i+2) {
      EEPROM.put(i, a);
  }
} // END restEEPROM

void initialiseEEPROM(){
  uint16_t b = 10000; 
  EEPROM.get(0, myMainStruct.myOpModeMain.runMode);
  if (myMainStruct.myOpModeMain.runMode == b){  //config not saved set default
    myMainStruct.myOpModeMain = {0,1,1,1,1,1};
    SaveToEEPROM(opModeMainGroupType, 0);    
  }else {LoadFromEEPROM(opModeMainGroupType, 0);}

  EEPROM.get(16, myGimbalStruct.myOpModeGimbal);
  if (myGimbalStruct.myOpModeGimbal.runMode == 10000){  //config not saved set default
    myGimbalStruct.myOpModeGimbal = {0,1,1,1};   //units, stepMode, stepSize, stepDelay      
    SaveToEEPROM(opModeGimbalGroupType, 0);         
  }else {LoadFromEEPROM(opModeGimbalGroupType, 0);}

  EEPROM.get(32, myMainStruct.myMainSettings); 
  if (myMainStruct.myMainSettings.avoidDistance == 10000){  //config not saved set default
     //runMode,joystickMode,steeringMode,steeringControl,gimbalMode,gimbalControl,autopan
    myMainStruct.myMainSettings = {25,0,255,5,10};
    SaveToEEPROM(mainSettingsGroupType, 0);         
  }else {LoadFromEEPROM(mainSettingsGroupType, 0);}

  EEPROM.get(48, myGimbalStruct.myGimbalSettings);
  if (myGimbalStruct.myGimbalSettings.units == 10000){  //config not saved set default
    myGimbalStruct.myGimbalSettings = {1,1,5,10};   //units, stepMode, stepSize, stepDelay      
    SaveToEEPROM(gimbalSettingsGroupType, 0);         
  }else {LoadFromEEPROM(gimbalSettingsGroupType, 0);}

  EEPROM.get(64, myGimbalStruct.myAutopanSettings);
  if (myGimbalStruct.myAutopanSettings.stepSize == 10000){  //config not saved set default
    myGimbalStruct.myAutopanSettings = {5,10,45,225};  //stepSize, stepDelay, autopanMin, autoPanMax           
    SaveToEEPROM(autopanSettingsType, 0);         
  }else {LoadFromEEPROM(autopanSettingsType, 0);}

  EEPROM.get(80, myServoStruct.myPitchServoSettings);
  if (myServoStruct.myPitchServoSettings.servoType == 10000){  //config not saved set default
    myServoStruct.myPitchServoSettings = {180,500,2500,100,500,2500};  //stepSize, stepDelay, autopanMin, autoPanMax 
    SaveToEEPROM(servoGimbalGroupType, servoPitch);              
  }else {LoadFromEEPROM(servoGimbalGroupType, servoPitch);}

  EEPROM.get(96, myServoStruct.myRollServoSettings);
  if (myServoStruct.myRollServoSettings.servoType == 10000){  //config not saved set default
    myServoStruct.myRollServoSettings = {180,500,2500,100,500,2500};  //stepSize, stepDelay, autopanMin, autoPanMax           
    SaveToEEPROM(servoGimbalGroupType, servoRoll );  
  }else {LoadFromEEPROM(servoGimbalGroupType, servoRoll);}

  EEPROM.get(112, myServoStruct.myPanServoSettings);
  if (myServoStruct.myPanServoSettings.servoType == 10000){  //config not saved set default
    myServoStruct.myPanServoSettings = {270,500,2500,0,633,2167};  //stepSize, stepDelay, autopanMin, autoPanMax           
    SaveToEEPROM(servoGimbalGroupType, servoPan ); 
  }else {LoadFromEEPROM(servoGimbalGroupType, servoPan);}

  EEPROM.get(112, MyServoStructMain.myServoSettingsArray[1]);
  if (MyServoStructMain.myServoSettingsArray[1].servoType == 10000){  //config not saved set default
    MyServoStructMain.myServoSettingsArray[1] = {180,500,2500,100,500,2500};
    MyServoStructMain.myServoSettingsArray[2] = {180,500,2500,100,500,2500};
    MyServoStructMain.myServoSettingsArray[3] = {180,500,2500,100,500,2500}; 
    MyServoStructMain.myServoSettingsArray[4] = {180,500,2500,100,500,2500};
    MyServoStructMain.myServoSettingsArray[5] = {180,500,2500,100,500,2500};
    MyServoStructMain.myServoSettingsArray[6] = {180,500,2500,100,500,2500}; 
    SaveToEEPROM(servoGimbalGroupType, 0 ); //saves all
  }else {LoadFromEEPROM(servoWheelGroupType, 0);}
} //END EEPROMInitialise

void LoadFromEEPROM(int loadType, int servotype){ 
  DPRINT("EEPROM LOAD "); DPRINTLN(loadType);
  switch (loadType){
    case opModeMainGroupType:
      EEPROM.get(0, myMainStruct.myOpModeMain);
      _opModeMain = myMainStruct.myOpModeMain;
    break;
    case opModeGimbalGroupType:
    EEPROM.get(16, myGimbalStruct.myOpModeGimbal);
      _opModeGimbal = myGimbalStruct.myOpModeGimbal;
    break;
    case mainSettingsGroupType:
      EEPROM.get(32,  myMainStruct.myMainSettings);
      _mainSettings = myMainStruct.myMainSettings;
    break;
    case gimbalSettingsGroupType:
      EEPROM.get(48, myGimbalStruct.myGimbalSettings);
      _gimbalSettings = myGimbalStruct.myGimbalSettings;
    break; 
    case autopanSettingsType:     
      EEPROM.get(64, myGimbalStruct.myAutopanSettings);
      _autopanSettings = myGimbalStruct.myAutopanSettings;
    break;
    case servoGimbalGroupType:
      if (servotype == servoPitch || servotype == 0){EEPROM.get(80, myServoStruct.myPitchServoSettings); _servoPitchSettings = myServoStruct.myPitchServoSettings;}
      if (servotype == servoRoll || servotype == 0){EEPROM.get(96, myServoStruct.myRollServoSettings); _servoRollSettings = myServoStruct.myRollServoSettings;}
      if (servotype == servoPan || servotype == 0){EEPROM.get(112, myServoStruct.myPanServoSettings); _servoPanSettings = myServoStruct.myPanServoSettings;} 
    break;
    case servoWheelGroupType:
      if (servotype == 1 || servotype == 0){EEPROM.get(112, MyServoStructMain.myServoSettingsArray[1]);} 
      if (servotype == 2 || servotype == 0){EEPROM.get(112, MyServoStructMain.myServoSettingsArray[2]);} 
      if (servotype == 3 || servotype == 0){EEPROM.get(112, MyServoStructMain.myServoSettingsArray[3]);} 
      if (servotype == 4 || servotype == 0){EEPROM.get(112, MyServoStructMain.myServoSettingsArray[4]);} 
      if (servotype == 5 || servotype == 0){EEPROM.get(112, MyServoStructMain.myServoSettingsArray[5]);} 
      if (servotype == 6 || servotype == 0){EEPROM.get(112, MyServoStructMain.myServoSettingsArray[6]);} 
    break;
  }       
} //END EEPROMLoad

void SaveToEEPROM(int saveType, int servotype){ 
  DPRINT("EEPROM SAVE "); DPRINTLN(saveType);
  switch (saveType){
    case opModeMainGroupType:
      EEPROM.put(0, myMainStruct.myOpModeMain);
    break;
    case opModeGimbalGroupType:
      EEPROM.put(16, myGimbalStruct.myOpModeGimbal);
    break;
    case mainSettingsGroupType:
      EEPROM.put(32, myMainStruct.myMainSettings);
    break;
    case gimbalSettingsGroupType:
      EEPROM.put(48, myGimbalStruct.myGimbalSettings);
    break; 
    case autopanSettingsType:     
      EEPROM.put(64, myGimbalStruct.myAutopanSettings);
    break;  
    case servoGimbalGroupType:     
      if (servotype == servoPitch || servotype == 0){EEPROM.put(80, myServoStruct.myPitchServoSettings);}
      if (servotype == servoRoll || servotype == 0){EEPROM.put(96, myServoStruct.myRollServoSettings);}
      if (servotype == servoPan || servotype == 0){EEPROM.put(112, myServoStruct.myPanServoSettings);}
    break;
    case servoWheelGroupType:
      if (servotype == servoPitch || servotype == 0){EEPROM.put(128, MyServoStructMain.myServoSettingsArray[1]);}
      if (servotype == servoPitch || servotype == 0){EEPROM.put(144, MyServoStructMain.myServoSettingsArray[2]);}
      if (servotype == servoPitch || servotype == 0){EEPROM.put(160, MyServoStructMain.myServoSettingsArray[3]);}
      if (servotype == servoPitch || servotype == 0){EEPROM.put(176, MyServoStructMain.myServoSettingsArray[4]);}
      if (servotype == servoPitch || servotype == 0){EEPROM.put(192, MyServoStructMain.myServoSettingsArray[5]);}
      if (servotype == servoPitch || servotype == 0){EEPROM.put(208, MyServoStructMain.myServoSettingsArray[6]);}
    break;
  }
} //END EEPROMSave

void saveToEEPROMAllMain(){
  EEPROM.put(0,   myMainStruct.myOpModeMain);
  EEPROM.put(32,  myMainStruct.myMainSettings);
  EEPROM.put(128, MyServoStructMain.myServoSettingsArray[1]);
  EEPROM.put(144, MyServoStructMain.myServoSettingsArray[2]);
  EEPROM.put(160, MyServoStructMain.myServoSettingsArray[3]);
  EEPROM.put(176, MyServoStructMain.myServoSettingsArray[4]);
  EEPROM.put(192, MyServoStructMain.myServoSettingsArray[5]);
  EEPROM.put(208, MyServoStructMain.myServoSettingsArray[6]);
}

void saveToEEPROMAllGimbal(){
  //Any changes to settings are automatically copied to myServoStruct and sent to the gimbal controller but not saved
  //locally in the EEPROM. 
  EEPROM.put(16,  myGimbalStruct.myOpModeGimbal);
  EEPROM.put(48,  myGimbalStruct.myGimbalSettings);
  EEPROM.put(64,  myGimbalStruct.myAutopanSettings);
  EEPROM.get(80,  myServoStruct.myPitchServoSettings); 
  EEPROM.get(96,  myServoStruct.myRollServoSettings);
  EEPROM.get(112, myServoStruct.myPanServoSettings);
}

/*      
    }else if (controlMode == radio){ //
      char key = keypad.getKey(); 
      if (key != NO_KEY){
        DPRINTLN(key);
        bool inMenu = true; 
        switch (key){
          case 'Y': //F1  start pan
            //while (inMenu == true){
            //  inMenu = F1Menu();
            //}
            break;
          case 'Z': //F2 stop pan
            //while (inMenu == true){
            //  inMenu = F2Menu();
            //}
            break;
          break;
        case '*':
          cameraControl();   //use arrow keys to step
          redisplayStartScreen();
          break;
        }
      }
*/

