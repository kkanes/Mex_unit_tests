/*
 * ServoMotorUT.cpp
 *
 *  Created on: 20.12.2020
 *      Author: aml
 */

#include "../SimplUnitTestFW.hpp"
#include "../ServoMotor.hpp"
#include "ServoMotorUT.hpp"




namespace UT_ServoMotor{

bool execUnitTests(string xmlFilename){
	// a unit a class
	UnitTest unit("ServoMotor");

	// a unit for each method
	TestSuite TS01("setPositionInAbs");
	TestSuite TS02("getPositionInAbs");
	TestSuite TS03("getMinPosInAbs");
	TestSuite TS04("getMidPosInAbs");
	TestSuite TS05("getMaxPosInAbs");
	TestSuite TS06("getServoNumber");
	TestSuite TS07("constructor");

	// add all test suits to the unit
	unit.addTestItem(&TS01);
	unit.addTestItem(&TS02);
	unit.addTestItem(&TS03);
	unit.addTestItem(&TS04);
	unit.addTestItem(&TS05);
	unit.addTestItem(&TS06);
	unit.addTestItem(&TS07);

	//
	// test cases for test suite TS01
	//
	// create the defined test cases for method initSerialCom to test suite TS01
	TC11 tc11("setPositionInAbs - having closed communication channel");
	TC12 tc12("setPositionInAbs - with no communication channel");
	TC13 tc13("setPositionInAbs - with open communication channel");
	TC14 tc14("setPositionInAbs - check the set value within its limits");
	TC15 tc15("setPositionInAbs - try to set pos value larger then max");
	TC16 tc16("setPositionInAbs - try to set pos value smaller then min");




	// add specific test cases to test suite TS01
	TS01.addTestItem(&tc11);
	TS01.addTestItem(&tc12);
	TS01.addTestItem(&tc13);
	TS01.addTestItem(&tc14);
	TS01.addTestItem(&tc15);
	TS01.addTestItem(&tc16);



	//
	// test cases for test suite TS02
	//
	// create the defined test cases for method initSerialCom to test suite TS02
	TC21 tc21("setPositionInAbs - having closed communication channel");
	TC22 tc22("setPositionInAbs - with no communication channel");
	TC23 tc23("setPositionInAbs - with open communication channel");

	// add specific test cases to test suite TS02
	TS02.addTestItem(&tc21);
	TS02.addTestItem(&tc22);
	TS02.addTestItem(&tc23);



	//
	// test cases for test suite TS03
	//
	// create the defined test cases for method initSerialCom to test suite TS03
	TC31 tc31("getMinPosInAbs - having closed communication channel");
	TC32 tc32("getMinPosInAbs - with open communication channel");

	// add specific test cases to test suite TS03
	TS03.addTestItem(&tc31);
	TS03.addTestItem(&tc32);

	//
	// test cases for test suite TS04
	//
	// create the defined test cases for method initSerialCom to test suite TS04
	TC41 tc41("getMidPosInAbs - having closed communication channel");
	TC42 tc42("getMidPosInAbs - with open communication channel");

	// add specific test cases to test suite TS04
	TS04.addTestItem(&tc41);
	TS04.addTestItem(&tc42);


	//
	// test cases for test suite TS05
	//
	// create the defined test cases for method initSerialCom to test suite TS05
	TC51 tc51("getMaxPosInAbs - having closed communication channel");
	TC52 tc52("getMaxPosInAbs - with open communication channel");

	// add specific test cases to test suite TS05
	TS05.addTestItem(&tc51);
	TS05.addTestItem(&tc52);


	//
	// test cases for test suite TS06
	//
	// create the defined test cases for method initSerialCom to test suite TS06
	TC61 tc61("getServoNumber - with open communication channel");
	TC62 tc62("getServoNumber - having closed communication channel");

	// add specific test cases to test suite TS06
	TS06.addTestItem(&tc61);
	TS06.addTestItem(&tc62);


	//
	// test cases for test suite TS07
	//
	// create the defined test cases for method initSerialCom to test suite TS07
	TC71 tc71("constructor - with no communication channel");
	TC72 tc72("constructor - negative servo motor nmb");
	TC73 tc73("constructor - negative neutral position values");
	TC74 tc74("constructor - delta value = 0");
	TC75 tc75("constructor - non matching neutral and delta values");
	TC76 tc76("constructor - call with no motor connected");
	TC77 tc77("constructor - call with non existing servo board ID");


	// add specific test cases to test suite TS07
	TS07.addTestItem(&tc71);
	TS07.addTestItem(&tc72);
	TS07.addTestItem(&tc73);
	TS07.addTestItem(&tc74);
	TS07.addTestItem(&tc75);
	TS07.addTestItem(&tc76);
	TS07.addTestItem(&tc77);

	// execute unit tests
	unit.testExecution();
	unit.writeResultsToFile(xmlFilename);

	return unit.getResult();
}

bool TC71::testRun(){ // constructor - with no communication channel
	cout << ".";
	try{
		try{
			ServoMotor m(0,6000,3000,NULL);
			return false;
		}catch(IException *e){
			return true;
		}catch(...){
			return false;
		};
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
};

bool TC72::testRun(){ // constructor - negative servo motor nmb
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.openConnection();
		try{
			int srvNmb = -1;
			ServoMotor m(srvNmb,6000,3000,&p);
			p.getErrors();
			return false;
		}catch(IException *e){
			p.getErrors();
			return true;
		}catch(...){
			p.getErrors();
			return false;
		};
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
	return false;
};

bool TC73::testRun(){ // constructor - negative neutral position values
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.openConnection();
		try{
			int nPos = -1;
			ServoMotor m(0,nPos,3000,&p);
			if(nPos != m.getMidPosInAbs()){
				return true;
			}else{
				return false;
			}
		}catch(IException *e){
			return false;
		}catch(...){
			return false;
		};
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
	return false;
};

bool TC74::testRun(){ // constructor - delta values = 0
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.openConnection();
		try{
			int delta = 0;
			ServoMotor m(0,delta,3000,&p);
		}catch(IException *e){
			return true;
		}catch(...){
			return false;
		};
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
	return false;
};

bool TC75::testRun(){ // constructor - non matching neutral and delta values
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.openConnection();
		unsigned short delta = 6001;
		unsigned short nPos = 6000;
		try{
			ServoMotor m(0,nPos,delta,&p);
			return false;
		}catch(IException *e){
			return true;
		}catch(...){
			return false;
		};
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
	return false;
};


bool TC76::testRun(){ // constructor - call with no motor connected
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.openConnection();
		try{
			ServoMotor m(1,6000,3000,&p); // servo motor board ID must not be
			                                        // connected to a servo motor
			return true;
		}catch(IException *e){
			return false;
		}catch(...){
			return false;
		};
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
	return false;
};


bool TC77::testRun(){ // constructor - call with non existing servo board ID
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.openConnection();
		try{
			ServoMotor m(111,6000,3000,&p); // servo motor board ID must not
													  // be defined for used board
			return true;
		}catch(IException *e){
			return false;
		}catch(...){
			return false;
		};
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
	return false;
};


bool TC61::testRun(){ // getServoNumber - having closed communication channel
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.openConnection();
		unsigned short sNmb, value;
		sNmb = 0;
		ServoMotor m(sNmb,6000,3000,&p);
		p.closeConnection();
		value = m.getServoNumber();
		try{
			if(value != sNmb){
				return false;
			}else{
				return true;
			}
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


bool TC62::testRun(){ // getServoNumber - with open communication channel
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.openConnection();
		unsigned short sNmb, value;
		sNmb = 0;
		ServoMotor m(sNmb,6000,3000,&p);
		value = m.getServoNumber();
		try{
			if(value != sNmb){
				return false;
			}else{
				return true;
			}
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









bool TC51::testRun(){ // getMaxPosInAbs - having closed communication channel
	cout << ".";
	try{
		unsigned short mid = 6000;
		unsigned short delta = 3000;
		unsigned short pos;
		Pololu p("/dev/ttyACM0",9600);
		p.openConnection();
		ServoMotor m(0,mid,delta,&p);
		p.closeConnection();
		pos = m.getMaxPosInAbs();
		try{
			if(pos != (mid + delta)){
				return false;
			}else{
				return true;
			};
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


bool TC52::testRun(){ // getMaxdPosInAbs - with open communication channel
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.openConnection();
		unsigned short mid = 6000;
		unsigned short delta = 3000;
		unsigned short pos;
		ServoMotor m(0,mid,delta,&p);
		pos = m.getMaxPosInAbs();
		try{
			if(pos != (mid + delta)){
				return false;
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





bool TC41::testRun(){ // getMidPosInAbs - having closed communication channel
	cout << ".";
	try{
		unsigned short mid = 6000;
		unsigned short delta = 3000;
		unsigned short pos;
		Pololu p("/dev/ttyACM0",9600);
		p.openConnection();
		ServoMotor m(0,mid,delta,&p);
		p.closeConnection();
		pos = m.getMidPosInAbs();
		try{
			if(pos != mid){
				return false;
			}else{
				return true;
			};
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


bool TC42::testRun(){ // getMidPosInAbs - with open communication channel
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.openConnection();
		unsigned short mid = 6000;
		unsigned short delta = 3000;
		unsigned short pos;
		ServoMotor m(0,mid,delta,&p);
		pos = m.getMidPosInAbs();
		try{
			if(pos != mid){
				return false;
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


bool TC31::testRun(){ // getMinPosInAbs - having closed communication channel
	cout << ".";
	try{
		unsigned short mid = 6000;
		unsigned short delta = 3000;
		unsigned min;
		Pololu p("/dev/ttyACM0",9600);
		p.openConnection();
		ServoMotor m(0,mid,delta,&p);
		p.closeConnection();
		min = m.getMinPosInAbs();
		try{
			if(min != (mid - delta)){
				return false;
			}else{
				return true;
			};
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


bool TC32::testRun(){ // getMinPosInAbs - with open communication channel
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.openConnection();
		unsigned short mid = 6000;
		unsigned short delta = 3000;
		unsigned min;
		ServoMotor m(0,mid,delta,&p);
		min = m.getMinPosInAbs();
		try{
			if(min != (mid - delta)){
				return false;
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







bool TC21::testRun(){ // getPositionInAbs - having closed communication channel
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.openConnection();
		ServoMotor m(0,6000,3000,&p);
		p.closeConnection();
		try{
			m.getPositionInAbs();
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


bool TC22::testRun(){ // getPositionInAbs - with no communication channel
	cout << ".";
	try{
		try{
			ServoMotor m(0,6000,3000,NULL);
			m.getPositionInAbs();
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


bool TC23::testRun(){ // getPositionInAbs - with open communication channel
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.openConnection();
		ServoMotor m(0,6000,3000,&p);
		try{
			short pos = m.getPositionInAbs();
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







bool TC11::testRun(){ // setPositionInAbs - having closed communication channel
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.openConnection();
		ServoMotor m(0,6000,3000,&p);
		p.closeConnection();
		try{
			m.setPositionInAbs(6000);
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


bool TC12::testRun(){ // setPositionInAbs - with no communication channel
	cout << ".";
	try{
		try{
			ServoMotor m(0,6000,3000,NULL);
			m.setPositionInAbs(6000);
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


bool TC13::testRun(){ // setPositionInAbs - with open communication channel
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.openConnection();
		ServoMotor m(0,6000,3000,&p);
		try{
			short pos = m.getPositionInAbs();
			m.setPositionInAbs(pos);
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



bool TC14::testRun(){ // setPositionInAbs - check the set value within its limits
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.openConnection();
		ServoMotor m(0,6000,3000,&p);
		unsigned short mid = m.getMidPosInAbs();
		unsigned short max = m.getMaxPosInAbs();
		unsigned short posTarget = mid - ((max - mid) / 2);
		unsigned short pos;
		try{
			m.setPositionInAbs(posTarget);
			pos = m.getPositionInAbs();
			if(pos != posTarget){
				cout << "ServoMotorBaseUT::setPositionInAbs - check the set value within its limits";
				cout << "'curr. pos. " << pos << " is unequal to target pos " << posTarget << "'";
				return false;
			}else{
				return true;
			}
		}catch(IException *e){
			cout << e->getMsg();
			return false;
		}catch(...){
			cout << "unknown and unexcepted error.";
			return false;
		}
	}catch(IException *e){
		return false;
	}catch(...){
		return false;
	}
	return false;
}


bool TC15::testRun(){ // setPositionInAbs - try to set pos value larger then max.
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.openConnection();
		ServoMotor m(0,6000,3000,&p);
		unsigned short max = m.getMaxPosInAbs();
		unsigned short posTarget = max + 1;
		try{
			m.setPositionInAbs(posTarget);
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

bool TC16::testRun(){ // setPositionInAbs - try to set pos value smaller then min.
	cout << ".";
	try{
		Pololu p("/dev/ttyACM0",9600);
		p.openConnection();
		ServoMotor m(0,6000,3000,&p);
		unsigned short min = m.getMinPosInAbs();
		unsigned short posTarget = min - 1;
		try{
			m.setPositionInAbs(posTarget);
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



} // ende namespace UT_ServoMotor
