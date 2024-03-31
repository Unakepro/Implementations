#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <cassert>


void incr_pair(std::pair<size_t, size_t>& obj) {
    obj.second = (obj.second + 1) % 32;
    obj.first += (obj.second == 0);
}

void decr_pair(std::pair<size_t, size_t>& obj) {
    obj.second = (obj.second - 1) + 32 * (obj.second == 0);
    obj.first -= (obj.second == 31);
}


template <typename Iterator>
class deque_reverse_iterator {
    Iterator iter;
public:
    deque_reverse_iterator(const Iterator& iter): iter(iter) {}

    deque_reverse_iterator<Iterator>& operator++() {
        --iter;
        return *this;
    }

    Iterator base() const {
        return iter;
    }

};

template <typename T>
class Deque {
    T** container = nullptr;
    size_t c_size;
    size_t elements;
    std::pair<size_t, size_t> start_index;
    std::pair<size_t, size_t> end_index;

public:
    Deque():  c_size(0), elements(0), start_index({0, 0}), end_index({0, 0}) {}

    Deque(size_t size, const T& value = T()) {

        size_t num = std::ceil(size/32.0);
        size_t diff = num * 32 - size;
        
        container = new T*[num+2];
        c_size = num+2;
        elements = size;

        start_index.first = 1;
        start_index.second = diff/2;

        end_index.first = num;
        end_index.second = (32-(diff - diff/2))-1;
        

        for(size_t i = 0; i < c_size; ++i) {
            container[i] = reinterpret_cast<T*>(new int8_t[32*sizeof(T)]); 
        }


        for (size_t j = start_index.second; j <= 32 - (32 - end_index.second) * (start_index.first == end_index.first); ++j)
        {
            new(container[start_index.first]+j) T(value);
        }
        
        for(size_t i = start_index.first+1; i < end_index.first; ++i) {
            for(size_t j = 0; j < 32; ++j) {
                new(container[i]+j) T(value);     
            }
        }
        
        for(size_t j = 0; j < (end_index.second+1) * (start_index.first != end_index.first); ++j) {
            new(container[end_index.first]+j) T(value);
        }

    }

    Deque(const Deque<T>& obj) {
        if(this != &obj) {
        

            start_index.first = obj.start_index.first;
            start_index.second = obj.start_index.second;

            end_index.first = obj.end_index.first;
            end_index.second = obj.end_index.second;
            
            container = new T*[obj.c_size];
            c_size = obj.c_size;
            elements = obj.elements;


            for(size_t i = 0; i < c_size; ++i) {
                container[i] = reinterpret_cast<T*>(new int8_t[32*sizeof(T)]); 
            }


            for (size_t j = start_index.second; j < 32 - (32 - end_index.second) * (start_index.first == end_index.first); ++j)
            {
                new(container[start_index.first]+j) T(*(obj.container[obj.start_index.first]+j));
            }
            
            for(size_t i = start_index.first+1; i < end_index.first; ++i) {
                for(size_t j = 0; j < 32; ++j) {
                    new(container[i]+j) T(*(obj.container[i]+j));     
                }
            }
            
            for(size_t j = 0; j < (end_index.second+1) * (start_index.first != end_index.first); ++j) {
                new(container[end_index.first]+j) T(*(obj.container[obj.end_index.first]+j));
            }

        }    
    }

    
    void resize_deque() {
        size_t new_size = c_size*2;
        size_t diff = (new_size-c_size)/2;    

        T** tmp_c = new T*[new_size];

        for(size_t i = start_index.first; i <= end_index.first; ++i) {
            tmp_c[i+diff] = container[i];
        }

        start_index.first = start_index.first + diff;
        end_index.first = end_index.first + diff;

        for(size_t i = 0; i < start_index.first; ++i) {
            tmp_c[i] = reinterpret_cast<T*>(new int8_t[32*sizeof(T)]);
        }

        for(size_t i = end_index.first+1; i < new_size; ++i) {
            tmp_c[i] = reinterpret_cast<T*>(new int8_t[32*sizeof(T)]);
        }

        delete [] container;            

        container = tmp_c;
        c_size = new_size;
    }


