#include "visitor.hpp"
#include <iostream>

// #define DEBUG 0

void LLCodegenVisitor::dumpLLVMIR() 
    {TheModule->print(llvm::outs(), nullptr);}

// assuming that the ASTIR file contains only one module: -> use block
void LLCodegenVisitor::ASTIRtoLLVMIR(std::string path) {
    codegen::Module module(path);
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
    auto printf_func_callee = TheModule->getOrInsertFunction(
        "printf", 
        llvm::FunctionType::get(
            llvm::IntegerType::getInt32Ty(*TheContext), 
            {llvm::PointerType::getInt8PtrTy(*TheContext)}, 
            true));
    std::vector<llvm::Value *> printfArgsV;

    // puts
    auto puts_func_callee = TheModule->getOrInsertFunction(
        "puts", 
        llvm::FunctionType::get(
            llvm::IntegerType::getInt32Ty(*TheContext), 
            {llvm::PointerType::getInt8PtrTy(*TheContext)}, 
            true));

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
                
                printfArgsV.push_back(Builder->CreateGlobalStringPtr("%d"));

                for (Ins *ptr = (Ins *)module.blocks[i].bytes; 
                ptr - (Ins *)module.blocks[i].bytes < module.blocks[i].size; 
                ptr++) 
                {
                    // std::cout << ptr->sort << std::endl;
                    llvm::Value *vptr = codegen(*ptr);

                    # ifdef DEBUG
                    // DEBUG: PRINT ALL RETURN VALUES
                        if (vptr != nullptr ) {
                            if (vptr->getType()->isIntegerTy(8) /*char*/ || 
                                vptr->getType()->isIntegerTy(32) /*int*/ )
                            {
                                printfArgsV.push_back(vptr);
                                Builder->CreateCall(printf_func_callee, printfArgsV, "printfCall");
                                // std::cout << printfArgsV.size();
                                printfArgsV.pop_back();
                            }
                            if (vptr->getType()->isPointerTy() )
                            {
                                Builder->CreateCall(puts_func_callee,
                                    vptr, "putsCall");
                            }
                        }
                    # endif
                    
                    if (ptr->sort == Ins::Jump)
                    {   
                        #ifdef DEBUG
                            std::cout << "J" << i;
                        #endif
                        JumpMap[i] = ptr->dst;
                    }
                    if (ptr->sort == Ins::Br) 
                    {   
                        #ifdef DEBUG
                            std::cout << "B" << i;
                        #endif
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
            IdMapVal[StringDstMap[i]] = Builder->CreateGlobalStringPtr(StringMap[i]);
        }
        i++;
    }

    Builder->CreateRet(
        llvm::ConstantInt::get(llvm::IntegerType::getInt32Ty(*TheContext), 0)
    );

    return;
}