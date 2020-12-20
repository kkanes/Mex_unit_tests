/*
 * PololuUT.cpp
 *
 *  Created on: 19.12.2020
 *      Author: ubuntu
 */


#include <string>
#include "../SimplUnitTestFW.hpp"
#include "../Pololu.hpp"
#include "PololuUT.hpp"

using namespace std;

namespace UT_Pololu{

bool execUnitTests(string xmlFilename){

	// a unit a class
	UnitTest unit("Pololu");

	// a unit for each method
	TestSuite TS01("initConnection");
	TestSuite TS02("openConnection");
	TestSuite TS03("closeConnection");
	TestSuite TS04("getMovingState");
	TestSuite TS05("constructor");
	TestSuite TS06("getErrors");

	// add all test suits to the unit
	unit.addTestItem(&TS01);
	unit.addTestItem(&TS02);
	unit.addTestItem(&TS03);
	unit.addTestItem(&TS04);
	unit.addTestItem(&TS05);
	unit.addTestItem(&TS06);

	//
	// test cases for test suite TS01
	//
	// create the defined test cases for method initSerialCom to test suite TS01
	TC11 tc11("initConnection - init first");
	TC12 tc12("initConnection - init second time");
	TC13 tc13("initConnection - repeated init");

	// add specific test cases to test suite TS01
	TS01.addTestItem(&tc11);
	TS01.addTestItem(&tc12);
	TS01.addTestItem(&tc13);



	//
	// test cases for test suite TS02
	//
	// create the defined test cases for method initSerialCom to test suite TS02
	TC21 tc21("openConnection - open first");
	TC22 tc22("openConnection - open second time");
	TC23 tc23("openConnection - repeated open");
	TC24 tc24("openConnection - try to open wrong channel");

	// add specific test cases to test suite TS02
	TS02.addTestItem(&tc21);
	TS02.addTestItem(&tc22);
	TS02.addTestItem(&tc23);
	TS02.addTestItem(&tc24);


	//
	// test cases for test suite TS03
	//
	// create the defined test cases for method initSerialCom to test suite TS03
	TC31 tc31("closeConnection - repeated close");
	TC32 tc32("closeConnection - close before open");

	// add specific test cases to test suite TS03
	TS03.addTestItem(&tc31);
	TS03.addTestItem(&tc32);



	//
	// test cases for test suite TS04
	//
	// create the defined test cases for method initSerialCom to test suite TS04
	TC41 tc41("getMovingState - request after init and before open");
	TC42 tc42("getMovingState - request before after init");
	TC43 tc43("getMovingState - request  after close");
	TC44 tc44("getMovingState - request after open");

	// add specific test cases to test suite TS04
	TS04.addTestItem(&tc41);
	TS04.addTestItem(&tc42);
	TS04.addTestItem(&tc43);
	TS04.addTestItem(&tc44);


	//
	// test cases for test suite TS05
	//
	// create the defined test cases for method initSerialCom to test suite TS05
	TC51 tc51("constructor - call without parameter");

	// add specific test cases to test suite TS05
	TS05.addTestItem(&tc51);


	//
	// test cases for test suite TS06
	//
	// create the defined test cases for method initSerialCom to test suite TS06
	TC61 tc61("getErrors - call with closed communication channel");

	// add specific test cases to test suite TS06
	TS06.addTestItem(&tc61);




	// execute unit tests
	unit.testExecution();
	unit.writeResultsToFile(xmlFilename);

	return unit.getResult();
}





bool TC61::testRun(){// getErrors - call with closed communication channel
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.getErrors();
		return false;
	}catch(IException *e){
		return true;
	}catch(...){
		return false;
	}
	return false;
}


bool TC51::testRun(){// constructor - call without parameter
	cout << ".";
	try{
		//Pololu p;
		return true;
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
	return false;
}


bool TC41::testRun(){// getMovingState - request after init and before open
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.getMovingState();
		return false;
	}catch(IException *e){
		return true;
	}catch(...){
		return false;
	}
	return false;
}

bool TC42::testRun(){// getMovingState - request after open
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.openConnection();
		p.getMovingState();
		return true;
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
	return false;
}

bool TC43::testRun(){// getMovingState - request  after close
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.openConnection();
		p.closeConnection();
		p.getMovingState();
		return false;
	}catch(IException *e){
		return true;
	}catch(...){
		return false;
	}
	return false;
}


bool TC44::testRun(){// getMovingState - request after close and open
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.openConnection();
		p.closeConnection();
		p.openConnection();
		p.getMovingState();
		return true;
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
	return false;
}






bool TC31::testRun(){ // closeConnection - repeated close
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.openConnection();
		p.closeConnection();
		p.closeConnection();
		p.closeConnection();
		return true;
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
	return false;
}

bool TC32::testRun(){ // closeConnection - close before open
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.closeConnection();
		return true;
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
	return false;
}



bool TC21::testRun(){ // openConnection - open first
	cout << ".";
	try{
		Pololu p("/dev/ttyACM1",9600);
		p.initConnection("/dev/ttyACM0",9600);
		return true;
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
	return false;
}

bool TC22::testRun(){ // openConnection - init open time
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.closeConnection();
		p.initConnection("/dev/ttyACM1",9600);
		p.openConnection();
		p.initConnection("/dev/ttyACM0",9600);
		return true;
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
	return false;
}

bool TC23::testRun(){ // openConnection - repeated open
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		for(int i=0; i < 23; i++){
			p.openConnection();
			p.openConnection();
		}
		return true;
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
	return false;
}

bool TC24::testRun(){ // openConnection - try to open wrong channel
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.initConnection("/dev/ttyAMC1",9600);
		p.openConnection();
		return false;
	}catch(IException *e){
		return true;
	}catch(...){
		return false;
	}
	return false;
}




bool TC11::testRun(){ // initConnection - init first
	cout << ".";
	try{
		Pololu p("/dev/ttyACM1",9600);
		p.initConnection("/dev/ttyACM0",9600);
		return true;
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
	return false;
}

bool TC12::testRun(){ // initConnection - init second time
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.closeConnection();
		p.initConnection("/dev/ttyACM1",9600);
		p.openConnection();
		p.initConnection("/dev/ttyACM0",9600);
		return true;
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
	return false;
}

bool TC13::testRun(){ // initConnection - repeated init
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		for(int i=0; i < 23; i++){
			p.openConnection();
			p.initConnection("/dev/ttyACM1",9600);
			p.openConnection();
			p.initConnection("/dev/ttyACM0",9600);
		}
		return true;
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
	return false;
}


}// ende namespace UT_Pololu
