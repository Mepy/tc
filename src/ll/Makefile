CC = g++
LLVMPATH = /usr/local/llvm
CFLAGS = $(shell ${LLVMPATH}/bin/llvm-config --cxxflags --ldflags --libs --system-libs) -fexceptions -Wall -ggdb
OBJ = visitor.o instr_codegen.o type_codegen.o

test : test.out 
	./$< ../ast/get_put.hex > $@.ll && cat $@.ll \
	&& ${LLVMPATH}/bin/clang++ $@.ll ./lib/io.ll -o tc.out && ./tc.out

test.out: test.o ${OBJ}
	${CC} $? ${CFLAGS} -o $@ 

test.o: test.cpp visitor.hpp 
	${CC} $< ${CFLAGS} -c -o $@
	
visitor.o: visitor.cpp visitor.hpp ir_loader.hpp
	${CC} $< ${CFLAGS} -c -o $@ 

instr_codegen.o: instr_codegen.cpp visitor.hpp
	${CC} $< ${CFLAGS} -c -o $@ 

type_codegen.o: type_codegen.cpp visitor.hpp
	${CC} $< ${CFLAGS} -c -o $@

struct : struct.cpp
	${CC} $< ${CFLAGS} -o $@ && ./$@ 

demo : demo.out
	./$< > $@.ll && cat $@.ll 

demo.out : demo.cpp
	${CC} $< ${CFLAGS} -o $@ 

clean : 
	rm *.ll *.out ${OBJ}