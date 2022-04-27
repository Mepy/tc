#ifndef tc_utils_double_ended_forward_list_hpp
#define tc_utils_double_ended_forward_list_hpp

namespace tc {
namespace utils {

template<typename T, typename Size>
struct double_ended_forward_list
{
    using Value = T;
    using List = double_ended_forward_list;
    struct Node
    {
        Value       value;
        struct Node *next;
        inline Node():next(nullptr){}
        inline Node(Value& value, struct Node* next=nullptr)
        :value(value), next(next){}
        inline ~Node(){ if(nullptr!=next) delete next; }
    };
    struct Iterator
    {
        struct Node* pointer;
        Iterator(struct Node* pointer=nullptr):pointer(pointer){}
        ~Iterator(){}
        struct Iterator& operator++()
        {
            this->pointer = pointer->next;
            return *this;
        }
        bool operator!=(struct Iterator rhs)
        {
            return this->pointer!=rhs.pointer;
        }
        Value& operator*()
        { return pointer->value; }
    };

    struct Node* head;
    struct Node* tail;
    Size         size;

    double_ended_forward_list():size(0)
    { head = tail = new Node(); }
    ~double_ended_forward_list()
    { delete head; }

    inline void push_tail(Value&& value){ push_tail(value); }
    inline void push_tail(Value& value)
    {
        tail = tail->next = new Node(value);
        ++size;
    }

    inline void push_head(Value&& value){ push_head(value); }
    inline void push_head(Value& value)
    {   
        head->next = new Node(value, head->next);
        if(size==0)
            tail = head->next;
        ++size;
    }
    inline void clear()
    {
        if(size!=0)
        {
            delete head->next; 
            head->next = nullptr;
            tail = head;
            size=0;
        }

    }
    inline Iterator begin()
    { return Iterator(head->next); }
    inline Iterator end()
    { return Iterator(nullptr); }

    List& operator+(List& other)
    {
        this->tail->next = other.head->next;
        this->tail = other.tail;
        other.tail = other.head;
        other.head->next = nullptr;
        return *this;
    }
};

}}

#endif