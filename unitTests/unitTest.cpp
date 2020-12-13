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

using namespace std;

int main(){

	try{


		SerialCom a;
		a.openSerialCom();
		try{
			a.initSerialCom();
		}catch(IException *e){
			cout << "PASSED\n";
			cout <<"LOG:" <<  e->getMsg() << endl;
		}catch(...){
			cout << "FAILED\n";
		}


		SerialCom b;
		b.openSerialCom();
		try{
			b.openSerialCom();
		}catch(IException *e){
			cout << "PASSED\n";
			cout << "LOG:" << e->getMsg() << endl;
		}catch(...){
			cout << "FAILED\n";
		}
	}catch(IException *e){
		cout << "unintended IException error:" <<e->getMsg() << " Stop testing.\n";
	}catch(...){
		cout << "unintended error. stop testing.\n";
	}

}

