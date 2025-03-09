void printOpModeMain(){
  DPRINTLN("OPMODE MAIN");
  DPRINT("runMode " );DPRINTLN(myMainStruct.myOpModeMain.runMode);
  DPRINT("joystickMode " );DPRINTLN(myMainStruct.myOpModeMain.joystickMode);
  DPRINT("steeringMode " );DPRINTLN(myMainStruct.myOpModeMain.steeringMode);
  DPRINT("steeringControl " );DPRINTLN(myMainStruct.myOpModeMain.steeringControl);
  DPRINT("mirrorMode " );DPRINTLN(myMainStruct.myOpModeMain.mirrorMode);
  DPRINT("crashMode " );DPRINTLN(myMainStruct.myOpModeMain.crashMode);
}

void printMainDrive(){
  DPRINTLN("MAIN DRIVE");
  DPRINT("dcMotorSpeed " );DPRINTLN(myMainStruct.myMainDrive.dcMotorSpeed);
  DPRINT("dcMotorDirection " );DPRINTLN(myMainStruct.myMainDrive.dcMotorDirection);
  DPRINT("dcMotorDistance " );DPRINTLN(myMainStruct.myMainDrive.dcMotorDistance);
  DPRINT("servoMotorDirection " );DPRINTLN(myMainStruct.myMainDrive.servoMotorDirection);
}

void printOpModeGimbal(){
  DPRINTLN("OPMODE GIMBAL");
  DPRINT("runMode " );DPRINTLN(myMainStruct.myOpModeMain.runMode);
  DPRINT("gimbalMode " );DPRINTLN(myGimbalStruct.myOpModeGimbal.gimbalMode);
  DPRINT("gimbalControl " );DPRINTLN(myGimbalStruct.myOpModeGimbal.gimbalControl);
  DPRINT("autopanMode " );DPRINTLN(myGimbalStruct.myOpModeGimbal.autopanMode);
}

void printMainSettings(){
  DPRINTLN("MAIN SETTINGS");
  DPRINT("crashMode " );DPRINTLN(myMainStruct.myOpModeMain.crashMode);
  DPRINT("avoidDistance " );DPRINTLN(myMainStruct.myMainSettings.avoidDistance);
  DPRINT("maxSpeed " );DPRINTLN(myMainStruct.myMainSettings.maxSpeed);
  DPRINT("minSpeed " );DPRINTLN(myMainStruct.myMainSettings.minSpeed);
  DPRINT("steeringServoStepSize " );DPRINTLN(myMainStruct.myMainSettings.steeringServoStepSize);
  DPRINT("steeringServoStepDelay " );DPRINTLN(myMainStruct.myMainSettings.steeringServoStepDelay);
}

void printGimbalSettings(){
  DPRINTLN("GIMBAL SETTINGS");
  DPRINT("units" );DPRINTLN(myGimbalStruct.myGimbalSettings.units);
  DPRINT("stepSize " );DPRINTLN(myGimbalStruct.myGimbalSettings.stepSize);
  DPRINT("stepDelay " );DPRINTLN(myGimbalStruct.myGimbalSettings.stepMode);
  DPRINT("autopanSpeed " );DPRINTLN(myGimbalStruct.myGimbalSettings.stepSize);
  DPRINT("autopanRange " );DPRINTLN(myGimbalStruct.myGimbalSettings.stepDelay);
}

void printAutopanSettings(){
  DPRINT("AUTOPAN SETTINGS");
  DPRINT("panStepSize " );DPRINTLN(myGimbalStruct.myAutopanSettings.stepSize);
  DPRINT("panStepDelay " );DPRINTLN(myGimbalStruct.myAutopanSettings.stepDelay);
  DPRINT("autopanMin " );DPRINTLN(myGimbalStruct.myAutopanSettings.autopanMin);
  DPRINT("autopanMax " );DPRINTLN(myGimbalStruct.myAutopanSettings.autopanMax);
}

void printGimbalDrive(){
  DPRINT("GIMBAL DRIVE");
  DPRINT("pitchUp " );DPRINTLN(myGimbalStruct.myGimbalDrive.pitchUp);
  DPRINT("pitchDown " );DPRINTLN(myGimbalStruct.myGimbalDrive.pitchDown);
  DPRINT("rollLeft " );DPRINTLN(myGimbalStruct.myGimbalDrive.rollLeft);
  DPRINT("rollRight " );DPRINTLN(myGimbalStruct.myGimbalDrive.rollRight);
  DPRINT("panLeft " );DPRINTLN(myGimbalStruct.myGimbalDrive.panLeft);
  DPRINT("panRight " );DPRINTLN(myGimbalStruct.myGimbalDrive.panRight);
}

void printmyMainStruct(){
  DPRINT("to " );DPRINTLN(myMainStruct.to);
  DPRINT("groupType " );DPRINTLN(myMainStruct.groupType);
  DPRINT("type " );DPRINTLN(myMainStruct.type);
  DPRINT("subType " );DPRINTLN(myMainStruct.subType);
  DPRINT("action " );DPRINTLN(myMainStruct.action);
  printOpModeMain();
  printMainSettings();
  //printMainDrive();
} //END printmyMainStruct

void printmyGimbalStruct(){
  DPRINT("to " );DPRINTLN(myGimbalStruct.to);
  DPRINT("groupType " );DPRINTLN(myGimbalStruct.groupType);
  DPRINT("type " );DPRINTLN(myGimbalStruct.type);
  DPRINT("subType " );DPRINTLN(myGimbalStruct.subType);
  DPRINT("action " );DPRINTLN(myGimbalStruct.action);
  printOpModeGimbal();
  printGimbalSettings();
  printAutopanSettings();
  //printGimbalDrive();
}  //END printmyGimbalStruct

