#ifndef tc_ast_rc_hpp
#define tc_ast_rc_hpp

#include "head.hpp"

namespace tc{
namespace ast{

/* simple Reference Count for memory manangement */
struct RC 
{
    Size rc;
    RC():rc(1){}
    ~RC(){}
    void _rc_incr(){        ++rc   ; }
    bool _rc_decr(){ return --rc==0; }
};
template<typename T>
inline void decr(T* ptr)
{
    if(ptr!=NULL&&ptr->_rc_decr()) 
        delete ptr;
}
template<typename T>
inline void decr(vector<T*> ptrs)
{
    for(auto iter=ptrs.begin(); iter!=ptrs.end(); ++iter)
        decr(*iter);
}
template<typename T>
inline T* incr(T* ptr)
{
    if(ptr!=NULL) ptr->_rc_incr();
    return ptr;
}
template<typename T>
inline vector<T*> incr(vector<T*> ptrs)
{
    for(auto iter=ptrs.begin(); iter!=ptrs.end(); ++iter)
        incr(*iter);
    return ptrs;
}


/* for those who don't share memory */
template<typename T>
inline void del(T* ptr){ if(ptr!=NULL) delete ptr; }
template<typename T>
inline void del(vector<T*> ptrs)
{   
    for(auto iter=ptrs.begin(); iter!=ptrs.end(); ++iter)
        del(*iter);
}
template<typename K, typename V>
inline void del(map<K, V*> m)
{   
    for(auto iter=m.begin(); iter!=m.end(); ++iter)
        del(iter->second);
}


}}

#endif