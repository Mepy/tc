#include "ir_parser.hpp"
#include <iostream>

namespace ir = tc::ast::ir;

using Cat             = ir::Cat;
using Kind            = ir::Kind;

using Ins             = ir::Instruction;
using Module          = ir::parser::Module;
using Block           = ir::parser::Block;


void member_like();
void stream_like();

int main()
{
    std::cout
    <<"ir_parser  : "
    <<"sizeof(Ins) = "
    <<sizeof(Ins)
    <<std::endl;

    stream_like();
}

void stream_like()
{
    Module module("test.ir");
    Block block;

    block
    <<Kind::INST
    <<Ins::IImm(1, 1234)
    <<Ins::IImm(2, 5678)
    <<Ins(Ins::IAdd, 3, 1, 2)
    <<Ins(Ins::ISub, 3, 1, 2)
    <<Ins(Ins::IMul, 3, 1, 2)
    <<Ins(Ins::IDiv, 3, 1, 2)
    <<Ins(Ins::IMod, 3, 1, 2)
    <<Ins::FImm(4, 3.14)
    <<Ins::FImm(5, 2.71)
    <<Ins(Ins::FAdd, 6, 4, 5)
    <<Ins(Ins::FSub, 6, 4, 5)
    <<Ins(Ins::FMul, 6, 4, 5)
    <<Ins(Ins::FDiv, 6, 4, 5)
    <<Ins(Ins::ILt, 7, 1, 2)
    <<Ins(Ins::Br, 7, 1, 2)
    >>module
    
    <<Ins::Return(3)
    >>module

    <<Ins::Return(6)
    >>module

    <<Ins::ItoF(9, 1)
    <<Ins::FtoI(10, 9)
    >>module

    <<Ins(Ins::New, 20, 10, 1)
    <<Ins::Delete(20)
    >>module
    ;

}

void member_like()
{
    Module module("test.ir");
    Block block;
    block.kind = Kind::INST;
    block.push(Ins::IImm(1, 1234));
    block.push(Ins::IImm(2, 5678));
    block.push(Ins(Ins::IAdd, 3, 1, 2));
    block.push(Ins(Ins::ISub, 3, 1, 2));
    block.push(Ins(Ins::IMul, 3, 1, 2));
    block.push(Ins(Ins::IDiv, 3, 1, 2));
    block.push(Ins(Ins::IMod, 3, 1, 2));

    block.push(Ins::FImm(4, 3.14));
    block.push(Ins::FImm(5, 2.71));
    block.push(Ins(Ins::FAdd, 6, 4, 5));
    block.push(Ins(Ins::FSub, 6, 4, 5));
    block.push(Ins(Ins::FMul, 6, 4, 5));
    block.push(Ins(Ins::FDiv, 6, 4, 5));

    block.push(Ins(Ins::ILt, 7, 1, 2));
    block.push(Ins(Ins::Br, 7, 1, 2));
    block.save(module);

    block.push(Ins::Return(3));
    block.save(module);

    block.push(Ins::Return(6));
    block.save(module);
}