#include "globalAutostageVars.h"

serialReturn interpretCommand(String inputString)
{
	serialReturn returnData;//Struct to return comand respone including movement
	int linearMove, angularMove, vibPWM;
	char inputChar[4];	
  if(inputString == "{HB}")//  Heatbeat
	
	{
		returnData.move = false;
		returnData.responce = HB;
		returnData.vib = 0;
		returnData.lin = 0;
		returnData.ang = 0;
	}
	else if(inputString =="help" || inputString =="Help")
	{
		returnData.move = false;
		returnData.responce = HELP;
		returnData.vib = 0;
		returnData.lin = 0;
		returnData.ang = 0;
	}

	else if(inputString =="{btsequence}")
	{
		returnData.move = true;
		returnData.responce = SEQUENCEACK;
		returnData.vib = 0;
		returnData.lin = 0;
		returnData.ang = 0;
		returnData.posnumber = 0;
		returnData.numberpos = 39;
    goFlag = true;
	}

  else if(inputString =="{btnext}")
  {
    returnData.move = true;
    returnData.responce = NEXTACK;
    returnData.vib = 0;
    returnData.lin = 0;
    returnData.ang = 0;
    goFlag = true;
  } 

  else if(inputString =="{btprev}")
  {
    returnData.move = true;
    returnData.responce = PREVACK;
    returnData.vib = 0;
    returnData.lin = 0;
    returnData.ang = 0;
    goFlag = true;
  }
	else if(inputString =="{btcentre}")
	{
		returnData.move = true;
		returnData.responce = CENTREACK;
		returnData.vib = 0;
		returnData.lin = 50;
		returnData.ang = 0;
		returnData.posnumber = 0;
		returnData.numberpos = 0;
    goFlag = false;
	}
	
	
  else if(inputString.substring(0,8) == "{btgoto ")
	{
		if(inputString.endsWith("}"))
		{
			linearMove = (inputString.substring(8,11).toInt());   
			angularMove =(inputString.substring(11,15).toInt());
      Serial.println(linearMove);
      Serial.println(angularMove);
			stringComplete = true;
			if (((linearMove >= -10) && (linearMove <= 100)) && ((angularMove >= 000) && (angularMove <= 360)))
			{
				returnData.move = true;
				returnData.responce = GOTOACK;
				returnData.lin = linearMove;//in order to account for direction?
				returnData.ang = angularMove;//-180 to account for direction?
//				returnData.posnumber = NOPROGRAM;
//				returnData.numberpos = 1;
        goFlag = false;
				
			}
			else
			{
				returnData.move = false;
				returnData.responce = GOTOSWERR;
				returnData.vib = 0;
				returnData.lin = 0;
				returnData.ang = 0;
			}
		}
		else
		{
			returnData.move = false;
			returnData.responce = GOTOSWERR;
			returnData.vib = 0;
			returnData.lin = 0;
			returnData.ang = 0;
			returnData.posnumber = NOPROGRAM;
		}

	}
  else if(inputString.substring(0,9) == "{btgopos ")
	{
   
		if(inputString.endsWith("}"))
		{
			sampleStep = (inputString.substring(9,12).toInt());   
			stringComplete = true;
			if ((sampleStep >= 0) && (sampleStep  <= 39)) 
			{
				returnData.move = true;
				returnData.responce = GOPOSACK;
				returnData.posnumber = sampleStep;
				returnData.numberpos = 39;
        goFlag = true;
				
			}
			else
			{
				returnData.move = false;
				returnData.responce = GOTOSWERR;
				returnData.vib = 0;
				returnData.lin = 0;
				returnData.ang = 0;
			}
		}
		else
		{
			returnData.move = false;
			returnData.responce = GOTOSWERR;
			returnData.vib = 0;
			returnData.lin = 0;
			returnData.ang = 0;
		}
	}
	
	// vib
 else if(inputString.substring(0,7) == "{btvib ")
	{
		
		if(inputString.endsWith("}"))
		{
			vibPWM = (inputString.substring(7,10).toInt());   
			stringComplete = true;
			
			if ((vibPWM >= 0)  && (vibPWM <=255))//Add 100 to desired value in order to ensure numeric value sent
			{
				returnData.move = false;
				returnData.responce = VIBACK;
				returnData.vib = vibPWM;
				returnData.lin = 0;
				returnData.ang = 0;
			}
			else
			{
				
				returnData.move = false;
				returnData.responce = VIBERR;
				returnData.vib = 0;
				returnData.lin = 0;
				returnData.ang = 0;				
			}
		}
		else
		{
			returnData.move = false;
			returnData.responce = GOTOSWERR;
			returnData.vib = 0;
			returnData.lin = 0;
			returnData.ang = 0;
		}

	}
	// end of vib	
	
	else if(inputString == "{btredy}")//Ready??
	{
		returnData.move = false;
		returnData.responce = READYACK;
		returnData.vib = 0;
		returnData.lin = 0;
		returnData.ang = 0;
	}
 else if(inputString == "{btload}")//HOME
	
	{
		returnData.move = false;
		returnData.responce = LOADACK;
		returnData.vib = 0;
		returnData.lin = 0;
		returnData.ang = 0;
	}
	
else if(inputString  == "{btextd}")//Extend
	{
		returnData.move = false;
		returnData.responce = EXTENDACK;
		returnData.vib = 0;
		returnData.lin = 0;
		returnData.ang = 0;
	}
	
else if(inputString  == "{btpos}")//Extend
  {
    returnData.move = false;
    returnData.responce = POSACK;

  }
 else if(inputString == "{btinfo}")//INFO
	{
		returnData.move = false;
		returnData.responce = INFO;
		//		Serial.println("Got to BTINFO");
		returnData.vib = 0;
		returnData.lin = 0;
		returnData.ang = 0;
	}
	
else if(inputString.substring(0,8) == "{btwtsn ")//Serial number write
	
	{
		if (inputString.endsWith("}"))
		{
			EEPROM.write(0, inputString[8]);//Write directy to EEPROM here rather than exit as it is a very infrequent activity
			EEPROM.write(1, inputString[9]);
			EEPROM.write(2, inputString[10]);
			EEPROM.write(3, inputString[11]);
			EEPROM.write(4, inputString[12]);
			EEPROM.write(5, inputString[13]);
			returnData.move = false;
			returnData.responce = SNACK;
			returnData.vib = 0;
			returnData.lin = 0;
			returnData.ang = 0;
		}
		else
		{
			returnData.move = false;
			returnData.responce = NORESPONCE_CLEAR;
			returnData.vib = 0;
			returnData.lin = 0;
			returnData.ang = 0;
		}
	}
	else //Default case dealing with bad commands
	{
		int defresponce = 0;
		if(inputString[0] == "{")
		{
      defresponce = NORESPONCE;
			for(int x = 1;x<16;x++)
			{
				if(inputString[x] =="}")
				{
					defresponce = COMMANDERROR;
				}
        returnData.responce = defresponce;
			}
		}
    else
    {
      defresponce = COMMANDERROR;
    }
		returnData.responce = defresponce;
		returnData.move = false;
		returnData.vib = 0;
		returnData.lin = 0;
		returnData.ang = 0;
			
		}
   	
	return returnData;
	
}
