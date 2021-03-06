#include "visitor.hpp"
// #include "src/ast/ir.hpp"
// #include <llvm/IR/Value.h>
#include <iostream>
#include <string>

llvm::Value *LLCodegenVisitor::codegen(const Ins &ins) {
    // std::cout << "in codegen\n";
    switch (ins.sort) 
    {
        /* 
        case Ins::Null:
        {
            auto dst = llvm::ConstantPointerNull::get(); // TODO
            IdMapVal[ins.dst] = dst;
            return dst;
        }
        */
        case Ins::IImm:
        {
            llvm::Value* IImm_ptr = llvm::ConstantInt::get(
                this->TypeMap[3], 
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
        case Ins::CImm:
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
            auto *FImm_ptr = llvm::ConstantFP::get(
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
                // CSTR always after ins
                throw std::runtime_error("string already defined");
            }
            else 
            {
                auto& CSTRblock = this->module.blocks[ins.src.id[0]];
                auto str_size = CSTRblock.head.ord.size;
                std::string str(CSTRblock.extra.chars);
                llvm::StringRef str_ref(str);
                IdMapVal[ins.dst] = Builder->CreateGlobalStringPtr(str_ref);
                return nullptr;
            }
            break;
        }
        case Ins::I2F:
        {
            auto Val_it = IdMapVal.find(ins.src.id[0]);
            if (Val_it == IdMapVal.end())
                throw std::invalid_argument("I2F: src id[0] not found.");
            auto dst = 
                Builder->CreateSIToFP(Val_it->second
                    , llvm::Type::getDoubleTy(*TheContext)
                    , "symb_"+std::to_string(ins.dst));
            IdMapVal[ins.dst] = dst;
            return dst;
        }
        case Ins::F2I:
        {
            auto Val_it = IdMapVal.find(ins.src.id[0]);
            if (Val_it == IdMapVal.end())
                throw std::invalid_argument("F2I: src id[0] not found.");
            auto dst = 
                Builder->CreateFPToSI(Val_it->second
                    , llvm::Type::getInt64Ty(*TheContext)
                    , "symb_"+std::to_string(ins.dst));
            IdMapVal[ins.dst] = dst;
            return dst;
        }
        case Ins::INeg:
        {
            auto Val_it = IdMapVal.find(ins.src.id[0]);
            if (Val_it == IdMapVal.end())
                throw std::invalid_argument("INeg: src id[0] not found.");
            auto dst = 
                Builder->CreateNeg(Val_it->second, "symb_"+std::to_string(ins.dst));
            IdMapVal[ins.dst] = dst;
            return dst;
        }
        case Ins::FNeg:
        {
            auto Val_it = IdMapVal.find(ins.src.id[0]);
            if (Val_it == IdMapVal.end())
                throw std::invalid_argument("FNeg: src id[0] not found.");
            auto dst = 
                Builder->CreateFNeg(Val_it->second, "symb_"+std::to_string(ins.dst));
            IdMapVal[ins.dst] = dst;
            return dst;
        }
        case Ins::IAdd:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end())
                throw std::invalid_argument("IAdd: src id[0] not found.");
            if(Val2_it == IdMapVal.end())
                throw std::invalid_argument("IAdd: src id[1] not found.");
            auto dst = 
                Builder->CreateAdd(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
            // llvm::BinaryOperator::CreateAdd(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
            IdMapVal[ins.dst] = dst;
            return dst;
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
                Builder->CreateSub(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
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
                Builder->CreateMul(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
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
                Builder->CreateSDiv(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
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
            auto ret_val = Builder->CreateSRem(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
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
                Builder->CreateFAdd(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
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
                Builder->CreateFSub(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
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
                Builder->CreateFMul(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
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
                Builder->CreateFDiv(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
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
                Builder->CreateFRem(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }

        // Pointer Arithmetic ops
        case Ins::PAdd:
        {
            auto Ptr1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Ptr1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("PAdd: src id not found.");
            }
            llvm::Value *ret_ptr = 
                Builder->CreateGEP(Ptr1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
            #if DEBUG
            std::cout << ret_ptr->getType()->isPointerTy() << std::endl;
            #endif
            IdMapVal[ins.dst] = ret_ptr;
                // Builder->CreateAlloca(
                // ret_ptr->getType()->getPointerElementType());
            // Builder->CreateStore(ret_ptr, IdMapVal[ins.dst]);
            return ret_ptr;
            break;
        }
        case Ins::PSub:
        {
            auto Ptr1_it = IdMapVal.find(ins.src.id[0]);
            auto Ptr2_it = IdMapVal.find(ins.src.id[1]);
            if (Ptr1_it == IdMapVal.end() || Ptr2_it == IdMapVal.end())
            {
                throw std::invalid_argument("PSub: src id not found.");
            }
            // Ensure that the pointers are of the same type
            if (Ptr1_it->second->getType() != Ptr2_it->second->getType())
            {
                throw std::invalid_argument("PSub: Pointer types do not match.");
            }
            // Ensure that the pointers are pointing to the same object
            // Not sure if it is the right way to validate this
            // if (Ptr1_it->second->getOperand(0) != Ptr2_it->second->getOperand(0))
            // {
            //     throw std::invalid_argument("PSub: Pointers do not point to the same object.");
            // }
            llvm::Value *ret_val = 
                Builder->CreatePtrDiff(Ptr1_it->second, Ptr2_it->second, "symb_"+std::to_string(ins.dst));
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::PMov:
        {
            // Assign the pointer to the destination
            auto Ptr1_it = IdMapVal.find(ins.src.id[0]);
            if (Ptr1_it == IdMapVal.end())
            {
                throw std::invalid_argument("PMov: src id not found.");
            }
            auto &alloc_ref = Ptr1_it->second;
            IdMapVal[ins.dst] = alloc_ref;
            return alloc_ref;
            break;
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
                Builder->CreateShl(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
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
                Builder->CreateLShr(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
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
            llvm::Value *ret_val = Builder->CreateNot(Val1_it->second, "symb_"+std::to_string(ins.dst));
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
                Builder->CreateAnd(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
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
                Builder->CreateOr(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
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
                Builder->CreateXor(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
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
                "symb_"+std::to_string(ins.dst));
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
                Builder->CreateLogicalAnd(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
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
                Builder->CreateLogicalOr(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
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
                                "symb_"+std::to_string(ins.dst)),
                            "symb_"+std::to_string(ins.dst)),
                    Builder->CreateLogicalAnd(
                        Val2_it->second, 
                        // negate Val2_it->second
                        Builder->CreateXor(
                            Val1_it->second, 
                            llvm::ConstantInt::get(
                                Val1_it->second->getType(), 
                                -1, 
                                true /* signed */), 
                                "symb_"+std::to_string(ins.dst)),
                            "symb_"+std::to_string(ins.dst)),
                    "symb_"+std::to_string(ins.dst));
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        // Ptr comparison
        case Ins::PLt:
        {
            auto Ptr1_it = IdMapVal.find(ins.src.id[0]);
            auto Ptr2_it = IdMapVal.find(ins.src.id[1]);
            if (Ptr1_it == IdMapVal.end() || Ptr2_it == IdMapVal.end())
            {
                throw std::invalid_argument("PLt: src id not found.");
            }
            if (Ptr1_it->second->getType() != Ptr2_it->second->getType())
            {
                throw std::invalid_argument("PLt: src type not match.");
            }
            // Ensure that the pointers are pointing to the same object
            // Not sure if it is the right way to validate this
            // if (Ptr1_it->second->getOperand(0) != Ptr2_it->second->getOperand(0))
            // {
            //     throw std::invalid_argument("PLt: src ptr not pointing to the same object.");
            // }
            llvm::Value *ret_val = Builder->CreateICmpSLT(
                llvm::dyn_cast<llvm::ConstantInt>(Ptr1_it->second), 
                llvm::dyn_cast<llvm::ConstantInt>(Ptr2_it->second), "symb_"+std::to_string(ins.dst));
        }
        case Ins::PLe:
        {
            auto Ptr1_it = IdMapVal.find(ins.src.id[0]);
            auto Ptr2_it = IdMapVal.find(ins.src.id[1]);
            if (Ptr1_it == IdMapVal.end() || Ptr2_it == IdMapVal.end())
            {
                throw std::invalid_argument("PLe: src id not found.");
            }
            if (Ptr1_it->second->getType() != Ptr2_it->second->getType())
            {
                throw std::invalid_argument("PLe: src type not match.");
            }
            // Ensure that the pointers are pointing to the same object
            // Not sure if it is the right way to validate this
            // if (Ptr1_it->second->getOperand(0) != Ptr2_it->second->getOperand(0))
            // {
            //     throw std::invalid_argument("PLe: src ptr not pointing to the same object.");
            // }
            llvm::Value *ret_val = Builder->CreateICmpSLE(
                llvm::dyn_cast<llvm::ConstantInt>(Ptr1_it->second), 
                llvm::dyn_cast<llvm::ConstantInt>(Ptr2_it->second), "symb_"+std::to_string(ins.dst));
        }
        case Ins::PGt:
        {
            auto Ptr1_it = IdMapVal.find(ins.src.id[0]);
            auto Ptr2_it = IdMapVal.find(ins.src.id[1]);
            if (Ptr1_it == IdMapVal.end() || Ptr2_it == IdMapVal.end())
            {
                throw std::invalid_argument("PGt: src id not found.");
            }
            if (Ptr1_it->second->getType() != Ptr2_it->second->getType())
            {
                throw std::invalid_argument("PGt: src type not match.");
            }
            // Ensure that the pointers are pointing to the same object
            // Not sure if it is the right way to validate this
            // if (Ptr1_it->second->getOperand(0) != Ptr2_it->second->getOperand(0))
            // {
            //     throw std::invalid_argument("PGt: src ptr not pointing to the same object.");
            // }
            llvm::Value *ret_val = Builder->CreateICmpSGT(
                llvm::dyn_cast<llvm::ConstantInt>(Ptr1_it->second), 
                llvm::dyn_cast<llvm::ConstantInt>(Ptr2_it->second), "symb_"+std::to_string(ins.dst));
        }
        case Ins::PGe:
        {
            auto Ptr1_it = IdMapVal.find(ins.src.id[0]);
            auto Ptr2_it = IdMapVal.find(ins.src.id[1]);
            if (Ptr1_it == IdMapVal.end() || Ptr2_it == IdMapVal.end())
            {
                throw std::invalid_argument("PLe: src id not found.");
            }
            if (Ptr1_it->second->getType() != Ptr2_it->second->getType())
            {
                throw std::invalid_argument("PLe: src type not match.");
            }
            // Ensure that the pointers are pointing to the same object
            // Not sure if it is the right way to validate this
            // if (Ptr1_it->second->getOperand(0) != Ptr2_it->second->getOperand(0))
            // {
            //     throw std::invalid_argument("PLe: src ptr not pointing to the same object.");
            // }
            llvm::Value *ret_val = Builder->CreateICmpSGE(
                llvm::dyn_cast<llvm::ConstantInt>(Ptr1_it->second), 
                llvm::dyn_cast<llvm::ConstantInt>(Ptr2_it->second), "symb_"+std::to_string(ins.dst));
        }
        case Ins::PEq:
        {
            auto Ptr1_it = IdMapVal.find(ins.src.id[0]);
            auto Ptr2_it = IdMapVal.find(ins.src.id[1]);
            if (Ptr1_it == IdMapVal.end() || Ptr2_it == IdMapVal.end())
            {
                throw std::invalid_argument("PEq: src id not found.");
            }
            if (Ptr1_it->second->getType() != Ptr2_it->second->getType())
            {
                throw std::invalid_argument("PEq: src type not match.");
            }
            // Ensure that the pointers are pointing to the same object
            // Not sure if it is the right way to validate this
            // if (Ptr1_it->second->getOperand(0) != Ptr2_it->second->getOperand(0))
            // {
            //     throw std::invalid_argument("PEq: src ptr not pointing to the same object.");
            // }
            llvm::Value *ret_val = Builder->CreateICmpEQ(
                llvm::dyn_cast<llvm::ConstantInt>(Ptr1_it->second), 
                llvm::dyn_cast<llvm::ConstantInt>(Ptr2_it->second), "symb_"+std::to_string(ins.dst));
        }
        case Ins::PNe:
        {
            auto Ptr1_it = IdMapVal.find(ins.src.id[0]);
            auto Ptr2_it = IdMapVal.find(ins.src.id[1]);
            if (Ptr1_it == IdMapVal.end() || Ptr2_it == IdMapVal.end())
            {
                throw std::invalid_argument("PNe: src id not found.");
            }
            if (Ptr1_it->second->getType() != Ptr2_it->second->getType())
            {
                throw std::invalid_argument("PNe: src type not match.");
            }
            // Ensure that the pointers are pointing to the same object
            // Not sure if it is the right way to validate this
            // if (Ptr1_it->second->getOperand(0) != Ptr2_it->second->getOperand(0))
            // {
            //     throw std::invalid_argument("PNe: src ptr not pointing to the same object.");
            // }
            llvm::Value *ret_val = Builder->CreateICmpNE(
                llvm::dyn_cast<llvm::ConstantInt>(Ptr1_it->second), 
                llvm::dyn_cast<llvm::ConstantInt>(Ptr2_it->second), "symb_"+std::to_string(ins.dst));
        }

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
                Builder->CreateICmpSLT(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
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
                Builder->CreateICmpSLE(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
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
                Builder->CreateICmpSGT(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::IGe:
        {
            #if DEBUG
            std::cout << "IGe: " << std::endl;
            #endif
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("IGe: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateICmpSGE(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
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
                Builder->CreateICmpEQ(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
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
                Builder->CreateICmpNE(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
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
                Builder->CreateFCmpOLT(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
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
                Builder->CreateFCmpOLE(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
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
                Builder->CreateFCmpOGT(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
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
                Builder->CreateFCmpOGE(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
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
                Builder->CreateFCmpOEQ(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
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
                Builder->CreateFCmpONE(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        
        case Ins::CEq:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("CEq: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateICmpEQ(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::CNe:
        {
            auto Val1_it = IdMapVal.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Val1_it == IdMapVal.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("CNe: src id not found.");
            }
            llvm::Value *ret_val = 
                Builder->CreateICmpNE(Val1_it->second, Val2_it->second, "symb_"+std::to_string(ins.dst));
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }

        // typed comparison to be implemented


        case Ins::Br:
        {
            #if DEBUG
            std::cout << "Br: " << IdMapVal[ins.dst]->getType()->isIntegerTy() << std::endl;
            #endif
            if (IdMapVal.find(ins.dst) == IdMapVal.end()) {
                throw std::invalid_argument("Br: dst id not found.");
            }
            if (IdMapVal[ins.dst]->getType()->isIntegerTy()) {

                auto func = this->Builder->GetInsertBlock()->getParent();
                
                llvm::BasicBlock *BB_True, *BB_False;
                {
                auto id_T = ins.src.id[0];
                auto iter = this->BasicBlockMap.find(id_T);
                if(iter==this->BasicBlockMap.end())
                {

                    BB_True = llvm::BasicBlock::Create(*TheContext, "block_"+std::to_string(id_T), func);
                    this->BlockStack.push(std::make_pair<>(
                        BB_True, &this->module.blocks[id_T]
                    ));
                    this->BasicBlockMap.insert(std::make_pair<>(
                        id_T, BB_True
                    ));
                }
                else BB_True = iter->second;
                }
                {
                auto id_F = ins.src.id[1];
                auto iter = this->BasicBlockMap.find(id_F);
                if(iter==this->BasicBlockMap.end())
                {
                    BB_False = llvm::BasicBlock::Create(*TheContext, "block_"+std::to_string(id_F), func);
                    this->BlockStack.push(std::make_pair<>(
                        BB_False, &this->module.blocks[id_F]
                    ));
                    this->BasicBlockMap.insert(std::make_pair<>(
                        id_F, BB_False
                    ));
                }
                else BB_False = iter->second;
                }

                this->Builder->CreateCondBr(IdMapVal[ins.dst], BB_True, BB_False);
                return IdMapVal[ins.dst];
            }
            else {
                throw std::invalid_argument("Br: src val not boolean.");
            }
        }
        case Ins::Jump:
        {
            llvm::BasicBlock *BB;
            {
            auto id = ins.dst;
            auto iter = this->BasicBlockMap.find(id);
            if(iter==this->BasicBlockMap.end())
            {
                auto func = this->Builder->GetInsertBlock()->getParent();
                BB = llvm::BasicBlock::Create(*TheContext, "block_"+std::to_string(id), func);
                this->BlockStack.push(std::make_pair<>(
                    BB, &this->module.blocks[id]
                ));
                this->BasicBlockMap.insert(std::make_pair<>(
                    id, BB
                ));
            }
            else BB = iter->second;
            }
            this->Builder->CreateBr(BB);
            return nullptr;
        }
        case Ins::Ret:
        {
            Builder->CreateRet(IdMapVal[ins.dst]);
            return IdMapVal[ins.dst];
        }
        case Ins::Call:
        {
            #if DEBUG
                std::cout << "Args exist: " << (ArgsMap.find(ins.src.id[1]) != ArgsMap.end()) << std::endl;
            # endif
            auto &args_block = this->module.blocks[ins.src.id[1]];
            std::vector<llvm::Value*> args;
            for (auto i = 0; i < args_block.head.ord.size; ++i)
            {
                auto arg_id = args_block.extra.ids[i];
                auto arg_val = this->IdMapVal[arg_id];
                auto arg_type = arg_val->getType();
                auto arg_name = "symb_"+std::to_string(arg_id);
                args.push_back(arg_val);
            }
            auto func = FuncMap[ins.src.id[0]];
            auto ret_val = Builder->CreateCall(func, args);
            if(ret_val->getType()!=Builder->getVoidTy())
                ret_val->setName("symb_"+std::to_string(ins.dst));
            IdMapVal[ins.dst] = ret_val;
            return nullptr;
            // Implemented in visitor.cpp
            // return nullptr;
            // if (SymMap[ins.src.id[0]].first == 'B')
            // {
            //     // block-id

            // }
            // IdMapVal[ins.dst] = Builder->CreateCall(
            //                         , 
            //                         ArgsMap[ins.src.id[1]]);
        }
        case Ins::Array:
        {
            // throw std::invalid_argument("Array: not implemented.");
            auto init_it = IdMapVal.find(ins.src.id[0]);
            if (init_it == IdMapVal.end())
            {
                throw std::invalid_argument("Array: src(init val) id not found.");
            }
            auto size_it = IdMapVal.find(ins.src.id[1]);
            if (size_it == IdMapVal.end())
            {
                throw std::invalid_argument("Array: src(size) id not found.");
            }
            // auto constIntSize = llvm::dyn_cast<llvm::ConstantInt>(size_it->second);
            // #if DEBUG
            // std::cout << "Array: " << constIntSize << std::endl;
            // #endif
            auto IntType = llvm::Type::getInt64Ty(*TheContext);
            // #if DEBUG
            // std::cout << "Array: " << arr_type << std::endl;
            // #endif
            // std::vector<llvm::Constant*> arr_init_vals(
            //     llvm::dyn_cast<llvm::ConstantInt>(size_it->second)->getZExtValue(),
            //     llvm::dyn_cast<llvm::ConstantInt>(init_it->second)
            // );
            #if DEBUG
            std::cout << "Array: "  << std::endl;
            #endif
            IdMapVal[ins.dst] = Builder->CreateAlloca(init_it->second->getType(), 
                size_it->second, "symb_"+std::to_string(ins.dst));
            #if DEBUG
            std::cout << "Array: " << "Out" << std::endl;
            #endif
            // Builder->CreateStore(
            //     llvm::ConstantArray::get(arr_type, arr_init_vals),
            //     IdMapVal[ins.dst]
            // );
            return nullptr;
        }
        case Ins::Alloc:
        {
            auto val_it = IdMapVal.find(ins.src.id[0]);
            if (val_it == IdMapVal.end() ){
                throw std::invalid_argument("Alloc: src id not found.");
            }
            std::string name = "symb_" + std::to_string(ins.dst);
            llvm::Value *ret_val = val_it->second;
            llvm::Type *type = ret_val->getType();

            IdMapVal[ins.dst] = Builder->CreateAlloca(type, nullptr /*size*/, name);
            Builder->CreateStore(ret_val, IdMapVal[ins.dst]);
            return ret_val;
        }
        case Ins::New:
        {
            // Call the _Znwm function from libc
            // The first argument is the size of the memory to allocate
            // The second argument is the alignment of the memory to allocate
            // The return value is a pointer to the allocated memory
            // The memory is uninitialized
            // The memory is allocated on the stack
            // The memory is not freed when the function returns
            #if DEBUG
            std::cout << "New: " << std::endl;
            #endif
            auto val_it = IdMapVal.find(ins.src.id[0]);
            if (val_it == IdMapVal.end() ){
                throw std::invalid_argument("New: src id not found.");
            }
            std::string name = "malloc_" + std::to_string(val_it->first);
            llvm::Instruction* Malloc = 
                llvm::CallInst::CreateMalloc(
                    Builder->GetInsertBlock(),
                    llvm::Type::getInt64PtrTy(*TheContext), /*IntPtrTy*/
                    val_it->second->getType(), /*AllocatedType*/
                    llvm::ConstantExpr::getSizeOf(val_it->second->getType()), /*AllocatedTypeSize*/
                    nullptr, /*ArraySize*/
                    nullptr, /*function default*/
                    "malloc"
                );
            
            IdMapVal[ins.dst] = Builder->CreateBitCast(
                Malloc->getOperand(0), llvm::PointerType::getUnqual(val_it->second->getType()), name);

            #if DEBUG
            std::cout << "New: " << "end" << std::endl;
            #endif
            
            // IdMapVal[ins.dst] = Malloc->getOperand(0);
            Builder->CreateStore(val_it->second, IdMapVal[ins.dst]);
            return nullptr;
        }
        case Ins::NewAr:
        {
            // Call the malloc function to allocate space for an array and init its value
            auto val_it = IdMapVal.find(ins.src.id[0]);
            if (val_it == IdMapVal.end() ){
                throw std::invalid_argument("NewAr: src(init) id not found.");
            }
            auto size_it = IdMapVal.find(ins.src.id[1]);
            if (size_it == IdMapVal.end() ){
                throw std::invalid_argument("NewAr: src(len) id not found.");
            }
            std::string name = "malloc_" + std::to_string(val_it->first);
            llvm::Instruction* Malloc = 
                llvm::CallInst::CreateMalloc(
                    Builder->GetInsertBlock(),
                    llvm::Type::getInt64PtrTy(*TheContext), /*IntPtrTy*/
                    val_it->second->getType(), /*AllocatedType*/
                    llvm::ConstantExpr::getSizeOf(val_it->second->getType()), /*AllocatedTypeSize*/
                    size_it->second, /*ArraySize*/
                    nullptr, /*function default*/
                    "malloc"
                );
            IdMapVal[ins.dst] = Builder->CreateBitCast(
                Malloc->getOperand(0), llvm::PointerType::getUnqual(val_it->second->getType()), name);
            

                        
            // #if DEBUG
            // std::cout << IdMapVal[ins.dst]->getType()->isPointerTy() << std::endl;
            // IdMapVal[ins.dst] = Builder->CreateLoad(Malloc->getOperand(0));
            
            auto memset = TheModule->getOrInsertFunction("memset", 
                llvm::FunctionType::get(
                    llvm::Type::getVoidTy(*TheContext),
                    {
                        llvm::Type::getInt8PtrTy(*TheContext),
                        llvm::Type::getInt8PtrTy(*TheContext),
                        llvm::Type::getInt32Ty(*TheContext)
                    },
                    false
                )
            );
            // if (memset == nullptr)
            // {
            //     throw std::invalid_argument("NewAr: memset not found.");
            // }
            Builder->CreateCall(memset, {IdMapVal[ins.dst], val_it->second, size_it->second});
            
            #if DEBUG
            std::cout << "NewAr: " << "end, no init" << std::endl;
            #endif
            return nullptr;
        }
        case Ins::Del:
        {
            auto dst_= IdMapVal.find(ins.dst);
            if (dst_ == IdMapVal.end() ){
                throw std::invalid_argument("Del: dst id not found.");
            }
            if (dst_->second->getNumUses() != 0){
                throw std::invalid_argument("Del: dst id has uses.");
            }
            Builder->CreateCall(
                TheModule->getOrInsertFunction("free", 
                    llvm::FunctionType::get(
                        llvm::Type::getVoidTy(*TheContext),
                        {
                            llvm::Type::getInt8PtrTy(*TheContext)
                        },
                        false
                    )
                ),
                {dst_->second}
            );
            return nullptr;
        }

        case Ins::Set:
        {
            #if DEBUG
            std::cout << "Set: " << std::endl;
            #endif
            if (IdMapVal.find(ins.dst) == IdMapVal.end() ){
                throw std::invalid_argument("Set: dst(ptr) id not found.");
            }
            if (IdMapVal.find(ins.src.id[0]) == IdMapVal.end() ) {
                throw std::invalid_argument("Set: src(val) id not found.");
            }
            auto& src = IdMapVal[ins.src.id[0]];
            auto& dst = IdMapVal[ins.dst];
            llvm::Value *index;
            if (dst->getType()->isArrayTy() ) 
            {
                #if DEBUG
                std::cout << "Set: " << "array" << std::endl;
                #endif
                llvm::Value *index = llvm::ConstantInt::get(
                    llvm::Type::getInt64Ty(*TheContext), ins.src.id[1]);

                llvm::Value *val_store_ptr = Builder->CreateGEP(
                    dst->getType()->getArrayElementType(),
                    dst, 
                    index, 
                    std::to_string(ins.src.id[0])
                );

                Builder->CreateStore(dst, val_store_ptr);
            }
            else if (dst->getType()->isPointerTy() ) 
            {
                #if DEBUG
                std::cout << "Set: " << "ptr" << std::endl;
                #endif
                if (ins.src.id[1] != 0) 
                {
                    // TODO: this can be a warning, not an error?
                    throw std::invalid_argument("Set: src(ptr) id mapped to ptr; But offset is non-zero.");
                }
                if (dst->getType()->getPointerElementType()->isArrayTy())
                {   // pointer to array type: in CStr
                    #if DEBUG
                    std::cout << "Set: src(ptr) to array (CStr).\n";
                    #endif
                    auto cast = Builder->CreateBitCast(src, 
                        dst->getType()->getPointerElementType()->getArrayElementType()->getPointerTo()
                    ); // cast from ptr to array to ptr to element
                    Builder->CreateStore(
                        src, 
                        cast);
                    return nullptr;
                }
                #if DEBUG
                std::cout << "Set: src(ptr) to ptr.\n";
                #endif
                Builder->CreateStore(src, dst);
            }
            return nullptr;
        }
        case Ins::Get:
        {
            #if DEBUG
            std::cout << "Get: " << ins.dst << " <- " << ins.src.id[0] << std::endl;
            // std::cout << src->isArrayAllocation() << std::endl;
            #endif
            if (IdMapVal.find(ins.src.id[0]) == IdMapVal.end() ) {
                throw std::invalid_argument("Get: src(ptr) id not found.");
            }
            auto& src = (IdMapVal[ins.src.id[0]]);
            if (src->getType()->isArrayTy() ) {
                // needs testing
                llvm::Value *index = llvm::ConstantInt::get(
                    llvm::Type::getInt64Ty(*TheContext), ins.src.id[1]);
                auto val_ptr = Builder->CreateGEP(
                    src->getType(),
                    src, 
                    index, 
                    std::to_string(ins.src.id[0])
                );
                IdMapVal[ins.dst] = Builder->CreateLoad(val_ptr, "symb_"+std::to_string(ins.dst));
            }
            if(src->getType()->isPointerTy())
            {
                //CreateGEP pointer
                #if DEBUG
                std::cout << "Get: src(ptr) id mapped to non-array.\n";
                #endif
                // non-array: should not have non-zero offset field
                // Since ptrs have their add ops
                if (ins.src.id[1] != 0) 
                {
                    // TODO: this can be a warning, not an error?
                    throw std::invalid_argument("Get: src(ptr) id mapped to ptr type, but offset is non-zero.");
                }
                if (src->getType()->getPointerElementType()->isArrayTy())
                {   // pointer to array type: in CStr
                    #if DEBUG
                    std::cout << "Get: src(ptr) to array (CStr).\n";
                    #endif
                    auto cast = Builder->CreateBitCast(src, 
                        src->getType()->getPointerElementType()->getArrayElementType()->getPointerTo()
                    ); // cast from ptr to array to ptr to element
                    IdMapVal[ins.dst] = Builder->CreateLoad(
                        cast->getType()->getPointerElementType(), 
                        cast);
                    return IdMapVal[ins.dst];
                }
                //else: product of CreateGEP, simply load
                IdMapVal[ins.dst] = Builder->CreateLoad(
                    src->getType()->getPointerElementType(), 
                    src, "symb_"+std::to_string(ins.dst));
            } 
            return IdMapVal[ins.dst];
        }
        default:
            throw std::invalid_argument("Unknown block." + std::to_string(ins.sort));
            break;
    }
    return nullptr;
}

