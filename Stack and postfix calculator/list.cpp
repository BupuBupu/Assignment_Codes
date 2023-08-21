#include "list.h"
List::List(){
    sentinel_head = new Node();
    sentinel_tail = new Node();
    size = 0; //Initialised as a zero sized list
    sentinel_head->next = sentinel_tail;
    sentinel_tail->prev = sentinel_head;
}
List::~List(){
    while (this->get_size()!=0)
    {
        this->delete_tail();
    }
    delete sentinel_head;
    delete sentinel_tail;
}
void List::insert(int v){
    Node* nd = new Node(v,nullptr,nullptr);
    Node* prv = sentinel_tail->prev;
    prv->next = nd;
    nd->prev = prv;
    sentinel_tail->prev = nd;
    nd->next = sentinel_tail;
    size++;
}
int List::delete_tail(){
    Node* nd = sentinel_tail->prev;
    int val = nd->get_value();
    size--;
    Node* prv = nd->prev;
    prv->next = sentinel_tail;
    sentinel_tail->prev = prv;
    delete nd;
    return val;
}
int List::get_size(){
    return size;
}
Node* List::get_head(){
    Node* tmp = sentinel_head;
    return tmp;
}
