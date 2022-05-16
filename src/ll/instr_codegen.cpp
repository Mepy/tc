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
            
            IdMapVal[ins.dst] = IImm_ptr;
            return IImm_ptr;
            //e.g.
            // %Iimm0 = alloca i64, align 8
            // store i64 1234, i64* %Iimm0, align 4
        }
        // case Ins::BImm:
        // {
        //     auto *BImm_ptr = llvm::ConstantInt::get(
        //         llvm::Type::getInt1Ty(*TheContext),
        //         ins.src.Bimm
        //     );
        //     IdMapVal[ins.dst] = BImm_ptr;
        //     return BImm_ptr;
        // }
        case Ins::CImm: //Char?
        {
            auto *CImm_ptr = llvm::ConstantInt::get(
                llvm::Type::getInt8Ty(*TheContext),
                ins.src.Cimm
            );
            IdMapVal[ins.dst] = CImm_ptr;
            return CImm_ptr;
        }
        case Ins::FImm:
        {
            auto *FImm_ptr = llvm::ConstantInt::get(
                llvm::Type::getDoubleTy(*TheContext),
                ins.src.Fimm
            );  
            IdMapVal[ins.dst] = FImm_ptr;
            return FImm_ptr;          
        }
        case Ins::SImm:
        {
            auto *SImm_ptr = Builder->CreateGlobalStringPtr(
                ins.src.SImm
            );
            IdMapVal[ins.dst] = SImm_ptr;
            return SImm_ptr;
        }
        case Ins::CStr:
        {
            if (StringMap.find(ins.src.id[0]) != StringMap.end())
            {
                auto *CStr_ptr = Builder->CreateGlobalStringPtr(
                    StringMap[ins.src.id[0]]
                );
                IdMapVal[ins.dst] = CStr_ptr;
                return IdMapVal[ins.dst];
            }
            else 
            {
                // assume that CSTR decl before reference
                // throw std::invalid_argument("CSTR src id not found in StringMap.");
                StringDstMap[ins.src.id[0]] = ins.dst;
                return nullptr;
            }
            break;
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
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("ISub: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateSub(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;            
        }
        case Ins::IMul:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("IMul: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateMul(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::IDiv:
        {
            // throw "IDiv: Not Sure.\n";
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("IDiv: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateSDiv(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::IMod:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("IMod: src id not found.");
            }
            auto ret_val = Builder->CreateSRem(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::FAdd:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("FAdd: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateFAdd(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;            
        }
        case Ins::FSub:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("FSub: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateFSub(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::FMul:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("FMul: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateFMul(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::FDiv:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("FDiv: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateFDiv(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::FMod:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("FMod: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateFRem(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::PAdd:
        {

        }

        case Ins::LShift:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("LShift: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateShl(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::RShift:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("RShift: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateLShr(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::BNot:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            if (Val1_it == IdMapVal.end())
            {
                throw std::invalid_argument("BNot: src id not found.");
            }
            // do bit-wise negation in builder
            llvm::Value *ret_val = Builder->CreateNot(Val1_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::BAnd:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("BAnd: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateAnd(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::BOr:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("BOr: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateOr(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::BXor:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("BXor: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateXor(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::LNot:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            if (Val1_it == IdMapVal.end())
            {
                throw std::invalid_argument("LNot: src id not found.");
            }
            llvm::Value *ret_val = Builder->CreateXor(
                Val1_it->second, 
                llvm::ConstantInt::get(Val1_it->second->getType(), -1, true /* signed */),
                "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::LAnd:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("LAnd: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateLogicalAnd(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::LOr:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("LOr: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateLogicalOr(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::LXor:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("LXor: src id not found.");
            }
            llvm::Value *ret_val = // ^AB+A^B
                Builder->CreateLogicalOr(
                    Builder->CreateLogicalAnd(
                        Val1_it->second, 
                        // negate Val2_it->second
                        Builder->CreateXor(
                            Val2_it->second, 
                            llvm::ConstantInt::get(
                                Val2_it->second->getType(), 
                                -1, 
                                true /* signed */), 
                                ""),
                            ""),
                    Builder->CreateLogicalAnd(
                        Val2_it->second, 
                        // negate Val2_it->second
                        Builder->CreateXor(
                            Val1_it->second, 
                            llvm::ConstantInt::get(
                                Val1_it->second->getType(), 
                                -1, 
                                true /* signed */), 
                                ""),
                            ""),
                    "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        // Ptr comparison: to be implemented...

        // Int comparison
        case Ins::ILt:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("ILt: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateICmpSLT(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::ILe:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("ILe: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateICmpSLE(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::IGt:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("IGt: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateICmpSGT(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::IGe:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("IGe: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateICmpSGE(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::IEq:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("IEq: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateICmpEQ(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::INe:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("INe: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateICmpNE(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::FLt:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("FLt: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateFCmpOLT(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::FLe:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("FLe: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateFCmpOLE(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::FGt:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("FGt: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateFCmpOGT(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::FGe:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("FGe: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateFCmpOGE(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::FEq:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("FEq: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateFCmpOEQ(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::FNe:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("FNe: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateFCmpONE(Val1_it->second, Val2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }



        case Ins::Br:
        {
            if (IdMapVal.find(ins.dst) == IdMapVal.end()) {
                throw std::invalid_argument("Br: dst id not found.");
            }
            if (IdMapVal[ins.dst]->getType()->isIntegerTy(1)) {
                // boolean
                // auto boolVal = llvm::cast<llvm::IntegerType>(IdMapVal[ins.dst]);
                return IdMapVal[ins.dst];
            }
            else {
                throw std::invalid_argument("Br: src val not boolean.");
            }
        }
        case Ins::Jump:
        {
            // Implemented in visitor.cpp
            return nullptr;
        }
        case Ins::Ret:
        {
            Builder->CreateRet(IdMapVal[ins.dst]);
            return IdMapVal[ins.dst];
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

            IdMapAlloc[ins.dst] = Builder->CreateAlloca(type, nullptr /*size*/, name);
            Builder->CreateStore(ret_val, IdMapAlloc[ins.dst]);
            return ret_val;
        }

        case Ins::Set:
        {
            if (IdMapAlloc[ins.dst] == nullptr ) {
                throw std::invalid_argument("Set: dst(ptr) id not found.");
            }
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
            if (IdMapAlloc[ins.src.id[0]] == nullptr ) {
                throw std::invalid_argument("Get: src(ptr) id not found.");
            }
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
                IdMapVal[ins.dst] = Builder->CreateLoad(IdMapAlloc[ins.src.id[0]]);
            }
            return IdMapVal[ins.dst];
        }
        default:
            throw std::invalid_argument("Unknown instruction.");
            break;
    }
    return nullptr;
}

