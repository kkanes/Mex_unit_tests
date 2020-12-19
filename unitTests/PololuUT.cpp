/*
 * PololuUT.cpp
 *
 *  Created on: 19.12.2020
 *      Author: ubuntu
 */

#include "../SimplUnitTestFW.hpp"
#include "../Pololu.hpp"
#include "PololuUT.hpp"


namespace UT_Pololu{

void execUnitTests(){

	// a unit a class
	UnitTest unit("SerialCom");

	// a unit for each method
	TestSuite TS01("initConnection");
	TestSuite TS02("openConnection");
	TestSuite TS03("closeConnection");
	TestSuite TS04("getMovingState");

	// add all test suits to the unit
	unit.addTestItem(&TS01);
	unit.addTestItem(&TS02);
	unit.addTestItem(&TS03);
	unit.addTestItem(&TS04);


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
	// create the defined test cases for method initSerialCom to test suite TS01
	TC21 tc21("openConnection - init first");
	TC22 tc22("openConnection - init second time");
	TC23 tc23("openConnection - repeated init");

	// add specific test cases to test suite TS01
	TS02.addTestItem(&tc21);
	TS02.addTestItem(&tc22);
	TS02.addTestItem(&tc23);





	// execute unit tests
	unit.testExecution();
	unit.writeResultsToFile("UT_Pololu.xml");

}



bool TC21::testRun(){ // openConnection - open first
	cout << ".";
	try{
		Pololu p("/dev/ttyACM1",9600);
		p.initConnection("/dev/ttyACM0",9600);
		return false;
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
}

bool TC22::testRun(){ // openConnection - init open time
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.closeConnection();
		p.initConnection("/dev/ttyACM1",9600);
		p.openConnection();
		p.initConnection("/dev/ttyACM0",9600);
		return false;
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
}

bool TC23::testRun(){ // openConnection - repeated open
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		for(int i=0; i < 23; i++){
			p.openConnection();
			p.initConnection("/dev/ttyACM1",9600);
			p.openConnection();
			p.initConnection("/dev/ttyACM0",9600);
		}
		return false;
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
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
}


}// ende namespace UT_Pololu
