#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <cassert>
#include "deque.hpp"


class Test {
    double x;

public:
    Test(double x): x(x) {}

    ~Test() {
        std::cout << " object destructed "; 
    }

    friend std::ostream& operator<<(std::ostream& out, const Test& obj) {
        out << obj.x;
        return out;
    }
};



int main() {
    Deque<int> xs(5, 5);

    for(int i = 1; i < 101; ++i) {
        xs.push_back(i);
    }

    for(int i = 0; i < 105; ++i) {
        std::cout << xs[i] << ' ';
    }
  
    std::cout << std::endl;
    auto it = xs.begin();
    auto it2 = xs.begin();
    ++it;
    it+=4;
    it+=32;
    it+=-32;

    std::cout << (it == it2) << std::endl;
    std::cout << (it != it2) << std::endl;
    std::cout << (it > it2) << std::endl;
    std::cout << (it < it2) << std::endl;
    std::cout << (it <= it2) << std::endl;
    std::cout << (it >= it2) << std::endl;

    std::cout << (it-it2) << std::endl;

    auto it3 = xs.cbegin();
    auto it4 = xs.cedn();

    while (it3 != it4)
    {
        std::cout << (*it3) << ' ';
        ++it3;
    }

    std::cout << "\n\n\n";

    auto it5 = xs.crbegin();
    auto it6 = xs.crend();

    
    while(it5.base() != it6.base()) {
        std::cout << *(it5.base()) << ' ';
        ++it5;
    }

    std::cout << "\n\n\n";

    auto it7 = xs.rbegin();
    auto it8 = xs.rend();

    while(it7.base() != it8.base()) {
        std::cout << *(it7.base()) << ' ';
        ++it7;
    }
    std::cout << "\n\n\n";

    auto it9 = xs.begin();


    xs.insert(it9, 404);

    std::cout << "\n\n\n";

    for(int i = 0; i < 106; ++i) {
      xs.erase(it9);
    }

    Deque<int> xxs;

    for(int i = 0; i < 100; ++i) {
        xxs.push_front(i);
    }

    Deque<Test> xxy;
    for(int i = 0; i < 100; ++i) {
        xxy.push_back(Test(5.0));
    }


}