//motiontmc2130stepper.cpp

#include "motiontmc2130stepper.h"
#include "globalAutostageVars.h"
#include <math.h>
#define NOLIMIT 0
#define BACKLIMIT 1
#define FRONTLIMIT 2
#define BOTHLIMITS 3

int motionTMC2130Stepper::initilise(int microSteps,int SilinentStepStick,int StealthChop, long setacceleration, long setspeed)
{
	TMC2130Stepper::begin();
	TMC2130Stepper::microsteps(microSteps);
	TMC2130Stepper::rms_current(SilinentStepStick);// Set stepper current
	TMC2130Stepper::stealthChop(StealthChop); // Enable extremely quiet stepping
	AccelStepper::setMaxSpeed(setacceleration);
	AccelStepper::setAcceleration(setspeed);
	copyMicroSteps = microSteps;//Keeps track fo microsteps so that move can take it onto account.
	currentPos = UNKNOWN_POSITION;// Position is unknown untill home sequence complete.
	
	return 0;
}
int motionTMC2130Stepper::initilise()
{
	TMC2130Stepper::begin();
	TMC2130Stepper::microsteps(256);
	TMC2130Stepper::rms_current(1200);
	TMC2130Stepper::stealthChop(1); // Enable extremely quiet stepping
	AccelStepper::setMaxSpeed(2000.0);
	AccelStepper::setAcceleration(2000.0);
	copyMicroSteps = 256;
	currentPos = UNKNOWN_POSITION;//
	
	return 0;
}
long motionTMC2130Stepper::moveRelative(long move)
{
}
int motionTMC2130Stepper::position()
{
	return currentPos;
}

///////// Angular methods

int angularTMC2130Stepper::initilise(int microSteps,int SilinentStepStick,int Stealthchop, long setacceleration, long setspeed)
{
	motionTMC2130Stepper::initilise(microSteps,SilinentStepStick,Stealthchop, setacceleration, setspeed);
	copyMicroSteps = microSteps;
	TMC2130Stepper::rms_current(600);
	AccelStepper::setMaxSpeed(3000.0);
	AccelStepper::setAcceleration(1000.0);
	pinMode(index_pin,INPUT); 
}
int angularTMC2130Stepper::initilise()
{
    motionTMC2130Stepper::initilise();
	motionTMC2130Stepper::microsteps(256);
	copyMicroSteps = 256;
	TMC2130Stepper::rms_current(600);
	AccelStepper::setMaxSpeed(3000.0);
	AccelStepper::setAcceleration(1000.0);
    pinMode(index_pin,INPUT); 
}

long angularTMC2130Stepper::moveRelative(long move)
{
	stepsToMove = move*(360.0/(STEPS*copyMicroSteps));
	AccelStepper::move(stepsToMove);
	shaftDir <=AccelStepper::_direction;
	currentPos+=move;
	return (move%(STEPS*copyMicroSteps));// If 0 is returned all is good in life,  else shows partial step required to complete angle
}

long angularTMC2130Stepper::moveAbsolute(long move)
{
	move = move-currentPos;
  if(move >180)
    move = move -360;
  if(move <-180)
    move = move + 360;
	stepsToMove = (((long)move*STEPS*copyMicroSteps)/360);

	AccelStepper::move(stepsToMove);
	shaftDir <=AccelStepper::_direction;
	currentPos+=move;
  if(currentPos >= 360)
    currentPos = currentPos - 360;
	return (move%(STEPS*copyMicroSteps));// If 0 is returned all is good in life,  else shows partial step required to complete angle
};

byte angularTMC2130Stepper::load()
{
	return ANGULAR_HOME;
}
byte angularTMC2130Stepper::centre()
{
  moveAbsolute(0);
  return 0;
}

int angularTMC2130Stepper::index()
{
	return 0;
}

bool angularTMC2130Stepper::run()
{
	return AccelStepper::run();	
}



