#########################################################
#             PROJECT 1: MetroSim Makefile             #
#########################################################

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

#this rule builds the metrosim 
MetroSim: main.o MetroSim.o PassengerQueue.o Passenger.o
	$(CXX) $(LDFLAGS) -o $@ $^

#this rule builds the testing metrosim 
MetroSimTest: drivertest.o MetroSim.o PassengerQueue.o Passenger.o
	$(CXX) $(LDFLAGS) -o $@ $^

#this rule builds main.o 
main.o: main.cpp MetroSim.h PassengerQueue.h Passenger.h

#this rule builds the testing main.o
drivertest.o: drivertest.cpp MetroSim.h PassengerQueue.h Passenger.h

#this rule builds metrosim.o
MetroSim.o: MetroSim.cpp MetroSim.h PassengerQueue.h Passenger.h

# This rule builds PassengerQueue.o
PassengerQueue.o: PassengerQueue.cpp PassengerQueue.h Passenger.h 

# This rule builds passenger.o
Passenger.o: Passenger.h 


#this builds unit test
unit_test: unit_test_driver.o PassengerQueue.o Passenger.o MetroSim.o
	$(CXX) $(CXXFLAGS) $^


# This rule provides your final submission 
# NOTE: Don't forget to add any additional files you want to submit to this
#		rule! If you do not add them, they will not be submitted.
provide:
	provide comp15 proj1_MetroSim MetroSim.cpp MetroSim.h PassengerQueue.h \
				    main.cpp PassengerQueue.cpp \
				    Passenger.h Passenger.cpp  \
				    unit_tests.h Makefile README edgecase1.txt edgecase2.txt \
					edgecase3.txt edgecase4.txt drivertest.cpp

# remove executables, object code, and temporary files from the current folder 
# -- the executable created by unit_test is called a.out
clean: 
	rm *.o *~ a.out
