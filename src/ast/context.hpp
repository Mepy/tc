#ifndef tc_ast_context_hpp
#define tc_ast_context_hpp
#include <iostream>
#include "head.hpp"
#include "token.hpp"
#include "node.hpp"

namespace tc{
namespace ast{
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
struct Def : public set<Data>
{
    Data& operator[](ID id) // [WARNING] : Why const_iterator??
    { return *(Data*)&*(this->find(Data(id))); }

    ~Def(){}
};

template<typename Data>
struct Namespace
{
    using Def = Def<Data>;

    Sym* sym;
    Def  def;
    Namespace():sym(new Sym())
    { def.insert(Data(0)); }
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

}

struct Context
{
    context::Type type;
    context::Expr expr;

    // for { stmts; }'s           recursive
    stack<Stmtp> blocks;
    
    // for match e with | ...'s   recursive
    stack<Exprp> matches;

    // for \ a1 ... an => body 's recursive
    stack<Exprp> funcs; // for $ 

    // both for func and match's branch
    stack<Exprp> funcs_retyck;

    // for func(a1, ..., an) 's   recursive
    stack<Exprp> calls;

    // for { A1 ... An -> R }'s   recursive
    stack<Typep> func_types; 

    Name type_name;
    Typep adt;

    Context(){}
    ~Context(){}

    /* type unification */
    ast::Type& unify    (ast::Type& t1, ast::Type& t2);
    ast::Type& unify_N_N(ast::Type& t1, ast::Type& t2);
    ast::Type& unify_I_N(ast::Type& t1, ast::Type& t2);
    ast::Type& unify_I_U(ast::Type& t1, ast::Type& t2);
    ast::Type& unify_I_I(ast::Type& t1, ast::Type& t2);

};

}}

#endif