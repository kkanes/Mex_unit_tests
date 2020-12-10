CC=g++
INCL=
LIBS=-lstdc++
CFLAGS=-std=c++11 -Wpointer-arith


TARGETS = main

all:	$(TARGETS)

Pololu.o:	Pololu.cpp Pololu.hpp
	$(CC) $(INCL) $(CFLAGS) -c  $<

SerialCom.o:	SerialCom.cpp SerialCom.hpp
	$(CC) $(INCL) $(CFLAGS) -c  $<

ServoMotor.o:	ServoMotor.cpp ServoMotor.hpp
	$(CC) $(INCL) $(CFLAGS) -c  $<

TestUnits.o:	TestUnits.cpp TestUnits.hpp
	$(CC) $(INCL) $(CFLAGS) -c  $<

main.o:	main.cpp SerialCom.cpp SerialCom.hpp Pololu.cpp Pololu.hpp TestUnits.cpp TestUnits.hpp ServoMotor.cpp ServoMotor.hpp 
	$(CC) $(INCL) $(CFLAGS) -c  $<

main:	main.o Pololu.o SerialCom.o TestUnits.o ServoMotor.o
	$(CC) -o $@ $^   $(LIBS)

doc:
	doxygen Doxyfile

#cleaning up
clean:
	rm -r *.o *~ $(TARGETS) DOXYGENDOC
