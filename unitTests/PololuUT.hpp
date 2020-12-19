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

void execUnitTests();


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





} // ende namespace UT_Pololu


#endif /* UNITTESTS_POLOLUUT_HPP_ */
