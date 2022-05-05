CC = g++
STD = -std=c++11

test      : context.o ast.o test.o
	${CC} $^ -o $@ && ./$@ && rm ./$@

build     : context.o ast.o

test.o    : api.cpp api.hpp
	${CC} $< ${STD} -c -o $@

context.o : context.cpp context.hpp
	${CC} $< ${STD} -c -o $@

ast.o     : impl.cpp api.hpp
	${CC} $< ${STD} -c -o $@

clean     : 
	rm *.o