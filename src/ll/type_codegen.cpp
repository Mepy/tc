#include "visitor.hpp"

using Sort = ir::Type::Sort;
void    LLCodegenVisitor::load_type()
{
    auto& block = this->module.blocks[0];
    auto size   = block.head.ord.size;
    auto types  = block.extra.types;
    for(auto i = 0;i<size; ++i)
    {
        auto type = types[i];
        switch(type.sort)
        {
        case Sort::Unit:
        {
            this->TypeMap.insert(std::make_pair<>(
                i, llvm::Type::getVoidTy(*TheContext)
            ));
            break;
        }
        case Sort::Bool:
        {
            this->TypeMap.insert(std::make_pair<>(
                i, llvm::Type::getInt1Ty(*TheContext)
            ));
            break;
        }
        case Sort::Char:
        {
            this->TypeMap.insert(std::make_pair<>(
                i, llvm::Type::getInt8Ty(*TheContext)
            ));
            break;
        }
        case Sort::Int:
        {
            this->TypeMap.insert(std::make_pair<>(
                i, llvm::Type::getInt64Ty(*TheContext)
            ));
            break;
        }
        case Sort::Float:
        {
            this->TypeMap.insert(std::make_pair<>(
                i, llvm::Type::getDoubleTy(*TheContext)
            ));
            break;
        }
        case Sort::Ptr:
        {
            auto src = this->TypeMap[type.id];
            this->TypeMap.insert(std::make_pair<>(
                i, llvm::PointerType::get(src, 0/*Address Space*/ )
            ));
            break;
        }
        case Sort::Array:
        {
            auto& block = this->module.blocks[type.id];
            auto src = TypeMap[block.head.arr.type];
            auto len = block.head.arr.Len;
            this->TypeMap.insert(std::make_pair<>(
                i, llvm::ArrayType::get(src, len)
            ));
            break;
        }
        case Sort::Func:
        {
            std::vector<llvm::Type*> argTypes;
            auto& block = module.blocks[type.id];
            auto size = block.head.ord.size;
            auto ids = block.extra.ids;
            auto retType = this->TypeMap[ids[0]];

            for(auto i=1;i<size;i++)
                argTypes.push_back(TypeMap[ids[i]]);
            this->TypeMap.insert(std::make_pair<>(
                i, llvm::FunctionType::get(retType, llvm::ArrayRef<llvm::Type*>(argTypes), false)
            ));
            break;
        }
        case Sort::Tuple:
        {
            throw std::runtime_error("Tuple types not supported.");
        }
        case Sort::ADT:
        {
            throw std::runtime_error("ADT types not supported.");
        }
        case Sort::ADTR:
        {
            throw std::runtime_error("ADTR types not supported.");
        }
        default:
            throw std::invalid_argument("TYPE: Sort Unknown.");
        }
    
    }
}

