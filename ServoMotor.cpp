//============================================================================
// Name        : ServoMotor.cpp
// Author      : Willi Penner
//
// Description : ServoMotor source file. It contains the definition of the
//               functions of the ServoMotor class.
//============================================================================
#include "ServoMotor.hpp"
#include "Pololu.hpp"
#include <iostream>
#include <sstream>
#include <cmath>

/** \brief ServoMotor class constructor. An object of the ServoMotor type must be initiated via the constructor.
 *
 * 	\param servo = is the slot number on the controller board to which the servo is connected
 *  \param startingPosition = is the center position of the servo motor (must be determined in the Pololu Maestro Control Center)
 *  \param delta = is the range of motion that the servo can reach from the center position
 *  \param *connection = is a pointer to the Pololu object for the serial connection
 *
 * */
ServoMotor::ServoMotor(unsigned short servo, unsigned short startingPosition, unsigned short delta, Pololu *connection){
	servoNumber_ = servo;
	startingPosition_ = startingPosition;
	delta_ = delta;
	connection_ = connection;
}

/** \brief Returns the port to which the servo is connected to the controller board.
 *
 *  \return The return value is the servoNumber+1 because the internal counting of the controller starts at 0.
 *
 */
unsigned short ServoMotor::getServoNumber(){
	return servoNumber_;
}

/** \brief Returns the minimum position the servo is able to reach.
 *
 *  \return The return value is the set startingPosition minus the set delta
 *
 */
unsigned short ServoMotor::getMinPosInAbs (){
	return startingPosition_ - delta_ ;
}

/** \brief Returns the center position of the servo.
 *
 *  \return The return value is the set startingPosition.
 *
 */
unsigned short ServoMotor::getMidPosInAbs (){
	return startingPosition_;
}

/** \brief Returns the maximum position the servo is able to reach.
 *
 *  \return The return value is the set startingPosition plus the set delta.
 *
 */
unsigned short ServoMotor::getMaxPosInAbs (){
	return startingPosition_ + delta_ ;
}

/** \brief Function causes the servo to move to a specific new position (position
 *  is specified as an absolute value in a range from 5860 +- 3600).
 *
 *  \param newPosition as an absolut value
 *
 *  \return The return value is the return value of the setPosition funktion of the Pololu object.
 */
unsigned short ServoMotor::setPositionInAbs(unsigned short newPosition){
	if (newPosition > (startingPosition_ + delta_) || newPosition < (startingPosition_ - delta_)){
		throw std::string("ServoMotor::setPositionInAbs: Abs position is out of range (startingPosition +- delta).");
	}else{
		return connection_->setPosition(servoNumber_, newPosition);
	}
}

/** \brief Function causes the servo to move to a specific new position (position is set with a value between -90 and 90 degrees).
 *
 *  \param newPosition in degrees
 *
 *  \return The return value is the return value of the setPosition funktion of the Pololu object.
 */
short ServoMotor::setPositionInDeg(short newPosition){
	if (newPosition > maxDeg || newPosition < -maxDeg){
		throw std::string("ServoMotor::setPositionInDeg: Degree is out of range (-90 - 90).");
	}else{
		return connection_->setPosition(servoNumber_, startingPosition_ + newPosition * conFactorDegToPos * conFactorMyToPos);
	}
}

/** \brief Function causes the servo to move to a specific new position (position is set with a radiant between -PI/2 and PI/2).
 *
 *  \param newPosition as radiant
 *
 *  \return The return value is the return value of the setPosition funktion of the Pololu object.
 */
float ServoMotor::setPositionInRad(float newPosition){
	// Since float numbers cannot be compared, the radians are converted to an int. The factor 100 sets the accuracy to 2 digits after the decimal point.
	if ((int)(100 * newPosition) > (int)(100 * (maxRad)) || (int)(100 * newPosition) < (int)(100 * (-maxRad))){
		throw std::string("ServoMotor::setPositionInRad: Radiant is out of range (-PI/2 - +PI/2).");
	}else{
		// first the neu radiant position is converted to degree (newPosition * 180 / M_PI)
		return connection_->setPosition(servoNumber_, (startingPosition_ + (newPosition * 180 / M_PI) * conFactorDegToPos * conFactorMyToPos));
	}
}

/** \brief Sets the speed at which the servo should move (speed range is between 1 and 255)
 *
 *  \param newSpeed = Speed value (1 is (0.25 microseconds) / (10 milliseconds),
 *  255 is (63,75 microseconds) / (10 milliseconds))
 *
 *  \return The return value is the return value of the setSpeed funktion of the Pololu object.
 */
