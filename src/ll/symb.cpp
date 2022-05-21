#include "visitor.hpp"

using Sort = ir::Symbol::Sort;
void    LLCodegenVisitor::load_symb()
{
    { // buitlin 
    this->IdMapVal[1] = llvm::ConstantInt::getTrue(*TheContext);
    this->IdMapVal[2] = llvm::ConstantInt::getFalse(*TheContext);
    this->FuncMap[5] = llvm::Function::Create(
        ((llvm::FunctionType*)(this->TypeMap[7]))
        , llvm::Function::ExternalLinkage, "geti", *TheModule
    );
    this->FuncMap[6] = llvm::Function::Create(
        ((llvm::FunctionType*)(this->TypeMap[8]))
        , llvm::Function::ExternalLinkage, "puti", *TheModule
    );
    this->FuncMap[7] = llvm::Function::Create(
        ((llvm::FunctionType*)(this->TypeMap[10]))
        , llvm::Function::ExternalLinkage, "puts", *TheModule
    );
    this->FuncMap[8] = llvm::Function::Create(
        ((llvm::FunctionType*)(this->TypeMap[11]))
        , llvm::Function::ExternalLinkage, "putchar", *TheModule
    );
    }
    auto blocks = this->module.blocks;
    auto& block = blocks[1];
    auto size   = block.head.ord.size;
    auto symbs  = block.extra.symbs;
    llvm::Twine name("fn_");
    for(auto i = 9;i<size; ++i)
    {
        auto symb = symbs[i];
        switch(symb.sort)
        {
        case Sort::CFun:
        case Sort::CPrg:
        {
            auto func_block = &blocks[symb.info.block]; // Kind = FUNC
            auto info = func_block->head.func;
            auto func = this->func = this->FuncMap[i] = 
                llvm::Function::Create(((llvm::FunctionType*)(this->TypeMap[info.type]))
                , llvm::Function::ExternalLinkage, name.concat(std::to_string(i)), *TheModule
                );
            auto param_block = &blocks[info.param];
            auto params = param_block->extra.ids;

            auto size = param_block->head.ord.size;
            for(auto i=0;i<size;++i)
                this->IdMapVal.insert(std::make_pair<>(
                    params[i], func->getArg(i)
                ));
            auto BB = llvm::BasicBlock::Create(*TheContext, "", func);
            auto ID = info.body;
            BlockStack.push(std::make_pair<>(BB, &blocks[ID]));
            BasicBlockMap.insert(std::make_pair<>(ID, BB));
            break;
        }
        case Sort::Const:
        case Sort::Param:
        case Sort::NonD:
        case Sort::Ctor:
        case Sort::Brch:
            break;
        default:
            throw std::invalid_argument("SYMB: Sort Unknown.");
        }
    
    }
}

