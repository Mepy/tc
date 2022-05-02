#include "ir_parser.hpp"
#include "ir_helper.hpp"
#include <iostream>

namespace ir          = tc::ast::ir;
namespace ins         = ir::instruction;
namespace symbol      = ir::symbol;
namespace type        = ir::type;

using Cat             = ir::Cat;
using Kind            = ir::Kind;

using IR              = ir::parser::IR;
using Block           = ir::parser::Block;
using Ins             = ir::Instruction;
using Symbol          = ir::Symbol;
using Type            = ir::Type;

void member_like();
void stream_like();

int main()
{
    std::cout
    <<"ir_parser  : "
    <<"sizeof(Ins) = "
    <<sizeof(Ins)
    <<", sizeof(Symbol) = "
    <<sizeof(Symbol)
    <<", sizeof(Type) = "
    <<sizeof(Type)
    <<std::endl;

    std::cout
    <<"Please view "
    <<"test.ir"
    <<" in binary format."
    <<std::endl;

    stream_like();
}

void stream_like()
{
    IR ir("test.ir", Cat::EXEC);
    Block block;

    block
    <<Kind::INST
    <<ins::IImm(1, 1234)
    <<ins::IImm(2, 5678)
    <<Ins(Ins::IAdd, 3, 1, 2)
    <<Ins(Ins::ISub, 3, 1, 2)
    <<Ins(Ins::IMul, 3, 1, 2)
    <<Ins(Ins::IDiv, 3, 1, 2)
    <<Ins(Ins::IMod, 3, 1, 2)
    <<ins::FImm(4, 3.14)
    <<ins::FImm(5, 2.71)
    <<Ins(Ins::FAdd, 6, 4, 5)
    <<Ins(Ins::FSub, 6, 4, 5)
    <<Ins(Ins::FMul, 6, 4, 5)
    <<Ins(Ins::FDiv, 6, 4, 5)
    <<Ins(Ins::ILt, 7, 1, 2)
    <<Ins(Ins::Br, 7, 1, 2)
    >>ir
    
    <<ins::Return(3)
    >>ir

    <<ins::Return(6)
    >>ir

    <<ins::I2F(9, 1)
    <<ins::F2I(10, 9)
    >>ir

    <<ins::New(20, 10)
    <<ins::Delete(20)
    >>ir
    ;

}

void member_like()
{
    IR ir("test.ir");
    Block block;
    block.kind = Kind::INST;
    block.push(ins::IImm(1, 1234));
    block.push(ins::IImm(2, 5678));
    block.push(Ins(Ins::IAdd, 3, 1, 2));
    block.push(Ins(Ins::ISub, 3, 1, 2));
    block.push(Ins(Ins::IMul, 3, 1, 2));
    block.push(Ins(Ins::IDiv, 3, 1, 2));
    block.push(Ins(Ins::IMod, 3, 1, 2));

    block.push(ins::FImm(4, 3.14));
    block.push(ins::FImm(5, 2.71));
    block.push(Ins(Ins::FAdd, 6, 4, 5));
    block.push(Ins(Ins::FSub, 6, 4, 5));
    block.push(Ins(Ins::FMul, 6, 4, 5));
    block.push(Ins(Ins::FDiv, 6, 4, 5));

    block.push(Ins(Ins::ILt, 7, 1, 2));
    block.push(Ins(Ins::Br, 7, 1, 2));
    block.save(ir);

    block.push(ins::Return(3));
    block.save(ir);

    block.push(ins::Return(6));
    block.save(ir);
}