unsigned short ServoMotor::setSpeed(unsigned short newSpeed){
	if (newSpeed > maxSpeed || newSpeed < minSpeed){
		throw std::string("ServoMotor::setSpeed: Speed is out of range (1 - 255).");
	}else{
		return connection_->setSpeed(servoNumber_, newSpeed);
	}
}

/** \brief Sets the acceleration with which the set speed should be reached (acceleration range is between 1 and 255)
 *
 *  \param newAcceleration = Acceleration value (1 is (0.25 microseconds) / (10 milliseconds) / (80 milliseconds),
 *  255 is (63,75 microseconds) / (10 milliseconds) / (80 milliseconds))
 *
 *  \return The return value is the return value of the setAcceleration funktion of the Pololu object.
 */
unsigned short ServoMotor::setAcceleration(unsigned short newAcceleration){
	if (newAcceleration > maxAcceleration || newAcceleration < minAcceleration){
		throw std::string("ServoMotor::setAcceleration: Acceleration is out of range (1 - 255).");
	}else{
		return connection_->setAcceleration(servoNumber_, newAcceleration);
	}
}

/** \brief Returns the position of the servo as absolute value.
 *
 *  \return The return value is the return value of the getPosition function of the Pololu object.
 *
 */
unsigned short ServoMotor::getPositionInAbs(){
	try{
		unsigned short v = connection_->getPosition(servoNumber_);
		return v;
	}catch(ExceptionSerialCom *e){
		stringstream  ss;
		ss << "getPositionInAbs:: Error while execution getPositon for servo motor '";
		ss << servoNumber_ << "'.";
		throw new ExceptionServoMotor(e->getMsg() + ss.str());
	}catch(ExceptionPololu *e){
		stringstream  ss;
		ss << "getPositionInAbs:: Error while execution getPositon for servo motor '";
		ss << servoNumber_ << "'.";
		throw new ExceptionServoMotor(e->getMsg() + ss.str());
	}catch(string msg){
		stringstream  ss;
		ss << "getPositionInAbs:: string error while execution getPositon for servo motor '";
		ss << servoNumber_ << "'.";
		throw new ExceptionServoMotor(msg + ss.str());
	}catch(...){
		stringstream  ss;
		ss << "getPositionInAbs:: Unknown Error while execution getPositon for servo motor '";
		ss << servoNumber_ << "'.";
		throw new ExceptionServoMotor(ss.str());
	}
}

/** \brief Returns the position of the servo in degrees.
 *
 *  \return The return value is the return value of the getPosition function of the Pololu object converted into degrees.
 *
 */
short ServoMotor::getPositionInDeg(){
	return (connection_->getPosition(servoNumber_) / conFactorMyToPos - startingPosition_) / conFactorDegToPos;
}

/** \brief Returns the position of the servo as radiant.
 *
 *  \return The return value is the return value of the getPosition function of the Pololu object converted into radiant.
 *
 */
float ServoMotor::getPositionInRad(){
	return (connection_->getPosition(servoNumber_) / conFactorMyToPos - startingPosition_) * M_PI / conFactorDegToPos / 180;
}

/** \brief Shows which settings have to be made in the Pololu Maestro Control Center for the servo,
 *  based on the starting position and the delta for the specific servo.
 */
void ServoMotor::showPololuValues (unsigned short& min, unsigned short& mid, unsigned short& max){
	min = (unsigned short)((startingPosition_ - delta_) / conFactorMyToPos);
	max = (startingPosition_ + delta_) / conFactorMyToPos;
	mid = (startingPosition_) / conFactorMyToPos;
}







/***
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */



ServoMotorPololuBase::ServoMotorPololuBase(unsigned short servoID,
										   unsigned short neutralPos,
										   unsigned short delta,
										   IPololu  *pololuController){

	if(servoNmb_ < 0){
		string msg("ServoMotorPololuBase::servo number is negative.");
		throw new ExceptionServoMotorBase(msg);
	}
	servoNmb_ = servoID;

	if(neutralPosition_ < 0){
		string msg("ServoMotorPololuBase:: neutral position is negative.");
		throw new ExceptionServoMotorBase(msg);
	}
	neutralPosition_ = neutralPos;

	if(neutralPosition_ <= delta){
		string msg("ServoMotorPololuBase:: delta range is larger than neutral position.");
		throw new ExceptionServoMotorBase(msg);
	}
	delta_ = delta;

	if(pololuController == NULL){
		string msg("ServoMotorPololuBase:: controller reference is NULL pointer.");
		throw new ExceptionServoMotorBase(msg);
	}
	pololuCtrl_ = pololuController;

	return;
}



