CC=g++
INCL=
LIBS=-lstdc++
CFLAGS=-std=c++11

OBJ=obj/
TESTDIR=./unitTests/

TARGETS = main unitTest

all:	$(TARGETS)


#
# source code
#

Pololu.o:	Pololu.cpp Pololu.hpp
	$(CC) $(INCL) $(CFLAGS) -c  Pololu.cpp  -o $(OBJ)Pololu.o

SerialCom.o:	SerialCom.cpp SerialCom.hpp
	$(CC) $(INCL) $(CFLAGS) -c  SerialCom.cpp  -o $(OBJ)SerialCom.o

ServoMotor.o:	ServoMotor.cpp ServoMotor.hpp
	$(CC) $(INCL) $(CFLAGS) -c  ServoMotor.cpp  -o $(OBJ)ServoMotor.o


#
# application
#

main.o:	main.cpp SerialCom.cpp SerialCom.hpp Pololu.cpp Pololu.hpp ServoMotor.cpp ServoMotor.hpp 
	$(CC) $(INCL) $(CFLAGS) -c  main.cpp -o $(OBJ)main.o

main:	main.o SerialCom.o ServoMotor.o Pololu.o
	$(CC) -o main  $(OBJ)main.o $(OBJ)Pololu.o $(OBJ)SerialCom.o $(OBJ)ServoMotor.o  $(LIBS)  $(CFLAGS)



#
# unit tests
#

TestUnits.o:	$(TESTDIR)TestUnits.cpp $(TESTDIR)TestUnits.hpp
	$(CC) $(INCL) $(CFLAGS) -c  $(TESTDIR)TestUnits.cpp -o $(OBJ)TestUnits.o

	
unitTest.o:	$(TESTDIR)unitTest.cpp SerialCom.cpp SerialCom.hpp Pololu.cpp Pololu.hpp ServoMotor.cpp ServoMotor.hpp 
	$(CC) $(INCL) $(CFLAGS) -c  $(TESTDIR)unitTest.cpp -o $(OBJ)unitTest.o	

SerialComUT.o:	$(TESTDIR)SerialComUT.cpp SerialCom.cpp SerialCom.hpp  
	$(CC) $(INCL) $(CFLAGS) -c  $(TESTDIR)SerialComUT.cpp -o $(OBJ)SerialComUT.o	
	
PololuUT.o:	$(TESTDIR)PololuUT.cpp Pololu.cpp Pololu.hpp  
	$(CC) $(INCL) $(CFLAGS) -c  $(TESTDIR)PololuUT.cpp -o $(OBJ)PololuUT.o 
	
ServoMotorBaseUT.o:	$(TESTDIR)ServoMotorBaseUT.cpp ServoMotor.cpp ServoMotor.hpp  
	$(CC) $(INCL) $(CFLAGS) -c  $(TESTDIR)ServoMotorBaseUT.cpp -o $(OBJ)ServoMotorBaseUT.o 	
	
ServoMotorUT.o:	$(TESTDIR)ServoMotorUT.cpp ServoMotor.cpp ServoMotor.hpp  
	$(CC) $(INCL) $(CFLAGS) -c  $(TESTDIR)ServoMotorUT.cpp -o $(OBJ)ServoMotorUT.o 		
	
unitTest:	unitTest.o TestUnits.o SerialCom.o ServoMotor.o Pololu.o SerialComUT.o PololuUT.o ServoMotorBaseUT.o ServoMotorUT.o
	$(CC) -o unitTest $(OBJ)unitTest.o $(OBJ)TestUnits.o $(OBJ)SerialCom.o $(OBJ)Pololu.o $(OBJ)ServoMotor.o \
						$(OBJ)SerialComUT.o  $(OBJ)PololuUT.o $(OBJ)ServoMotorBaseUT.o $(OBJ)ServoMotorUT.o $(LIBS)  $(CFLAGS)


#
# additional processes
#

doc:
	doxygen Doxyfile

#cleaning up
clean:
	rm -r $(OBJ)*.o  *.xml  *~ $(TARGETS) DOXYGENDOC
