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





	// execute unit tests
	unit.testExecution();
	unit.writeResultsToFile("UT_Pololu.xml");

}


bool TC11::testRun(){ // initConnection - init first
	cout << ".";
	try{
		return false;
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
}

bool TC12::testRun(){ // initConnection - init second time
	cout << ".";
	try{
		return false;
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
}

bool TC13::testRun(){ // initConnection - repeated init
	cout << ".";
	try{
		return false;
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
}


}// ende namespace UT_Pololu
