// SerialResponder.ino
#include "globalAutostageVars.h"

int serialResponder(int responce)
{
	switch(responce)
	{
		case HB:
		{
			Serial.write("<HB>");
			Serial.write('\n');
			break;
		}	
		case GOTOACK:
		{
			Serial.write("<btgoto ack>");
			Serial.write('\n');
			break;
		}
		case GOTOSWERR:
		{
			Serial.write("<btgoto swerr>");//Error condtion from btgoto
			Serial.write('\n');
			break;
		}
		case READYACK:
		{
			if(inmove == false)
			{
			  Serial.write("<btredy ack>");//Device ready after setup
			  Serial.write('\n');
			}
     else
     {
        Serial.write("<btntredy>");//Device not after setup
        Serial.write('\n');
     }
			break;
		}
		case READYSWERR:
		{
			Serial.write("<btredy swerr>");//btready error,  startup sequence not complete properly
			Serial.write('\n');
			break;
		}
		case SEQUENCEACK:
		{
			Serial.write("<sequence ack>");//Acknoledge sequence recived
			Serial.write('\n');
      break;
		}

    case NEXTACK:
    {
      Serial.write("<next ack>");//next in sequence recived
      Serial.write('\n');
      break;
    }
    
    case PREVACK:
    {
      Serial.write("<prev ack>");//previous in sequence recived
      Serial.write('\n');
      break;
    }
     case GOPOSACK:
    {
      Serial.write("<gopos ack>");//previous in sequence recived
      Serial.write('\n');
      break;
    }  
		case MOVECOMPLETE:
		{
			if ((returnedData.posnumber == returnedData.numberpos) && (returnedData.numberpos >0) && (goFlag ==true))
			{
				Serial.write("<btseqcomplete>");//Sequence complete 
			}
			else if ((returnedData.posnumber < returnedData.numberpos) && (returnedData.numberpos >0)&& (goFlag == true))
			{
				Serial.write("<btseq ");
				if(returnedData.posnumber <10)//Shows <001/039> where 001 is the point in the sequence completed and 039 being the total number of sequences ie 0-39 (40 steps)
					Serial.write("00");
				else
					Serial.write("0");
				Serial.print(returnedData.posnumber);
				Serial.write("/");
				if(returnedData.numberpos <10)
				  Serial.write("00");
				else
			    Serial.write("0");
				Serial.print(returnedData.numberpos);
				Serial.write(">");
			}
     else
     {
      Serial.write("<btmovecomplete>");
      }
      goFlag = false;
			Serial.write('\n');
      break;
		}
		case LOADACK:
		{
			Serial.write("<btload ack>");//Acknologment for load sequence
			Serial.write('\n');
			break;
		}
    case CENTREACK:
    {
      Serial.write("<btcentre ack>");//Acknologment for centre sequence
      Serial.write('\n');
      break;
    }  
//		case EXTENDACK:
//		{
//			Serial.write("<btextd ack>");//Unused,  extend,  load replaced
//			Serial.write('\n');
//			break;
//		}
//		case EXTENDSWERR://Error from extend
//		{
//			Serial.write("<btextd swerr>");
//			Serial.write('\n');
//			break;
//		}
		case NORESPONCE_CLEAR:
		{
			Serial.write("<btnotcl>");//ie not clear...
			Serial.write('\n');
			break;
		}
		case SNACK ://Serial number written to EEPROM
		{
			Serial.write("<btwtsn ack>");
			Serial.write('\n');
			break;
		}
		case HELP:
		{
			helpPrint();
			break;
		}
		case GOTOBSY://Stepper motors busy cannot move yet
		{
			Serial.write("<btgoto bsy>");
			Serial.write('\n');
			break;
		}
		case INFO:
		{
			printInfo();
			break;
		}

		case COMMANDERROR://Error in command
		{
			Serial.write("<btcomd err>");
			Serial.write('\n');
			break;
		}
		case VIBACK:
		{
			Serial.write("<btvib ack>");//vibrate ack
			Serial.write('\n');
			break;
		}
    case VIBERR:
    {
      Serial.write("<btvib err>");
      Serial.write('\n');
      break;
     }
   case POSACK://request for position  in formt <btpos lin:000 ang:000>
   {
      Serial.write("<btpos lin:");
      Serial.print(TMC2130_LS.currentPos);
      Serial.write(" ang:");
      Serial.print(TMC2130_TT.currentPos);
      Serial.write(">");
      Serial.write('\n');
      Serial.write("<btseq ");
      if(returnedData.posnumber <10)//Shows <001/039> where 001 is the point in the sequence completed and 039 being the total number of sequences ie 0-39 (40 steps)
        Serial.write("00");
      else
         Serial.write("0");
      Serial.print(returnedData.posnumber);
      Serial.write("/");
      if(returnedData.numberpos <10)
        Serial.write("00");
      else
        Serial.write("0");
      Serial.print(returnedData.numberpos);
      Serial.write(">");
      Serial.write('\n');
      break;
   }
		
		default :
		{
			Serial.write("<?>");// Esentually unknown command
			Serial.write('\n');
			break;
		}
		
	}
}


void helpPrint()
{
	Serial.println(F("Command list"));// Define list of comands to be printed.......
  Serial.println(F("{HB},             Heartbeat."));
  Serial.println(F("{btinfo},         Returns device info."));
  Serial.println(F("{btgoto LLLAAA},  Command to move"));
  Serial.println(F("{btsequence},     Start sequence."));
  Serial.println(F("{btnext},         Move Next."));
  Serial.println(F("{btprev},         Move Previous."));
  Serial.println(F("{btpos},          Show current pos"));
  Serial.println(F("{btwtsn ****},    Write sn"));
  Serial.println(F("{btvib ***},      Set vib level"));
  Serial.println(F("{btredy},        Ready?"));
  Serial.print(F("help,             Help sheet"));
	Serial.write('\n');
}

void printInfo()
{
	Serial.print(F("<bt info "));
	Serial.print(F("hw:xxxx "));
	Serial.print(F("fw:0.0.1 "));
	Serial.print(F("sn "));
	Serial.write((char)EEPROM.read(0));
	Serial.write((char)EEPROM.read(1));
	Serial.write((char)EEPROM.read(2));
	Serial.write((char)EEPROM.read(3));
	Serial.write((char)EEPROM.read(4));
	Serial.write((char)EEPROM.read(5));
	Serial.print(F(" wa:0650"));
	Serial.print(F(" sc:0000"));  //Error code storage to be defined.
	Serial.print(F(">"));
	Serial.write('\n');
}