void printServoStruct(uint16_t servotype){
  switch(servotype){
    case 1:
    DPRINTLN("PITCH");
    DPRINT("servoType " );DPRINTLN(myServoStruct.myPitchServoSettings.servoType);
    DPRINT("servoMin " );DPRINTLN(myServoStruct.myPitchServoSettings.servoMin);
    DPRINT("servoMax " );DPRINTLN(myServoStruct.myPitchServoSettings.servoMax);
    DPRINT("servoCTR " );DPRINTLN(myServoStruct.myPitchServoSettings.servoCTR);
    DPRINT("sweepMin " );DPRINTLN(myServoStruct.myPitchServoSettings.sweepMin);
    DPRINT("sweepMax " );DPRINTLN(myServoStruct.myPitchServoSettings.sweepMax);
    break;
    case 2:
    DPRINTLN("ROLL");
    DPRINT("servoType " );DPRINTLN(myServoStruct.myRollServoSettings.servoType);
    DPRINT("servoMin " );DPRINTLN(myServoStruct.myRollServoSettings.servoMin);
    DPRINT("servoMax " );DPRINTLN(myServoStruct.myRollServoSettings.servoMax);
    DPRINT("servoCTR " );DPRINTLN(myServoStruct.myRollServoSettings.servoCTR);
    DPRINT("sweepMin " );DPRINTLN(myServoStruct.myRollServoSettings.sweepMin);
    DPRINT("sweepMax " );DPRINTLN(myServoStruct.myRollServoSettings.sweepMax);
    break;
    case 3:
    DPRINTLN("PAN");
    DPRINT("servoType " );DPRINTLN(myServoStruct.myPanServoSettings.servoType);
    DPRINT("servoMin " );DPRINTLN(myServoStruct.myPanServoSettings.servoMin);
    DPRINT("servoMax " );DPRINTLN(myServoStruct.myPanServoSettings.servoMax);
    DPRINT("servoCTR " );DPRINTLN(myServoStruct.myPanServoSettings.servoCTR);
    DPRINT("sweepMin " );DPRINTLN(myServoStruct.myPanServoSettings.sweepMin);
    DPRINT("sweepMax " );DPRINTLN(myServoStruct.myPanServoSettings.sweepMax);
    break;
  }
} //END printServoStruct

void fillmyGimbalStruct(){
  myGimbalStruct.to = 1;
  myGimbalStruct.groupType = 100;
  myGimbalStruct.type = 0;
  myGimbalStruct.action = 0;
  myGimbalStruct.myOpModeGimbal.runMode = 0;
  myGimbalStruct.myOpModeGimbal.gimbalMode = 1;
  myGimbalStruct.myOpModeGimbal.gimbalControl = 1;
  myGimbalStruct.myOpModeGimbal.autopanMode = 1;

  myGimbalStruct.myGimbalSettings.units = degr;
  myGimbalStruct.myGimbalSettings.stepMode = absolute;
  myGimbalStruct.myGimbalSettings.stepSize = 5;
  myGimbalStruct.myGimbalSettings.stepDelay = 10;

  myGimbalStruct.myAutopanSettings.stepSize = 5;
  myGimbalStruct.myAutopanSettings.stepDelay = 10;
  myGimbalStruct.myAutopanSettings.autopanMin = 45;
  myGimbalStruct.myAutopanSettings.autopanMax = 225;

  myGimbalStruct.myGimbalDrive.pitchUp = 0;
  myGimbalStruct.myGimbalDrive.pitchDown = 0;
  myGimbalStruct.myGimbalDrive.rollLeft = 0;
  myGimbalStruct.myGimbalDrive.rollRight = 0;
  myGimbalStruct.myGimbalDrive.panLeft = 0;
  myGimbalStruct.myGimbalDrive.panRight = 0;
}

void fillmyServoStruct(uint16_t servotype){
  myServoStruct.to = keypadControllerID;
  myServoStruct.groupType = 20;
  myServoStruct.type = servotype;
  myServoStruct.action = 0;
  myServoStruct.myPitchServoSettings.servoType = 180;
  myServoStruct.myPitchServoSettings.servoMin = 500;
  myServoStruct.myPitchServoSettings.servoMax = 2500;
  myServoStruct.myPitchServoSettings.servoCTR = 0;
  myServoStruct.myPitchServoSettings.sweepMin = 500;
  myServoStruct.myPitchServoSettings.sweepMax = 2500;
}


void Serial_recvWithStartEndMarkers() {
    static boolean serialRecvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
 
    while (Serial.available() >= 1 && newSerialData == false) { 
         rc = Serial.read();
         if (serialRecvInProgress == true) {
            if (rc != endMarker) {
                serial_receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                serial_receivedChars[ndx] = '\0'; // terminate the string
                serialRecvInProgress = false;
                ndx = 0;
                newSerialData = true;
            }
        }

        else if (rc == startMarker) {
            serialRecvInProgress = true;
        }   
    }
} //END Serial_recvWithStartEndMarkers()

void processTerminalString(){
  String myNewString(serial_receivedChars);
  DPRINTLN(myNewString);
  char *ptr = NULL;
  byte index = 0;
  ptr = strtok(serial_receivedChars, ",");  // delimiter
  while (ptr != NULL)
  {
    strings[index] = ptr;
    index++;
    ptr = strtok(NULL, ",");
  }
  Serial.print("Sending: "); Serial.println(atoi(strings[0]));
  sending(atoi(strings[0]) == 1);

}