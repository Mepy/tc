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
        llVisitor.ASTIRtoLLVMIR("../../ir/while.hex");
        // std::cout << "Into dump.\n";
        llVisitor.dumpLLVMIR();
    }
    catch(const std::invalid_argument &e)
    {
        std::cout << e.what() << '\n';
    }
    catch(const char* &str) 
    {
        std::cout << str << '\n';
    }
    catch(const std::string str)
    {
        std::cout << str << '\n';
    }
    return 0;
}