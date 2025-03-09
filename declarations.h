uint8_t packetID;
const uint8_t mainControllerID = 1;    const uint8_t mainControllerServoID = 10;  
const uint8_t gimbalControllerID = 2;  const uint8_t gimbalControllerServoID = 20; 
const uint8_t keypadControllerID = 3;

const uint16_t servoPitch = 1;
const uint16_t servoRoll = 2;
const uint16_t servoPan = 3;

//Used servoTypeHandler to track servo is to be configured
int servoID = 0;
int servoOption; 


//Group Types
#define opModeMainGroupType      0
#define opModeGimbalGroupType    1
#define mainSettingsGroupType    2
#define mainDriveGroupType       3
#define gimbalSettingsGroupType  4
#define servoGimbalGroupType     7
#define servoWheelGroupType      8

//Types                           //in groupType
#define SteeringModeType    2     //0
#define SteeringControlType 3     //0     
#define JoystickModeType    4     //0     
#define SystemSettingsType  5     //2
#define GimbalModeType      7     //1   
#define gimbalDriveGroupType 6
#define GimbalControlType   8     //1   
#define AutopanModeType     9     //1
#define DriveSettingsType   10    //2
#define systemOperatingType 11    //0
#define CrashModeType       12    //0    
#define MirrorModeType      13    //0 
#define autopanSettingsType 15    //5
#define UnitType            16    //4
#define StepModeType        17    //4
#define gimbalServoType     18    //7
#define wheelServoType      19    //8
#define DriveModeType       20    //0

//Sub Types 
#define panstepSizeST       1
#define panstepDelayST      2
#define autopanMinST        3
#define autopanMaxST        4

#define degr               1
#define us                 2
#define relative           1
#define absolute           2

#define stopped 0
#define forward 1
#define reverse 2

bool flag1 = false;

bool autopanState = false;  //false = off true = on

uint16_t speed = 0;
uint16_t neg_minSpeed = 0;
uint16_t pos_minSpeed = 0; 
uint16_t pos_maxSpeed = 255;
uint16_t neg_maxSpeed = -255;
uint16_t direction = 0;  //servo motor direction
uint16_t distance = 0;
uint16_t motorDirection = stopped;
uint16_t absSpeed = 0;

/*** USED FOR CONTROLLING THE GIMBAL BOARD DIRECTLY*/
uint16_t currentSteeringMode = 1;
uint16_t currentSteeringControl = 1;
uint16_t currentjoystickMode = 1;
uint16_t currentCrashMode = 1;
uint16_t currentMirrorMode = 1;
uint16_t currentDriveMode = 1;
uint16_t currentGimbalMode = 1;
uint16_t currentGimbalControl = 1;
uint16_t currentAutopanMode = 1;
uint16_t currentUnits = 1;
uint16_t currentStepMode = 1;

struct opModeMain{           //used to control the actions of the main control board
  uint16_t runMode;          // = control mode 
  uint16_t joystickMode;
  uint16_t steeringMode;
  uint16_t steeringControl;
  uint16_t driveMode;        // pwm, pid
  uint16_t mirrorMode;      // off, on
  uint16_t crashMode;       // off, on
};opModeMain _opModeMain;

struct opModeGimbal{        //used to control the actions of the main control board
  uint16_t runMode;        // = control mode 
  uint16_t gimbalMode;    //note keypad range is 1 to 4 subract 1 before sending
  uint16_t gimbalControl; //note keypad range is 1 to 2 subract 1 before sending
  uint16_t autopanMode;   //note keypad range is 1 to 3 subract 1 before sending
};opModeGimbal _opModeGimbal;

struct mainSettings{
  uint16_t avoidDistance;
  uint16_t minSpeed;
  uint16_t maxSpeed;
  uint16_t steeringServoStepSize;
  uint16_t steeringServoStepDelay;
};mainSettings _mainSettings;

struct mainDrive{
  uint16_t servoID = 0;
  uint16_t dcMotorSpeed = 0;
  uint16_t dcMotorDirection = 0;
  uint16_t dcMotorDistance = 0;
  uint16_t servoMotorDirection= 0;
};mainDrive _mainDrive;

struct gimbalSettings{
  uint16_t units;            //0 = microseconds 1 = degrees
  uint16_t stepMode;         //0 = absolute 1 = realative
  uint16_t stepSize;         
  uint16_t stepDelay; 
};gimbalSettings _gimbalSettings;

