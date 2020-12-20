/*
 * ServoMotorBase.hpp
 *
 *  Created on: 20.12.2020
 *      Author: aml
 */

#ifndef SERVOMOTORBASE_HPP_
#define SERVOMOTORBASE_HPP_



#include "../SimplUnitTestFW.hpp"


namespace UT_ServoMotorBase{

void execUnitTests();

class TC71 : public TestCase{
	TC71() : TestCase(){};
public:
	TC71(string s = string("constructor - with no communication channel")) : TestCase(s){};
	virtual bool testRun(); // constructor - with no communication channel
};

class TC72 : public TestCase{
	TC72() : TestCase(){};
public:
	TC72(string s = string("constructor - negative servo motor nmb")) : TestCase(s){};
	virtual bool testRun(); // constructor - negative servo motor nmb
};

class TC73 : public TestCase{
	TC73() : TestCase(){};
public:
	TC73(string s = string("constructor - negative neutral position values")) : TestCase(s){};
	virtual bool testRun(); // constructor - negative neutral position values
};

class TC74 : public TestCase{
	TC74() : TestCase(){};
public:
	TC74(string s = string("constructor - non positive delta position values")) : TestCase(s){};
	virtual bool testRun(); // constructor - non positive delta position values
};

class TC75 : public TestCase{
	TC75() : TestCase(){};
public:
	TC75(string s = string("constructor - non matching neutral and delta values")) : TestCase(s){};
	virtual bool testRun(); // constructor - non matching neutral and delta values
};






class TC61 : public TestCase{
	TC61() : TestCase(){};
public:
	TC61(string s = string("getServoNumber - with open communication channel")) : TestCase(s){};
	virtual bool testRun(); // getServoNumber - with open communication channel
};

class TC62 : public TestCase{
	TC62() : TestCase(){};
public:
	TC62(string s = string("getServoNumber - having closed communication channel")) : TestCase(s){};
	virtual bool testRun(); // getServoNumber - having closed communication channel
};




class TC51 : public TestCase{
	TC51() : TestCase(){};
public:
	TC51(string s = string("getMaxPosInAbs - having closed communication channel")) : TestCase(s){};
	virtual bool testRun(); // getMaxPosInAbs - having closed communication channel
};

class TC52 : public TestCase{
	TC52() : TestCase(){};
public:
	TC52(string s = string("getMaxPosInAbs - with no communication channel")) : TestCase(s){};
	virtual bool testRun(); // getMaxPosInAbs - with no communication channel
};



class TC41 : public TestCase{
	TC41() : TestCase(){};
public:
	TC41(string s = string("getMidPosInAbs - having closed communication channel")) : TestCase(s){};
	virtual bool testRun(); // getMidPosInAbs - having closed communication channel
};

class TC42 : public TestCase{
	TC42() : TestCase(){};
public:
	TC42(string s = string("getMidPosInAbs - with no communication channel")) : TestCase(s){};
	virtual bool testRun(); // getMidPosInAbs - with no communication channel
};




class TC31 : public TestCase{
	TC31() : TestCase(){};
public:
	TC31(string s = string("getMinPosInAbs - having closed communication channel")) : TestCase(s){};
	virtual bool testRun(); // getMinPosInAbs - having closed communication channel
};

class TC32 : public TestCase{
	TC32() : TestCase(){};
public:
	TC32(string s = string("getMinPosInAbs - with no communication channel")) : TestCase(s){};
	virtual bool testRun(); // getMinPosInAbs - with no communication channel
};




class TC21 : public TestCase{
	TC21() : TestCase(){};
public:
	TC21(string s = string("getPositionInAbs - having closed communication channel")) : TestCase(s){};
	virtual bool testRun(); // getPositionInAbs - having closed communication channel
};

class TC22 : public TestCase{
	TC22() : TestCase(){};
public:
	TC22(string s = string("getPositionInAbs - with no communication channel")) : TestCase(s){};
	virtual bool testRun(); // getPositionInAbs - with no communication channel
};


class TC23 : public TestCase{
	TC23() : TestCase(){};
public:
	TC23(string s = string("getPositionInAbs - with open communication channel")) : TestCase(s){};
	virtual bool testRun(); // getPositionInAbs - with open communication channel
};









class TC11 : public TestCase{
	TC11() : TestCase(){};
public:
	TC11(string s = string("setPositionInAbs - having closed communication channel")) : TestCase(s){};
	virtual bool testRun(); // setPositionInAbs - having closed communication channel
};

class TC12 : public TestCase{
	TC12() : TestCase(){};
public:
	TC12(string s = string("setPositionInAbs - with no communication channel")) : TestCase(s){};
	virtual bool testRun(); // setPositionInAbs - with no communication channel
};


class TC13 : public TestCase{
	TC13() : TestCase(){};
public:
	TC13(string s = string("setPositionInAbs - with open communication channel")) : TestCase(s){};
	virtual bool testRun(); // setPositionInAbs - with open communication channel
};




class TC14 : public TestCase{
	TC14() : TestCase(){};
public:
	TC14(string s = string("setPositionInAbs - check the set value within its limits")) : TestCase(s){};
	virtual bool testRun(); // setPositionInAbs - check the set value within its limits
};

class TC15 : public TestCase{
	TC15() : TestCase(){};
public:
	TC15(string s = string("setPositionInAbs - try to set pos value larger then max.")) : TestCase(s){};
	virtual bool testRun(); // setPositionInAbs - try to set pos value larger then max.
};

class TC16 : public TestCase{
	TC16() : TestCase(){};
public:
	TC16(string s = string("setPositionInAbs - try to set pos value smaller then min.")) : TestCase(s){};
	virtual bool testRun(); // setPositionInAbs - try to set pos value smaller then min.
};



} // ende namespace UT_ServoMotorBase


#endif /* SERVOMOTORBASE_HPP_ */