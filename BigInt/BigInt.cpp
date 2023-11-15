#include <iostream>
#include <cassert>
#include "BigInt.hpp"

int main() {
    BigInt x(10);
    BigInt y(2);

    std::cout << x << std::endl;
	
	//std::cin >> y;
	//std::cout << y.toString() << std::endl;
    //std::cin >> y;
    //std::cout << y << std::endl;


    //std::cout << (x*=y) << std::endl;
    //std::cout << (x/=y) << std::endl;

    //std::cout << x % x << std::endl;


	
    std::cout << (x > y) << std::endl;
    std::cout << (x < y) << std::endl;
    std::cout << (x >= y) << std::endl;
    std::cout << (x <= y) << std::endl;   

    std::cout << (x == y) << std::endl;
    std::cout << (x != y) << std::endl;
	
	//std::cout << (-x) << std::endl;

	for(int i=0; i<999999; ++i) {
		BigInt k(i);
		for(int j=0; j<999999;++j) {
			BigInt v(j);
			std::cout << "BigInt: " << (k+v) << " add: " << (i+j) << '\n';
			assert(k+v == i+j);
		}
	}

    //std::cout << (x+=y) << std::endl;

    //std::cout << x++ << std::endl;
    //std::cout << ++x << std::endl;

    //std::cout << x-- << std::endl;
    //std::cout << --x << std::endl;



    return 0;
}

