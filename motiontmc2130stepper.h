//motiontmc2130stepper.h
//#pragma once
#include <SPI.h>
#include <TMC2130Stepper.h>
#include <AccelStepper.h>

#ifndef MOTIONTMC2130STEPPER_H
	#define MOTIONTMC2130STEPPER_H
	#define STEPS 400
	#define LEADSCREW_PITCH 2.54
	#define UNKNOWN_POSITION 400
	#include "globalAutostageVars.h"
	
	class motionTMC2130Stepper : public TMC2130Stepper, public AccelStepper{
		
		public:
		
		motionTMC2130Stepper(int enable_pin, int dir_pin, int step_pin,int cs_pin)
		:TMC2130Stepper(enable_pin, dir_pin, step_pin, cs_pin) ,AccelStepper(DRIVER, step_pin, dir_pin)
		{
			copyEnable_pin = enable_pin;
			copyDir_pin = dir_pin; 
			copyStep_pin = step_pin;
			copyCs_pin = cs_pin;
		}
		
		int initilise(int,int,int, long, long);//To be used in setup code section,  performs begin, microsteps,SilentStepStick & stelthChop
		int initilise();
		byte load();//move to home position returns 1 when complete?
		long stepCalc(long);
		long moveRelative(long);//Move relative from existing point,  returns absolute position
		long moveAbsolute(long);//Move to absolute position 
		int position();// Returns position of stepper
		int copyMicroSteps;//Copy of pins so we dont have to look inside the black box.
		int copyEnable_pin;
		int copyDir_pin;
		int copyStep_pin;
		int copyCs_pin;
		int currentPos;
		long stepsToMove;
		long intStepsToMove;
		int moveang;
		int moveReturnVar;
		bool shaftDir;
		
		
	};
	
	class angularTMC2130Stepper : public motionTMC2130Stepper{
		public:
		
		angularTMC2130Stepper(int enable_pin, int dir_pin, int step_pin,int cs_pin, int index_pin)
		:motionTMC2130Stepper(enable_pin, dir_pin, step_pin, cs_pin),index_pin(index_pin)
		{
			
		}
		int index();//to return 1 when indexer microswitch tripped
        int initilise(int,int,int, long, long);
        int initilise();
        long moveRelative(long);
        long moveAbsolute(long);
		long stepsToMove;
        bool run();
        byte load();
        byte centre();
		long stepCalc(long);
		//       int position();        
		private:				
		int index_pin;
	};
	
	
	class linearTMC2130Stepper : public TMC2130Stepper{
		public:
		linearTMC2130Stepper(int enable_pin, int dir_pin, int step_pin,int cs_pin, int limit1_pin, int limit2_pin)
		:TMC2130Stepper(enable_pin, dir_pin, step_pin, cs_pin),limit1_pin(limit1_pin), limit2_pin(limit2_pin)
		{
			copyEnable_pin = enable_pin;
			copyDir_pin = dir_pin; 
			copyStep_pin = step_pin;
			copyCs_pin = cs_pin;
		}					
	    int initilise(int,int,int);
        int initilise();
		int copyMicroSteps;
		long getMoveCount();
        long moveRelative(long);
		long decreaseMoveCount();
        long moveAbsolute(long);
		int copyEnable_pin;
		int copyDir_pin;
		int copyStep_pin;
		int copyCs_pin;
		int currentPos;
		int intStepsToMove;
		long stepsToMove;
		long stepCalc(long);
		byte limit();
    byte centre();
        bool run();
        byte load();
		//        int position();
		private:
		int limit1_pin;
		int limit2_pin;
		bool backStop;
		bool frontStop;
		bool shaftDir;
		long moveCount;
		
	};
#endif /* MOTIONTMC2120STEPPER_H */
