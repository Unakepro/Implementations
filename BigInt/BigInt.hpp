#ifndef BIGINT
#define BIGINT


#include <iostream>
#include <string>


class BigInt {
	std::string digits="0";
	bool sign = 0;

public:
	BigInt(long long x);
    
	BigInt(const BigInt& obj) = default;
	BigInt() = default;

	size_t size() const;
	bool get_sign() const;

	const std::string toString();

	bool is_zero();

	BigInt& operator+=(const BigInt&);
	BigInt& operator-=(const BigInt&);
	BigInt& operator*=(const BigInt&);
	BigInt& operator/=(const BigInt&);


	bool operator>(const BigInt&) const;
	bool operator<(const BigInt&) const;
	bool operator>=(const BigInt&) const;
	bool operator<=(const BigInt&) const;

	bool operator==(const BigInt&) const;
	bool operator!=(const BigInt&) const;

	BigInt& operator++();
	BigInt& operator--();
	BigInt operator++(int);
	BigInt operator--(int);

	BigInt operator-() const;

	char& operator[](int);
	const char& operator[](int) const;


	friend std::ostream& operator<<(std::ostream& out, const BigInt& obj);
	friend std::istream& operator>>(std::istream& in, BigInt& obj);

	explicit operator bool();

};

BigInt operator+(const BigInt& obj, const BigInt& obj1);
BigInt operator-(const BigInt& obj, const BigInt& obj1);
BigInt operator*(const BigInt& obj, const BigInt& obj1);
BigInt operator/(const BigInt& obj, const BigInt& obj1);

BigInt operator%(const BigInt& obj, const BigInt& obj1);

bool abs_compare(const BigInt& obj, const BigInt& obj1);


#endif