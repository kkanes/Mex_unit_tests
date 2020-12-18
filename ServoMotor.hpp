//============================================================================
// Name        : ServoMotor.hpp
// Author      : Willi Penner / martin huelse (martin.huelse@fh-bielefeld.de)
//
// Description : Header file contains the interface IServoMotor and the class
//               ServoMotor with its functions to control a specific servo.
//============================================================================
#include "Pololu.hpp"
#include <cmath>

#ifndef SERVOMOTOR_HPP_
#define SERVOMOTOR_HPP_


/**
 *
 * \class IServoMotorBase
 *
 * \brief Interface class that specifies the basic
 * functionality of object that initializes and
 * controls a servo motor.
 *
 * The positions of the servo motor are defined
 * by positions values (given in units).
 *
 *
 */
class IServoMotorBase{
public:
	virtual ~IServoMotorBase(){};

	/**
	 *
	 * \brief Delivers the ID of the servo motor instance.
	 * This ID might related to certain connectors of the
	 * board / HW used to control the servo motor.
	 * This must be specified in the actual implementation
	 * of this inteface by the derived classes.
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
	virtual unsigned short getMinPosInAbs() = 0;

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
	virtual unsigned short getMidPosInAbs() = 0;

	/**
	 *
	 * \brief Delivers the maximal position value the servo motor
	 * can / shall move to.
	 *
	 *  \return unsigned short
	 *
	 */
	virtual unsigned short getMaxPosInAbs() = 0;

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
	 * \brief Delivers the position value (in units) the servo trageted at.
	 *
	 *  \return unsigned short.
	 *
	 */
	virtual unsigned short getPositionInAbs() = 0;

};

/**
 *
 * \class IServoMotoBaseAdv
 *
 * \brief Interface class that specifies additional
 * functionality with respect to set maximal speed
 * and acceleration.
 *
 *
 */
class IServoMotoBaseAdv : public IServoMotorBase{
public:
	virtual ~IServoMotoBaseAdv(){};

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
	virtual unsigned short setAcceleration(unsigned short newAcceleration) = 0;

};



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
 * Furthermore, implementation of this interface can also differe
 * because of the boards used to drive the servo motors.
 * These parameters (working area and units) must be specified / documented
 * in the derived classes that implement these methods.
 *
 */
class IServoMotor : public IServoMotoBaseAdv{
public:
	virtual ~IServoMotor(){};

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


class ServoMotorPololuBase : public IServoMotorBase{
public:

	/**
	 *
	 * \brief Parameterized constructor. In case of an error
	 * 			an exception is thrown.
	 *
	 *	\param servoID unsigned short. Index (>= 0) of the servo motor that
	 * 					identifies which slot / pin on the
	 * 					micro controller board the servo is
	 * 					connected with.
	 *
	 * 	\param neutralPos unsigned short. (neutralPos > 0) Neutral position of the servo,
	 * 					usually defined by an impulse of 1'500 micro seconds
	 * 					impulse length.
	 * 					The position value is usually given by impulse length per
	 * 					one micro seconds. Using the pololu micro-controller to
	 * 					control the servor motor the impulse length is given per
	 * 					units of 1/4 of a quarter of the micro-second.
	 * 					Therefore, position here is defined impulse length per
	 * 					one micro second per 1/4 micro second.
	 * 					Thus, position value = impulse lengths * 4 (units).
	 *					See Pololu manual for further explanations.
	 *
	 *	\param delta unsigned short. (delta < neutralPos) Defines the range of positions values,
	 * 					starting from the neutral positions +/- delta.
	 *
	 *
	 * 	\param *pololuController. Pointer to a pololu instance that controls the servo motors.
	 */
	ServoMotorPololuBase(unsigned short  servoID,
						 unsigned short  neutralPos,
						 unsigned short  delta,
						        IPololu *pololuController);
	~ServoMotorPololuBase();
	unsigned short getServoNumber();
	unsigned short getMinPosInAbs();
	unsigned short getMidPosInAbs();
	unsigned short getMaxPosInAbs();
	unsigned short setPositionInAbs(unsigned short newPosition);
	unsigned short getPositionInAbs();
protected:
	/**
	 *
	 * \var pololuCtrl_
	 *
	 * \brief Pointer to a API-object of the
	 * pololu controller (\ref class \IPololu).
	 */
	IPololu *pololuCtrl_ = NULL;


	/**
	 *
	 * \var servoNmb_
	 *
	 * \brief Index of the servo motor that
	 * identifies which slot / pin on the
	 * micro controller board the servo is
	 * connected with.
	 */
	unsigned int servoNmb_;

	/**
	 *
	 * \var neutralPosition_
	 *
	 * \brief Neutral position of the servo, usually defined by
	 * an impulse of 1'500 micro seconds impulse length.
	 * The position value is usually given by impulse length per
	 * one micro seconds. Using the pololu microcontroller to
	 * control the servor motor the impulse length is given per
	 * units of 1/4 of a quarter of the micro-second.
	 * Therefore, position here is defined impulse length per
	 * one micro second per 1/4 micro second.
	 * Thus, position value = impulse lengths * 4 (units).
	 *
	 * See Pololu manual for further explanations.
	 */
	unsigned short neutralPosition_;

	/**
	 *
	 * \var delta_
	 *
	 * \brief Defines the range of positions values.
	 * Starting from the neutral positions +/- delta.
	 *
	 */
	unsigned short delta_;

	ServoMotorPololuBase(){pololuCtrl_ = NULL;};
};


class ServoMotorPololuBaseAdv : public ServoMotorPololuBase, public IServoMotoBaseAdv{
public:
	ServoMotorPololuBaseAdv(){throw ExceptionPololu(string("NIY"));};
	~ServoMotorPololuBaseAdv(){throw ExceptionPololu(string("NIY"));};
	unsigned short setSpeed(unsigned short newSpeed){throw ExceptionPololu(string("NIY"));};
	unsigned short setAcceleration(unsigned short newAcceleration){throw ExceptionPololu(string("NIY"));};
};


class ServoMotorPololu : public ServoMotorPololuBaseAdv, public IServoMotor{
public:
	ServoMotorPololu(){throw ExceptionPololu(string("NIY"));};
	~ServoMotorPololu(){throw ExceptionPololu(string("NIY"));};
	short setPositionInDeg(short newPosition){throw ExceptionPololu(string("NIY"));};
	float setPositionInRad(float newPosition){throw ExceptionPololu(string("NIY"));};
	short getPositionInDeg(){throw ExceptionPololu(string("NIY"));};
	float getPositionInRad(){throw ExceptionPololu(string("NIY"));};
	void showPololuValues (unsigned short& min, unsigned short& mid, unsigned short& max){throw ExceptionPololu(string("NIY"));};
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
	unsigned short getMinPosInAbs();
	unsigned short getMidPosInAbs();
	unsigned short getMaxPosInAbs();
	unsigned short setPositionInAbs(unsigned short newPosition);
	short setPositionInDeg(short newPosition);
	float setPositionInRad(float newPosition);
	unsigned short setSpeed(unsigned short newSpeed);
	unsigned short setAcceleration(unsigned short newAcceleration);
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
