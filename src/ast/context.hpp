#ifndef tc_ast_context_hpp
#define tc_ast_context_hpp

#include "node.hpp"
#include "ir_parser.hpp"

namespace tc{
namespace ast{

using IR = ir::parser::IR;

struct Data 
{
    using ID = Byte4;
    vector<Name> names;
    /* In most time, there is only no name for an ID (ANF) */
    Data():names(0){} 
    ~Data(){}
    template<typename Data>
    struct Namespace
    {
        using SymBase = map<string, typename Data::ID>;
        using Def     = map<typename Data::ID,   Data>;
        struct Sym : public SymBase
        {
            Sym* parent;
            Sym(Sym* parent=NULL):parent(parent){}
            ~Sym(){}

            typename SymBase::iterator find(string& name)
            {
                typename SymBase::iterator iter;
                iter = SymBase::find(name);
                if(iter!=this->end() || parent==NULL)
                    return iter;

                iter = parent->find(name);
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
        typename Data::ID tid(){ return def.rbegin()->first  ; }
        typename Data::ID nid(){ return def.rbegin()->first+1; }

        /* 0 -> NotFound */
        typename Data::ID operator[](string name)
        {
            auto iter = this->sym.find(name);
            if(iter!=this->sym.end())
                return iter->second;
            else
                return 0;
        }
        Data& operator[](typename Data::ID id)
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
        Data():type(NULL){}
        ~Data(){}
        using Namespace = ast::Data::Namespace<Data>;
    };
}
namespace expr
{
    using Sort = ir::Symbol::Sort;
    struct Data : public ast::Data
    {
        Typep type;
        Exprp expr;
        Sort  sort;
        Data():type(NULL){}
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

    Context(std::string path):ir(path){}
    ~Context(){}
};

}}

#endif