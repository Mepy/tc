#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Constant.h>
#include "../ast/ir.hpp"
#include "ir_loader.hpp"

namespace ir = tc::ast::ir;
namespace codegen = tc::ast::ir::codegen;

using Cat = ir::Cat;
using Kind =ir::Kind;
using Ins = ir::Instruction;
using Sym = ir::Symbol;
// using Type = ir::Type; -> ambiguity
// using Sort = ir::Type::Sort;
using Block = ir::codegen::Block;

class irVisitor
{
public:
    virtual llvm::Value *codegen(const Ins &ins) = 0;
    // virtual llvm::Value *codegen(const Sym &sym) = 0;
    virtual llvm::Type *codegen(const ir::Type &type, int index) = 0;
    
};

class LLCodegenVisitor: public irVisitor
{
protected:
    std::unique_ptr<llvm::LLVMContext> TheContext;
    std::unique_ptr<llvm::IRBuilder<>> Builder;
    std::unique_ptr<llvm::Module> TheModule;
    
    //map from id to llvm::Type *
    std::map<std::uint32_t, llvm::Type *> TypeMap;
    //map from id to Info -> type-typeid('T')/block-blockid('B') (see ir.hpp)
    std::map<std::uint32_t, std::pair<char, std::uint32_t>> SymMap;
    //map id to llvm::Value*
    std::map<std::uint32_t, llvm::Value *> IdMapVal;
    //map id to llvm::AllocaInst* (can be interpreted as ptr to llvm::Value*)
    std::map<std::uint32_t, llvm::AllocaInst *> IdMapAlloc;
    //map src block-id to dst block-id
    std::map<std::uint32_t, std::uint32_t> JumpMap;
    //map src block-id to (boolean value, (dst-if-true block-id, dst-if-false block-id))
    std::map<std::uint32_t, std::pair<llvm::Value *, std::pair<std::uint32_t, std::uint32_t>>> BrMap;
    //map block-id to CSTR 
    std::map<std::uint32_t, std::string> StringMap;
    //map block-id of string to id of IdMapVal 
    std::map<std::uint32_t, std::uint32_t> StringDstMap;
    //map id of block of type TFUN to vector of llvm::Type *
    std::map<std::uint32_t, llvm::FunctionType *> TypeFuncMap;
    //map block-id to llvm::FunctionCallee
    std::map<std::uint32_t, llvm::FunctionCallee> FuncMap;
    //map arg-id to function arguments (vector of llvm::Value*)
    std::map<std::uint32_t, std::vector<llvm::Value*>> ArgsMap; 
    //map formatting arguments to llvm::Constant* (strings)
    std::map<std::string, llvm::Constant *> FormatMap;
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
    void dumpAllMap(); 
    void builtinFuncInit();

    llvm::FunctionType *getFuncType(Block *block);
    

    llvm::Value *codegen(const Ins &ins) override;
    // llvm::Value *codegen(const Sym &sym) override;
    llvm::Type *codegen(const ir::Type &type, int index) override;
};