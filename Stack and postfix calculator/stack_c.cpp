#include "stack_c.h"
#include <stdexcept>
#include <iostream>
Stack_C::Stack_C(){
    stk = new List();
}
Stack_C::~Stack_C(){
    delete stk;
}
void Stack_C::push(int data){
    try{
        stk->insert(data);
    }
    catch(const std::bad_alloc& exp){
        throw std::runtime_error("Out of Memory");
    }
}
int Stack_C::pop(){
    if (stk->get_size() <1)
    {
        throw std::runtime_error("Empty Stack");
    }
    else{
        try{
        int elm = stk->delete_tail();
        return elm;
        }
        catch(const std::bad_alloc& exp){
        throw std::runtime_error("Out of Memory");
        }
    }
}
int Stack_C::add(){
    if(stk->get_size()>=2){
        int res = pop()+pop();
        push(res);
        return res;
    }
    else{
        throw std::runtime_error("Not Enough Arguments");
    }
}
int Stack_C::subtract(){
    if(stk->get_size()>=2){
        int num1 = pop();
        int num2 = pop();
        int res = num2-num1;
        push(res);
        return res;
    }
    else{
        throw std::runtime_error("Not Enough Arguments");
    }
}
int Stack_C::multiply(){
    if(stk->get_size()>=2){
        int res = pop()*pop();
        push(res);
        return res;
    }
    else{
        throw std::runtime_error("Not Enough Arguments");
    }
}
int Stack_C::divide(){
    if(stk->get_size()>=2){
        int num1 = pop();
        int num2 = pop();
        if(num1!=0){
            if (num1*num2<=0 && num2%num1!=0)
            {
                int res = num2/num1 -1;
                push(res);
                return res;
            }
            else{
                int res = num2/num1;
                push(res);
                return res;
            } 
        }
        else{
            throw std::runtime_error("Divide by Zero Error");
        }
    }
    else{
        throw std::runtime_error("Not Enough Arguments");
    }
}
int Stack_C::get_size(){
    return stk->get_size();
}
List* Stack_C::get_stack(){
    List* tmp = stk;
    return tmp;
}
void Stack_C::print_stack(bool top_or_bottom){
    if(top_or_bottom == true)//Print from top
    {
        int stksize = stk->get_size();
        Node* stkhead = stk->get_head();//This is not he stack head this is linked list head for stack head qwe need to go to linked list tail
        for (int i = 0; i<= stksize; i++)
        {
            stkhead= stkhead->next;
        }
        for (int i = 0; i < stksize; i++)
        {
            std::cout<<stkhead->prev->get_value()<<std::endl;
            stkhead = stkhead->prev;
        }
        
    }
    else{
        int stksize = stk->get_size();
        Node* stkhead = stk->get_head();
        for (int i = 0; i < stksize; i++)
        {
            std::cout<<stkhead->next->get_value()<<std::endl;
            stkhead= stkhead->next;
        }
    }
}
int Stack_C::get_element_from_top(int idx){
    int stksize = stk->get_size();
    if (idx>=0 && idx<stksize)
    {
        Node* stkhead = stk->get_head();
        for (int i = 0; i<= stksize; i++)
        {
            stkhead= stkhead->next;
        }
        for (int i = 0; i <= idx; i++)
        {
            stkhead=stkhead->prev;
        }
        return stkhead->get_value();
        
    }
    else{
        throw std::runtime_error("Index out of range");
    }  
}
int Stack_C::get_element_from_bottom(int idx){
    int stksize = stk->get_size();
    if (idx>=0 && idx<stksize)
    {
        Node* stkhead = stk->get_head();
        
        for (int i = 0; i <= idx; i++)
        {
            stkhead=stkhead->next;
        }
        return stkhead->get_value();
        
    }
    else{
        throw std::runtime_error("Index out of range");
    }
}
