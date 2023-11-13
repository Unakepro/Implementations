#include <iostream>
#include <type_traits>

template <typename First, typename Second, typename... Other>
struct is_homogeneous {
	static const bool value = std::is_same_v<First, Second> && is_homogeneous<Second, Other...>::value;
};

template <typename First, typename Second>
struct is_homogeneous<First, Second> {
	static const bool value = std::is_same_v<First, Second>;
};

int main() {
	std::cout << is_homogeneous<int, int, double>::value << std::endl;
	std::cout << is_homogeneous<char, char>::value << std::endl;
}
