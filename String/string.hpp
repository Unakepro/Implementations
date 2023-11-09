#ifndef STRING_C
#define STRING_C

#include <iostream>
#include <cstring>


class String {

    size_t capacity=10;
    size_t size=0;
    char* str=nullptr;


public:


    String(const char* c_str):  capacity(strlen(c_str)*2), size(strlen(c_str)), str(new char[capacity]) {
        memcpy(str, c_str, size);
    }

    String(size_t n, char c): capacity(n*2), size(n), str(new char[capacity]) {
        memset(str, c, size);
    }

    String(char c): capacity(10), size(1), str(new char[capacity]) {
        str[0] = c;
    }

    String(const String& x): capacity(x.size*2), size(x.size), str(new char[capacity]) {
        memcpy(str, x.str, size);
    }

    String(): capacity(10), size(0), str(new char[capacity]) {}


    String& operator=(String);

    char& operator[](size_t);
    const char& operator[](size_t) const;

    String& operator+=(const String&);
    bool operator==(const String&) const;



    size_t length() const {
        return size;
    }



    void push_back(char c) {
        if(size == capacity) {

            capacity *= 2;
            char* tmp = new char[capacity];

            memcpy(tmp, str, size);

            delete [] str;

            str = tmp;
        }
        str[size] =  c;
        size +=1;
    }

    void pop_back() {
        if(empty()) {
            throw std::logic_error("Pop on empty str");
        }
        --size;
    }

    char& front() {
        if(empty()) {
            throw std::logic_error("Front on empty str");
        }
        return str[0];
    }

    char& back() {
        if(empty()) {
            throw std::logic_error("Back on empty str");
        }
        return str[size-1];
    }

    size_t find(const String& x) {
        for(size_t i=0; i < (size - x.length + 1); ++i)  {
			String copy;
            for(size_t j=0; j < x.length(); ++j) {
                copy.push_back(str[i+j]);
            }
            if(x == copy) {
                return i;
            }
        }
        return size;
    }

	size_t rfind(const String& x) {

        for(size_t i = (size-1); i >= (x.length()-1); --i)  {

            String copy;

	        for(int j = (x.length()-1); j>=0; --j) {

				copy.push_back(str[i-j]);
			}
           if(x == copy) {
                return i;
            }
        }
        return size;
    }


	String substr(size_t start, size_t count) {
		if(start+count > size) {
			throw std::logic_error("Too many symbols in substr");
		}

		String copy;

		for(size_t i = start; i < (start+count); ++i) {
			copy.push_back(str[i]);
		}
		return copy;
	}


	bool empty() {
        return size==0;
    }

    void clear() {
        size = 0;
    }


~String() {
        delete [] str;
    }

private:
    void swap(String& x, String& y) {
        std::swap(x.capacity, y.capacity);
        std::swap(x.size, y.size);
        std::swap(x.str, y.str);
    }


};

String& String::operator=(String x) {
        swap(*this, x);
        return *this;
}

char& String::operator[](size_t i) {
        return str[i];
    }

const char& String::operator[](size_t i) const{
        return str[i];
}


String& String::operator+=(const String& x) {
	for(size_t i=0;i<x.length(); ++i) {
            push_back(x[i]);
    }
	return *this;
}


bool String::operator==(const String& x) const {

	if (nullptr == x.str) {
		return false;
    }

    if(size != x.size) {
    	return false;
    }

	for(size_t i=0;i<size;++i) {
		if(str[i] != x.str[i]) {
        	return false;
        }
    }
    return true;
}



String operator+(const String& x, const String& y) {
    String copy = x;
    for(size_t i=0; i < y.length(); ++i) {
        copy.push_back(y[i]);
    }
    return copy;
}


std::ostream& operator<<(std::ostream& out, const String& x) {

    for(size_t i = 0; i < x.length(); ++i) {
        out << x[i];
    }
    return out;
}

std::istream& operator>>(std::istream& in, String& x) {

	for(size_t i = 0; i < x.length(); ++i) {
		in >> x[i];
	}
	return in;

}


#endif
