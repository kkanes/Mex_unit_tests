CC=g++
INCL=
LIBS=-lstdc++
CFLAGS=-std=c++11


TARGETS = main

all:	$(TARGETS)

Pololu.o:	Pololu.cpp Pololu.hpp
	$(CC) $(INCL) $(CFLAGS) -c  $<

SerialCom.o:	SerialCom.cpp SerialCom.hpp
	$(CC) $(INCL) $(CFLAGS) -c  $<

main.o:	main.cpp SerialCom.cpp SerialCom.hpp Pololu.cpp Pololu.hpp
	$(CC) $(INCL) $(CFLAGS) -c  $<

main:	main.o Pololu.o SerialCom.o
	$(CC) -o $@ $^   $(LIBS)

doc:
	doxygen Doxyfile

#cleaning up
clean:
	rm -r *.o *~ $(TARGETS) DOXYGENDOC
