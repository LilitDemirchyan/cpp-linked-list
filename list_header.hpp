#ifndef LIST_HEADER
#define LIST_HEADER

#include <iostream>
#include <utility>
#include <initializer_list>

class List {

public:
    using value_type = int;
    using size_type = std::size_t;
    using reference = int&;
    using const_reference =const int&;
    using const_pointer = const int*;
private:
    struct Node {
        Node(value_type val);
        value_type data;
        Node* next;
    };
public:
    //ctors and dtors
    List();
    List(const std::initializer_list<value_type>&);
    List(size_type count, const_reference value);
    List(const List&);
    List(List&&);
    ~List();
public:
    List& operator=(const List& other);
    List& operator=(List&& other);
    List& operator=(const std::initializer_list<value_type>& ilist);
    Node& operator[](size_t index);
    const Node& operator[](size_t index) const;
    const List operator+(const List& rhs) const;

//methods;
    void push_front(const_reference obj);
    void push_back(const_reference obj);
    value_type pop_front();
    value_type pop_back();
    void insert(size_type index, const_reference value);
    void erase(size_type pos);
    void clear() noexcept;

    // Lookup
    bool find(const_reference value) const;
    Node* search(size_t index) const;


    //element accses
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    //capacity
    bool empty() const;
    size_type size() const;


private:
    Node* head;
    Node* tail;
    size_t m_size;
};




#endif// LIST_HPP
