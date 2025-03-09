char roverDrive(){
  bool changed = false;
  u8g2.clear();
  u8g2.setCursor(0,7);
  u8g2.print("Set..."); 
  u8g2.setCursor(0,24);
  u8g2.print("Speed (U/D):"); 
  u8g2.setCursor(100,17);
  u8g2.print(speed);      
  u8g2.setCursor(0,31);
  u8g2.print("Direction (</>):");
  u8g2.setCursor(100,31);
  u8g2.print(direction);      
  u8g2.setCursor(0,48);
  u8g2.print("Key '0' to Zero");
  u8g2.setCursor(0,56);
  u8g2.print("Key 'Esc' to Exit");
  u8g2.sendBuffer();
  bool controlStatus = false;
  char controlKey = getControlKey();
  int msDirection = 1500;
  while (controlKey != 'C'){
    //speed range -255 to 255 -ve = reverse
    //the min and max spped apply to both the -255 and the 255
    if (controlKey == 'U'){
      if (speed == 0){
        speed = pos_minSpeed;
        changed = true;
      }else{  
        speed = speed+10;
        changed = true;
        if (speed > pos_maxSpeed){
          speed = pos_maxSpeed;
          changed = true;
        }
      }
      if (speed > neg_minSpeed && speed < pos_minSpeed){
        speed = 0;
        changed = true;
      }
      displayValue(100,17, speed);
      changed = true;
    }else if (controlKey == 'D'){
      if (speed == 0){
        speed = neg_minSpeed;
        changed = true;
      }else{  
        speed = speed-10;
        changed = true; 
        if (speed < neg_maxSpeed){
          speed = neg_maxSpeed;
          changed = true;
        }
      }
      if (speed > neg_minSpeed && speed < pos_minSpeed){
        speed = 0;
        changed = true;
      }  
      displayValue(100,17, speed);
      changed = true;
    }else if (controlKey == '0'){
      speed = 0;
      displayValue(100,17, speed);
      changed = true;
    }else if (controlKey == '>'){
      if (direction >=-90 && direction <= (90 - 5)){
        direction = direction + 5;
        displayValue(100,31, direction);
        msDirection = direction * 10 + 1500;
        changed = true;
      }
    }else if (controlKey == '<'){
      if (direction >=-90+5 && direction <= 90){
        direction = direction - 5;
        displayValue(100,31, direction);
        msDirection = direction * 10 + 1500;
        changed = true;
      }
    }else if (controlKey == '0'){
      direction = 0;
      speed = 0;
      changed = true;
    }
    if (changed == true){
      changed = false;
    }
    controlKey = getControlKey();
  }
  return controlKey;
} //END roverDrive


char gimbalDrive(){
  char key;
  bool changed = false;
  u8g2.clear();
  u8g2.setCursor(0,7);
  u8g2.print("Gimbal Control"); 
  u8g2.setCursor(0,8);
  u8g2.print("Use keys.."); 
  u8g2.setCursor(0,16);
  u8g2.print("4 and 5 to Pan"); 
  u8g2.setCursor(0,24);
  u8g2.print("2 and 8 to Pitch");     
  u8g2.setCursor(0,32);
  u8g2.print("< and > to Roll");
  u8g2.setCursor(0,40);
  u8g2.print("5 to Pause");
  u8g2.setCursor(0,48); 
  u8g2.print("3 Pan on/off");
  u8g2.setCursor(0,56); 
  u8g2.print("'Esc' to Exit");
  u8g2.sendBuffer();
  clearMovement();
  key = getgimbalControlKey();
  while (key != 'C'){
    Serial.println(key);
    //speed range -255 to 255
    if (key == '2'){                //pitch up
      _gimbalDrive.pitchUp = 1; changed = true;
    }else if (key == '8'){          //pitch down
      _gimbalDrive.pitchDown = 1; changed = true;  
    }else if (key == '6'){          //pan right
      _gimbalDrive.panRight = 1; changed = true;
    }else if (key == '4'){          //pan left
      _gimbalDrive.panLeft = 1; changed = true;
    }else if (key == '<'){          //roll left
      _gimbalDrive.rollLeft = 1; changed = true;
    }else if (key == '>'){          //roll right
      _gimbalDrive.rollRight = 1; changed = true;
    }else if (key == '5'){          //pause
      _opModeGimbal.autopanMode = 2;
    }else if (key == '0'){          //centre gimbal
        //centreGimbal();
    }else if (key == '3'){        //pan on/off
      autopanState = !autopanState;
      if (autopanState == false){
        _opModeGimbal.autopanMode = 0;
      }else if (autopanState == true){
        _opModeGimbal.autopanMode = 1;
      }
    }
    if (changed == true){
      clearMovement();
      changed = false;
    }
    key = getControlKey();
  }
  return key;
} //END gimbalDrive
