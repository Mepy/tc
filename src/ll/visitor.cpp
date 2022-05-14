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

    // printf
    auto printf_func_type = llvm::FunctionType::get(
        Builder->getInt32Ty(),
        llvm::IntegerType::getInt8Ty(*TheContext)->getPointerTo(),
        true
    );
    std::vector<llvm::Value *> ArgsV;
    auto printf_func_callee = TheModule->getOrInsertFunction("printf", printf_func_type);

    // puts
    std::vector<llvm::Type*> params_type;
    params_type.push_back(
        llvm::IntegerType::getInt8Ty(*TheContext)->getPointerTo() // char*
    );
    auto puts_func_type = llvm::FunctionType::get(
        Builder->getInt32Ty(), // return_type
        llvm::ArrayRef<llvm::Type*>(params_type), // params_type, but : ArrayRef<Type*>
        false // UNKNOWN
    ); 

    // call function named puts
    auto puts_func_callee = TheModule->getOrInsertFunction("puts", puts_func_type);

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
                    if (vptr != nullptr ) {
                        // DEBUG: PRINT ALL RETURN VALUES

                        if (vptr->getType()->isIntegerTy(8) /*char*/ || 
                            vptr->getType()->isIntegerTy(32) /*int*/ )
                        {
                            ArgsV.push_back(vptr);
                            Builder->CreateCall(printf_func_callee, ArgsV, "printfCall");
                            // std::cout << ArgsV.size();
                            ArgsV.pop_back();
                        }
                        if (vptr->getType()->isPointerTy() )
                        {
                            Builder->CreateCall(puts_func_callee,
                                vptr, "putsCall");
                        }
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

            case Kind::CSTR:
            {
                
                auto BB = llvm::BasicBlock::Create(
                        *TheContext,
                        std::to_string(i),
                        main
                        // entry
                    );
                std::string content((char *)(module.blocks[i].bytes));
                StringMap[i] = content;
                break;
            }

            case Kind::TARR:
            {
                auto BB = llvm::BasicBlock::Create(
                        *TheContext,
                        std::to_string(i),
                        main
                        // entry
                    );                
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
        if (prevFlag) 
        {
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
        else 
        {
            // if (block.getInstList().empty()) 
            {
                // std::cout << i << "\n";
                // set insert point for the next iteration to avoid empty-block error
                // TODO: final iter?
                Builder->SetInsertPoint(&block);
                prevFlag = true;
            }
        }

        if (StringMap.find(i) != StringMap.end() ) 
        {
            Builder->SetInsertPoint(&block);
            IdMapVal[StringdstMap[i]] = Builder->CreateGlobalStringPtr(StringMap[i]);
        }
        i++;
    }

    Builder->CreateRet(
        llvm::ConstantInt::get(llvm::IntegerType::getInt32Ty(*TheContext), 0)
        // Builder->CreateLoad()
    );

    return;
}