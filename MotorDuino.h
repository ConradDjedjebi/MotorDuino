/****************************************************************************************************
  MotorDuino.h

  author : Conrad Djedjebi
  version v1.0
  License: GNU AGPLv3

  A motor library for Arduino

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Affero General Public
  License as published by the Free Software Foundation; either
  version 3 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Affero General Public License for more details.
  
  You should have received a copy of the GNU Affero General Public
  License along with this library; If not, see <http://www.gnu.org/licenses/>.

Version Modified By Date     Comments
------- ----------- -------- --------
0001    C DJEDJEBI    xx/xx/xx ..
****************************************************************************************************/

#ifndef MOTOR_DUINO_H_
#define MOTOR_DUINO_H_

#include "Arduino.h"
#include <string.h>
#include <math.h>
#include <Macros.h>
#include <EEPROM.h>
#include <timers.h>

typedef enum {
	STEP_MOTOR,
	BRUSHED_MOTOR,
	AC_MOTOR
} motorType;

class MotorDuino 
{
	public:
		MotorDuino(void);
		MotorDuino(char nom[]);		
		MotorDuino(char nom[], motorType type);
		~MotorDuino(void);
		/**
		 * Methods
		 */
		void saveNbSteps(unsigned int nbSteps);
		void motorOpen(char name[]);
		void motorTurn(void);  
		void motorTurnSteps(unsigned int steps);
		void motorTurnRounds(unsigned int round);
		void motorTurnRoundsPerSecond(float roundsPerSecond);
		void motorTurnStepsPerSecond(unsigned int stepsPerSecond);
		void motorSetVolumePerRound(float volume);
		void motorStop();
		void setSpeed(unsigned int speed);
		void setNbSteps(unsigned int nbSteps);
		int getSpeed(void);
    	motorType getType();		
    	void setType(motorType type);   		
		void saveState(bool state);	
		int getStateAddress();		
		void setStateAddress(int stateAddress);		
		void setNbStepsAddress(int nbStepsAddress);			

		char motorName[MAX_CARACTERES];		  	
		int frequence;
		int steps;
	  	unsigned int stepsPerRound;
	  	int motorSpeed;
	  	int pinDirection;
	  	int pinStep;
	  	int pinEnable;
		int stateAddress;
		int nbStepsAddress;	
	private:
		motorType type;
		void stepMotorTurn(void);
		void brushedMotorTurn(void);
		void acMotorTurn(void);		
};

#endif
