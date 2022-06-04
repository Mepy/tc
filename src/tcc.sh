make

tci()
{
    ./analyser < $1
}

tcl()
{
    tci $1
    ./codegen tc.hex > tc.ll
}

tcc()
{
    tcl $1
    /usr/local/llvm/bin/clang++ tc.ll ./ll/lib/io.ll -o tc.out
}

tcx()
{
    tcc $1
    ./tc.out < input.txt
}