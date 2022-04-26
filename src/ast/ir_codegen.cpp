#include "ir_codegen.hpp"
#include <iostream>
#include "../utils/obfstream.hpp"

namespace ir = tc::ast::ir;

using Cat             = ir::Cat ;
using Kind            = ir::Kind;


using Ins             = ir::Instruction;
using Module          = ir::codegen::Module;
using Block           = ir::codegen::Block;

using Obfs            = tc::utils::obfstream;

int main()
{
    std::cout
    <<"ir_codegen : "
    <<"sizeof(Ins) = "
    <<sizeof(Ins)
    <<std::endl;
    Module module("test.ir");
    
    /* Block is reference data type
     * while copy constructor default 
     * therefore please do not COPY it!!
     */
    auto& block = module.blocks[0];

    Obfs obfs("t.ins");
    obfs<<*(Ins*)block.bytes;
}