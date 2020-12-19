CC=g++
INCL=
LIBS=-lstdc++
CFLAGS=-std=c++11

OBJ=obj/
TESTDIR=./unitTests/

TARGETS = main unitTest

all:	$(TARGETS)

Pololu.o:	Pololu.cpp Pololu.hpp
	$(CC) $(INCL) $(CFLAGS) -c  Pololu.cpp  -o $(OBJ)Pololu.o

SerialCom.o:	SerialCom.cpp SerialCom.hpp
	$(CC) $(INCL) $(CFLAGS) -c  SerialCom.cpp  -o $(OBJ)SerialCom.o

ServoMotor.o:	ServoMotor.cpp ServoMotor.hpp
	$(CC) $(INCL) $(CFLAGS) -c  ServoMotor.cpp  -o $(OBJ)ServoMotor.o

TestUnits.o:	$(TESTDIR)TestUnits.cpp $(TESTDIR)TestUnits.hpp
	$(CC) $(INCL) $(CFLAGS) -c  $(TESTDIR)TestUnits.cpp -o $(OBJ)TestUnits.o

main.o:	main.cpp SerialCom.cpp SerialCom.hpp Pololu.cpp Pololu.hpp ServoMotor.cpp ServoMotor.hpp 
	$(CC) $(INCL) $(CFLAGS) -c  main.cpp -o $(OBJ)main.o
	
unitTest.o:	$(TESTDIR)unitTest.cpp SerialCom.cpp SerialCom.hpp Pololu.cpp Pololu.hpp ServoMotor.cpp ServoMotor.hpp 
	$(CC) $(INCL) $(CFLAGS) -c  $(TESTDIR)unitTest.cpp -o $(OBJ)unitTest.o	

SerialComUT.o:	$(TESTDIR)SerialComUT.cpp SerialCom.cpp SerialCom.hpp  
	$(CC) $(INCL) $(CFLAGS) -c  $(TESTDIR)SerialComUT.cpp -o $(OBJ)SerialComUT.o	
	
PololuUT.o:	$(TESTDIR)PololuUT.cpp Pololu.cpp Pololu.hpp  
	$(CC) $(INCL) $(CFLAGS) -c  $(TESTDIR)PololuUT.cpp -o $(OBJ)PololuUT.o 
	
	
main:	main.o SerialCom.o ServoMotor.o Pololu.o
	$(CC) -o main  $(OBJ)main.o $(OBJ)Pololu.o $(OBJ)SerialCom.o $(OBJ)ServoMotor.o  $(LIBS)  $(CFLAGS)



unitTest:	unitTest.o TestUnits.o SerialCom.o ServoMotor.o Pololu.o SerialComUT.o PololuUT.o
	$(CC) -o unitTest $(OBJ)unitTest.o $(OBJ)TestUnits.o $(OBJ)SerialCom.o $(OBJ)Pololu.o $(OBJ)ServoMotor.o \
						$(OBJ)SerialComUT.o  $(OBJ)PololuUT.o  $(LIBS)  $(CFLAGS)

doc:
	doxygen Doxyfile

#cleaning up
clean:
	rm -r $(OBJ)*.o  *.xml  *~ $(TARGETS) DOXYGENDOC
