#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>

using namespace llvm;


llvm::Function* Struct(llvm::LLVMContext& context, llvm::Module* module, ArrayRef<Type*>& field_types)
{
    auto struct_type = StructType::create(context, field_types, "struct.X");
    auto constructor_type = FunctionType::get(
        struct_type, // return_type
        field_types, // params_type
        false // Constant length of params
    );
    auto constructor = Function::Create(constructor_type, Function::LinkOnceODRLinkage, "_constructor", module);
    auto entry = BasicBlock::Create(context, "_entry", constructor);
    IRBuilder<> builder(context);
    builder.SetInsertPoint(entry);

    auto object = builder.CreateAlloca(struct_type);

    {
    auto i = 0;
    auto _ = ConstantInt::get(builder.getInt32Ty(), 0);
    for(auto field_type:field_types)
    {
        auto ptr = builder.CreateInBoundsGEP(object, {_, ConstantInt::get(builder.getInt32Ty(), i)});
        auto arg = constructor->getArg(i);
        builder.CreateStore(arg, ptr);
        i++;
    }
    }
    auto oo = builder.CreateLoad(object);
    builder.CreateRet(oo);

    return constructor;
}
inline llvm::Function* Struct(llvm::LLVMContext& context, llvm::Module* module, ArrayRef<Type*>&& field_types)
{ return Struct(context, module, field_types); }

int main() 
{
    LLVMContext context;
    auto module = new Module("demo.ll", context);
    {
    std::vector<Type*> fields_type;
    /*
     struct {
         Int x, y, z;
     };
     */
    auto tyi32 = IntegerType::getInt32Ty(context);
    fields_type.push_back(tyi32);
    fields_type.push_back(tyi32);
    fields_type.push_back(tyi32);
    fields_type.push_back(IntegerType::getFloatTy(context));
    
    auto constructor = Struct(context, module, fields_type);
    }

    // print LLVM IR to stdout
    module->print(llvm::outs(), nullptr);

    delete module;
}