ServoMotorPololuBase::~ServoMotorPololuBase(){
	pololuCtrl_ = NULL;
	return;
};

unsigned short ServoMotorPololuBase::getServoNumber(){return servoNmb_;};

unsigned short ServoMotorPololuBase::getMinPosInAbs(){return (neutralPosition_ - delta_);};

unsigned short ServoMotorPololuBase::getMidPosInAbs(){return  neutralPosition_;};

unsigned short ServoMotorPololuBase::getMaxPosInAbs(){return (neutralPosition_ + delta_);};

unsigned short ServoMotorPololuBase::setPositionInAbs(unsigned short newPosition){
	if((newPosition < this->getMinPosInAbs()) ||
			(newPosition > this->getMaxPosInAbs())){
		string msg("setPositionInDeg:: position value is out of range.");
		throw new ExceptionServoMotorBase(msg);
	}


	try{
		pololuCtrl_->setPosition(servoNmb_,newPosition);
	}catch(IException *e){
		string msg("setPositionInAbs:: error while trying to set a new position:");
		msg += e->getMsg();
		throw new ExceptionServoMotorBase(msg);
	}catch(...){
		string msg("setPositionInAbs:: error while trying to set a new position.");
		throw new ExceptionServoMotorBase(msg);
	}

	try{
		return (pololuCtrl_->getPosition(servoNmb_));
	}catch(IException *e){
		string msg("setPositionInAbs:: error while trying to set a new position:");
		msg += e->getMsg();
		throw new ExceptionServoMotorBase(msg);
	}catch(...){
		string msg("setPositionInAbs:: error while trying to set a new position.");
		throw new ExceptionServoMotorBase(msg);
	}

};

unsigned short ServoMotorPololuBase::getPositionInAbs(){
	try{
		return (pololuCtrl_->getPosition(servoNmb_));
	}catch(IException *e){
		string msg("setPositionInAbs:: error while trying to set a new position:");
		msg += e->getMsg();
		throw new ExceptionServoMotorBase(msg);
	}catch(...){
		string msg("setPositionInAbs:: error while trying to set a new position.");
		throw new ExceptionServoMotorBase(msg);
	}
};



/**
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */

/**
 *
 * \brief Set the maximal speed of the servo motor movement.
 *
 * \param newSpeed unsigned short. Value 1 represents the lowest speed.
 *               Value 255 and 0 represent the maximal speed.
 *
 *
 *
 */
unsigned short ServoMotorPololuBaseAdv::setSpeed(unsigned short newSpeed){
	if(newSpeed > 255){
		newSpeed = 255;
	}
	try{
		pololuCtrl_->setSpeed(servoNmb_, newSpeed);
		return newSpeed;
	}catch(IException *e){
		string msg("setPositionInAbs:: error while trying to set a new speed value:");
		msg += e->getMsg();
		throw new ExceptionServoMotorBaseAdv(msg);
	}catch(...){
		string msg("setPositionInAbs:: unknown error while trying to set a new speed value.");
		throw new ExceptionServoMotorBaseAdv(msg);
	}
}

/**
 *
 * \brief Set the maximal acceleration of the servo motor movement.
 *
 * \param newSpeed unsigned short. Value 1 represents the lowest speed.
 *               Value 255 and 0 represent the maximal speed.
 *
 *
 *
 */
unsigned short ServoMotorPololuBaseAdv::setAcceleration(unsigned short newAcceleration){
	if(newAcceleration > 255){
		newAcceleration = 255;
	}
	try{
		pololuCtrl_->setSpeed(servoNmb_, newAcceleration);
		return newAcceleration;
	}catch(IException *e){
		string msg("setPositionInAbs:: error while trying to set a new acceleration value:");
		msg += e->getMsg();
		throw new ExceptionServoMotorBaseAdv(msg);
	}catch(...){
		string msg("setPositionInAbs:: unknown error while trying to set a new acceleration value.");
		throw new ExceptionServoMotorBaseAdv(msg);
	}
}


/**
 *
 *
 *
 *
 *
 *
 *
 *
 */

void  ServoMotorPololu::setMinMaxDegree(short minDegree, short maxDegree){
	if(maxDegree <= minDegree){
		string msg("setMinMaxDegree:: min degree is larger or equal than max degree.");
		throw new ExceptionServoMotor(msg);
	}
	minDeg_ = minDegree;
	maxDeg_ = maxDegree;
	return;
}

