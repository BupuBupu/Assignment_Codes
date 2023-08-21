#include "stack_a.h"
#include <stdexcept>
#include <iostream>
Stack_A::Stack_A(){
    size = 0;
}
void Stack_A::push(int data){
    if(size!=1024){
    stk[size] = data;
    size++;
    }
    else{
        throw std::runtime_error("Stack Full");
    }
}
int Stack_A::pop(){
    if (size>0){
        int elem = stk[size-1];
        size--;
        return elem;
    }
    else{
        throw std::runtime_error("Empty Stack");
    }
}
int Stack_A::get_element_from_bottom(int idx){
    if(idx>=0 && idx<size){
        return stk[idx];
    }
    else{
        throw std::runtime_error("Index out of range");
    }
}
int Stack_A::get_element_from_top(int idx){
    if(idx>=0 && idx<size){
        return stk[size-idx-1];
    }
    else{
        throw std::runtime_error("Index out of range");
    }
}
void Stack_A::print_stack(bool top_or_bottom){
    if(top_or_bottom==true){ //true means printinhg from top
        int num = size;
        while(num>0){
            std::cout<<stk[num-1]<<'\n';
            num--;
        }
    }
    else{
        int num=0;
        while(num<size){
            std::cout<<stk[num]<<'\n';
            num++;
        }
    }
}
int Stack_A::add(){
    if(size>=2){
        int res = pop()+pop();
        push(res);
        return res;
    }
    else{
        throw std::runtime_error("Not Enough Arguments");
    }
}
int Stack_A::subtract(){
    if(size>=2){
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
int Stack_A::multiply(){
    if(size>=2){
        int res = pop()*pop();
        push(res);
        return res;
    }
    else{
        throw std::runtime_error("Not Enough Arguments");
    }
}
int Stack_A::divide(){
    if(size>=2){
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
int* Stack_A::get_stack(){
    int *arr = stk;
    return arr;
}
int Stack_A::get_size(){
    return size;
}