/*
 * PololuUT.hpp
 *
 *  Created on: 19.12.2020
 *      Author: ubuntu
 */

#ifndef UNITTESTS_POLOLUUT_HPP_
#define UNITTESTS_POLOLUUT_HPP_


#include "../SimplUnitTestFW.hpp"

namespace UT_Pololu{

bool execUnitTests(string xmlFilename);


class TC61 : public TestCase{
	TC61() : TestCase(){};
public:
	TC61(string s = string("getErrors - call with closed communication channel")) : TestCase(s){};
	virtual bool testRun(); // getErrors - call with closed communication channel
};


class TC51 : public TestCase{
	TC51() : TestCase(){};
public:
	TC51(string s = string("constructor - call without parameter")) : TestCase(s){};
	virtual bool testRun(); // constructor - call without parameter
};


class TC11 : public TestCase{
	TC11() : TestCase(){};
public:
	TC11(string s = string("initConnection - init first")) : TestCase(s){};
	virtual bool testRun(); // initConnection - init first
};

class TC12 : public TestCase{
	TC12() : TestCase(){};
public:
	TC12(string s = string("initConnection - init second time")) : TestCase(s){};
	virtual bool testRun(); // initConnection - init second time
};


class TC13 : public TestCase{
	TC13() : TestCase(){};
public:
	TC13(string s = string("initConnection - repeated init")) : TestCase(s){};
	virtual bool testRun(); // initConnection - repeated init
};



class TC21 : public TestCase{
	TC21() : TestCase(){};
public:
	TC21(string s = string("openConnection - open first")) : TestCase(s){};
	virtual bool testRun(); // openConnection - open first
};

class TC22 : public TestCase{
	TC22() : TestCase(){};
public:
	TC22(string s = string("openConnection - init open time")) : TestCase(s){};
	virtual bool testRun(); // openConnection - init open time
};


class TC23 : public TestCase{
	TC23() : TestCase(){};
public:
	TC23(string s = string("openConnection - repeated open")) : TestCase(s){};
	virtual bool testRun(); // openConnection - repeated open
};


class TC24 : public TestCase{
	TC24() : TestCase(){};
public:
	TC24(string s = string("openConnection - try to open wrong channel")) : TestCase(s){};
	virtual bool testRun(); // openConnection - try to repeated open
};


class TC31 : public TestCase{
	TC31() : TestCase(){};
public:
	TC31(string s = string("closeConnection - repeated close")) : TestCase(s){};
	virtual bool testRun(); // closeConnection - repeated close
};

class TC32 : public TestCase{
	TC32() : TestCase(){};
public:
	TC32(string s = string("closeConnection - close before open")) : TestCase(s){};
	virtual bool testRun(); // closeConnection - close before open
};


class TC41 : public TestCase{
	TC41() : TestCase(){};
public:
	TC41(string s = string("getMovingState - request after init and before open")) : TestCase(s){};
	virtual bool testRun(); // getMovingState - request after init and before open
};


class TC42 : public TestCase{
	TC42() : TestCase(){};
public:
	TC42(string s = string("getMovingState - request after open")) : TestCase(s){};
	virtual bool testRun(); // getMovingState - request after open
};


class TC43 : public TestCase{
	TC43() : TestCase(){};
public:
	TC43(string s = string("getMovingState - request  after close")) : TestCase(s){};
	virtual bool testRun(); // getMovingState - request  after close
};


class TC44 : public TestCase{
	TC44() : TestCase(){};
public:
	TC44(string s = string("getMovingState - request after close and open")) : TestCase(s){};
	virtual bool testRun(); // getMovingState - request after close and open
};

} // ende namespace UT_Pololu


#endif /* UNITTESTS_POLOLUUT_HPP_ */
