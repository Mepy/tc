#include "visitor.hpp"

llvm::Type *LLCodegenVisitor::codegen(const ir::Type &type, int i /*index*/)
{
    switch (type.sort)
    {
        case ir::Type::Sort::SUNO:
        {
            throw std::invalid_argument("TYPE: Sort Unknown.");
        }
        case ir::Type::Sort::Unit:
        {
            TypeMap[i] = llvm::Type::getVoidTy(*TheContext);
            return TypeMap[i];
        }
        case ir::Type::Sort::Bool:
        {
            TypeMap[i] = llvm::Type::getInt1Ty(*TheContext);
            return TypeMap[i];
        }
        case ir::Type::Sort::Char:
        {
            TypeMap[i] = llvm::Type::getInt8Ty(*TheContext);
            return TypeMap[i];
        }
        case ir::Type::Sort::Int:
        {
            TypeMap[i] = llvm::Type::getInt32Ty(*TheContext);
            return TypeMap[i];
        }
        case ir::Type::Sort::Float:
        {
            TypeMap[i] = llvm::Type::getFloatTy(*TheContext);
            return TypeMap[i];
        }
        case ir::Type::Sort::Ptr:
        {
            // Info(ID) refers to the type of the pointer
            TypeMap[i] = llvm::PointerType::get(TypeMap[type.id], 0 /*Address Space*/);
        }
        case ir::Type::Sort::Array:
        {
            //impl in visitor.cpp
            break;
        }
        case ir::Type::Sort::Func:
        {
            //impl in visitor.cpp
            break;
        }
        case ir::Type::Sort::Tuple:
        {
            throw std::runtime_error("Tuple types not supported.");
        }
        case ir::Type::Sort::ADT:
        {
            throw std::runtime_error("ADT types not supported.");
        }
        case ir::Type::Sort::ADTR:
        {
            throw std::runtime_error("ADTR types not supported.");
        }
    
        default:
            break;
    };
    return nullptr;
}