    void push_back(const T& value) {
        if(c_size == 0) {
            c_size = 3;
            container = new T*[c_size];
            
            for(size_t i = 0; i < c_size; ++i) {
                container[i] = reinterpret_cast<T*>(new int8_t[32*sizeof(T)]); 
            }
            
            new(container[end_index.first]+end_index.second) T(value);
            ++elements;
        }
        else {
            if(end_index.first == c_size-1 && end_index.second == 31) {
                resize_deque();
            }
            
            incr_pair(end_index);
            new(container[end_index.first]+end_index.second) T(value);
            ++elements;
        }
    }

    void push_front(const T& value) {
        if(c_size == 0) {
            c_size = 3;
            container = new T*[c_size];
            
            start_index.first = 1;
            start_index.second = 15;

            end_index.first = 1;
            end_index.second = 15;
            for(size_t i = 0; i < c_size; ++i) {
                container[i] = reinterpret_cast<T*>(new int8_t[32*sizeof(T)]); 
            }
            
            new(container[start_index.first]+start_index.second) T(value);
            ++elements;
        }
        else {
            if(start_index.first == 0 && start_index.second == 0) {
                resize_deque();
            }

            decr_pair(start_index);
            new(container[start_index.first]+start_index.second) T(value);
            ++elements;
        }
    }



    void pop_back() {
        if(size() != 0) {
            (container[end_index.first]+end_index.second)->~T();
             
            decr_pair(end_index);
            --elements;
        }
  
    }

    void pop_front() {
        if(size() != 0) {
            (container[start_index.first]+start_index.second)->~T(); 
            
            incr_pair(start_index);
            --elements;
        }
    }

    size_t size() const {
        return elements;
    }

    size_t capacity() const {
        return c_size*32;
    }

    T& operator[](int index) {
        return container[((start_index.second+index)/32) + start_index.first][(index+start_index.second)%32];
    }

    const T& operator[](int index) const {
        return container[((start_index.second+index)/32) + start_index.first][(index+start_index.second)%32];
    }

    T& at(int index) {
        if(index < 0 || index >= size()) {
            throw std::logic_error("Index out of bounds");
        }
        return container[((start_index.second+index)/32) + start_index.first][(index+start_index.second)%32];
    }

    template <bool isConst>
    class common_iterator {
        T** ptr;
        std::pair<size_t, size_t> iter_index;
    public:
        common_iterator(T** ptr, size_t container_index, size_t item_index):  ptr(ptr), iter_index({container_index, item_index}) {}


        std::conditional_t<isConst, const T&, T&> operator*() {
            return ptr[iter_index.first][iter_index.second];
        }

        std::conditional_t<isConst, const T*, T*> operator->() {
            return ptr[iter_index.first]+iter_index.second;
        }


        std::conditional_t<isConst, const common_iterator&, common_iterator&> operator++() {
            incr_pair(iter_index);
            
            return *this;
        }

        std::conditional_t<isConst, const common_iterator&, common_iterator&> operator--() {
            decr_pair(iter_index);
            
            return *this;
        }

        std::conditional_t<isConst, const common_iterator&, common_iterator&> operator+=(int64_t value) {
            if(value >= 0) {
                iter_index.first += (static_cast<long int>(iter_index.second) + value) / 32;            
                iter_index.second = (static_cast<long int>(iter_index.second) + value) % 32;
            }
            else {
                iter_index.first -= (static_cast<long int>(iter_index.second) + std::abs(value)) / 32;
                iter_index.second = (static_cast<long int>(iter_index.second) + value) + 32 * (static_cast<long int>(iter_index.second) < std::abs(value));
            }

            return *this;
        }

        int64_t operator-(const common_iterator& obj) {
            return 32*(iter_index.first - obj.iter_index.first) + (iter_index.second - obj.iter_index.second);
        }

        std::pair<size_t, size_t> getPair() const {
            return iter_index;
        }

        bool operator==(const common_iterator& obj) const {
            return iter_index.first == obj.iter_index.first && iter_index.second == obj.iter_index.second;
        }

        bool operator!=(const common_iterator& obj) const {
            return !(*this == obj);
        }

        bool operator>(const common_iterator& obj) const {
            return iter_index.first > obj.iter_index.first || (iter_index.first >= obj.iter_index.first && iter_index.second > obj.iter_index.second);
        }

