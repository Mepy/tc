CC = g++
LLVMPATH = /usr/local/llvm
CFLAGS = $(shell ${LLVMPATH}/bin/llvm-config --cxxflags --ldflags --libs --system-libs) -fexceptions -Wall -ggdb
OBJ = visitor.o inst.o type.o symb.o

test : test.out 
	./$< ../ast/incr_if.hex > $@.ll && cat $@.ll \
	&& ${LLVMPATH}/bin/clang++ $@.ll ./lib/io.ll -o tc.out && ./tc.out

test.out: test.o ${OBJ}
	${CC} $? ${CFLAGS} -o $@ 

test.o: test.cpp visitor.hpp 
	${CC} $< ${CFLAGS} -c -o $@
	
visitor.o: visitor.cpp visitor.hpp ir_loader.hpp
	${CC} $< ${CFLAGS} -c -o $@ 

inst.o: inst.cpp visitor.hpp
	${CC} $< ${CFLAGS} -c -o $@ 

type.o: type.cpp visitor.hpp
	${CC} $< ${CFLAGS} -c -o $@

symb.o : symb.cpp visitor.hpp
	${CC} $< ${CFLAGS} -c -o $@

struct : struct.cpp
	${CC} $< ${CFLAGS} -o $@ && ./$@ 

demo : demo.out
	./$< > $@.ll && cat $@.ll 

demo.out : demo.cpp
	${CC} $< ${CFLAGS} -o $@ 

clean : 
	rm *.ll *.out ${OBJ}