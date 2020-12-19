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

using namespace std;

int main(){

	UT_SerialCom::execUnitTests();
	UT_Pololu::execUnitTests();

	return 0;
}

