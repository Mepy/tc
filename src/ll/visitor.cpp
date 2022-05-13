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
        // std::cout << module.blocks[i].kind << std::endl;
        switch (module.blocks[i].kind)
        {   
            case Kind::INST:
            {
                auto BB = llvm::BasicBlock::Create(
                    *TheContext,
                    std::to_string(i),
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
                    if (vptr != nullptr && vptr->getType()->isIntegerTy()) {
                        // DEBUG: PRINT ALL RETURN VALUES

                        // auto IntType = llvm::IntegerType::getInt32Ty(*TheContext);
                        // llvm::IntegerType *CI = llvm::cast<llvm::Integer>(vptr);
                        ArgsV.push_back(vptr);
                        Builder->CreateCall(func_callee, ArgsV, "printfCall");
                        // std::cout << ArgsV.size();
                        ArgsV.pop_back();
                    }
                    if (ptr->sort == Ins::Jump)
                    {
                        // std::cout << "J" << i;
                        JumpMap[i] = ptr->dst;
                    }
                    if (ptr->sort == Ins::Br) 
                    {
                        // std::cout << "B" << i;
                        BrMap[i] = std::make_pair(vptr, 
                            std::make_pair(ptr->src.id[0], ptr->src.id[1]));
                    }
                }
                break;
            }
        
            default:
                auto BB = llvm::BasicBlock::Create(
                        *TheContext,
                        std::to_string(i),
                        main
                        // entry
                    );
                break;
        }
    }

    //Impl Br & Jump
    int i = 0;
    bool prevFlag = false;
    for (auto &block : main->getBasicBlockList() )
    {
        if (prevFlag) {
            //to avoid empty llvm::BasicBlock induced error
            Builder->CreateBr(&block);
            prevFlag = false;
        }
        // std::cout << i;
        if (JumpMap.find(i) != JumpMap.end()) 
        {
            Builder->SetInsertPoint(&block);
            auto target_it = main->getBasicBlockList().begin();
            for (int j=0; j<JumpMap[i]; j++, target_it++);
            Builder->CreateBr(&*target_it);
        }
        else if (BrMap.find(i) != BrMap.end())
        {
            Builder->SetInsertPoint(&block);
            auto target_true_it = main->getBasicBlockList().begin();
            auto target_false_it = main->getBasicBlockList().begin();
            for (int j=0; j<BrMap[i].second.first; j++, target_true_it++);
            for (int k=0; k<BrMap[i].second.second; k++, target_false_it++);
            Builder->CreateCondBr(BrMap[i].first, &*target_true_it, &*target_false_it);
        }
        else {
            if (block.getInstList().empty()) {
                // std::cout << i << "\n";
                //set insert point for the next iteration
                //TODO: final iter?
                Builder->SetInsertPoint(&block);
                prevFlag = true;
            }
        }
        i++;
    }

    Builder->CreateRet(
        llvm::ConstantInt::get(llvm::IntegerType::getInt32Ty(*TheContext), 0)
        // Builder->CreateLoad()
    );

    return;
}