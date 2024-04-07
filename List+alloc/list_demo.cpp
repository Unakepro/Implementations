#include "list.hpp"

int main() {
    List<int> lst;

    for(int i = 0; i < 100; ++i) {
        lst.push_back(i);
    }

    for(int i = 100; i > 0; --i) {
        lst.push_front(i);
    }

    lst.print();
}