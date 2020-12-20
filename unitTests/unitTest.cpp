/*
 * unitTest.cpp
 *
 *  Created on: 11.12.2020
 *      Author: aml
 */

#include "../SerialCom.hpp"
#include "../Pololu.hpp"
#include "../ServoMotor.hpp"
#include "./TestUnits.hpp"
#include "./SerialComUT.hpp"
#include "./PololuUT.hpp"
#include "./ServoMotorBaseUT.hpp"
#include "./ServoMotorUT.hpp"

using namespace std;

int main(){

	bool result, res1, res2, res3, res4;

	res1 = UT_SerialCom::execUnitTests("UT_SerialCom.xml");
	res2 = UT_Pololu::execUnitTests("UT_Pololu.xml");
	res3 = UT_ServoMotorBase::execUnitTests("UT_ServoMotorBase.xml");
	res4 = UT_ServoMotor::execUnitTests("UT_ServoMotor.xml");

	result = res1 && res2 && res3 && res4;
	if(result){
		cout << "\nAll units tests successfully passed.\n";
	}else{
		cout << "\nNOT all unit tests have been successfully passed. Check xml-files for detailed test results.\n";
	}

	return 0;
}

