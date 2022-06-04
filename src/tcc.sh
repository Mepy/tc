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
    /usr/local/llvm/bin/clang++ ${LL} ./ll/lib/io.ll -o ${OUT}
}

tcx()
{
    tcc $1
    ./tc.out
}