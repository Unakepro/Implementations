#include <iostream>


template <typename T>
struct remove_pointer {
	using rem_type = T;
};

template <typename T> 
struct remove_pointer<T*> {
	using rem_type = T;
};

template <typename T>
using rem_type_t = typename remove_pointer<T>::rem_type;



int main() {
	rem_type_t<int*> b;

	return 0;
}
