###
### Makefile for gerp Project
### gerp is a file searcher
###
### Author:  Charlie Biskupiak / Jack Edwards 

# this is needed to have make follow symlinks in dependency lists -- please keep
# it! (but remove this comment)
MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

hash: hashExample.o 
	$(CXX) $(LDFLAGS) -o $@ $^

#this builds the entire program 
gerp: main.o gerp.o HashTable.o FSTree.o DirNode.o stringProcessing.o
	$(CXX) $(LDFLAGS) -o $@ $^

#this builds main
main.o: main.cpp gerp.h HashTable.h DirNode.h FSTree.h stringProcessing.h

#this builds HashTable
HashTable.o: HashTable.cpp HashTable.h DirNode.h gerp.h

#this builds gerp
gerp.o: gerp.cpp gerp.h HashTable.h DirNode.h FSTree.h stringProcessing.h

#this builds treeTraversal
treeTraversal: FSTreeTraversal.o FSTree.o DirNode.o 
	$(CXX) $(LDFLAGS) -o $@ $^

#this builds treeTraversal
FSTreeTraversal.o: FSTreeTraversal.cpp FSTree.h DirNode.h

#this builds FSTree
FSTree.o: FSTree.h DirNode.h

DirNode.o: DirNode.h

stringProcessing.o: stringProcessing.cpp stringProcessing.h

hashExample.o: hashExample.cpp

#this builds unit test
unit_test: unit_test_driver.o HashTable.o gerp.o DirNode.o FSTree.o stringProcessing.o
	$(CXX) $(CXXFLAGS) $^


# This rule provides your final submission 
# NOTE: Don't forget to add any additional files you want to submit to this
#		rule! If you do not add them, they will not be submitted.
provide:
	provide comp15 proj4_gerp stringProcessing.h FSTree.h \
									stringProcessing.cpp HashTable.cpp \
									HashTable.h gerp.cpp gerp.h Makefile \
									main.cpp unit_tests.h README 

# remove executables, object code, and temporary files from the current folder 
# -- the executable created by unit_test is called a.out
clean: 


##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^