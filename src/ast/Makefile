CC = g++
STD = -std=c++11


test : ir_parser.out
	./ir_parser.out && \
	echo "Please view test.ir in binary format."

ir_parser.out : ir_parser.cpp
	${CC} $< ${STD} -o $@

clean : 
	rm *.out *.ir