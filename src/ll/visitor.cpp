#include "visitor.hpp"
#include <iostream>

void LLCodegenVisitor::dumpLLVMIR() 
    {TheModule->print(llvm::outs(), nullptr);}

void LLCodegenVisitor::ASTIRtoLLVMIR(std::string path) {
    codegen::Module module(path);
    //assuming that the ASTIR file contains only one module: -> use block
    // std::cout << "Module loaded." << std::endl;

    auto main_type = llvm::FunctionType::get(
        llvm::IntegerType::getInt32Ty(*TheContext),
        false);
    auto main = llvm::Function::Create(
        main_type, 
        llvm::Function::ExternalLinkage, 
        "main", 
        *TheModule);

    // std::vector<llvm::Type*> param_type;
    // param_type.push_back(
    //     llvm::IntegerType::getInt8Ty(*TheContext)->getPointerTo()
    // );

    auto func_type = llvm::FunctionType::get(
        Builder->getInt32Ty(),
        llvm::IntegerType::getInt8Ty(*TheContext)->getPointerTo(),
        true
    );

    std::vector<llvm::Value *> ArgsV;

    auto func_callee = TheModule->getOrInsertFunction("printf", func_type);

    for (int i=0; i<module.size; i++) {
        // auto block = module.blocks[i]; !!!
        switch (module.blocks[i].kind)
        {
            case Kind::INST:
            {
                auto BB = llvm::BasicBlock::Create(
                    *TheContext,
                    "entry",
                    main
                    // entry
                );
                Builder->SetInsertPoint(BB);
                ArgsV.push_back(Builder->CreateGlobalStringPtr("%d"));
                for (Ins *ptr = (Ins *)module.blocks[i].bytes; 
                ptr - (Ins *)module.blocks[i].bytes < module.blocks[i].size; 
                ptr++) 
                {
                    // std::cout << ptr->sort << std::endl;
                    llvm::Value *vptr = codegen(*ptr);
                    if (vptr != nullptr && vptr->getType()->isIntegerTy(32)) {
                        // auto IntType = llvm::IntegerType::getInt32Ty(*TheContext);
                        // llvm::IntegerType *CI = llvm::cast<llvm::Integer>(vptr);
                        ArgsV.push_back(vptr);
                        Builder->CreateCall(func_callee, ArgsV, "printfCall");
                        // std::cout << ArgsV.size();
                        ArgsV.pop_back();
                    }
                }
                
                // std::cout << "Out of instr_codegen loop.\n";
                break;
            }
        
            default:
                break;
        }
    }

    Builder->CreateRet(
        llvm::ConstantInt::get(llvm::IntegerType::getInt32Ty(*TheContext), 0)
        // Builder->CreateLoad()
    );

    return;
}