#ifndef LIST
#define LIST

#include <iostream>
#include <memory>


template <typename T, typename Allocator = std::allocator<T>>
class List {    
    
    struct Node {
        T value;
        Node* next = nullptr;
        Node* prev = nullptr;

        Node(const T& obj): value(obj) {}
        Node(const Node& obj): value(obj.value), next(obj.next), prev(obj.next) {}
    };


    Node* head = nullptr;
    Node* tail = nullptr;

    size_t elements = 0;

    using AllocTraits = std::allocator_traits<Allocator>;
    using NodeAllocator = typename AllocTraits::template rebind_alloc<Node>;
    using NodeAllocTraits = std::allocator_traits<NodeAllocator>;
    
    NodeAllocator node_alloc;

public:
    //explicit List(const Allocator& obj = Allocator()) {
    //
    //}

    size_t size() const {
        return elements;
    }

    void push_back(const T& obj) {
        Node* newnode = NodeAllocTraits::allocate(node_alloc, 1);
        NodeAllocTraits::construct(node_alloc, newnode, obj);

        if(elements == 0) {
            head = newnode;
            tail = newnode;
        }
        else {
            newnode->prev = head;
            head = newnode;
            
            (head->prev)->next = head;
        }
        ++elements;
    }

    void push_front(const T& obj) {
        Node* newnode = NodeAllocTraits::allocate(node_alloc, 1);
        NodeAllocTraits::construct(node_alloc, newnode, obj);


        if(elements == 0) {
            head = newnode;
            tail = newnode;
        }
        else {
            newnode->next = tail;
            tail = newnode;
            
            (tail->next)->prev = head;
        }
    }

    void pop_back() {
        if(elements != 0) {
            if(elements == 1) {
                NodeAllocTraits::destroy(node_alloc, head);
                head = nullptr;
                tail = nullptr;
            }
            else {
                head = head->prev;
                NodeAllocTraits::destroy(node_alloc, head->next);
                head->next = nullptr;
            }
        }
    }


    void pop_front() {
        if(elements != 0) {
            if(elements == 1) {
                //AllocTraits::destroy(alloc, tail);
                head = nullptr;
                tail = nullptr;
            }
            else {
                tail = tail->next;
                //AllocTraits::destroy(alloc, tail->prev);
                tail->prev = nullptr;
            }
        }
    }

    Allocator get_allocator() const {
        return node_alloc;
    }

    void print() {
        
        for(Node* i = tail; i != nullptr;) {
            std::cout << (i->value) << ' ';
            i = i->next;
        }
    }

};

#endif