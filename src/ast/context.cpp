#include "context.hpp"

namespace tc{
namespace ast{

ast::Type &Context::unify    (ast::Type &t1, ast::Type &t2)
{
    if (t1.id == t2.id)
        return t1;

    if (type::Shape::Infer == t1.shape->flag)
    {
        if (type::Shape::Infer == t2.shape->flag) // Both Infer
            return unify_I_I(t1, t2);
        else
            return unify_I_N(t1, t2);
    }
    else
    {
        if (type::Shape::Infer == t2.shape->flag)
            return unify_I_N(t2, t1);
        else if (t1.id < t2.id)
            return unify_N_N(t1, t2);
        else
            return unify_N_N(t2, t1);
    }
}
ast::Type &Context::unify_I_I(ast::Type &t1, ast::Type &t2)
{
    // type::Shape::Infer==t1.shape->flag &&
    // type::Shape::Infer==t2.shape->flag
    auto &id1 = t1.typ_id();
    auto &id2 = t2.typ_id();

    if (0 != id1)
    {
        if (0 != id2) // I_I
        {
            auto &res = unify(this->type[id1], this->type[id2]);
            id1 = id2 = res.id;
            return res;
        }
        else // U_I
            return unify_I_U(t2, t1);
    }
    else if (0 != id2) // I_U
        return unify_I_U(t1, t2);
    else // U_U
    {
        if (t1.id < t2.id) // id bigger ~> smaller
        {
            id2 = t1.id;
            return t1;
        }
        else
        {
            id1 = t2.id;
            return t2;
        }
    }
}
ast::Type &Context::unify_I_U(ast::Type &t1, ast::Type &t2)
{
    // type::Shape::Infer==t1.shape->flag && 0!=id1 &&
    // type::Shape::Infer==t2.shape->flag && 0==id2
    auto &id1 = t1.typ_id();
    auto &id2 = t2.typ_id();

    if (t2.id < id1)
    {
        auto &_t1 = this->type[id1];
        id1 = t2.id;
        return unify(_t1, t2);
    }
    else
    {
        id2 = id1;
        return t1;
    }
}
ast::Type &Context::unify_N_N(ast::Type &t1, ast::Type &t2)
{
    // type::Shape::Infer!=t1.shape->flag &&
    // type::Shape::Infer!=t2.shape->flag &&
    // t1.id < t2.id

    if (t1.shape->flag != t2.shape->flag)
        throw "Not Typed.\n";

    switch (t1.shape->flag)
    {
    case type::Shape::Infer: // tc Compiler bugs here
        throw "TC COMPILER DEBUG please.\n";
    case type::Shape::U:
    case type::Shape::B:
    case type::Shape::C:
    case type::Shape::I:
    case type::Shape::F:
        break;

    case type::Shape::ADT:
        throw "Not Typed.\n"; // t1.id < t2.id

    case type::Shape::Ref:
    case type::Shape::Ptr:
    {
        auto &id1 = t1.typ_id();
        auto &id2 = t2.typ_id();
        auto &ty1 = this->type[id1];
        auto &ty2 = this->type[id2];
        id1 = unify(ty1, ty2).id;
        break;
    }
    case type::Shape::Array:
    {
        auto &id1 = ((type::Array*)(t1.shape))->id;
        auto &id2 = ((type::Array*)(t2.shape))->id;
        auto &ty1 = this->type[id1];
        auto &ty2 = this->type[id2];
        auto size1 = ((type::Array*)(t1.shape))->size;
        auto size2 = ((type::Array*)(t2.shape))->size;
        if (size1 != size2)
            throw "Not Typed Array Size.\n";

        id1 = unify(ty1, ty2).id;
        break;
    }
    case type::Shape::Fun:
    {
        auto shape1 = (type::Fun *)t1.shape;
        auto shape2 = (type::Fun *)t2.shape;

        auto &id1 = shape1->retype;
        auto &id2 = shape2->retype;

        id1 = unify(this->type[id1], this->type[id2]).id;

        auto &params1 = shape1->params;
        auto &params2 = shape2->params;

        if (params1.size() != params2.size())
            throw "Not Typed Fun Params Size.";

        for (auto it1 = params1.begin(), it2 = params2.begin(); it1 != params1.end(); ++it1, ++it2)
            *it1 = unify(this->type[*it1], this->type[*it2]).id;

        break;
    }
    default:
        break;
    }

    // t1.id < t2.id
    delete t2.shape;
    t2.shape = type::helper::infer(t1.id);

    return t1;
}
ast::Type &Context::unify_I_N(ast::Type &t1, ast::Type &t2)
{
    // type::Shape::Infer==t1.shape->flag && 
    // type::Shape::Infer!=t2.shape->flag
    auto &id1 = t1.typ_id();
    if (0 == id1) // Unknown Now
    {
        if (t1.id < t2.id) // swap, id bigger ~> smaller
        {
            id1 = t1.id;
            auto shape = t1.shape;
            t1.shape = t2.shape;
            t2.shape = shape;
            t1.type = t2.type;
            t1.names.merge(t2.names);
            return t1;
        }
        else
        {
            id1 = t2.id;
            return t2;
        }
    }
    else // t1 ~> _t1
    {
        auto &_t1 = this->type[id1];
        auto &res = unify(_t1, t2);
        id1 = res.id;
        return res;
    }
}

}}