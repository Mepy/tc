#include "./visitor.hpp"
#include <iostream>
#include <string>

using namespace llvm;

int main(int argc, char* argv[]) 
{
    if(argc>=2)
    try
    {
        LLCodegenVisitor llVisitor;
        /* code */
        // std::cout << "Started demo.\n";
        llVisitor.ASTIRtoLLVMIR(argv[1]);
        // std::cout << "Into dump.\n";
        llVisitor.dumpLLVMIR();
    }
    catch (const std::runtime_error &e) 
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