        bool operator<(const common_iterator& obj) const {
            return (obj > *this);
        }

        bool operator>=(const common_iterator& obj) const {
            return (*this > obj) || (*this == obj);
        }

        bool operator<=(const common_iterator& obj) const {
            return (*this < obj) || (*this == obj);
        }
    };


    using iterator = common_iterator<false>;
    using const_iterator = common_iterator<true>;
    using reverse_iterator = deque_reverse_iterator<iterator>;
    using const_reverse_iterator = deque_reverse_iterator<const_iterator>;


    std::conditional_t<std::is_const_v<T>, const_iterator, iterator> begin() {
        if constexpr(std::is_const_v<T>) {
            return const_iterator(container, start_index.first, start_index.second);
        }
        else {
            return iterator(container, start_index.first, start_index.second);
        }
    }
    
    std::conditional_t<std::is_const_v<T>, const_iterator, iterator> end() {
        std::pair<size_t, size_t> copy_end(end_index);
        incr_pair(copy_end);

        if constexpr(std::is_const_v<T>) {
            return const_iterator(container, copy_end.first, copy_end.second);
        }
        else {
            return iterator(container, copy_end.first, copy_end.second);
        }
    }

    const_iterator cbegin() const {
        return const_iterator(container, start_index.first, start_index.second);
    }

    const_iterator cedn() const {
        std::pair<size_t, size_t> copy_end(end_index);
        incr_pair(copy_end);
        return const_iterator(container, copy_end.first, copy_end.second);
    }

    std::conditional_t<std::is_const_v<T>, const_reverse_iterator, reverse_iterator> rbegin() {
        if constexpr(std::is_const_v<T>) {
            return const_reverse_iterator(const_iterator(container, end_index.first, end_index.second));
        }  
        else {
            return reverse_iterator(iterator(container, end_index.first, end_index.second));
        }
    }

    std::conditional_t<std::is_const_v<T>, const_reverse_iterator, reverse_iterator> rend() {
        std::pair<size_t, size_t> copy_start(start_index);
        decr_pair(copy_start);
        if constexpr(std::is_const_v<T>) {
            return const_reverse_iterator(const_iterator(container, copy_start.first, copy_start.second));
        }  
        else {
            return reverse_iterator(iterator(container, copy_start.first, copy_start.second));
        }
    }

    const_reverse_iterator crbegin() {
        return const_reverse_iterator(const_iterator(container, end_index.first, end_index.second));
    }

    const_reverse_iterator crend() {
        std::pair<size_t, size_t> copy_start(start_index);
        decr_pair(copy_start);
        return const_reverse_iterator(const_iterator(container, copy_start.first, copy_start.second));
    }

    void insert(iterator iter, const T& value) {
        if(end_index.first == c_size-1 && end_index.second == 31) { 
            resize_deque();
        }

        T tmp_value = *iter;
        T hold_value;

        *iter = value;

        while(iter != end()) {
            ++iter;
            hold_value = *iter;          
            *iter = tmp_value;
            tmp_value = hold_value;
        }
        *(++iter) = tmp_value;

        ++elements;
        incr_pair(end_index);  
    }

    void erase(iterator iter) {
        if(size() == 0 || end_index.first < iter.getPair().first || (end_index.first == iter.getPair().first && end_index.second < iter.getPair().second)) {
            throw std::logic_error("Erase on non-existing element");
        }
        iter->~T();
        
        auto end_iter = iterator(container, end_index.first, end_index.second);

        T tmp_value = *end_iter;
        T hold_value;

        while(end_iter != iter) {
            --end_iter;
            hold_value = *end_iter;
            *end_iter = tmp_value;
            tmp_value = hold_value;
        }

        decr_pair(end_index);
        --elements;
    }

    ~Deque() {
        auto iter_start = (*this).begin();
        auto iter_end = (*this).end();

        while(iter_start != iter_end) {
            iter_start->~T();
            ++iter_start;
        }
        
        for(size_t i = 0; i < c_size; ++i) {
            delete [] reinterpret_cast<int8_t*>(container[i]);
        }
        delete [] container;

    }
};