struct autopanSettings{
  uint16_t stepSize;
  uint16_t stepDelay;
  uint16_t autopanMin;
  uint16_t autopanMax;
};autopanSettings _autopanSettings;

struct gimbalDrive{
  uint16_t pitchUp = 0;
  uint16_t pitchDown = 0;
  uint16_t rollLeft = 0;
  uint16_t rollRight = 0;
  uint16_t panLeft = 0;
  uint16_t panRight = 0;
};gimbalDrive _gimbalDrive;

struct servoSettings {
  uint16_t servoType;
  uint16_t servoMin;
  uint16_t servoCTR;
  uint16_t servoMax;      
  uint16_t sweepMin;
  uint16_t sweepMax;
};servoSettings _servoSettings;
servoSettings _servoPanSettings = {270,500,2500,0,633,2167};
servoSettings _servoRollSettings = {180,500,2500,100,500,2500};
servoSettings _servoPitchSettings = {180,500,2500,0,500,2500};

servoSettings servoSettingsArray[7];

struct mainStruct {  //packetID = 2            
  uint16_t to = 0;      
  uint16_t groupType = 0;                       
  uint16_t type = 0;                      
  uint16_t subType = 0;                      
  uint16_t action = 0;                     
  opModeMain myOpModeMain; 
  mainSettings myMainSettings;
  mainDrive myMainDrive;                
} myMainStruct;
mainStruct myTempMainStruct;
         
struct gimbalStruct { //packetID = 3           
  uint16_t to = keypadControllerID;      
  uint16_t groupType = 100;                       
  uint16_t type = 0;                       
  uint16_t subType = 0;                      
  uint16_t action = 0;
  opModeGimbal myOpModeGimbal;                    
  gimbalSettings myGimbalSettings;
  autopanSettings myAutopanSettings ;
  gimbalDrive myGimbalDrive;           
} myGimbalStruct;
gimbalStruct myTempGimbalStruct;

struct keypadStruct {     
  uint16_t to = 0;      
  uint16_t groupType = 0;                       
  uint16_t type = 0;                       
  uint16_t subType = 0;                      
  uint16_t action = 0; 
  int16_t keyboard_Array[6] = {0, 0, 0, 0, 0, 0};           
} myKeypadStruct;
keypadStruct myTempKeypadStruct;

struct servoStruct {
  uint16_t to = keypadControllerID;      
  uint16_t groupType = 0;                       
  uint16_t type = 0;                                             
  uint16_t action = 0;
  servoSettings myPitchServoSettings;      
  servoSettings myRollServoSettings;      
  servoSettings myPanServoSettings;      
} myServoStruct;
servoStruct myTempServoStruct;

struct servoStructMain {
  uint16_t to = keypadControllerID;      
  uint16_t groupType = 0;                       
  uint16_t type = 0;                                             
  uint16_t action = 0;
  servoSettings myServoSettingsArray[7];    
} MyServoStructMain;
servoStruct myTempServoStructMain;

struct settings {
  servoSettings _servoPitchSettings;
  servoSettings _servoRollSettings;
  servoSettings _servoPanSettings;
  mainStruct myMainStruct;
  gimbalStruct myGimbalStruct; 
}; settings _settings;


/**F2 Menu*********************************************************/
char string1F2[] = "System setting";char string2F2[] = "Drive setting";char string3F2[] = "Gimbal Setting";char string4F2[] = "Autopan Setting";char string5F2[] = "Servo Setting";
char * F2MenuText[] = {string1F2,string2F2,string3F2,string4F2,string5F2};

char string1SS[] = "Avoid Distance";char string2SS[] = "Min Speed";char string3SS[] = "Max Speed";
char * systemSettingsText[] = {string1SS,string2SS,string3SS};

char string1DS[] = "Servo stepSize";char string2DS[] = "Servo stepDelay";
char * driveSettingsText[] = {string1DS,string2DS};

char string1GS[] = "Units";char string2GS[] = "Step Mode";char string3GS[] = "Step Size";char string4GS[] = "Step Delay";
char * gimbalSettingsText[] = {string1GS,string2GS,string3GS,string4GS};

char string1AS[] = "Step Size";char string2AS[] = "Step Delay";char string3AS[] = "Autopan Min";char string4AS[] = "Autopan Max";
char * autopanSettingsText[] = {string1AS,string2AS,string3AS,string4AS};

