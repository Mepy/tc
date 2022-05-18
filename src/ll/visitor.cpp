#include "visitor.hpp"
#include <iostream>

#define DEBUG 0
#define PRINT_INTER_RESULT 0
#define TEST_GETI_PUTI 0 // to evalute ARGS before INST

void LLCodegenVisitor::dumpLLVMIR() 
    {TheModule->print(llvm::outs(), nullptr);}

void LLCodegenVisitor::dumpAllMap()
{   
    // std::cout << "TypeMap:\n";
    // for(auto &it : TypeMap)
    // {
    //     std::cout << it.first << ": " << it.second->getTypeID() << '\n';
    // }
    // std::cout << "SymMap:\n";
    // for(auto &it : SymMap)
    // {
    //     std::cout << it.first << ": " << it.second.first << " " << it.second.second << '\n';
    // }
    // std::cout << "IdMapVal:\n";
    for(auto &it : IdMapVal)
    {
        std::cout << it.first << ": " << it.second->getName().str() << '\n';
    }
    std::cout << "IdMapAlloc:\n";
    for(auto &it : IdMapAlloc)
    {
        std::cout << it.first << ": " << it.second->getName().str() << '\n';
    }
    // std::cout << "JumpMap:\n";
    // for(auto &it : JumpMap)
    // {
    //     std::cout << it.first << ": " << it.second << '\n';
    // }
    // std::cout << "BrMap:\n";
    // for(auto &it : BrMap)
    // {
    //     std::cout << it.first << ": " << it.second.first << " " << it.second.second.first << " " << it.second.second.second << '\n';
    // }
    // std::cout << "StringMap:\n";
    // for(auto &it : StringMap)
    // {
    //     std::cout << it.first << ": " << it.second << '\n';
    // }
    // std::cout << "StringDstMap:\n";
    // for(auto &it : StringDstMap)
    // {
    //     std::cout << it.first << ": " << it.second << '\n';
    // }
    // std::cout << "TypeFuncMap:\n";
    // for(auto &it : TypeFuncMap)
    // {
    //     std::cout << it.first << ": ";
    //     for(auto &it2 : it.second)
    //     {
    //         std::cout << it2 << " ";
    //     }
    //     std::cout << '\n';
    // }
    // std::cout << "FuncMap:\n";
    // for(auto &it : FuncMap)
    // {
    //     std::cout << it.first << ": " << it.second << '\n';
    // }
    // std::cout << "ArgsMap:\n";
    // for(auto &it : ArgsMap)
    // {
    //     std::cout << it.first << ": ";
    //     for(auto &it2 : it.second)
    //     {
    //         std::cout << " " << it2;
    //     }
    //     std::cout << '\n';
    // }
}

void LLCodegenVisitor::builtinFuncInit()
{
    FormatMap["int"] = Builder->CreateGlobalStringPtr("%d");
}

llvm::FunctionType *LLCodegenVisitor::getFuncType(Block *block)
{
    std::vector<llvm::Type*> argTypes;
    #if DEBUG
        std::cout << "getFuncType: " << block->head.ord.size << '\n';
    #endif
    auto retType = TypeMap[(block->extra.ids[0])];
    for(auto ptr = block->extra.ids + 1; ptr - block->extra.ids < block->head.ord.size; ++ptr)
    {   
        #if DEBUG
            std::cout << "getFuncType: " << *ptr << '\n';
        #endif
        argTypes.push_back(TypeMap[(*ptr)]);
    }
    return llvm::FunctionType::get(retType, llvm::ArrayRef<llvm::Type*>(argTypes), false);
}

