#include <iostream>
#include "string.hpp"

int main() {

 	const char* cs = "Hello World!";


 	String a(2, 'a');
 	String b(cs);
 	String c(a);
 	String d;

 	d = b;

	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << c << std::endl;
	std::cout << d << std::endl;

	std::cout << (a == c) << std::endl;
	std::cout << (a == b) << std::endl;

	a.pop_back();

	for(int i=0;i<10;++i) {
		a.push_back('c');
	}

	std::cout << a << std::endl;

	std::cout << d.front() << std::endl;
	std::cout << d.back() << std::endl;



	a += 's';
	a += b;

	std::cout << a << std::endl;

	std::cout << a+b << '\n' << '#' + b << std::endl;

	std::cout << b << std::endl;

	std::cout << a.find(b) << std::endl;
	std::cout << a.rfind(b) << std::endl;

	
	std::cout << a.substr(3, 21) << std::endl;

	String ex;
	std::cin >> ex;

	std::cout << "1";
	return 0;
}
