#ifndef tc_ast_context_hpp
#define tc_ast_context_hpp

#include "head.hpp"
#include "token.hpp"
#include "node.hpp"
#include "ir.hpp"
#include "ir_helper.hpp"
#include <iostream>
namespace tc{
namespace ast{
namespace Ih = ir::instruction;
namespace ir{
struct Block
{
    ID       id;
    Kind   kind;
    Insts insts;

    // For those kind!=Kind::INST
    Size   size;
    Byte8 extra;
    
    Block(ID id):id(id){}
    Block(Kind kind, Size size, Byte8 extra, ID id=0):id(id), kind(kind), size(size), extra(extra){}
};
inline bool operator<(const Block& lhs, const Block& rhs){ return lhs.id<rhs.id; }
}

namespace context{

using SymBase = map<string, ID>;
struct Sym : public SymBase
{
    Sym* parent;
    Sym(Sym* parent=nullptr):parent(parent){}
    ~Sym(){}
    typename SymBase::iterator recursive_find(string& name)
    {
        typename SymBase::iterator iter;
        iter = SymBase::find(name);
        if(iter!=this->end() || parent==nullptr)
            return iter;

        iter = parent->recursive_find(name);
        if(iter!=parent->end())
            return iter;
        else
            return this->end();
    }
};

template<typename Data>
struct Space : public set<Data>
{
    Data& operator[](ID id) // [WARNING] : Why const_iterator??
    { return *(Data*)&*(this->find(Data(id))); }

    ~Space(){}
};

template<typename Data>
struct Namespace
{
    using Def = Space<Data>;

    Sym* sym;
    Def  def;
    Namespace():sym(new Sym()){}
    ~Namespace(){ delete sym; }

    ID nid(){ return def.size(); }
    void bind(ID id, Name&& name){ bind(id, name); }
    void bind(ID id, Name& name)
    {
        sym->insert(pair<string, ID>(name, id));
        def[id].names.push_back(name);
    }

    // 0 -> NotFound
    ID operator[](string& name)
    {
        auto iter = this->sym->recursive_find(name);
        if(iter!=this->sym->end())
            return iter->second;
        else
            return 0;
    }
    // if exists, whether it is free varaibles
    bool is_free(string& name) 
    { return this->sym->find(name)==this->sym->end(); }
    Data& operator[](ID id)
    { return this->def[id]; }
    void insert(Data&& data){ this->def.insert(data); }
    void insert(Data&  data){ this->def.insert(data); }

    void scope_beg(){ this->sym = new Sym(this->sym); }
    void scope_end()
    {
        auto sym = this->sym->parent;
        delete this->sym;
        this->sym = sym;
    }
};

using Expr = Namespace<ast::Expr>;

struct Type : public Namespace<ast::Type>
{
    ast::Type& operator[](ID id) // for unify
    {
        auto type = &(this->def[id]);
        while(type::Shape::Infer==type->shape->flag)
        {
            auto shape = ((type::Typ*)(type->shape));
            auto id    = shape->id;
            if(0!=id)
                type = &(this->def[id]);
            else
                break;
        }
        return *type;
    }
    ID shortcut(ID id) // for save
    {
        auto type = &(*this)[id];
        if(type::Shape::Saved==type->shape->flag)
            return ((type::Typ*)(type->shape))->id;
        else
            return type->id;
    }
    ID operator[](string& name)
    {
        auto iter = this->sym->recursive_find(name);
        if(iter!=this->sym->end())
            return iter->second;
        else
            return 0;
    }
    Type():Namespace<ast::Type>(){}
    ~Type(){}
};

using Block = Space<ir::Block>;

}



struct Context
{
    context::Type   type;
    context::Expr   expr;
    context::Block block; // IR block

    // for { stmts; }'s           recursive
    stack<Stmtp> blocks;
    
    // for while's break n & continue n
    vector<Stmtp> whiles;

    // for match e with | ...'s   recursive
    stack<Exprp> matches;

    // for \ a1 ... an => body 's recursive
    stack<Exprp> funcs; // for $ 

    // for cons a1 ... an => body 's recursive
    stack<Exprp> branches;

    // for func(a1, ..., an) 's   recursive
    stack<Exprp> calls;

    // for { A1 ... An -> R }'s   recursive
    stack<Typep> func_types; 

    

    Name type_name;
    Typep u, b, c, i, f, adt;
    Exprp i2f, f2i;

    enum T_ID : ID
    {   T_UNIT  = 0
    ,   T_BOOL  = 1
    ,   T_CHAR  = 2
    ,   T_INT   = 3
    ,   T_FLOAT = 4
    };
    enum E_ID : ID 
    {   E_UNIT  = 0
    ,   E_TRUE  = 1
    ,   E_FALSE = 2
    ,   E_I2F   = 3
    ,   E_F2I   = 4
    ,   E_GETI  = 5
    ,   E_PUTI  = 6
    ,   E_PUTS  = 7
    ,   E_END
    };

    Context(){}
    ~Context(){}

    /* type unification */
    ast::Type& unify    (ast::Type& t1, ast::Type& t2);
    ast::Type& unify_N_N(ast::Type& t1, ast::Type& t2);
    ast::Type& unify_I_N(ast::Type& t1, ast::Type& t2);
    ast::Type& unify_I_U(ast::Type& t1, ast::Type& t2);
    ast::Type& unify_I_I(ast::Type& t1, ast::Type& t2);

    // optional := might be nullptr
    ast::Type* unify_opt(ast::Type* t1, ast::Type* t2)
    {
        if(nullptr==t1)
            return t2;
        else if(nullptr==t2)
            return t1;
        else 
            return &unify(*t1, *t2);
    }

    ir::Block* new_block(ir::Kind kind=ir::Kind::INST, Size size=0, Byte8 extra=RESERVED)
    {
        auto id = this->block.size();
        this->block.insert(ir::Block(kind, size, extra, id));
        auto block = &(this->block[id]);
        return block;
    }
    ir::Block* new_branch(ID constructor, ID params, ID body)
    {
        return new_block(ir::Kind::BRCH, constructor, (Byte8(body)<<32)|Byte8(params));
    }
    ir::Block* new_func(ID type, ID params, ID body)
    {
        return new_block(ir::Kind::FUNC, type, (Byte8(body)<<32)|Byte8(params));
        /* type, params, body */
    }
    ir::Block* new_IDs(ir::Kind kind, IDs& ids)
    {
        auto size = ids.size();
        switch (size)
        {
        case 0:
            return new_block(kind, 0, 0x44494F5620454854L); // "THE VOID"
        case 1:
            return new_block(kind, 1, Byte8(ids[0]));
        default:
        {
            auto block = new_block(kind, size, *(Byte8*)&ids[0]);
            Size index=2;
            for( ; index+3<size; index+=4)
                block->insts.push_back(*(Inst*)(&ids[index]));
        
            switch(size-index)
            {
            case 3:block->insts.push_back(
                Ih::IDs(ids[index], ids[index+1], ids[index+2])
            ); break;
            case 2:block->insts.push_back(
                Ih::IDs(ids[index], ids[index+1])
            ); break;
            case 1:block->insts.push_back(
                Ih::IDs(ids[index])
            ); break;
            default: break;
            }
            return block;
        }
        }
    }
};

}}

#endif