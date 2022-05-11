#include "visitor.hpp"
// #include "src/ast/ir.hpp"
// #include <llvm/IR/Value.h>
#include <iostream>
#include <string>

llvm::Value *LLCodegenVisitor::codegen(const Ins &ins) {
    // std::cout << "in codegen\n";
    switch (ins.sort) 
    {
        case Ins::IImm:
        {
            llvm::Value* IImm_ptr = llvm::ConstantInt::get(
                llvm::Type::getInt32Ty(*TheContext), 
                ins.src.Iimm);
            // Builder->CreateAlloca(
            //     llvm::Type::getInt64Ty(*TheContext),
            //     nullptr /*arraysize*/,
            //     ""/*name*/);

            // Builder->CreateStore(IImm_ptr, IdMap[ins.dst], false/*isvolatile*/);
            
            IdMapVal[ins.dst] = IImm_ptr;
            return nullptr;
            //e.g.
            // %Iimm0 = alloca i64, align 8
            // store i64 1234, i64* %Iimm0, align 4
        }
        case Ins::BImm:
        {
            auto *BImm_ptr = llvm::ConstantInt::get(
                llvm::Type::getInt1Ty(*TheContext),
                ins.src.Bimm
            );
            // auto Store_ptr = Builder->CreateAlloca(
            //     llvm::Type::getInt1Ty(*TheContext),
            //     nullptr,
            //     ""
            // );
            // Builder->CreateStore(BImm_ptr, Store_ptr, false);
            IdMapVal[ins.dst] = BImm_ptr;
            return BImm_ptr;
        }
        case Ins::CImm: //Char?
        {
            auto *CImm_ptr = llvm::ConstantInt::get(
                llvm::Type::getInt8Ty(*TheContext),
                ins.src.Cimm
            );
            // auto Store_ptr = Builder->CreateAlloca(
            //     llvm::Type::getInt8Ty(*TheContext),
            //     nullptr,
            //     ""
            // );
            // Builder->CreateStore(CImm_ptr, Store_ptr, false);
            IdMapVal[ins.dst] = CImm_ptr;
            return CImm_ptr;
        }
        case Ins::FImm:
        {
            auto *FImm_ptr = llvm::ConstantInt::get(
                llvm::Type::getDoubleTy(*TheContext),
                ins.src.Fimm
            );
            // auto Store_ptr = Builder->CreateAlloca(
            //     llvm::Type::getDoubleTy(*TheContext),
            //     nullptr,
            //     ""
            // );
            // Builder->CreateStore(FImm_ptr, Store_ptr, false);  
            IdMapVal[ins.dst] = FImm_ptr;
            return FImm_ptr;          
        }
        case Ins::IAdd:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("IAdd: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateAdd(Val1_it->second, Val2_it->second, "");
            // llvm::BinaryOperator::CreateAdd(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::ISub:
        {
            
        }
        case Ins::IMul:
        {

        }
        case Ins::IDiv:
        {

        }
        case Ins::IMod:
        {

        }

        case Ins::Alloc:
        {
            auto val_it = IdMapVal.find(ins.src.id[0]);
            if (val_it == IdMapVal.end() ){
                throw std::invalid_argument("Alloc: src id not found.");
            }
            std::string name = std::to_string(val_it->first);
            llvm::Value *ret_val = val_it->second;
            llvm::Type *type = ret_val->getType();

            //??
            IdMapAlloc[ins.dst] = Builder->CreateAlloca(type, nullptr /*size*/, name);
            Builder->CreateStore(ret_val, IdMapAlloc[ins.dst]);
            // IdMapAlloc[ins.dst] = alloca_inst;
            // std::cout << alloca_inst->getType()->getScalarType();
            return ret_val;
        }

        case Ins::Set:
        {
            // auto ptr_it = IdMapAlloc.find(ins.dst);
            if (IdMapAlloc[ins.dst] == nullptr ) {
                throw std::invalid_argument("Set: dst(ptr) id not found.");
            }
            // auto val_it = IdMapVal.find(ins.src.id[0]);
            if (IdMapVal[ins.src.id[0]] == nullptr ) {
                throw std::invalid_argument("Set: src(val) id not found.");
            }
            llvm::Value *index;
            if (IdMapAlloc[ins.dst]->isArrayAllocation() ) 
            {
                llvm::Value *index = llvm::ConstantInt::get(
                    llvm::Type::getInt32Ty(*TheContext), ins.src.id[1]);

                llvm::Value *val_ptr = Builder->CreateGEP(
                    IdMapAlloc[ins.src.id[0]]->getType(),
                    IdMapAlloc[ins.src.id[0]], 
                    index, 
                    std::to_string(ins.src.id[0])
                );

                Builder->CreateStore(IdMapVal[ins.src.id[0]], val_ptr);
            }
            else
            {
                // if (ins.src.id[1] != 0) 
                // {
                    // TODO: this can be a warning, not an error?
                // throw std::invalid_argument("Set: src(ptr) id mapped to non-ptr. But offset is non-zero.");
                // }
                // index = llvm::ConstantInt::get(
                //     llvm::Type::getInt32Ty(*TheContext), 0);
                Builder->CreateStore(IdMapVal[ins.src.id[0]], IdMapAlloc[ins.dst]);
            }
            return nullptr;
        }
        case Ins::Get:
        {   
            // auto ptr_it = IdMapAlloc.find(ins.src.id[0]);
            if (IdMapAlloc[ins.src.id[0]] == nullptr ) {
                throw std::invalid_argument("Get: src(ptr) id not found.");
            }
            // std::string name = std::to_string(ptr_it->first);
            // auto base_ptr = ptr_it->second;
            // auto base_type = base_ptr->getType();
            // std::cout << base_ptr->getType()->isPointerTy();
            if (IdMapAlloc[ins.src.id[0]]->isArrayAllocation())
            {
                //pointer-type: add offset to it
                llvm::Value *index = llvm::ConstantInt::get(llvm::Type::getInt32Ty(*TheContext), ins.src.id[1]);
                
                llvm::Value *val_ptr = Builder->CreateGEP(
                    IdMapAlloc[ins.src.id[0]]->getType(),
                    IdMapAlloc[ins.src.id[0]], 
                    index, 
                    std::to_string(ins.src.id[0])
                );

                IdMapVal[ins.dst] = Builder->CreateLoad(val_ptr);
                //??
            }
            else 
            {
                // non-array: should not have non-zero offset field
                if (ins.src.id[1] != 0) 
                {
                    // TODO: this can be a warning, not an error?
                    throw std::invalid_argument("Get: src(ptr) id mapped to non-ptr. But offset is non-zero.");
                }
                // ret_val = base_ptr;
                // index = llvm::ConstantInt::get(llvm::Type::getInt32Ty(*TheContext), 0);
                IdMapVal[ins.dst] = Builder->CreateLoad(IdMapAlloc[ins.src.id[0]]);
            }
            return IdMapVal[ins.dst];
        }
        default:
            break;
    }
    return nullptr;
}