void  ServoMotorPololu::setMinMaxRadian(float minRadian, float maxRadian){
	if(maxRadian <= minRadian){
		string msg("setMinMaxRadian:: min value radian is larger or equal to max value radian.");
		throw new ExceptionServoMotor(msg);
	}

	try{
		this->setMinMaxDegree(this->rad2deg(minRadian),this->rad2deg(maxRadian));
	}catch(IException *e){
		string msg("setMinMaxRadian:: error while setting max and min values in radian");
		msg += e->getMsg();
		throw new ExceptionServoMotor(msg);
	}catch(...){
		string msg("setMinMaxRadian:: unknown error while setting max and min values in radian");
		throw new ExceptionServoMotor(msg);
	}

	return;
}

short ServoMotorPololu::setPositionInDeg(short newPosition){
	short actPos = newPosition;
	if((actPos < minDeg_) || (actPos > maxDeg_)){
		string msg("setPositionInDeg:: degree /radiant value is out of range.");
		throw new ExceptionServoMotor(msg);
	}

	try{
		pololuCtrl_->setPosition(servoNmb_,this->mapDegValue2PosValue(actPos));
	}catch(IException *e){
		string msg("setPositionInDeg:: error while trying to set and move to new position.");
		msg += e->getMsg();
		throw new ExceptionServoMotor(msg);
	}catch(...){
		string msg("setPositionInDeg:: unknown error while trying to set and move to new position.");
		throw new ExceptionServoMotor(msg);
	}

	return actPos;
};

float ServoMotorPololu::setPositionInRad(float newPosition){
	short deg;
	try{
		deg = this->setPositionInDeg(this->rad2deg(newPosition));
	}catch(IException *e){
		string msg("setPositionInRad:: error while trying to set and move to new position.");
		msg += e->getMsg();
		throw new ExceptionServoMotor(msg);
	}catch(...){
		string msg("setPositionInRad:: unknown error while trying to set and move to new position.");
		throw new ExceptionServoMotor(msg);
	};
	return (this->deg2rad(deg));
};

short ServoMotorPololu::getPositionInDeg(){
	short deg;
	unsigned short pos;
	try{
		pos = this->ServoMotorPololuBase::getPositionInAbs();
		deg = this->mapPosValue2DegValue(pos);
	}catch(IException *e){
		string msg("getPositionInDeg:: error while trying to read servo motor position.");
		msg += e->getMsg();
		throw new ExceptionServoMotor(msg);
	}catch(...){
		string msg("getPositionInDeg:: unknown error while trying to read servo motor position.");
		throw new ExceptionServoMotor(msg);
	}

	return deg;
};

float ServoMotorPololu::getPositionInRad(){
	float rad;
	short deg;
	unsigned short pos;
	try{
		pos = this->ServoMotorPololuBase::getPositionInAbs();
		deg = this->mapPosValue2DegValue(pos);
		rad = this->deg2rad(deg);
	}catch(IException *e){
		string msg("getPositionInRad:: error while trying to read servo motor position.");
		msg += e->getMsg();
		throw new ExceptionServoMotor(msg);
	}catch(...){
		string msg("getPositionInRad:: unknown error while trying to read servo motor position.");
		throw new ExceptionServoMotor(msg);
	}
	return rad;
};

void ServoMotorPololu::showPololuValues (unsigned short& min, unsigned short& mid, unsigned short& max){
	mid = neutralPosition_;
	max = mid + delta_;
	min = mid - delta_;
	return;
};

float ServoMotorPololu::deg2rad(unsigned short x){
	return (((float)x)*M_PI / 180.0);
};

short ServoMotorPololu::rad2deg(float x){
	short d = (short) (((((float)x)*180.0) / M_PI) + 0.5);
	return d;
};

unsigned short ServoMotorPololu::mapDegValue2PosValue(short d){
	float fact, pos;
	unsigned short servoPos;

	fact = ((float) this->maxDeg_) - ((float) this->minDeg_);
	fact = ( 2.0 * ((float) this->delta_) ) / fact;

	pos  =  fact * ( ((float) d) - ((float) this->minDeg_) );
	pos  = pos + ((float) (this->neutralPosition_ - this->delta_));

	servoPos = (unsigned short) pos;
	return (servoPos);
};

short ServoMotorPololu::mapPosValue2DegValue(unsigned short p){
	float fact, pos;
	short deg;

	fact = ((float) this->maxDeg_) - ((float) this->minDeg_);
	fact = fact / (2.0*((float) this->delta_));

	pos = fact * ( ((float)  p) - ((float) (neutralPosition_ - delta_)) );
	pos = pos + ((float) minDeg_);

	deg = (short) pos;
	return (deg);
};


