#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <cassert>

template <typename T>
class Deque {
    T** container = nullptr;
    size_t c_size;
    std::pair<size_t, size_t> start_index;
    std::pair<size_t, size_t> end_index;

public:
    Deque():  c_size(0), start_index({0, 0}), end_index({0, 0}) {}

    Deque(size_t size, const T& value = T()) {

        size_t num = std::ceil(size/32.0);
        size_t diff = num * 32 - size;
        
        container = new T*[num+2];
        c_size = num+2;

        start_index.first = 1;
        start_index.second = diff/2;

        end_index.first = num;
        end_index.second = (32-(diff - diff/2))-1;
        
        for(size_t i = 0; i < c_size; ++i) {
            container[i] = reinterpret_cast<T*>(new int8_t[32*sizeof(T)]); 
        }


        for (size_t j = start_index.second; j < 32 - (32 - end_index.second) * (start_index.first == end_index.first); ++j)
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

    void push_back(const T& value) {
        // doesn't work with push when zero elem
        if(end_index.first == c_size-1 && end_index.second == 31) {
            
            size_t new_size = c_size*2;
            size_t diff = (new_size-c_size)/2;    
            
            start_index.first = start_index.first + diff;
            end_index.first = end_index.first + diff;


            T** tmp_c = new T*[new_size];

            for(size_t i = 0; i < c_size; ++i) {
                tmp_c[i+diff] = container[i];
            }

            for(size_t i = 0; i < diff; ++i) {
                tmp_c[i] = reinterpret_cast<T*>(new int8_t[32*sizeof(T)]);
            }

            for(size_t i = c_size+diff; i < new_size; ++i) {
                tmp_c[i] = reinterpret_cast<T*>(new int8_t[32*sizeof(T)]);
            }

            delete [] container;            

            container = tmp_c;
            c_size = new_size;
        }
        
        if(end_index.second == 31) {
            ++end_index.first;
            end_index.second = 0;
        }
        else {
            ++end_index.second;
        }
        new(container[end_index.first]+end_index.second) T(value);
    }

    void push_front(const T& value) {
        if(start_index.first == 0 && start_index.second == 0) {
            
            size_t new_size = c_size*2;
            size_t diff = (new_size-c_size)/2;    
            
            start_index.first = start_index.first + diff;
            end_index.first = end_index.first + diff;


            T** tmp_c = new T*[new_size];

            for(size_t i = 0; i < c_size; ++i) {
                tmp_c[i+diff] = container[i];
            }

            for(size_t i = 0; i < diff; ++i) {
                tmp_c[i] = reinterpret_cast<T*>(new int8_t[32*sizeof(T)]);
            }

            for(size_t i = c_size+diff; i < new_size; ++i) {
                tmp_c[i] = reinterpret_cast<T*>(new int8_t[32*sizeof(T)]);
            }

            delete [] container;            

            container = tmp_c;
            c_size = new_size; 
        }
        
        if(start_index.second == 0) {
            --start_index.first;
            start_index.second = 31;
        }
        else {
            --start_index.second;
        }
        new(container[start_index.first]+start_index.second) T(value);
    }

    void pop_back() {

    }

    void pop_front() {
        
    }



    void print() {


        if(start_index.first == end_index.first) {
            for(size_t j = start_index.second; j <= end_index.second; ++j) {
                std::cout << container[start_index.first][j] << ' ';
            }
        }
        else {
            for(size_t j = start_index.second; j < 32; ++j) {
                std::cout << container[start_index.first][j] << ' ';
            }
            std::cout << std::endl;
            
            for(size_t i = start_index.first+1; i < end_index.first; ++i) {
                for(size_t j = 0; j < 32; ++j) {
                    std::cout << container[i][j] << ' ';
                }
                std::cout << std::endl;
            }
            for(size_t j = 0; j <= end_index.second; ++j) {
                std::cout << container[end_index.first][j] << ' ';
            }
            std::cout << std::endl;



        }
    }
    
    void print_memory() {
        for(size_t i = 0; i < c_size; ++i) {
            std::cout << container[i] << ' ';
        }
        std::cout << std::endl;
    }


    size_t size() const {
        return 32 * (end_index.first - start_index.first + 1) - start_index.second - (32 - (end_index.second)-((end_index.first+start_index.first) != 0));
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
    

};



int main() {
    Deque<int> xs(153, 5);

    xs.print();
    std::cout << xs.size() << std::endl;
    std::cout << xs.capacity() << std::endl;
    //std::cout << xxs.size() << std::endl;

    // std::cout << xs.capacity() << std::endl;
    // for(int i = 0; i < 153; ++i) {
    //     xs[i] = i+1;
    // }

    Deque<int> xxs = xs;
    std::cout << xxs.size() << std::endl;
    std::cout << xxs.capacity() << std::endl;

    //xxs.print();
    // for(int i = 0; i < 153; ++i) {
    //   std::cout << xs[i] << ' ';
    // }
    
    std::cout << "\n\n";

    for(int i = 3500; i > 0; --i) {
        xs.push_front(i);
    }
    

    for(int i = 36; i > 0; --i) {
        xs.push_back(1);
    }
    xs.push_back(404);
    
    int& test = xs[224];

    std::cout << test << std::endl;

    for(int i = 3500; i > 0; --i) {
        xs.push_back(i);
    }

    std::cout << test << std::endl;

    //std::cout << xxs.capacity() << std::endl;

    //xs.print_vector();
    //xxs.print_vector();

}