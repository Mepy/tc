#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Constant.h>
#include "../ast/ir.hpp"
#include "../ast/ir_codegen.hpp"

namespace ir = tc::ast::ir;
namespace codegen = tc::ast::ir::codegen;

using Cat = ir::Cat;
using Kind =ir::Kind;
using Ins = ir::Instruction;
using Sym = ir::Symbol;
// using Type = ir::Type; -> ambiguity

class irVisitor
{
public:
    virtual llvm::Value *codegen(const Ins &ins) = 0;
    // virtual llvm::Value *codegen(const Sym &sym) = 0;
    // virtual llvm::Type *codegen(const ir::Type &type) = 0;
};

class LLCodegenVisitor: public irVisitor
{
protected:
    std::unique_ptr<llvm::LLVMContext> TheContext;
    std::unique_ptr<llvm::IRBuilder<>> Builder;
    std::unique_ptr<llvm::Module> TheModule;
    
    //map id to llvm::Value*
    std::map<std::int32_t, llvm::Value *> IdMapVal;
    //map id to llvm::AllocaInst* (can be interpreted as ptr to llvm::Value*)
    std::map<std::int32_t, llvm::AllocaInst *> IdMapAlloc;
    //map src block-id to dst block-id
    std::map<std::int32_t, std::int32_t> JumpMap;
    //map src block-id to (boolean value, (dst-if-true block-id, dst-if-false block-id))
    std::map<std::int32_t, std::pair<llvm::Value *, std::pair<std::int32_t, std::int32_t>>> BrMap;
    //map block-id to CSTR 
    std::map<std::int32_t, std::string> StringMap;
    //map block-id of string to id of IdMapVal 
    std::map<std::int32_t, std::int32_t> StringDstMap;
public:
    LLCodegenVisitor() {
        // Open a new context and module.
        TheContext = std::make_unique<llvm::LLVMContext>();
        TheModule = std::make_unique<llvm::Module>("demoCodegen.ll", *TheContext);

        // Create a new builder for the module.
        Builder = std::make_unique<llvm::IRBuilder<>>(*TheContext);
        
        // Refresh all maps
        IdMapAlloc.clear();
        IdMapVal.clear();
        JumpMap.clear();
        BrMap.clear();
        StringMap.clear();
        StringDstMap.clear();
    }

    //Top level methods (in visitor.cpp)
    void ASTIRtoLLVMIR(std::string path_to_ASTir);
    void dumpLLVMIR(); 
    

    llvm::Value *codegen(const Ins &ins) override;
};