#include "visitor.hpp"
#include "../ast/convention.hpp"
using namespace tc::ast;
using Sort = ir::Symbol::Sort;
void    LLCodegenVisitor::load_symb()
{
    { // buitlin with convention
    this->IdMapVal[E_TRUE] = llvm::ConstantInt::getTrue(*TheContext);
    this->IdMapVal[E_FALSE] = llvm::ConstantInt::getFalse(*TheContext);

    this->FuncMap[E_GETC] = llvm::Function::Create(
        ((llvm::FunctionType*)(this->TypeMap[T_2C]))
        , llvm::Function::ExternalLinkage, "getchar", *TheModule
    ); 
    this->FuncMap[E_PUTC] = llvm::Function::Create(
        ((llvm::FunctionType*)(this->TypeMap[T_C2U]))
        , llvm::Function::ExternalLinkage, "putchar", *TheModule
    );
    this->FuncMap[E_GETI] = llvm::Function::Create(
        ((llvm::FunctionType*)(this->TypeMap[T_2I]))
        , llvm::Function::ExternalLinkage, "geti", *TheModule
    );
    this->FuncMap[E_PUTI] = llvm::Function::Create(
        ((llvm::FunctionType*)(this->TypeMap[T_I2U]))
        , llvm::Function::ExternalLinkage, "puti", *TheModule
    );
    this->FuncMap[E_GETS] = llvm::Function::Create(
        ((llvm::FunctionType*)(this->TypeMap[T_PC2PC]))
        , llvm::Function::ExternalLinkage, "gets", *TheModule
    );
    this->FuncMap[E_PUTS] = llvm::Function::Create(
        ((llvm::FunctionType*)(this->TypeMap[T_PC2U]))
        , llvm::Function::ExternalLinkage, "putstr", *TheModule
    );
    this->FuncMap[E_SGETI] = llvm::Function::Create(
        ((llvm::FunctionType*)(this->TypeMap[T_PC2I]))
        , llvm::Function::ExternalLinkage, "atoi", *TheModule
    );
    this->FuncMap[E_GETF] = llvm::Function::Create(
        ((llvm::FunctionType*)(this->TypeMap[T_2F]))
        , llvm::Function::ExternalLinkage, "getf", *TheModule
    );
    this->FuncMap[E_PUT1F] = llvm::Function::Create(
        ((llvm::FunctionType*)(this->TypeMap[T_F2U]))
        , llvm::Function::ExternalLinkage, "put1f", *TheModule
    );
    this->FuncMap[9] = llvm::Function::Create(
        ((llvm::FunctionType*)(this->TypeMap[13]))
        , llvm::Function::ExternalLinkage, "gets", *TheModule
    );
    this->FuncMap[10] = llvm::Function::Create(
        ((llvm::FunctionType*)(this->TypeMap[14]))
        , llvm::Function::ExternalLinkage, "getchar", *TheModule
    );
    }
    auto blocks = this->module.blocks;
    auto& block = blocks[1];
    auto size   = block.head.ord.size;
    auto symbs  = block.extra.symbs;
    llvm::Twine name("fn_");
    for(unsigned i = E_END;i<size; ++i)
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

