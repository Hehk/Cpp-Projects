CC=g++
CFLAGS=-c -Wall -ggdb -I. 
LDFLAGS=
# Put your .cpp files here
SOURCES=main.cpp tree.h
EXECUTABLE=a.out
# Put your test files here
TESTS = 

OBJECTS=$(SOURCES:.cpp=.o)
OBJECTSTEST=

FLAGS   = -Iinclude

all: $(SOURCES) $(EXECUTABLE)
	
# These next lines do a bit of magic found from http://stackoverflow.com/questions/2394609/makefile-header-dependencies
# Essentially it asks the compiler to read the .cpp files and generate the needed .h dependencies.
# This way if any .h file changes the correct .cpp files will be recompiled
depend: .depend
	

.depend: $(SOURCES)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ >> ./.depend;

include .depend
# End .h file magic

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -rf *o $(EXECUTABLE)
	-rm -f testrunner testrunner.cpp
	-rm -f ./.depend

# CXX Testing	
CXXTESTGEN = ../../cxxtest/bin/cxxtestgen

test: testrunner
	valgrind ./testrunner

testrunner: testrunner.cpp $(OBJECTSTEST)
	g++ -I. -I../../cxxtest/ -o testrunner $(OBJECTSTEST) testrunner.cpp

testrunner.cpp: $(HEADERS) $(SOURCES) $(TESTS)
	$(CXXTESTGEN) --error-printer -o testrunner.cpp $(TESTS)
