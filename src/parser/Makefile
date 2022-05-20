OBJ = lexer.o parser.o

test : test.out
	cat test.tc && cat test.tc | ./$<

test.out : api.o ${OBJ}
	g++ $^ -o $@

build : ${OBJ}
	g++ $^ -o $@ -lm

api.o : api.cpp 
	g++ $< -c

lexer.o : lexer.cpp parser.cpp
	g++ $< -c

parser.o : parser.cpp
	g++ $< -c

lexer.cpp : tc.l
	flex -o $@ $< 

parser.cpp : tc.y
	bison -d -o $@ $<

clean :
	rm *.o *.c *.h *.hex parser.cpp parser.hpp lexer.cpp test.out