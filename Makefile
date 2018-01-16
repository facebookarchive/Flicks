# This is for a linux system which has C++ installed

CC=c++

all: flicks_derivation flicks_test
	echo "FLICKS DERIVATION"
	./flicks_derivation
	echo "FLICKS TEST"
	./flicks_test

flicks_derivation: flicks_derivation.cpp
	$(CC) -o flicks_derivation -std=c++14 flicks_derivation.cpp

flicks_test: flicks_test.cpp
	$(CC) -o flicks_test -std=c++14 flicks_test.cpp

clean: 
	rm -f flicks_derivation flicks_test

