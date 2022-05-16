CC = g++
LLVMPATH = /usr/local/llvm
CFLAGS = $(shell ${LLVMPATH}/bin/llvm-config --cxxflags --ldflags --libs --system-libs) -fexceptions -Wall -ggdb

test : test.out 
	./$< ../ast/imm.hex > $@.ll && cat $@.ll 

test.out: test.o visitor.o instr_codegen.o
	${CC} $? ${CFLAGS} -o $@ 

test.o: test.cpp visitor.hpp 
	${CC} $< ${CFLAGS} -c -o $@
	
visitor.o: visitor.cpp visitor.hpp ir_loader.hpp
	${CC} $< ${CFLAGS} -c -o $@ 

instr_codegen.o: instr_codegen.cpp visitor.hpp
	${CC} $< ${CFLAGS} -c -o $@ 

demo : demo.out
	./$< > $@.ll && cat $@.ll 

demo.out : demo.cpp
	${CC} $< ${CFLAGS} -o $@ 

clean : 
	rm *.ll *.out *.o