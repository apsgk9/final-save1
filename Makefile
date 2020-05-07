###############################################################################
# -->Makefile<--
###############################################################################

###############################################################################
#
# Programmer :  Rob Wiehage
# Modified by:  Alain Markus P. Santos-Tankia
# Assignment :  Homework 3 - Euler's Method for ODEs and SIR(D) Model
#
# Instructor :  Professor Price
# Course     :  CS5201 Srping 2020
# Semester   :  Spring 2020
# Date 2/28/20
#
###############################################################################

###############################################################################
# This makefile will build an executable for the assignment.
###############################################################################

.PHONY: all clean

CXX = /usr/bin/g++
CXXFLAGS = -g -Wall -Wextra -Wpedantic -Werror -std=c++11

# The following 2 lines only work with gnu make.
# It's much nicer than having to list them out,
# and less error prone.
SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)

# Looks like it can be done like this, but won't work for gmake.
#SOURCES:sh = ls *.cpp
#HEADERS:sh = ls *.h

OBJECTS = $(SOURCES:%.cpp=%.o)

default: driver

driver: hw7.out

%.o: %.cpp
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

hw7.out: $(OBJECTS)
	@echo "Building $@"
	@$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

clean:
	-@rm -f core > /dev/null 2>&1
	-@rm -f hw7.out > /dev/null 2>&1
	-@rm -f depend > /dev/null 2>&1
	-@rm -f $(OBJECTS) > /dev/null 2>&1

# Automatically generate dependencies and include them in Makefile
depend: $(SOURCES) $(HEADERS)
	@echo "Generating dependencies"
	@$(CXX) -MM *.cpp > $@


-include depend
# Put a dash in front of include when using gnu make.
# It stops gmake from warning us that the file
# doesn't exist yet, even though it will be properly
# made and included when all is said and done.