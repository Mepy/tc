#include "double_ended_forward_list.hpp"
#include <iostream>
using defl = tc::utils::double_ended_forward_list<int>;

int main()
{
    defl list;
    list.push_head(10);
    list.push_head(11);
    list.push_head(12);
    
    list.push_tail(23);
    list.push_tail(25);
    list.push_tail(27);
    

    // for(auto iter=list.begin();iter!=list.end();++iter)
        // std::cout<<*iter<<" ";
    for(auto iter : list)
        std::cout<<iter<<" ";
        
    std::cout<<std::endl;
    return 0;
}