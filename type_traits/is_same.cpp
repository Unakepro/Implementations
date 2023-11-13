#include <iostream>

template <typename T, typename U>
struct is_same {
	const static bool value = false; 
};

template <typename T>
struct is_same<T, T> {
	const static bool value = true;
};

template <typename T, typename U>
const static bool is_same_v = is_same<T, U>::value;


int main() {
	std::cout << is_same_v<int, int> << std::endl;	
	std::cout << is_same_v<int, double> << std::endl;
}
