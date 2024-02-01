#include <iostream>
#include <vector>
#include <type_traits>
#include <utility>
#include <cmath>
#include "matrix.hpp"



int main() {
    std::vector<double> xs{1, 2, 2, 3, 1, 1};

    Matrix<2, 3> a(xs);

    std::cout << a << std::endl;
    
    for(auto x: a.getRow(0)) {
         std::cout << x << ' ';
    }

    std::cout << '\n';

    for(auto x: a.getColumn(0)) {
        std::cout << x << '\n';
    }
    std::cout << '\n';
    
    Matrix<3, 2> b({4, 2, 3, 1, 1, 5});
    
    std::cout << b << std::endl;

    for(auto x: b.getRow(0)) {
         std::cout << x << ' ';
    }

    std::cout << '\n';

    for(auto x: b.getColumn(0)) {   
        std::cout << x << '\n';
    }
       
    std::cout << (a+a) << std::endl;
    std::cout << (a-a) << std::endl;

    std::cout << (a == a) << std::endl;
    std::cout << (a != b) << std::endl;

    std::cout << (a * 5) << std::endl;

    std::cout << a << std::endl;
    std::cout << a.getRefValue(0, 0) << std::endl;

    std::cout << (a*b) << std::endl;

    std::vector<double> sq_m{1, 1, 1, 0, 0, 2, 3, 0, 2, 1, 5, 1, 4, 0, 7, -1};
    Matrix<4, 4> c(sq_m); 

    std::cout << c.trace() << std::endl;


    std::vector<int> tr_v{1, 2, 3, 4, 5, 6};
    Matrix<2, 3, int> d(tr_v);
    
    std::cout << d.transposed() << std::endl;

    a.getRefValue(0, 0) = 0;

    std::cout << a << std::endl;

    Matrix<3, 3, int> e({-1, 2, -5, 3, 4, 1, 0, 1, 2}); 

    e *= e;

    std::cout << e << std::endl;

    std::cout << e.det() << std::endl;

}