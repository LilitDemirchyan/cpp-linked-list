#include "list_header.hpp"
#include <iostream>

//Constructor and destructor

List::List() :head{nullptr}, tail{nullptr}, m_size{0}{}

List::Node::Node(value_type val) {
    data = val;
    next = nullptr;
}
List::List(const std::initializer_list<value_type>& init){
    for(int x : init){
        push_back(x);
    }
}
List::List(size_type count, const_reference value){
    for(int i = 0; i < count; ++i){
        push_back(value);
    }
}
List::List(const List& other){
    m_size = other.m_size;
    for(int i = 0; i < m_size; ++i){
        push_back(other[i].data);
    }
}
List::List(List&& other){
    this -> m_size = std::exchange(other.m_size, 0);
    this -> head = std::exchange(other.head, nullptr);
    this -> tail = std::exchange(other.tail, nullptr);
}
List::~List(){
    while(head != nullptr){
        Node* tmp = head;
        head = head -> next;
        delete tmp;
    }
    tail = nullptr;
    m_size = 0;
}
List& List::operator=(const List& other){
    if(this == &other){
        return *this;
    }
    clear();
    for(int i = 0; i < other.m_size; ++i){
        push_back(other[i].data);
    }
    return *this;
}
List& List::operator=(List&& other){
    if(this == &other){
        return *this;
    }
    this -> m_size = std::exchange(other.m_size, 0);
    this -> head = std::exchange(other.head, nullptr);
    this -> tail = std::exchange(other.tail, nullptr);
    return *this;
}
List& List::operator=(const std::initializer_list<value_type>& ilist){
    clear();
    for(value_type x : ilist){
        push_back(x);
    }
    return *this;
}
List::Node& List::operator[](size_t index){
    return const_cast<Node&>(static_cast<const List&>(*this).operator[](index));
}
const List::Node& List::operator[](size_t index) const{
    if(index >= m_size){
        throw std::out_of_range("Index is greater than size");
    }
    Node* cur = head;
    for(int i = 0; i < index; ++i){
        cur = cur -> next;
    }
    return *cur;
}
const List List::operator+(const List& other) const{
    List tmp;
    Node* tptr = this -> head;
    Node* optr = other.head;
    int size = std::min(m_size, other.m_size);
    for(int i = 0; i < size; ++i){
        tmp.push_back(tptr -> data);
        tmp.push_back(optr -> data);
        tptr = tptr -> next;
        optr = optr -> next;
    }
    if(tptr == nullptr){
        tptr = optr;
    }
    while(tptr != nullptr){
        tmp.push_back(tptr -> data);
        tptr = tptr -> next;
    }
    return tmp;
}

//methods

void List::push_front(const_reference obj){
    Node* node = new Node(obj);
    if(head == nullptr){
        tail = node;
    }
    node -> next = head;
    head = node;
    ++m_size;
}
void List::push_back(const_reference obj){
    Node* node = new Node(obj);
    if(head == nullptr){
        head = tail = node;  
    } 
    else{
        tail->next = node;
        tail = node;
    }
    ++m_size;
}
List::value_type List::pop_front(){
    if(m_size == 0){
        throw std::out_of_range("List is empty");
    }
    Node* node = head;
    head = head -> next;
    if(!head){
        tail = head;
    }
    value_type tmp2 = node -> data;
    delete node;
    --m_size;
    return tmp2;
}
List::value_type List::pop_back(){
    if(m_size == 0){
        throw std::runtime_error("list is empty:");
    }
    if (m_size == 1){
        value_type val = head -> data;
        delete head;
        head = tail = nullptr;
        m_size = 0;
        return val;
    }
    Node* curr = head;
    while(curr->next != tail){
        curr = curr->next;
    }
    value_type val = tail->data;
    delete tail;
    tail = curr;
    tail->next = nullptr;
    --m_size;
    return val;
}
void List::insert(size_type index, const_reference value){
    if (index > m_size){
        throw std::out_of_range("Index out of range");
    }
    if (index == 0){
        push_front(value);
        return;
    }
    if (index == m_size){
        push_back(value);
        return;
    }
    Node* prev = head;
    for (size_t i = 0; i < index - 1; ++i){
        prev = prev->next;
    }
    Node* newNode = new Node(value);
    newNode->next = prev->next;
    prev->next = newNode;
    ++m_size;
}
void List::erase(size_type pos){
    if (pos >= m_size){
        throw std::out_of_range("Index out of range");
    }
    if (pos == 0){
        pop_front();
        return;
    }
    Node* prev = head;
    for (size_t i = 0; i < pos - 1; ++i){
        prev = prev->next;
    }
    Node* fdelete = prev->next;
    prev->next = fdelete->next;
    if (fdelete== tail){
        tail = prev;
    }
    delete fdelete;
    --m_size;
}
void List::clear() noexcept{
    while (head != nullptr){
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
    tail = nullptr;
    m_size = 0;
}

//lookup

bool List::find(const_reference value) const{
    Node* curr = head;
    while (curr){
        if (curr->data == value){
            return true;
        }
        curr = curr->next;
    }
    return false;
}
List::Node* List::search(size_t index) const{
    if (index >= m_size){
        return nullptr;
    }
    Node* curr = head;
    for (size_t i = 0; i < index; ++i){
        curr = curr->next;
    }
    return curr;
}

//element acces

List::reference List::front(){
    if (empty()){
        throw std::out_of_range("List is empty");
    }
    return head->data;
}
List::const_reference List::front() const{
    if (empty()){
        throw std::out_of_range("List is empty");
    }
    return head->data;
}
List::reference List::back(){
    if (empty()){
        throw std::out_of_range("List is empty");
    }
    return tail->data;
}
List::const_reference List::back() const{
    if (empty()){
        throw std::out_of_range("List is empty");
    }
    return tail->data;
}

//capacity 

List::size_type List::size() const {
    return m_size;
}
bool List::empty() const {
    return m_size == 0;
}