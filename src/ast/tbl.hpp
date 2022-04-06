#ifndef tc_ast_tbl_hpp
#define tc_ast_tbl_hpp

#include "node.hpp"

namespace tc{
namespace ast{

struct Data : public ExtdBase
{
    using ID = ID;
    Name name;
    Data(Name name):name(name){}
    Data(){}
    ~Data(){}
    template<typename Data>
    struct Table
    {
        using SymBase = map<Name, typename Data::ID>;
        struct Sym : public SymBase
        {
            Sym* parent;
            Sym(Sym* parent=NULL):parent(parent){}
            ~Sym(){}
            /* always return iter of base */
            typename SymBase::iterator find(Name name)
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
        using Ref = map<Node::ID, typename Data::ID>;
        using Def = map<typename Data::ID,     Data>;
        Sym*sym;
        Ref ref;
        Def def;
        Table():sym(new Sym())
        { def[0]=Data(); }
        ~Table(){ delete sym; }
        /* constructor ensure def.rbegin() exists */
        typename Data::ID tid(){ return def.rbegin()->first  ; }
        typename Data::ID nid(){ return def.rbegin()->first+1; }
        typename Data::ID add(Name name){
            typename Data::ID id = nid();
            (*(this->sym))[name] = id   ;
            this->def[id].name   = name ;
            return id;
        }
        Data& operator[](typename Data::ID id)
        { return this->def[id]; }

        /* 0 -> NotFound */
        typename Data::ID operator[](Name name)
        {
            auto iter = this->sym.find(name);
            if(iter!=this->sym.end())
                return iter->second;
            else
                return 0;
        }
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
        Data(Name name):ast::Data(name), type(NULL){}
        Data():type(NULL){}
        ~Data(){}
        using Table = ast::Data::Table<Data>;
    };
}
namespace expr
{
    struct Data : public ast::Data
    {
        Typep type;
        Exprp expr;
        Data(Name name, Typep type, Exprp expr)
        :ast::Data(name), expr(expr), type(type){}
        Data():type(NULL){}
        ~Data(){}
        using Table = ast::Data::Table<Data>;
    };
}

struct TableBase
{
    /* Table Info */
    type::Data::Table type;
    expr::Data::Table expr;
    Stmts stmts;

    /* currently constructing nodes */
    stack<Node*> nodes;

    Typep u, b, c, i, f;

    TableBase(){}
    ~TableBase(){}
};

}}

#endif