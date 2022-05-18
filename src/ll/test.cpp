#include "./visitor.hpp"
#include <iostream>
#include <string>

using namespace llvm;

int main(int argc, char* argv[]) 
{
    if(argc>=2)
    try
    {
        // std::cout<<"Test "<<std::endl;
        LLCodegenVisitor llVisitor;
        /* code */
        // std::cout << "Started demo.\n";
        llVisitor.load(argv[1]);
        // llVisitor.ASTIRtoLLVMIR();
        // std::cout << "Into dump.\n";
        llVisitor.walk();
        llVisitor.dumpLLVMIR();
    }
    catch(const std::runtime_error &e) 
    {
        std::cout << e.what() << std::endl;
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