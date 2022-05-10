CC = g++
LLVMPATH = /usr/local/llvm
CFLAGS = $(shell ${LLVMPATH}/bin/llvm-config --cxxflags --ldflags --libs --system-libs) -fexceptions -Wall -ggdb

demo : demo.out
	./$< > $@.ll && cat $@.ll 

demo.out : demo.cpp
	${CC} $< ${CFLAGS} -o $@ 

# demoCodegen: demoCodegen.out

demoCodegen : demoCodegen.out 
	./$< > $@.ll && cat $@.ll 

demoCodegen.out: demoCodegen.o visitor.o instr_codegen.o
	${CC} $? ${CFLAGS} -o $@ 

demoCodegen.o: demoCodegen.cpp visitor.hpp 
	${CC} $< ${CFLAGS} -c -o $@
	
visitor.o: visitor.cpp visitor.hpp 
	${CC} $< ${CFLAGS} -c -o $@ 

instr_codegen.o: instr_codegen.cpp visitor.hpp
	${CC} $< ${CFLAGS} -c -o $@ 

clean : 
	rm *.ll *.out *.o