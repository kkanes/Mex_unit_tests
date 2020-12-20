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

using namespace std;

int main(){

	UT_SerialCom::execUnitTests();
	UT_Pololu::execUnitTests();
	UT_ServoMotorBase::execUnitTests();

	return 0;
}

