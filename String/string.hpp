#ifndef STRING_C
#define STRING_C

#include <iostream>

class String {

    size_t capacity = 10;
    size_t size = 0;
    char* str = nullptr;


public:


    String(const char* c_str);
    String(size_t n, char c);

    String(char c);
    String(const String& x);
    
    String();

    String& operator=(String);

    char& operator[](size_t);
    const char& operator[](size_t) const;

    String& operator+=(const String&);
    bool operator==(const String&) const;

    size_t length() const;


    void push_back(char c);
    void pop_back();

    char& front();
    char& back();


    size_t find(const String& x);
	size_t rfind(const String& x);

	String substr(size_t start, size_t count);

	bool empty();
    void clear();

    ~String();

private:
    void swap(String& x, String& y);

};


String operator+(const String& x, const String& y);
std::ostream& operator<<(std::ostream& out, const String& x);
std::istream& operator>>(std::istream& in, String& x);


#endif