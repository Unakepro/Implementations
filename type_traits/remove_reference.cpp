#include <iostream>

template <typename T>
struct remove_reference {
	using type = T;
};

template <typename T>
struct remove_reference<T&> {
	using type = T;
};

template <typename T>
using no_ref_t = typename remove_reference<T>::type;



int main() {
	no_ref_t<int&> b;
}