// assuming that the ASTIR file contains only one module: -> use block
void LLCodegenVisitor::ASTIRtoLLVMIR(std::string path) 
{
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

    // scanf
    auto scanf_func_callee = TheModule->getOrInsertFunction(
        "scanf", 
        llvm::FunctionType::get(
            llvm::IntegerType::getInt32Ty(*TheContext), 
            {llvm::PointerType::getInt8PtrTy(*TheContext)}, 
            true));

    // puts
    auto puts_func_callee = TheModule->getOrInsertFunction(
        "puts", 
        llvm::FunctionType::get(
            llvm::IntegerType::getInt32Ty(*TheContext), 
            {llvm::PointerType::getInt8PtrTy(*TheContext)}, 
            true));

    // getint
    auto getint_func_callee = TheModule->getOrInsertFunction(
        "getint", 
        llvm::FunctionType::get(
            llvm::IntegerType::getInt32Ty(*TheContext), 
            {}, 
            false));
    
    // putint
    auto putint_func_callee = TheModule->getOrInsertFunction(
        "putint", 
        llvm::FunctionType::get(
            llvm::Type::getVoidTy(*TheContext), 
            {llvm::IntegerType::getInt32Ty(*TheContext)}, 
            false));
#if TEST_GETI_PUTI
    bool lateInstrFlag = false;
    int nextBlockInd;
    int instrInd;
#endif
    for (int i=0; i<module.size; i++) 
    {
loop_start:
        auto& block = module.blocks[i];
        #if DEBUG
            std::cout << "Block Kind: " << block.kind << std::endl;
            std::cout << "Block Size: " << block.head.ord.size << std::endl;
            std::cout << "Block head size: " << sizeof(block.head.func) << std::endl;
        #endif
        switch (block.kind)
        {   
            case Kind::INST:
            {   
                #if TEST_GETI_PUTI
                    if (!lateInstrFlag && module.size > i && module.blocks[i+1].kind == Kind::ARGS)
                    {
                        lateInstrFlag = true;
                        instrInd = i;
                        i += 1;
                        goto loop_start;
                    }
                    else if (lateInstrFlag)
                    {
                        i = nextBlockInd;
                    }
                #endif
                auto BB = llvm::BasicBlock::Create(
                    *TheContext,
                    std::to_string(i),
                    main
                    // entry
                );
                Builder->SetInsertPoint(BB);
                builtinFuncInit();
                
                printfArgsV.push_back(Builder->CreateGlobalStringPtr("%d"));

                for (auto ptr = block.extra.insts; 
                ptr - block.extra.insts < block.head.ord.size; 
                ptr++) 
                {
                    #if DEBUG
                        std::cout << "INS:" << ptr->sort << std::endl;
                    #endif
                    llvm::Value *vptr = codegen(*ptr);

                    # if PRINT_INTER_RESULT
                        // std::cout << "IR: " << *vptr << std::endl;
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
                        #if DEBUG
                            std::cout << "J" << i;
                        #endif
                        JumpMap[i] = ptr->dst;
                    }
                    if (ptr->sort == Ins::Br) 
                    {   
                        #if DEBUG
                            std::cout << "B" << i;
                        #endif
                        BrMap[i] = std::make_pair(vptr, 
                            std::make_pair(ptr->src.id[0], ptr->src.id[1]));
                    }
                    if (ptr->sort == Ins::Call)
                    {
                        auto args_id = ptr->src.id[1];
                        auto &args_block = module.blocks[args_id];
                        if (args_block.head.ord.size == 0)
                        {
                            ArgsMap[i] = std::vector<llvm::Value *>();
                        }

                        std::vector<llvm::Value *> args;
                        for (auto ptr = args_block.extra.ids; 
                        ptr - args_block.extra.ids < args_block.head.ord.size; 
                        ptr++) 
                        {   
                            #if DEBUG
                                std::cout << "ARGS: push_back arg" << std::endl;
                            #endif
                            if (IdMapVal.find(*ptr) == IdMapVal.end())
                            {
                                throw std::runtime_error("Argument not found");
                            }
                            args.emplace_back(IdMapVal[*ptr]);
                        }
                        ArgsMap[args_id] = args;
                        llvm::Value* ret_val = codegen(*ptr);
                        if (ret_val == nullptr)
                        {
                            throw std::runtime_error("Return value should not be nullptr");
                        }                  
                    }
                }
                // break;
            }
            case Kind::TYPE:
            {
                auto BB = llvm::BasicBlock::Create(
                    *TheContext,
                    std::to_string(i),
                    main
                    // entry
                );
                Builder->SetInsertPoint(BB);

                int i = 0;
                for (auto ptr = block.extra.types; 
                ptr - block.extra.types < block.head.ord.size;
                ptr++) 
                {
                    #if DEBUG
                        std::cout << ptr->sort << std::endl;
                        std::cout << ptr->id << std::endl;
                    #endif

                    // auto type = *ptr;
                    auto ret_type_ptr = codegen(*ptr, i);
                    #if DEBUG
                        std::cout << "codegen OK" << std::endl;
                    #endif
                    switch (ptr->sort)
                    {
                        case ir::Type::Sort::Func:
                        {
                            std::vector<llvm::Type*> argTypes;
                            auto &block = module.blocks[ptr->id];
                            auto size = block.head.ord.size;
                            auto &retType = TypeMap[block.head.typefunc.ret];
                            if (size != 1)
                            {
                                argTypes.push_back(TypeMap[block.head.typefunc.param]);
                                if (size != 2)
                                {
                                    for (auto ptr = block.extra.ids; ptr - block.extra.ids < size; ++ptr)
                                    {
                                        argTypes.push_back(TypeMap[(*ptr)]);
                                    }
                                }
                            }
                            TypeFuncMap[i] = llvm::FunctionType::get(retType, llvm::ArrayRef<llvm::Type*>(argTypes), false);
                            
                            // getFuncType(&module.blocks[type.id]);
                            #if DEBUG
                                std::cout << "Not getFuncType's fault" << std::endl;
                            #endif
                            break;
                        }
                        case ir::Type::Sort::Array:
                        {
                            
                            // type.id is the block-id of Array spec (type, len)
                            auto &arr_block = module.blocks[ptr->id];
                            auto arr_type = arr_block.head.arr.type;
                            auto arr_len = arr_block.head.arr.Len;
                            TypeMap[i] = llvm::ArrayType::get(
                                TypeMap[arr_type], 
                                arr_len);
                            break;
                        }
                        default:
                        {
                            #if DEBUG
                                std::cout << "Keyword Processed in codegen." << std::endl;
                            #endif
                        }
                    }
                    i++;
                }
                break;   
            }
            case Kind::ARGS:
            {
                #if DEBUG
                    std::cout << "ARGS" << std::endl;
                #endif
                auto BB = llvm::BasicBlock::Create(
                    *TheContext,
                    std::to_string(i),
                    main
                    // entry
                );
                Builder->SetInsertPoint(BB);

                if (block.head.ord.size == 0)
                {
                    ArgsMap[i] = std::vector<llvm::Value *>();
                }

                std::vector<llvm::Value *> args;
                for (auto ptr = block.extra.ids; 
                ptr - block.extra.ids < block.head.ord.size; 
                ptr++) 
                {   
                    #if DEBUG
                        std::cout << "ARGS: push_back arg" << std::endl;
                    #endif
                    if (IdMapVal.find(*ptr) == IdMapVal.end())
                    {
                        throw std::runtime_error("Argument not found");
                    }
                    args.emplace_back(IdMapVal[*ptr]);
                }
                ArgsMap[i] = args;
                #if TEST_GETI_PUTI
                #if DEBUG
                    Builder->CreateCall(printf_func_callee, llvm::ArrayRef<llvm::Value*>(args), "printfCall");
                #endif
                    if (lateInstrFlag == true && module.blocks[i+1].kind != Kind::ARGS)
                    {
                        nextBlockInd = i+1;
                        i = instrInd;
                        goto loop_start;
                    }
                #endif
                break;
            }
            case Kind::SYMB:
            {
                auto BB = llvm::BasicBlock::Create(
                    *TheContext,
                    std::to_string(i),
                    main
                    // entry
                );
                Builder->SetInsertPoint(BB);

                #if DEBUG
                    std::cout << "SYMB size" << block.head.ord.size << std::endl;
                #endif

                for (auto ptr = block.extra.symbs; 
                ptr - block.extra.symbs < block.head.ord.size; 
                ptr++) 
                {
                    switch (ptr->sort)
                    {
                        case ir::Symbol::Sort::SUNO:
                        {
                            throw std::invalid_argument("SYM: ir::Type::Sort Unknown.");
                        }
                        case ir::Symbol::Sort::Const:
                        case ir::Symbol::Sort::Param:
                        case ir::Symbol::Sort::NonD:
                        {
                            SymMap[i] = std::make_pair<char, uint32_t>('T', uint32_t(ptr->info.type));
                            break;
                        }
                        case ir::Symbol::Sort::Ctor:
                        case ir::Symbol::Sort::CFun:
                        case ir::Symbol::Sort::CPrg:
                        case ir::Symbol::Sort::QFun:
                        case ir::Symbol::Sort::QPrg:
                        case ir::Symbol::Sort::Open:
                        case ir::Symbol::Sort::Clos:
                        {
                            SymMap[i] = std::make_pair<char, uint32_t>('B', uint32_t(ptr->info.block));
                            break;
                        }
                        default:
                        {
                            throw std::invalid_argument("SYM: ir::Symbol::Sort Invalid.");
                        }
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
                std::string content(block.extra.chars);
                StringMap[i] = content;
                break;
            }

            // case Kind::TARR:
            // {
            //     auto BB = llvm::BasicBlock::Create(
            //             *TheContext,
            //             std::to_string(i),
            //             main
            //             // entry
            //         );                
            //     break;
            // }
        
            // case Kind::TFUN:
            // {
            //     auto BB = llvm::BasicBlock::Create(
            //             *TheContext,
            //             std::to_string(i),
            //             main
            //             // entry
            //         );
            //     std::vector<llvm::Type *> args;
            //     for (auto ptr = (ir::Type *)block.extra.types;
            //     ptr - (ir::Type *)block.extra.types < block.head.ord.size;
            //     ptr++)
            //     {
            //         switch (ptr->sort)
            //         {
            //             case ir::Type::Sort::SUNO:
            //             {
            //                 throw std::invalid_argument("TFUN: Sort Unknown.");
            //             }
            //             case ir::Type::Sort::Unit:
            //             {
            //                 args.push_back(llvm::Type::getVoidTy(*TheContext));
            //                 break;
            //             }
            //             case ir::Type::Sort::Bool:
            //             {
            //                 args.push_back(llvm::Type::getInt1Ty(*TheContext));
            //                 break;
            //             }
            //             case ir::Type::Sort::Char:
            //             {
            //                 args.push_back(llvm::Type::getInt8Ty(*TheContext));
            //                 break;
            //             }
            //             case ir::Type::Sort::Int:
            //             {
            //                 args.push_back(llvm::Type::getInt32Ty(*TheContext));
            //                 break;
            //             }
            //             case ir::Type::Sort::Float:
            //             {
            //                 args.push_back(llvm::Type::getFloatTy(*TheContext));
            //                 break;
            //             }
            //             case ir::Type::Sort::Ptr:
            //             {
            //                 throw std::runtime_error("Pointer types not supported.");
            //             }
            //             case ir::Type::Sort::Array:
            //             {
                            
            //             }
            //             case ir::Type::Sort::Func:
            //             {
            //                 for (auto ptr2 = block.extra.ids;
            //                 ptr2 - block.extra.ids < block.head.ord.size;
            //                 ptr2++)
            //                 {
            //                     TypeFuncMap[i].push_back(*ptr);
            //                 }
            //             }
            //             case ir::Type::Sort::Tuple:
            //             {
            //                 throw std::runtime_error("Tuple types not supported.");
            //             }
            //             case ir::Type::Sort::ADT:
            //             {
            //                 throw std::runtime_error("ADT types not supported.");
            //             }
            //             case ir::Type::Sort::ADTR:
            //             {
            //                 throw std::runtime_error("ADTR types not supported.");
            //             }
            //             default:
            //                 break;
            //         }
            //         TypeFuncMap[i] = args;
            //     }
            //     break;
            // }
            // case Kind::FUNC:
            // {
            //     auto BB = llvm::BasicBlock::Create(
            //             *TheContext,
            //             std::to_string(i),
            //             main
            //             // entry
            //         );
            //     auto func_type = TypeFuncMap[block.head.func.type];
            //     auto ret_type = func_type[0];
            //     auto param_types = std::vector<llvm::Type *>(func_type.begin() + 1, func_type.end());
            //     auto func = llvm::Function::Create(
            //         llvm::FunctionType::get(ret_type, param_types, false),
            //         llvm::Function::ExternalLinkage,
            //         std::to_string(i),
            //         *TheModule
            //     );
            //     auto entry = llvm::BasicBlock::Create(
            //         *TheContext,
            //         "entry",
            //         func
            //     );
            //     Builder->SetInsertPoint(entry);

            //      // TODO: params and body
            // }
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
                // **set insert point for the next iteration to avoid empty-block error**
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

    #if DEBUG
        LLCodegenVisitor::dumpAllMap();
    #endif

    Builder->CreateRet(
        llvm::ConstantInt::get(llvm::IntegerType::getInt32Ty(*TheContext), 0)
    );

    return;
}