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

void LLCodegenVisitor::main_beg()
{
    auto main_block = &this->module.blocks[2];
    auto main_type = llvm::FunctionType::get(
        llvm::IntegerType::getInt32Ty(*TheContext),
        false);
    auto main = llvm::Function::Create(
        main_type, 
        llvm::Function::ExternalLinkage, 
        "main", 
        *TheModule);
    auto main_BB = llvm::BasicBlock::Create(*TheContext, "entry", main);

    this->BlockStack.push(std::make_pair<>(main_BB, main_block));
    this->BasicBlockMap.insert(std::make_pair<>(2, main_BB));
}

void LLCodegenVisitor::main_end()
{
    auto main = TheModule->getFunction("main");
    auto list = &main->getBasicBlockList();
    auto BB = &list->back();
    this->Builder->SetInsertPoint(BB);
    this->Builder->CreateRet(
    llvm::ConstantInt::get(llvm::IntegerType::getInt32Ty(*TheContext), 0)
    );
}