//globalAutostageVars.h
/*
	Initializes the library and turns the motor in alternating directions.
*/
#ifndef GLOBAL_VARS
	#define GLOBAL_VARS
	#define EN_PIN_TT    6  // Nano v3:  16 Mega:  38  //enable (CFG6)
	#define DIR_PIN_TT   A4 //      19      55  //direction
	#define STEP_PIN_TT  4  //      18      54  //step
	#define CS_PIN_TT    5  //      17      64  //chip select
	
	#define EN_PIN_LS    10  // Nano v3:  16 Mega:  38  //enable (CFG6)
	#define DIR_PIN_LS   9 //      19      55  //direction
	#define STEP_PIN_LS  8  //      18      54  //step
	#define CS_PIN_LS    7  //      17      64  //chip select
	#define GREEN_LED A0
	#define RED_LED A1
	#define MTR_DRV 3
	#define PB A5
	#define LST1 A2
	#define LST2 A3
	#define TTLS  2
	#define SUPERFINE 256
	#define FINE 64.0
	#define COURSE 1.0
	#define NORESPONCE 0
	#define HB 1
	#define GOTOACK 2
	#define GOTOSWERR 3
	#define READYACK 4
	#define READYSWERR 5
	#define LOADACK 6
	#define HOMESWERR 7
	#define EXTENDACK 8
	#define EXTENDSWERR 9
	#define NORESPONCE_CLEAR 10
	#define SNACK 11
	#define COMMANDERROR 12
	#define HELP 13
	#define GOTOBSY 14
	#define INFO 15
	#define VIBACK 16
	#define ANGULAR_HOME
	#define LINEAR_HOME
	#define RED 3
	#define GREEN 2
	#define ORANGE 1
	#define NO_COLOUR 0
	#define CENTREACK 17
	#define SEQUENCEACK 18
	#define SEQUENCECOMPLETE 19
	#define MOVECOMPLETE 20
	#define GOPOSACK 21
	#define NOPROGRAM 40
	#define CENTRECOMPLETE 22
  #define NEXTACK 23
  #define PREVACK 24
  #define GOBACKACK 25
  #define POSACK 26
  #define GOPOSACK 27
  #define VIBERR 28
  
	bool dir = true;
  bool goFlag = false;//To distingush from sequence and btgoto...
	byte val = 0;
	bool switcher = false;
	bool inmove = false;
	bool inmoveOld = false;
	byte colour = ORANGE;
	int linearPosition = 0;
	int angularPosition = 0;
  int newPosition = 0;//Where position sequence is used,  used to record desired position
	long previousMillis;
	long interval = 1000;
	struct serialReturn //Return for interpretCommand,  telling whether more required or not,  the coords to move to and responce code to be sent back to eyepass posnumber is the number of moves complete numposition is the total number of moves
	{
		bool move;
		int responce,lin,ang,vib,posnumber,numberpos;// Where posnumber is the current position and numberpos is the total number of positions
	};
	int serialResponder(int);
	
	const int sampleArray[40][2] = {{0,0},{0,18},{0,36},{0,54},{0,72},
		{0,90},{0,108},{0,126},{0,144},{0,162},{0,180},{0,198},
		{0,216},{0,234},{0,252},{0,270},{0,288},{0,306},{0,324},
		{0,342},{12,0},{12,30},{12,60},{12,90},{12,120},
		{12,150},{12,180},{12,210},{12,240},{12,270},{12,300},{12,330},
		{23,0},{23,60},{23,120},{23,180},{23,240},{23,300},
		{34,0},{34,180}};
		
	int sampleStep = 0;
	
	
#endif
