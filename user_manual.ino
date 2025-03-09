/*
The keyborad controller can be used to set:

F1 Menu             Sub menus
  Steering Mode     - 2 Wheel, 4Wheel, 6Wheel, Tank
  Steering Control  - Fixed Transition, Auto Transition, Ackermann, Full Auto
  Joystick Mode     - Speed LV/Steer RH, Speed LV/Steer LH, Speed RV/Steer LH, Speed LH/Steer RH, Speed RH/Steer LH, Speed RV/Steer RH
  Operating Modes
    Crash Mode      - Crash Mode Off, Crash Mode Off, Crash Mode Auto
    Mirror Mode     - Mirror Mode Off, Mirror Mode
    Drive Mode      - pwm mode, PID mode
  Gimbal Operation
    Gimbal Mode     - Gimbal off, gimbal on, hold, track
    Gimbal Control  - Full, Pitch/Roll
    Autopan Mode    - Autopan Off, Autopan On, Autopan Pause 

F2 Menu               Sub menus
  System setting    - crashMode, Avoid Distance, Max Speed, Min Speed, steeringServoStepSize, steeringServoStepDelay
  Gimbal settings   - units (0 = microseconds 1 = degrees), stepMode 0 = absolute 1 = realative, Step Size, Step Speed, 
  Autopan Settings  - Step Size, Step Speed, Autopan Min, Autopan Max, Save Settings
  Drive setting     - Servo stepSize, Servo stepDelay, Save System Setup
  servoSettings     - (not implimented)
    gimbalServos    - pitch settings, roll settings, pan settings
    wheel servos    - wb1, wb2,wb3,wb4,wb5,wb6
  Save Setup
# Menu  
  Drive Controls to mainboard (myMainStruct) - Speed, Direction, Distance, servo direction

* Menu
  Drive Controls to gimbal (myGimbalStruct)  - pitch, roll, pan


Keypad keys
  ENT (enter 'E')
  ESC (cancel 'C')
  <   (backspace '<')
  *   (decimal point '.') when entering numbers in F1Menu
  arros to setp through speed and direction in drive controls menu

  F1 menu 1
  F2 menu 2

//NOTE all changes are uploaded when changed but not saved hence this menu//

*******************************************************************************************
When the keypad sends the settings to the main controller board and to the gimbal controller board
these boards need to parse the data for actioning. The menu system breaks the settings in to 10 typew

GROUP Type  MENU TYPE     MENU ITEM                               SUBMENU TYPE ( = menuoption )

3           NA             # (Rover Drive)                          no subType                   
6           NA             * (Gimbal Drive)                         no subType

0           2             displaySteeringModeMenu                   submenu type = menuoption (_opModeMain.SteeringMode)          
0           3             displaySteeringControlMenu                submenu type = menuoption (_opModeMain.SteeringControl)
0           4             displayJoystickModeMenu                   submenu type = menuoption (_opModeMain.JoystickMode)
                          (SystemSettingsMenu)                     
2           5                 _mainSettings.avoidDistance           submenu type = menuoption = 1 
2           5                 _mainSettings.minSpeed                submenu type = menuoption = 2
2           5                 _mainSettings.maxSpeed                submenu type = menuoption = 3 
                          (gimbalSettingsMenu)                      
4           6                 _gimbalSettings.stepSize              submenu type = menuoption = 1
4           6                 _gimbalSettings.stepDelay             submenu type = menuoption = 2
4           6                 unitsMenu                             16    (_gimbalSettings.units)
4           6                 stepModeMenu                          17    (_gimbalSettings.stepMod)                                                 
                          (displayDriveSettingsMenu)                
2          10                  _mainSettings.steeringServoStepSize  submenu type = menuoption = 1
2          10                  _mainSettings.steeringServoStepDelay submenu type = menuoption = 2
                          (sytemOperatingModeMenu)                  sub menus....
0          11                  CrashModeMenu                        12   (_opModeMain.crashMode)  
0          11                  MirrorModeMenu                       13   (_opModeMain.mirrorMode)   
0          11                  DriveModeMenu                        13   (_opModeMain.mirrorMode)   
                         (displayGimbalOperatingModeMenu)          
1           7                   displayGimbalModeMenu               submenu type = menuoption (_opModeGimbal.gimbalMode)          
1           8                   displayGimbalCointrolMenu           submenu type = menuoption (_opModeGimbal.gimbalControl)
1           9                   displayAutopanMenu                  submenu type = menuoption (_opModeGimbal.autopanMode) 
                          (displayAutopanSettingsMenu)            
4           15                 _autopanSettings.stepSize            submenu type = menuoption = 1
4           15                 _autopanSettings.stepDelay           submenu type = menuoption = 2
4           15                 _autopanSettings.autopanMin          submenu type = menuoption = 3
4           15                 _autopanSettings.autopanMax;         submenu type = menuoption = 4
                          (gimbalServoTypeMenu)                     
7           18                 pitchMenu                            submenu type = menuoption = 1
7           18                 rollMenu                             submenu type = menuoption = 2
7           18                 panMenu                              submenu type = menuoption = 3
                           (wheelServoTypeMenuu)                    submenu type = menuoption
8           19                 wb1ServoMenu                         1
...         19                 ....                                 ...
8           19                 wb6ServoMenu                         6                  

*/
  
