CXX=		g++
CXXFLAGS=	-g -Wall -std=gnu++11
SHELL=		bash
#MEASURE=	gcc -Wall -std=gnu99 -o measure measure.c

all:		solution

solution:	LinkedList.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f solution

measure:
	gcc -Wall -std=gnu99 -o measure measure.c


test:		test-output test-memory test-time

test-output:	solution
	@echo Testing output...
	@diff --suppress-common-lines -y <(./solution < input) output

test-memory:	solution
	@echo Testing memory...
	@[ `valgrind --leak-check=full ./solution < input 2>&1 | grep ERROR | awk '{print $$4}'` = 0 ]

test-time:	measure solution
	@echo Testing time...
	@gcc -Wall -std=gnu99 -o measure measure.c
	@./measure ./solution < input | tail -n 1 | awk '{ if ($$1 > 1.0) { print "Time limit exceeded"; exit 1} }'
