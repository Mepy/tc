CC = g++
STD = -std=c++11

test_api : api.out
	./$<

api.out : api.o ast.o
	${CC} $^ -o $@

api.o : api.cpp api.hpp ir_parser.hpp
	${CC} $< ${STD} -c -o $@

test_ir_parser : ir_parser.out
	./$<
	

ir_parser.out : ir_parser.cpp
	${CC} $< ${STD} -o $@

ast.o : impl.cpp
	${CC} $< ${STD} -c -o $@

clean : 
	rm *.o *.out *.ir *.hex