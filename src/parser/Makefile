CC  = g++ 
STD = c++14
OBJ = lexer.o parser.o
CFLAGS = -std=${STD}
MakeOBJ = ${CC} ${CFLAGS} $< -c


test : test.out
	cat test.tc && cat test.tc | ./$< && rm ./$<

test.out : ${OBJ}
	g++ $^ ../ast/ast.o -o $@

# test.out : ${OBJ}
# 	g++ $^ api.o -o $@

build : ${OBJ}
	g++ $^ -o $@ -lm

api.o : api.cpp 
	${MakeOBJ}

lexer.o : lexer.cpp parser.cpp
	${MakeOBJ}

parser.o : parser.cpp
	${MakeOBJ}

lexer.cpp : tc.l
	flex -o $@ $< 

parser.cpp : tc.y
	bison -d -o $@ $<

clean :
	rm *.o *.c *.h *.hex parser.cpp parser.hpp lexer.cpp test.out