char string1SERVO[] = "ServoType";char string2SERVO[] = "servoMin";char string3SERVO[] = "servoMax";char string4SERVO[] = "servoCTR";char string5SERVO[] = "ssweepMin";char string6SERVO[] = "sweepMax";
char * servoSettingsText[] = {string1SERVO,string2SERVO,string3SERVO,string4SERVO,string5SERVO,string6SERVO};

/**F1 Menu*********************************************************/
char string1F1[] = "Steering Mode";char string2F1[] = "Steering Control";char string3F1[] = "Joystick Mode";char string4F1[] = "Operating Modes";char string5F1[] = "Gimbal Operation";
char * F1MenuText[] = {string1F1,string2F1,string3F1,string4F1,string5F1};

char string1SM[] = "2-Wheel";char string2SM[] = "4-Wheel";char string3SM[] = "6-Wheel";char string4SM[] = "Tank";
char * steeringModeMenuText[] = {string1SM,string2SM,string3SM,string4SM};

char string1SC[] = "Fixed Transition"; char string2SC[] = "Auto Transition"; char string3SC[] = "Ackermann";char string4SC[] = "Full Auto";
char * steeringControlMenuText[] = {string1SC,string2SC,string3SC,string4SC};

char string1JC[] = "Speed LV/Steer RH";char string2JC[] = "Speed RV/Steer LH";char string3JC[] = "Speed LV/Steer LH";char string4JC[] = "Speed RV/Steer RH";
char * joystickModeMenuText[] = {string1JC,string2JC,string3JC,string4JC};

char string1OM[] = "Crash Mode";char string2OM[] = "Mirror Mode";char string3OM[] = "Drive Mode";
char * systemOperatingText[] = {string1OM,string2OM,string3OM};

char string1GOM[] = "Gimbal Mode";char string2GOM[] = "Gimbal Control";char string3GOM[] = "Autopan Mode";
char * gimbalOperatingMenuText[] = {string1GOM,string2GOM,string3GOM};

/**Sub Selection Menus***********************************************/


char string1GM[] = "Gimbal OFF";char string2GM[] = "Gimbal ON";char string3GM[] = "Gimbal Hold";char string4GM[] = "Gimbal Track";
char * gimbalModeText[] = {string1GM,string2GM,string3GM,string4GM};

char string1GC[] = "Full";char string2GC[] = "Roll & Pitch";char string3GC[] = "Roll Only";
char * gimbalControlText[] = {string1GC,string2GC,string3GC};

char string1AC[] = "Autopan OFF";char string2AC[] = "Autopan ON";char string3AC[] = "Autopan Pause";
char * autopanControlText[] = {string1AC,string2AC,string3AC};

char string1DM[] = "PWM Mode";char string2DM[] = "PID Mode"; ;char string3DM[] = "Test Mode"; 
char * driveModeText[] = {string1DM,string2DM,string2DM};

char string1CM[] = "Crash Mode OFF";char string2CM[] = "Crash Mode ON";char string3CM[] = "Crash Mode Auto";
char * crashModeText[] = {string1CM,string2CM,string3CM};

char string1MM[] = "Mirror Mode OFF";char string2MM[] = "Mirror Mode ON";
char * mirrorModeText[] = {string1MM,string2MM};

char string1UM[] = "Degrees";char string2UM[] = "Microseconds";
char * unitsText[] = {string1UM,string2UM};

char string1ST[] = "Absolute";char string2ST[] = "Relative";
char * stepModeText[] = {string1ST,string2ST};

char string1SERVOT[] = "Pitch";char string2SERVOT[] = "Roll";char string3SERVOT[] = "Pan";char string4SERVOT[] = "Drive Servos";
char * servoTypeText[] = {string1SERVOT,string2SERVOT,string4SERVOT};

//Note all changes are uploaded when changed but not saved hence this menu

char string1EE[] = "Local Save Main"; char string2EE[] = "Local Save Gimbal "; char string3EE[] = "Main to Save"; char string4EE[] = "Gimbal to Save";
char * EEPROMText[] = {string1EE,string2EE,string3EE,string4EE};

char string1EEF1[] = "Upload Main "; char string2EEF1[] = "Upload Gimbal "; char string3EEF1[] = "Download Main"; char string4EEF1[] = "Downloa Gimbal";
char * uploadDownTextF1[] = {string1EEF1,string2EEF1,string3EEF1,string4EE};

