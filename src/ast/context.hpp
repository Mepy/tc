#ifndef tc_ast_context_hpp
#define tc_ast_context_hpp

#include "node.hpp"
#include "ir_parser.hpp"

namespace tc{
namespace ast{

using IR = ir::parser::IR;

struct Data 
{
    vector<Name> names;
    /* In most time, there is only no name for an ID (ANF) */
    Data():names(0){} 
    ~Data(){}
    template<typename Data>
    struct Namespace
    {
        using SymBase = map<string, ID>;
        using Def     = map<ID,   Data>;
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
        
        Sym* sym;
        Def  def;
        Namespace():sym(new Sym())
        { def[0]=Data(); }
        ~Namespace(){ delete sym; }
        /* constructor ensure def.rbegin() exists */
        ID nid()
        {
            auto id = def.rbegin()->first+1;
            def.insert(pair<ID, Data>(id, Data()));
            return id;
        }

        /* 0 -> NotFound */
        ID operator[](string& name)
        {
            auto iter = this->sym->recursive_find(name);
            if(iter!=this->sym->end())
                return iter->second;
            else
                return 0;
        }
        bool is_free(string& name) /* if exists, whether it is free varaibles */
        { return this->sym->find(name)==this->sym->end(); }

        Data& operator[](ID id)
        { return this->def[id]; }
        void scope_beg(){
            this->sym = new Sym(this->sym);
        }
        void scope_end(){
            auto sym = this->sym->parent;
            delete this->sym;
            this->sym = sym;
        }
    };

};
namespace type
{
    struct Data : public ast::Data
    {
        Typep type;
        Data():type(nullptr){}
        ~Data(){}
        using Namespace = ast::Data::Namespace<Data>;
    };
}
namespace expr
{
    struct Data : public ast::Data
    {
        Exprp expr;
        Data():expr(nullptr){}
        ~Data(){}
        using Namespace = ast::Data::Namespace<Data>;
    };
}

struct Context
{
    type::Data::Namespace type;
    expr::Data::Namespace expr;


    // TODO while list for break and continue

    IR ir;

    Typep u, b, c, i, f, adt;
    Exprp fun; 

    stack<Nodep> nodes; /* for recursive storage */ 
    stack<Exprp> funcs; /* for recursive and closure analysis */ 

    Context(std::string path):ir(path){}
    ~Context(){}
};

}}

#endif