#include "stack_b.h"
#include <iostream>
#include <stdexcept>
#define C 2
Stack_B::Stack_B(){
    capacity = 1024;
    stk = new int[capacity];
    size = 0;
}
Stack_B::~Stack_B(){
    delete stk;
}
void Stack_B::push(int data){
    if(size==capacity){
        try{
        int *tmp = new int[capacity*C];
        capacity = capacity*C;
        for (int i = 0; i < size; i++)
        {
            tmp[i] = stk[i];
        }
        delete stk;
        stk = tmp;
        stk[size] = data;
        size++;
        }
        catch(const std::bad_alloc& ecp){
            throw std::runtime_error("Out of Memory");
        }
    }
    else{
        stk[size]=data;
        size++;
    }
}
int Stack_B::pop(){
    if(size<=0){
        throw std::runtime_error("Empty Stack");
    }
    else{
        if(size-1<=(capacity/(C*C)) && (capacity/C)>=1024){
            try{
                int elem = stk[size-1];
                size--;
                int * tmp = new int[capacity/C];
                capacity = capacity/C;
                for (int i = 0; i < size; i++)
                {
                    tmp[i]=stk[i];
                }
                delete stk;
                stk = tmp;
                return elem;
            }
            catch(const std::bad_alloc& exp){
                throw std::runtime_error("Out of Memory");
            }
        }
        else{
            int elem = stk[size-1];
            size--;
            return elem;
        }
    }
}
int Stack_B::get_element_from_bottom(int idx){
    if(idx>=0 && idx<size){
        return stk[idx];
    }
    else{
        throw std::runtime_error("Index out of range");
    }
}
int Stack_B::get_element_from_top(int idx){
    if(idx>=0 && idx<size){
        return stk[size-idx-1];
    }
    else{
        throw std::runtime_error("Index out of range");
    }
}
void Stack_B::print_stack(bool top_or_bottom){
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
int Stack_B::add(){
    if(size>=2){
        int res = pop()+pop();
        push(res);
        return res;
    }
    else{
        throw std::runtime_error("Not Enough Arguments");
    }
}
int Stack_B::subtract(){
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
int Stack_B::multiply(){
    if(size>=2){
        int res = pop()*pop();
        push(res);
        return res;
    }
    else{
        throw std::runtime_error("Not Enough Arguments");
    }
}
int Stack_B::divide(){
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
int* Stack_B::get_stack(){
    int *arr = stk;
    return arr;
}
int Stack_B::get_size(){
    return size;
}
