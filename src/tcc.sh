tcs(){ 
    ./analyser < $1 
}
tcc(){
    ./codegen tc.hex > tc.ll
}

# --- llvm ---
tcl(){ 
    llvm-link tc.ll ./lib/io.ll -o tc.bc
}
tco(){ 
    llc tc.bc -o tc.out 
}
tcx(){ 
    lli tc.bc 
}