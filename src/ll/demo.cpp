#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>

using namespace llvm;
int main() 
{
    LLVMContext context;
    auto module = new Module("demo.ll", context);
    
    // entry is a basic block of the main function
    // therefore the entry of main
    auto main_type = FunctionType::get(IntegerType::getInt32Ty(context),false);
    auto main = Function::Create(main_type, Function::ExternalLinkage, "main", module);
    auto entry = BasicBlock::Create(context,"entry",main);

    // use IRBuilder to insert IR
    // which wiil insert instructions in entry
    IRBuilder<> builder(context);
    builder.SetInsertPoint(entry);
    
    
    std::vector<Type*> params_type;
    params_type.push_back(
        IntegerType::getInt8Ty(context)->getPointerTo() // char*
    );

    // int(char*)
    auto func_type = FunctionType::get(
        builder.getInt32Ty(), // return_type
        ArrayRef<Type*>(params_type), // params_type, but : ArrayRef<Type*>
        false // UNKNOWN
    ); 

    // call function named puts
    auto func_callee = module->getOrInsertFunction("puts", func_type);
    auto arguments = builder.CreateGlobalStringPtr("demo LLVM IR!\n");
    builder.CreateCall(func_callee, arguments);
    
    // return 0
    builder.CreateRet(
        ConstantInt::get(IntegerType::getInt32Ty(context), 0)
    );

    // print LLVM IR to stdout
    module->print(llvm::outs(), nullptr);

    delete module;
}
