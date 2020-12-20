/*
 * SerialComUT.cpp
 *
 *  Created on: 14.12.2020
 *      Author: aml
 */

#include "../SimplUnitTestFW.hpp"
#include "../SerialCom.hpp"
#include "SerialComUT.hpp"

namespace UT_SerialCom{

bool execUnitTests(string xmlFilename){

	// a unit a class
	UnitTest unit("SerialCom");

	// a unit for each method
	TestSuite TS01("initSerialCom");
	TestSuite TS02("openSerialCom");
	TestSuite TS03("closeSerialCom");
	TestSuite TS04("writeSerialCom");

	// add all test suits to the unit
	unit.addTestItem(&TS01);
	unit.addTestItem(&TS02);
	unit.addTestItem(&TS03);
	unit.addTestItem(&TS04);

	//
	// test cases for test suite TS01
	//
	// create the defined test cases for method initSerialCom to test suite TS01
	TC11 tc11("initSerialCom - init first");
	TC12 tc12("initSerialCom - init second time");
	TC13 tc13("initSerialCom - repeated init");

	// add specific test cases to test suite TS01
	TS01.addTestItem(&tc11);
	TS01.addTestItem(&tc12);
	TS01.addTestItem(&tc13);

	//
	//  test cases for test suite TS02
	//
	// create the defined test cases for method serialCom to test suite TS02
	TC21 tc21("openSerialCom - open first");
	TC22 tc22("openSerialCom - open second time");
	TC23 tc23("openSerialCom - repeated open");

	// add specific test cases to test suite TS02
	TS02.addTestItem(&tc21);
	TS02.addTestItem(&tc22);
	TS02.addTestItem(&tc23);

	//
	// test cases for test suite TS03
	//
	// create the defined test cases for method closeSerialCom to test suite TS03
	TC31 tc31("closeSerialCom - close a not open com");
	TC32 tc32("closeSerialCom - close a open com");
	TC33 tc33("closeSerialCom - repeated close without open again");

	// add specific test cases to test suite TS03
	TS03.addTestItem(&tc31);
	TS03.addTestItem(&tc32);
	TS03.addTestItem(&tc33);


	//
	// test cases for test suite TS04
	//
	// create the defined test cases for method closeSerialCom to test suite TS03
	TC41 tc41("writeSerialCom - write to closed serial com");
	TC42 tc42("writeSerialCom - closeSerialCom - write to open com");
	TC43 tc43("writeSerialCom - closeSerialCom - open, close and open write to serial com");

	// add specific test cases to test suite TS03
	TS04.addTestItem(&tc41);
	TS04.addTestItem(&tc42);
	TS04.addTestItem(&tc43);

	// execute unit tests
	unit.testExecution();
	unit.writeResultsToFile(xmlFilename);

	return unit.getResult();
}


bool TC41::testRun(){ // writeSerialCom - write to closed serial com
	cout << ".";
	try{
		unsigned char commandRead[2];
		commandRead[0] = 0x90;
		commandRead[1] = (unsigned char)3;
		unsigned char response[2];

		SerialCom b;
		b.initSerialCom("/dev/ttyACM0",9600);
		try{
			b.writeSerialCom(commandRead,2,response,2); // no exception expected
			return false;
		}catch(IException *e){
			return true;
		}catch(...){
			return false;
		}
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
	return false;
}
bool TC42::testRun(){ // closeSerialCom - write to open com
	cout << ".";
	try{
		unsigned char commandRead[2];
		commandRead[0] = 0x90;
		commandRead[1] = (unsigned char)3;
		unsigned char response[2];

		SerialCom b;
		b.openSerialCom();
		try{
			b.writeSerialCom(commandRead,2,response,2); // no exception expected
			return true;
		}catch(IException *e){
			return false;
		}catch(...){
			return false;
		}
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
	return false;
}
bool TC43::testRun(){ // closeSerialCom - open close and open write to serial com
	cout << ".";
	try{
		unsigned char commandRead[2];
		commandRead[0] = 0x90;
		commandRead[1] = (unsigned char)3;
		unsigned char response[2];

		SerialCom b;
		try{
			b.openSerialCom();
			b.closeSerialCom();
			b.openSerialCom();
			b.writeSerialCom(commandRead,2,response,2);
			return true;
		}catch(IException *e){
			return false;
		}catch(...){
			return false;
		}
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
	return false;
}


bool TC31::testRun(){ // closeSerialCom - close a not open com
	cout << ".";
	try{
		SerialCom b;
		b.initSerialCom("/dev/ttyACM0",9600);
		try{
			b.closeSerialCom(); // no exception expected
			return true;
		}catch(IException *e){
			return false;
		}catch(...){
			return false;
		}
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
	return false;
}
bool TC32::testRun(){ // closeSerialCom - close a open com
	cout << ".";
	try{
		SerialCom b;
		b.openSerialCom();
		try{
			b.closeSerialCom(); // no exception expected
			return true;
		}catch(IException *e){
			return false;
		}catch(...){
			return false;
		}
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
}
bool TC33::testRun(){ // closeSerialCom - repeated close without open again
	cout << ".";
	try{
		SerialCom b;
		try{
			for(int i=0; i < 32; i++){
				b.openSerialCom();
				b.closeSerialCom();
			}
			return true;
		}catch(IException *e){
			return false;
		}catch(...){
			return false;
		}
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
	return false;
}


bool TC13::testRun(){ // initSerialCom - repeated init
	cout << ".";
	try{
		SerialCom *c1 = new SerialCom();
		c1->initSerialCom("/dev/ttyACM0",9600);
		delete c1;

		SerialCom *c2 = new SerialCom();
		c1->initSerialCom("/dev/ttyACM0",9600);
		delete c2;

		return true;
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
	return false;
};

bool TC12::testRun(){ // initSerialCom - second
	cout << ".";
	try{
		SerialCom b;
		b.initSerialCom("/dev/ttyACM0",9600);
		try{
			b.initSerialCom("/dev/ttyACM1",9600); // no exceptions expected
			return true;
		}catch(IException *e){
			return false;
		}catch(...){
			return false;
		}
	}catch(IException *e){
		false;
	}catch(...){
		false;
	}
	return false;
};

bool TC11::testRun(){ // initSerialCom - open first
	cout << ".";
	try{
		SerialCom b;
		try{
			b.initSerialCom("/dev/ttyACM0",9600); // no exceptions expected
			return true;
		}catch(IException *e){
			return false;
		}catch(...){
			return false;
		}
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
	return false;
};


bool TC23::testRun(){ // openSerialCom - repeated open
	cout << ".";
	try{
		SerialCom *c1 = new SerialCom();
		c1->openSerialCom();
		int portNmbC1 = c1->getPort();
		delete c1;

		SerialCom *c2 = new SerialCom();
		c1->openSerialCom();
		int portNmbC2 = c2->getPort();
		delete c2;

		if(portNmbC1 != portNmbC2){
			return false;
		}
		return true;
	}catch(IException *e){
		;
	}catch(...){
		;
	}
	return false;
};

bool TC22::testRun(){ // "openSerialCom - second
	cout << ".";
	try{
		SerialCom b;
		b.openSerialCom();
		try{
			b.openSerialCom();
		}catch(IException *e){
			return true;
		}catch(...){
			return false;
		}
	}catch(IException *e){
		;
	}catch(...){
		;
	}
	return false;
};

bool TC21::testRun(){ // "openSerialCom - open first
	cout << ".";
	try{
		SerialCom b;
		b.openSerialCom();
		try{
			b.openSerialCom(); // must throw a ExceptionSerialCom
		}catch(IException *e){
			return true;
		}catch(...){
			return false;
		}
	}catch(IException *e){
		;
	}catch(...){
		;
	}
	return false;
};


} // ende namespace UT_SerialCom
