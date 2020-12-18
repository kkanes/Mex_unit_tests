//============================================================================
// Name        : main.cpp
// Author      : Willi Penner
//
// Description : Contains the main function. It also contains test functions
//               to test the connection to the controller and the movement of
//       		 the servos.
//============================================================================

#include "SerialCom.hpp"
#include "Pololu.hpp"
#include "ServoMotor.hpp"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	try{
		const char* portName = "/dev/ttyACM0";  // Linux
		Pololu conn(portName, 9600);
		// Open connection to COM port.
		conn.openConnection();
		// Define the servos of the robot manipulator
		ServoMotor arm_0(0, 6000, 3000	, &conn);
		cout << "max. pos.: " << arm_0.getMaxPosInAbs() << endl;
		cout << "min. pos.: " << arm_0.getMinPosInAbs() << endl;
		cout << "get current pos.: "  << arm_0.getPositionInAbs() << endl;

		unsigned short pMin, pMid, pMax;
		arm_0.showPololuValues(pMin,pMid,pMax);
		cout << pMin	<< " " << pMid << " " << pMax << endl;


		arm_0.setPositionInAbs(3000);


		conn.closeConnection();
	}catch(IException *e){
		cout << e->getMsg() << endl;
	}catch(string e){
		cout << "string Error: " << e << endl;
	}catch(...){
		cout << "unknown error\n";
	}

	return 0;
}