//////////// Linear methods
int linearTMC2130Stepper::initilise(int microSteps,int SilinentStepStick,int Stealthchop)
{
	TMC2130Stepper::begin();
	TMC2130Stepper::microsteps(microSteps);
	copyMicroSteps = microSteps;
	TMC2130Stepper::rms_current(SilinentStepStick);// Set stepper current
	TMC2130Stepper::stealthChop(Stealthchop); // Enable extremely quiet stepping	
	return 0;
}
	

int linearTMC2130Stepper::initilise()
{
	TMC2130Stepper::begin();
	TMC2130Stepper::microsteps(64);
	copyMicroSteps = 64;
	moveCount = 0.0;
	TMC2130Stepper::rms_current(800);
    pinMode(limit1_pin,INPUT);
    pinMode(limit2_pin,INPUT); 
}



long linearTMC2130Stepper::moveRelative(long move)
{
	return 0.0;	
}

long linearTMC2130Stepper::stepCalc(long moveL)
{
	 long moveCounter = (moveL*((((long)STEPS/2.0)*(long)copyMicroSteps)/(long)LEADSCREW_PITCH))/1.2;

	return moveCounter;
}

long linearTMC2130Stepper::decreaseMoveCount()
{
	if (moveCount > 0.0)
		moveCount = moveCount - 1.0;
	else if (moveCount < 0.0)
		moveCount = moveCount + 1.0;
	return moveCount;
}

long linearTMC2130Stepper::moveAbsolute(long moveLL)
{
    moveLL -= currentPos;
    moveCount = stepCalc(moveLL);
		if (moveCount >= 0.0)
		{
			TMC2130Stepper::shaft_dir(0);//Inverse (CW direction)
			shaftDir = 1;
		}	
	else
		{
			TMC2130Stepper::shaft_dir(1);
			shaftDir = 0;
		}
	currentPos+= moveLL;
			
    return moveCount;// If 0 is returned all is good in life,  else shows partial step required to complete angle
};

byte linearTMC2130Stepper::load()
{			
	moveAbsolute(-50);
	return 0;
}
byte linearTMC2130Stepper::centre()
{     
  moveAbsolute(50);
  return 0;
}

byte linearTMC2130Stepper::limit()
{
	byte limitReturn;
	//	String limity = "          ";
	byte stoplimit = PINC;
	byte backStoplimit = stoplimit & B00000100;
	byte frontStoplimit = stoplimit & B00001000;
	if(backStoplimit && (!frontStoplimit))
	{
		limitReturn = BACKLIMIT;
    if((shaftDir == 1) && (moveCount != 0.0))
      {
      currentPos = 40.0;
      }
	}
	else if ((!backStoplimit) && frontStoplimit)
	{
		limitReturn = FRONTLIMIT;
    if((shaftDir == 0) && (moveCount != 0.0))
      {
      currentPos = 0.0;
      }
	}
	else if (backStoplimit && frontStoplimit)
	{
		limitReturn = BOTHLIMITS;
	}
	else
	{
		limitReturn = NOLIMIT;
	}

	return limitReturn;	
}

long linearTMC2130Stepper::getMoveCount()
{
	return moveCount;
}


bool linearTMC2130Stepper::run()
{
byte limitSW  = limit();
bool stopMove = true;

if (limitSW == FRONTLIMIT && moveCount < 0.0)
	{
		stopMove = false;
		moveCount = 0.0;
	}	
if (limitSW == BACKLIMIT && moveCount > 0.0)
	{
		stopMove = false;
		moveCount = 0.0;
	}	
if (moveCount == 0)
	{
		stopMove = false;
	}

if (stopMove == false)
	{
		return stopMove;
	}
else
	{
		digitalWrite(copyStep_pin, HIGH);
		delayMicroseconds(10);
		digitalWrite(copyStep_pin, LOW);
		decreaseMoveCount();
		return true;
	}
	
}

