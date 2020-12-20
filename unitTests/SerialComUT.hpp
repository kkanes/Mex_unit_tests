/*
 * SerialComUT.hpp
 *
 *  Created on: 14.12.2020
 *      Author: aml
 */

#ifndef SERIALCOMUT_HPP_
#define SERIALCOMUT_HPP_

#include "../SimplUnitTestFW.hpp"


namespace UT_SerialCom{

bool execUnitTests(string xmlFilename);



class TC41 : public TestCase{
	TC41() : TestCase(){};
public:
	TC41(string s = string("writeSerialCom - write to closed serial com")) : TestCase(s){};
	virtual bool testRun(); // writeSerialCom - write to closed serial com
};

class TC42 : public TestCase{
	TC42() : TestCase(){};
public:
	TC42(string s = string("closeSerialCom - write to open com")) : TestCase(s){};
	virtual bool testRun(); // closeSerialCom - write to open com
};

class TC43 : public TestCase{
	TC43() : TestCase(){};
public:
	TC43(string s = string("closeSerialCom - open close and open write to serial com")) : TestCase(s){};
	virtual bool testRun(); // closeSerialCom - open close and open write to serial com
};






class TC31 : public TestCase{
	TC31() : TestCase(){};
public:
	TC31(string s = string("closeSerialCom - close a not open com")) : TestCase(s){};
	virtual bool testRun(); // closeSerialCom - close a not open com
};

class TC32 : public TestCase{
	TC32() : TestCase(){};
public:
	TC32(string s = string("closeSerialCom - close a open com")) : TestCase(s){};
	virtual bool testRun(); // closeSerialCom - close a open com
};


class TC33 : public TestCase{
	TC33() : TestCase(){};
public:
	TC33(string s = string("closeSerialCom - repeated close without open again")) : TestCase(s){};
	virtual bool testRun(); // closeSerialCom - repeated close without open again
};



class TC11 : public TestCase{
	TC11() : TestCase(){};
public:
	TC11(string s = string("initSerialCom - init first")) : TestCase(s){};
	virtual bool testRun(); // initSerialCom - init first
};

class TC12 : public TestCase{
	TC12() : TestCase(){};
public:
	TC12(string s = string("initSerialCom - init second")) : TestCase(s){};
	virtual bool testRun(); // initSerialCom - init second
};


class TC13 : public TestCase{
	TC13() : TestCase(){};
public:
	TC13(string s = string("initSerialCom - repeated init")) : TestCase(s){};
	virtual bool testRun(); // initSerialCom - repeated init
};




class TC21 : public TestCase{
	TC21() : TestCase(){};
public:
	TC21(string s = string("openSerialCom - open first")) : TestCase(s){};
	virtual bool testRun(); // "openSerialCom - open first
};

class TC22 : public TestCase{
	TC22() : TestCase(){};
public:
	TC22(string s = string("openSerialCom - open second")) : TestCase(s){};
	virtual bool testRun(); // "openSerialCom - second
};


class TC23 : public TestCase{
	TC23() : TestCase(){};
public:
	TC23(string s = string("openSerialCom - repeated open")) : TestCase(s){};
	virtual bool testRun(); // "openSerialCom - repeated open
};


} // namespace UT_SerialCom

#endif /* SERIALCOMUT_HPP_ */
