//============================================================================
// Name        : ServoMotor.hpp
// Author      : Willi Penner
//
// Description : Headerfile contains the interface IServoMotor and the class
//               ServoMotor with its functions to control a specific servo.
//============================================================================
#include "Pololu.hpp"
#include <cmath>

#ifndef SERVOMOTOR_HPP_
#define SERVOMOTOR_HPP_

/**
 *
 *
 * \brief Interface to control a servo motor.
 * The interface provides the basic functions for the
 * control for a specific servo motor.
 *
 * Note, different types of servo motors have different specification
 * with respect to working range and the counting of position units
 * representing certain motor positions.
 * These parameters (working area and units) must be specified / documented
 * in the derived classes that implement these methods.
 *
 */
class IServoMotor {
public:
	virtual ~IServoMotor(){};


	/**
	 *
	 * \brief Delivers the connector number the servo is connected on
	 * the controller board.
	 *
	 *  \return unsigned int number of the connector of the servo
	 *  motor on the board.
	 *
	 */
	virtual unsigned short getServoNumber() = 0;

	/**
	 *
	 * \brief Delivers the minimal position value the servo
	 * motor can / shall move to.
	 *
	 *  \return unsigned short
	 *
	 */
	virtual unsigned short getMinPos() = 0;

	/**
	 *
	 * \brief Delivers the position value in units for the so called
	 * neutral position of a servo motor given in units.
	 * This position might specifically defined by the developer
	 * for specific servo motors.
	 *
	 *  \return unsigned short
	 *
	 */
	virtual unsigned short getMidPos() = 0;

	/**
	 *
	 * \brief Delivers the maximal position value the servo motor
	 * can / shall move to.
	 *
	 *  \return unsigned short
	 *
	 */
	virtual unsigned short getMaxPos() = 0;

	/**
	 *
	 *
	 * \brief Moves the servo motor to the given position.
	 *
	 *  \param newPosition unsigned short position value given
	 *                     in units.
	 *
	 *  \return unsigned short actual position set given in units.
	 */
	virtual unsigned short setPositionInAbs(unsigned short newPosition) = 0;

	/**
	 *
	 *
	 * \brief Moves the servo motor to the given position.
	 *
	 *  \param newPosition unsigned short position value given
	 *                     in degree.
	 *
	 *  \return unsigned short actual position set in degree.
	 */
	virtual short setPositionInDeg(short newPosition) = 0;

	/**
	 *
	 *
	 * \brief Moves the servo motor to the given position.
	 *
	 *  \param newPosition unsigned short position value given
	 *                     in radian.
	 *
	 *  \return unsigned short actual position set in radian
	 */
	virtual float setPositionInRad(float newPosition) = 0;


	/**
	 *
	 *  \brief Sets the maximal speed the servo shall move.
	 *
	 *  \param unsigned short newSpeed (the meaning of the values
	 *      has to be specified in the derived class.)
	 *
	 *  \return unsigned short actual speed value set.
	 */
	virtual unsigned short setSpeed(unsigned short newSpeed) = 0;

	/**
	 *
	 *  \brief Sets the maximal acceleration the servo shall move.
	 *
	 *  \param unsigned short newAcceleration (the meaning of the values
	 *      has to be specified in the derived class.)
	 *
	 *  \return unsigned short actual accelaration value set.
	 */
	virtual unsigned short setAccelaration(unsigned short newAcceleration) = 0;

	/**
	 *
	 *
	 * \brief Delivers the position value (in units) the servo trageted at.
	 *
	 *  \return unsigned short.
	 *
	 */
	virtual unsigned short getPositionInAbs() = 0;


	/**
	 *
	 *
	 * \brief  Delivers the position value (in degree) the servo trageted at.
	 *
	 *  \return unsigned short.
	 *
	 */
	virtual short getPositionInDeg() = 0;

	/**
	 *
	 *
	 * \brief Delivers the position value (in radian) the servo trageted at.
	 *
	 *  \return unsigned short.
	 *
	 */
	virtual float getPositionInRad() = 0;


	/**
	 *
	 *
	 * \brief
	 *
	 *  Shows which settings have to be made in the Pololu Maestro Control Center for the servo,
	 *  based on the starting position and the delta for the specific servo.
	 *  See Pololu manual for further explainations.
	 */
	virtual void showPololuValues (unsigned short& min, unsigned short& mid, unsigned short& max) = 0;
};

/** \brief Class for the ServoMotor object
 *
 *	\param servoNumber_ = Port to which the servo is connected on the controller
 *	\param startingPosition_ = The center position of the servo, this position is determined in the Pololu Maestro Control Center.
 *	\param delta_ = Range of values that the servo can turn left and right.
 *	\param *connection_ = Pointer to an object of the type Pololu for the serial connection.
 */
class ServoMotor : public IServoMotor{
private:
	const short maxDeg = 90;				//maximum degree allowed
	const float maxRad = M_PI/2;			//maximum radiant allowed, M_PI is the constant from <cmath> for the number Pi
	const unsigned short maxSpeed = 255;				//maximum value for the speed
	const unsigned short maxAcceleration = 255;      //maximum value for the acceleration
	const unsigned short minSpeed = 1;				//minimum value for the speed
	const unsigned short minAcceleration = 1;  //minimum value for the acceleration
	const unsigned short conFactorDegToPos = 10;	    //conversion factor from degrees to position
	const unsigned short conFactorMyToPos = 4;		//conversion factor to convert �s (position value of a servo) to position values
	unsigned short servoNumber_;
	unsigned short startingPosition_;	//startPosition is the center position of a servo, in most cases it is value of 6000 (1500�s * 4)
	unsigned short delta_;
	Pololu *connection_ = NULL;
public:
	/** \brief ServoMotor class constructor. An object of the ServoMotor type must be initiated via the constructor.
	 *
	 * 	\param servo = is the slot number on the controller board to which the servo is connected
	 *  \param startingPosition = is the center position of the servo motor (must be determined in the Pololu Maestro Control Center)
	 *  \param delta = is the range of motion that the servo can reach from the center position
	 *  \param *connection = is a pointer to the Pololu object for the serial connection
	 *
	 * */
	ServoMotor(unsigned short servo, unsigned short startingPosition, unsigned short delta, Pololu *connection);
	unsigned short getServoNumber();
	unsigned short getMinPos ();
	unsigned short getMidPos ();
	unsigned short getMaxPos ();
	unsigned short setPositionInAbs(unsigned short newPosition);
	short setPositionInDeg(short newPosition);
	float setPositionInRad(float newPosition);
	unsigned short setSpeed(unsigned short newSpeed);
	unsigned short setAccelaration(unsigned short newAcceleration);
	unsigned short getPositionInAbs();
	short getPositionInDeg();
	float getPositionInRad();
	void showPololuValues (unsigned short& min, unsigned short& mid, unsigned short& max);
};


/**
 *
 * \class ExceptionServerMotor
 *
 * \brief Implementation of the exception class for
 * class ServoMotor
 *
 */
class ExceptionServoMotor : public IException{
public:
	ExceptionServoMotor(string msg){
		msg_ = string("ExceptionServoMotor::") + msg;
	};
	string getMsg(){return msg_;}
protected:
	string msg_;
private:
	ExceptionServoMotor(){};
};


#endif /* SERVOMOTOR_HPP_ */
