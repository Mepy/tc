
build : analyser codegen

test  : build
	echo 'puts("Hello, world!");' | ./analyser \
	&& ./codegen tc.hex > tc.ll \
	&& cat tc.ll

analyser : ast/build parser/build
	g++ $^ -o $@

codegen  : ll/build
	cp $< codegen

ast/build : 
	${MAKE} -C ast build

parser/build :
	${MAKE} -C parser build

ll/build : 
	${MAKE} -C ll build
	
clean : 
	- rm analyser codegen *.hex *.txt *.ll

clear : clean
	${MAKE} -C ast clean
	${MAKE} -C parser clean
	${MAKE} -C ll clean