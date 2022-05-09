CC = g++
LD = ld
STD = -std=c++11
MakeOBJ = ${CC} $< ${STD} -c -o $@
OBJ = context.o impl.o stmt.o save.o

test      : test.o ${OBJ}
	${CC} $^ -o $@ && ./$@ && rm ./$@

build     : ast.o

ast.o     : ${OBJ}
	${LD} -r $^ -o $@

test.o    : api.cpp api.hpp
	${MakeOBJ}

context.o : context.cpp context.hpp
	${MakeOBJ}

impl.o    : impl.cpp api.hpp context.hpp
	${MakeOBJ}

stmt.o    : stmt.cpp api.hpp context.hpp
	${MakeOBJ}

save.o    : save.cpp api.hpp
	${MakeOBJ}

clean     : 
	rm *.o *.hex