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
                // throw std::runtime_error("string already defined");
                // auto *CStr_ptr = Builder->CreateGlobalStringPtr(
                //     StringMap[ins.src.id[0]]
                // );
                // IdMapVal[ins.dst] = CStr_ptr;
                // return IdMapVal[ins.dst];
            }
            else 
            {
                // throw std::invalid_argument("CSTR src id not found in StringMap.");
                auto& CSTRblock = this->module.blocks[ins.src.id[0]];
                auto str_size = CSTRblock.head.ord.size;
                std::string str;
                for (auto i=0; i<str_size; i++)
                {
                   str += CSTRblock.extra.chars[i];
                }
                llvm::StringRef str_ref(str);
                llvm::Value *CStr_ptr = Builder->CreateGlobalStringPtr(str_ref);
                llvm::Value *name = llvm::ConstantDataArray::getString(
                        *TheContext, 
                        str_ref
                    );
                // Create alloc for string
                IdMapAlloc[ins.dst] = Builder->CreateAlloca(
                    name->getType(),
                    llvm::ConstantExpr::getSizeOf(name->getType()),
                    "CSTR");
                // Store string
                Builder->CreateStore(
                    name,
                    IdMapAlloc[ins.dst]
                );
                return nullptr;
            }
            break;
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
                Builder->CreateAdd(Val1_it->second, Val2_it->second);
            // llvm::BinaryOperator::CreateAdd(Val1_it->second, Val2_it->second, "");
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

        // Pointer Arithmetic ops
        case Ins::PAdd:
        {
            auto Ptr1_it = IdMapAlloc.find(ins.src.id[0]);
            auto Val2_it = IdMapVal.find(ins.src.id[1]);
            if (Ptr1_it == IdMapAlloc.end() || Val2_it == IdMapVal.end())
            {
                throw std::invalid_argument("PAdd: src id not found.");
            }
            llvm::Value *ret_ptr = 
                Builder->CreateGEP(Ptr1_it->second, Val2_it->second, "");
            #if DEBUG
            std::cout << ret_ptr->getType()->isPointerTy() << std::endl;
            #endif
            IdMapAlloc[ins.dst] = Builder->CreateAlloca(
                ret_ptr->getType());
            Builder->CreateStore(ret_ptr, IdMapAlloc[ins.dst]);
            return ret_ptr;
            break;
        }
        case Ins::PSub:
        {
            auto Ptr1_it = IdMapAlloc.find(ins.src.id[0]);
            auto Ptr2_it = IdMapAlloc.find(ins.src.id[1]);
            if (Ptr1_it == IdMapAlloc.end() || Ptr2_it == IdMapAlloc.end())
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
            if (Ptr1_it->second->getOperand(0) != Ptr2_it->second->getOperand(0))
            {
                throw std::invalid_argument("PSub: Pointers do not point to the same object.");
            }
            llvm::Value *ret_val = 
                Builder->CreatePtrDiff(Ptr1_it->second, Ptr2_it->second, "");
            IdMapVal[ins.dst] = ret_val;
            return ret_val;
        }
        case Ins::PMov:
        {
            // Assign the pointer to the destination
            auto Ptr1_it = IdMapAlloc.find(ins.src.id[0]);
            if (Ptr1_it == IdMapAlloc.end())
            {
                throw std::invalid_argument("PMov: src id not found.");
            }
            auto &alloc_ref = Ptr1_it->second;
            IdMapAlloc[ins.dst] = alloc_ref;
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
        // Ptr comparison
        case Ins::PLt:
        {
            auto Ptr1_it = IdMapAlloc.find(ins.src.id[0]);
            auto Ptr2_it = IdMapAlloc.find(ins.src.id[1]);
            if (Ptr1_it == IdMapAlloc.end() || Ptr2_it == IdMapAlloc.end())
            {
                throw std::invalid_argument("PLt: src id not found.");
            }
            if (Ptr1_it->second->getType() != Ptr2_it->second->getType())
            {
                throw std::invalid_argument("PLt: src type not match.");
            }
            // Ensure that the pointers are pointing to the same object
            // Not sure if it is the right way to validate this
            if (Ptr1_it->second->getOperand(0) != Ptr2_it->second->getOperand(0))
            {
                throw std::invalid_argument("PLt: src ptr not pointing to the same object.");
            }
            llvm::Value *ret_val = Builder->CreateICmpSLT(
                llvm::dyn_cast<llvm::ConstantInt>(Ptr1_it->second), 
                llvm::dyn_cast<llvm::ConstantInt>(Ptr2_it->second), "");
        }
        case Ins::PLe:
        {
            auto Ptr1_it = IdMapAlloc.find(ins.src.id[0]);
            auto Ptr2_it = IdMapAlloc.find(ins.src.id[1]);
            if (Ptr1_it == IdMapAlloc.end() || Ptr2_it == IdMapAlloc.end())
            {
                throw std::invalid_argument("PLe: src id not found.");
            }
            if (Ptr1_it->second->getType() != Ptr2_it->second->getType())
            {
                throw std::invalid_argument("PLe: src type not match.");
            }
            // Ensure that the pointers are pointing to the same object
            // Not sure if it is the right way to validate this
            if (Ptr1_it->second->getOperand(0) != Ptr2_it->second->getOperand(0))
            {
                throw std::invalid_argument("PLe: src ptr not pointing to the same object.");
            }
            llvm::Value *ret_val = Builder->CreateICmpSLE(
                llvm::dyn_cast<llvm::ConstantInt>(Ptr1_it->second), 
                llvm::dyn_cast<llvm::ConstantInt>(Ptr2_it->second), "");
        }
        case Ins::PGt:
        {
            auto Ptr1_it = IdMapAlloc.find(ins.src.id[0]);
            auto Ptr2_it = IdMapAlloc.find(ins.src.id[1]);
            if (Ptr1_it == IdMapAlloc.end() || Ptr2_it == IdMapAlloc.end())
            {
                throw std::invalid_argument("PGt: src id not found.");
            }
            if (Ptr1_it->second->getType() != Ptr2_it->second->getType())
            {
                throw std::invalid_argument("PGt: src type not match.");
            }
            // Ensure that the pointers are pointing to the same object
            // Not sure if it is the right way to validate this
            if (Ptr1_it->second->getOperand(0) != Ptr2_it->second->getOperand(0))
            {
                throw std::invalid_argument("PGt: src ptr not pointing to the same object.");
            }
            llvm::Value *ret_val = Builder->CreateICmpSGT(
                llvm::dyn_cast<llvm::ConstantInt>(Ptr1_it->second), 
                llvm::dyn_cast<llvm::ConstantInt>(Ptr2_it->second), "");
        }
        case Ins::PGe:
        {
            auto Ptr1_it = IdMapAlloc.find(ins.src.id[0]);
            auto Ptr2_it = IdMapAlloc.find(ins.src.id[1]);
            if (Ptr1_it == IdMapAlloc.end() || Ptr2_it == IdMapAlloc.end())
            {
                throw std::invalid_argument("PLe: src id not found.");
            }
            if (Ptr1_it->second->getType() != Ptr2_it->second->getType())
            {
                throw std::invalid_argument("PLe: src type not match.");
            }
            // Ensure that the pointers are pointing to the same object
            // Not sure if it is the right way to validate this
            if (Ptr1_it->second->getOperand(0) != Ptr2_it->second->getOperand(0))
            {
                throw std::invalid_argument("PLe: src ptr not pointing to the same object.");
            }
            llvm::Value *ret_val = Builder->CreateICmpSGE(
                llvm::dyn_cast<llvm::ConstantInt>(Ptr1_it->second), 
                llvm::dyn_cast<llvm::ConstantInt>(Ptr2_it->second), "");
        }
        case Ins::PEq:
        {
            auto Ptr1_it = IdMapAlloc.find(ins.src.id[0]);
            auto Ptr2_it = IdMapAlloc.find(ins.src.id[1]);
            if (Ptr1_it == IdMapAlloc.end() || Ptr2_it == IdMapAlloc.end())
            {
                throw std::invalid_argument("PEq: src id not found.");
            }
            if (Ptr1_it->second->getType() != Ptr2_it->second->getType())
            {
                throw std::invalid_argument("PEq: src type not match.");
            }
            // Ensure that the pointers are pointing to the same object
            // Not sure if it is the right way to validate this
            if (Ptr1_it->second->getOperand(0) != Ptr2_it->second->getOperand(0))
            {
                throw std::invalid_argument("PEq: src ptr not pointing to the same object.");
            }
            llvm::Value *ret_val = Builder->CreateICmpEQ(
                llvm::dyn_cast<llvm::ConstantInt>(Ptr1_it->second), 
                llvm::dyn_cast<llvm::ConstantInt>(Ptr2_it->second), "");
        }
        case Ins::PNe:
        {
            auto Ptr1_it = IdMapAlloc.find(ins.src.id[0]);
            auto Ptr2_it = IdMapAlloc.find(ins.src.id[1]);
            if (Ptr1_it == IdMapAlloc.end() || Ptr2_it == IdMapAlloc.end())
            {
                throw std::invalid_argument("PNe: src id not found.");
            }
            if (Ptr1_it->second->getType() != Ptr2_it->second->getType())
            {
                throw std::invalid_argument("PNe: src type not match.");
            }
            // Ensure that the pointers are pointing to the same object
            // Not sure if it is the right way to validate this
            if (Ptr1_it->second->getOperand(0) != Ptr2_it->second->getOperand(0))
            {
                throw std::invalid_argument("PNe: src ptr not pointing to the same object.");
            }
            llvm::Value *ret_val = Builder->CreateICmpNE(
                llvm::dyn_cast<llvm::ConstantInt>(Ptr1_it->second), 
                llvm::dyn_cast<llvm::ConstantInt>(Ptr2_it->second), "");
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
        
        // typed comparison to be implemented


        case Ins::Br:
        {
            if (IdMapVal.find(ins.dst) == IdMapVal.end()) {
                throw std::invalid_argument("Br: dst id not found.");
            }
            if (IdMapVal[ins.dst]->getType()->isIntegerTy(1)) {

                auto func = this->Builder->GetInsertBlock()->getParent();
                
                llvm::BasicBlock *BB_True, *BB_False;
                {
                auto id_T = ins.src.id[0];
                auto iter = this->BasicBlockMap.find(id_T);
                if(iter==this->BasicBlockMap.end())
                {
                    BB_True = llvm::BasicBlock::Create(*TheContext, std::to_string(id_T), func);
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
                    BB_False = llvm::BasicBlock::Create(*TheContext, std::to_string(id_F), func);
                    this->BlockStack.push(std::make_pair<>(
                        BB_False, &this->module.blocks[id_F]
                    ));
                    this->BasicBlockMap.insert(std::make_pair<>(
                        id_F, BB_False
                    ));
                }
                else BB_True = iter->second;
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
                BB = llvm::BasicBlock::Create(*TheContext, std::to_string(id), func);
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
            switch (ins.src.id[0] /*Func Symb id*/)
            {
                case 3: /*i2f; for details, see ir.hpp->conventions*/
                {
                    auto Args_it = ArgsMap.find(ins.src.id[1]);
                    if (Args_it == ArgsMap.end())
                    {
                        throw std::invalid_argument("Call: (i2f) src id not found.");
                    }
                    assert (Args_it->second.size() == 1);
                    llvm::Value *ret_val = Builder->CreateSIToFP(Args_it->second[0], llvm::Type::getFloatTy(*TheContext), "");
                    IdMapVal[ins.dst] = ret_val;
                    return ret_val;
                }
                case 4: /*f2i; for details, see ir.hpp->conventions*/
                {
                    auto Args_it = ArgsMap.find(ins.src.id[1]);
                    if (Args_it == ArgsMap.end())
                    {
                        throw std::invalid_argument("Call: (f2i) src id not found.");
                    }
                    assert (Args_it->second.size() == 1);
                    llvm::Value *ret_val = Builder->CreateFPToSI(Args_it->second[0], llvm::Type::getInt32Ty(*TheContext), "");
                    IdMapVal[ins.dst] = ret_val;
                    return ret_val;
                }
                case 5: /*getint; for details, see ir.hpp->conventions*/
                {
                    auto& args = this->module.blocks[ins.src.id[1]];
                    // assert (args.head.ord.size == 0);
                    // type safety for TyCk in AST, no need to assert
                    
                    auto geti = TheModule->getFunction("geti");
                    auto dst = Builder->CreateCall(geti);
                    IdMapVal[ins.dst] = dst;
                    return dst;
                }
                case 6: /*putint; for details, see ir.hpp->conventions*/
                {
                    auto& args = this->module.blocks[ins.src.id[1]];
                    
                    auto arg = this->IdMapVal[args.extra.ids[0]];
                    
                    auto puti = TheModule->getFunction("puti");
                    auto dst = Builder->CreateCall(puti, { arg });
                    IdMapVal[ins.dst] = dst;
                    return dst;
                }
                default:
                {   
                    // implemented in visitor.cpp
                    return nullptr;
                }
            }
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
            #if DEBUG
            std::cout << "Get: " << ins.dst << " <- " << ins.src.id[0] << std::endl;
            // std::cout << src->isArrayAllocation() << std::endl;
            #endif
            /*
            if (IdMapAlloc.find(ins.src.id[0]) == IdMapAlloc.end() ) {
                throw std::invalid_argument("Get: src(ptr) id not found.");
            }
            */
            auto &src = IdMapVal[ins.src.id[0]];
            if (src->isArrayAllocation())
            {
                //pointer-type: add offset to it
                llvm::Value *index = IdMapVal[ins.src.id[1]];
                
                llvm::Value *val_ptr = Builder->CreateGEP(
                    Builder->CreateLoad(src)->getType(),
                    src, 
                    index, 
                    std::to_string(ins.src.id[0])
                );

                IdMapVal[ins.dst] = Builder->CreateLoad(
                    val_ptr->getType()->getPointerElementType(), 
                    val_ptr);
            }
            else 
            {
                #if DEBUG
                std::cout << "Get: src(ptr) id mapped to non-array.\n";
                #endif
                // non-array: should not have non-zero offset field
                if (!src->getType()->isPointerTy() && ins.src.id[1] != 0) 
                {
                    // TODO: this can be a warning, not an error?
                    throw std::invalid_argument("Get: src(ptr) id mapped to non-array and non-ptr type, but offset is non-zero.");
                }
                IdMapVal[ins.dst] = Builder->CreateLoad(
                    src->getType()->getElementType(), 
                    src);
            }
            return IdMapVal[ins.dst];
        }
        default:
            throw std::invalid_argument("Unknown block.");
            break;
    }
    return nullptr;
}

