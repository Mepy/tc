CC = g++
LLVMPATH = /usr/local/llvm
CFLAGS = $(shell ${LLVMPATH}/bin/llvm-config --cxxflags --ldflags --libs --system-libs)

demo : demo.out
	./$< > $@.ll && cat $@.ll 

demo.out : demo.cpp
	${CC} $< ${CFLAGS} -o $@ 

clean : 
	rm *.ll *.out