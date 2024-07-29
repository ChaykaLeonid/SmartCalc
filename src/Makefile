WWW = -std=c++17 -Wall -Werror -Wextra -pedantic
LINUX=-lsubunit -lrt -lpthread -lm -lstdc++
LFLAGS=-fprofile-arcs -ftest-coverage
LIBS=-lgtest -lgmock -pthread
OS=$(shell uname -s)

all: clean tests

tests: clean smartcalc_oop.a
ifeq ($(OS), Darwin)
	gcc $(WWW) -lstdc++ SmartCalcV2/tests/test.cc smartcalc_oop.a -o test $(LIBS)
else
	gcc $(WWW) SmartCalcV2/tests/test.cc smartcalc_oop.a -o test $(LIBS) $(LINUX)
endif
	./test

smartcalc_oop.a: build_smartcalc_oop

dvi:
	open documentation.txt

dist:
	tar -cf dist.tar ../build/SmartCalcV2.app


install:
	mkdir build
	cd SmartCalcV2 && qmake && make && make clean && rm Makefile && mv SmartCalcV2.app ../build

uninstall:
	rm -rf build

build_smartcalc_oop:
	gcc -c SmartCalcV2/controller/*.cc SmartCalcV2/model/*cc
	ar rcs smartcalc_oop.a *.o
	ranlib smartcalc_oop.a

check: clean tests style
	leaks -atExit -- ./test
	
style:
	clang-format -n SmartCalcV2/*.cc
	clang-format -n SmartCalcV2/tests/*.cc
	clang-format -n SmartCalcV2/model/*.cc SmartCalcV2/model/*.h
	clang-format -n SmartCalcV2/controller/*.cc SmartCalcV2/controller/*.h
	clang-format -n SmartCalcV2/view/*.cc SmartCalcV2/view/*.h


clean:
	rm -rf test
	rm -rf *.a
	rm -rf *.o
