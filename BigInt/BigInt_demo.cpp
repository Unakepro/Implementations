#include <iostream>
#include <cassert>
#include "BigInt.hpp"

int main() {
    BigInt x(-2);
    BigInt y(11);

    std::cout << x << std::endl;
	
	std::cin >> y;
	std::cout << y.toString() << std::endl;


    std::cout << (x % x) << std::endl;



    std::cout << (x > y) << std::endl;
    std::cout << (x < y) << std::endl;
    std::cout << (x >= y) << std::endl;
    std::cout << (x <= y) << std::endl;   

    std::cout << (x == y) << std::endl;
    std::cout << (x != y) << std::endl;
	
	std::cout << (-x) << std::endl;


    std::cout << (x+y) << std::endl;
    std::cout << (x-y) << std::endl;

    std::cout << (x*y) << std::endl;
    std::cout << (x/y) << std::endl;

    std::cout << x++ << std::endl;
    std::cout << ++x << std::endl;

    std::cout << x-- << std::endl;
    std::cout << --x << std::endl;


    return 0;
}

