/****************************************************************************************************
  MotorDuino.cpp

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

#include "MotorDuino.h"

/**
 * Constructeur de l objet moteur
 */
MotorDuino::MotorDuino(void)
{
  this->frequence = 1650;
}

/**
 * Constructeur du moteur en lui specifiant
 * un nom
 *
 * \param char name[] : nom du moteur a contruire
 */
MotorDuino::MotorDuino(char name[]) : MotorDuino()
{
  this->motorOpen(name);
}

/**
 * Constructeur du moteur en lui specifiant
 * un nom
 *
 * \param char name[] : nom du moteur a contruire
 * \param MotorDuinoType type : type du moteur à construire 
 */
MotorDuino::MotorDuino(char name[], motorType type) : MotorDuino(name)
{
  this->type = type;
}

/**
 * Destructeur de l objet moteur
 */
MotorDuino::~MotorDuino(void)
{
  
}

/**
 * Getter pour récupérer la frequence du moteur
 *
 * \param void
 */
int MotorDuino::getSpeed(void)
{
  return this->frequence;
}

/**
 * Getter pour récupérer l'adresse de sauvegarde de l'état du moteur
 *
 * \param void
 */
int MotorDuino::getStateAddress(void)
{
  return this->stateAddress;
}

/**
 * Get MotorDuino type
 * @return int MotorDuino type
 */
motorType MotorDuino::getType(){
    return this->type;
}

/**
 * Initialisation du nom du moteur
 * 
 * \param char name[] : nom spécifique du moteur
 */
void MotorDuino::motorOpen(char name[])
{
  strcpy(motorName, name);
}

/**
 * Methode pour mettre en marche le moteur
 */
void MotorDuino::motorTurn(void)
{  
  switch(this->type){
    case STEP_MOTOR:
      this->stepMotorTurn();
      break;
    case BRUSHED_MOTOR:
      this->brushedMotorTurn();
      break;
    case AC_MOTOR:
      this->acMotorTurn();
      break;            
    default:
      this->stepMotorTurn();
      break;
  }
}

/**
 * Methode pour mettre en marche un moteur à pas
 */
void MotorDuino::stepMotorTurn(void)
{  
  digitalWrite(pinEnable, LOW);
  pwm(pinStep, (unsigned int)frequence, 0);
}

/**
 * Methode pour mettre en marche un brushed moteur
 */
void MotorDuino::brushedMotorTurn(void)
{  
}

/**
 * Methode pour mettre en marche un moteur ac
 */
void MotorDuino::acMotorTurn(void)
{  
}

/**
 * Methode  pour faire tourner le moteur d'un certain nombre de pas
 *
 * \param unsigned int steps : nombre de pas
 */
void MotorDuino::motorTurnSteps(unsigned int steps)
{  
  digitalWrite(pinEnable, LOW);
  pwm(pinStep, (unsigned int)frequence, (unsigned long)(steps*((float)1000/(float)frequence)));
}


/**
 * Methode pour faire tourner le moteur le nombre de tours donne
 *
 * \param unsigned int tours
 */
void MotorDuino::motorTurnRounds(unsigned int rounds)
{
  unsigned int steps = (unsigned int) (rounds * stepsPerRound);
  motorTurnSteps(steps);
}

/**
 * Faire tourner le moteur selon une vitesse donnee en pas par secondes
 *
 * \param unsigned int stepsPerSecond : vitesse du moteur
 */
void MotorDuino::motorTurnStepsPerSecond(unsigned int stepsPerSecond)
{
  digitalWrite(pinEnable, LOW);
  pwm(pinStep, (unsigned int)(stepsPerSecond), 0);  
}

/**
 * Faire tourner le moteur selon une vitesse donnee en tour par secondes
 *
 * \param float roundsPerSecond : vitesse du moteur
 */ 
void MotorDuino::motorTurnRoundsPerSecond(float roundsPerSecond)
{
  motorTurnStepsPerSecond((int)(roundsPerSecond * stepsPerRound));
}


/**
 * Methode pour arreter le moteur
 */
void MotorDuino::motorStop(){
  digitalWrite(pinEnable, HIGH);
  nopwm(pinStep);
}

/**
 * Setter pour modifier la frequence du moteur
 *
 * \param unsigned int speed : frequence a imposer
 */
void MotorDuino::setSpeed(unsigned int speed)
{
  frequence = speed;
}

/**
 * Setter pour modifier le nombre de pas du moteur
 *
 * \param unsigned int nbSteps : nombre de pas a imposer
 */
void MotorDuino::setNbSteps(unsigned int nbSteps)
{
  steps = nbSteps;  
}

/**
 * Setter pour établir l'adresse de sauvegarde de l'état du moteur
 *
 * \param int stateAddress
 */
void MotorDuino::setStateAddress(int stateAddress)
{
  this->stateAddress = stateAddress;
}

/**
 * Setter pour établir l'adresse de sauvegarde du nombre de pas du moteur
 *
 * \param int nbStepsAddress
 */
void MotorDuino::setNbStepsAddress(int nbStepsAddress)
{
  this->nbStepsAddress = nbStepsAddress;
}
		
/**
 * Sauvegarde de l etat du moteur dans la memoire
 * de la carte
 *
 * \param bool state : etat du moteur
 */
void MotorDuino::saveState(bool state){
  EEPROM.put(this->stateAddress, state);
}

/**
 * Consigne pour sauvegarder la valeur du nombre de pas du moteur dans la mémoire de la carte
 *
 * \param unsigned int nbSteps : nombre de pas a imposer
 */
void MotorDuino::saveNbSteps(unsigned int nbSteps)
{
  EEPROM.put(this->nbStepsAddress, nbSteps); 
}