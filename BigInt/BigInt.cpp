#include "BigInt.hpp"


int main() {
    BigInt x(99999);
    BigInt y;

    std::cout << x << std::endl;
	
	std::cin >> y;
	std::cout << y.toString() << std::endl;
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
	
	std::cout << (-x) << std::endl;

    //std::cout << (x-=y) << std::endl;

    //std::cout << x++ << std::endl;
    //std::cout << ++x << std::endl;

    //std::cout << x-- << std::endl;
    //std::cout << --x << std::endl;



    return 0;
}

