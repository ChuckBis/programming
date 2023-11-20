###
### Makefile for Zap Project
### Zap is a encoder/decoder
###
### Author:  Charlie Biskupiak 

# this is needed to have make follow symlinks in dependency lists -- please keep
# it! (but remove this comment)
MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

#this rule was made to text out zapUtil things 
ZapExample: ZapUtilExample.o ZapUtil.o HuffmanTreeNode.o
	$(CXX) $(LDFLAGS) -o $@ $^

#this rule makes the zap program 
zap: main.o phaseOne.o HuffmanTreeNode.o HuffmanCoder.o BinaryIO.o 
	$(CXX) $(LDFLAGS) -o $@ $^

#this rule made the .o for a test 
ZapUtilExample.o: ZapUtilExample.cpp ZapUtil.h HuffmanTreeNode.h

# This rule builds phaseOne.o
phaseOne.o: phaseOne.cpp phaseOne.h HuffmanTreeNode.h 

# This rule builds HuffmanTreeNode.o
HuffmanTreeNode.o: HuffmanTreeNode.h 

#this rule builds ZapUtil.o
ZapUtil.o: ZapUtil.h HuffmanTreeNode.h 

#this rule builds BinaryIO.o
BinaryIO.o: BinaryIO.h

#this rule builds main.o 
main.o: main.cpp HuffmanCoder.h HuffmanTreeNode.h phaseOne.h BinaryIO.h

#this rule builds HuffmanCoder.o
HuffmanCoder.o: HuffmanCoder.cpp HuffmanCoder.h HuffmanTreeNode.h phaseOne.h BinaryIO.h


#this builds unit test
unit_test: unit_test_driver.o phaseOne.o HuffmanTreeNode.o ZapUtil.o HuffmanCoder.o BinaryIO.o
	$(CXX) $(CXXFLAGS) $^


# This rule provides your final submission 
# NOTE: Don't forget to add any additional files you want to submit to this
#		rule! If you do not add them, they will not be submitted.
provide:
	provide comp15 proj3_zap phaseOne.cpp phaseOne.h unit_tests.h Makefile \
	README HuffmanTreeNode.h HuffmanCoder.cpp \
	HuffmanCoder.h BinaryIO.h main.cpp \
	input.txt

# remove executables, object code, and temporary files from the current folder 
# -- the executable created by unit_test is called a.out
clean: 


##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^