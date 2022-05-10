#include "./visitor.hpp"
#include <iostream>
#include <string>

using namespace llvm;
int main() {
    try
    {
        LLCodegenVisitor llVisitor;
        /* code */
        // std::cout << "Started demo.\n";
        llVisitor.ASTIRtoLLVMIR("../ast/test.hex");
        // std::cout << "Into dump.\n";
        llVisitor.dumpLLVMIR();
    }
    catch(const std::string &str)
    {
        std::cout << str << '\n';
    }
    return 0;
}