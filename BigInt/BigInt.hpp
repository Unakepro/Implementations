#ifndef BIGINT
#define BIGINT


#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

class BigInt {
	std::string digits="0";
	bool sign = 0;

public:
	 BigInt(long long x): sign(std::signbit(x)) {
		x = llabs(x);
		digits = std::to_string(x);
	}

    BigInt(const BigInt& obj) = default;

	BigInt() = default;

	size_t size() const {
		return digits.size();
	}

	bool get_sign() const {
		return sign;
	}

	const std::string toString() {
		return (sign ? '-': '+') + digits;
	}

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

	explicit operator bool() {
		return *this != 0;
	}

};

bool is_zero(std::string& obj) {
    for(int i=obj.size()-1; i >= 0; --i) {
        if(obj[i]-'0' != 0) {
            return false;
        }
    }
    return true;
}

bool abs_compare(const BigInt& obj, const BigInt& obj1) {

	if(obj.size() > obj1.size()) {
    	return true;
    }

	if(obj.size() == obj1.size()) {
		for(size_t i=0; i < obj.size(); ++i) {
            if((obj[i]-'0') > (obj1[i]-'0')) {
                return true;
            }
        }
        return false;
    }
	return false;
}

bool BigInt::operator>(const BigInt& obj) const {

    if(this->sign == 0 && obj.sign == 1) {
		return true;
	}

	if(this->sign == obj.sign) {
		if(this->sign == 0) {
			return abs_compare(*this, obj);
		}
		else {
			return abs_compare(obj, *this);
		}
	}
	return false;
}

bool BigInt::operator<(const BigInt& obj) const {
	return obj > (*this);
}

bool BigInt::operator==(const BigInt& obj) const {
	return !((*this) > obj || (*this) < obj);
}

bool BigInt::operator!=(const BigInt& obj) const {
	return !((*this)==obj);
}

bool BigInt::operator>=(const BigInt& obj) const {
	return ((*this) > obj || (*this) == obj);
}


bool BigInt::operator<=(const BigInt& obj) const {
    return ((*this) < obj || (*this) == obj);
}


BigInt BigInt::operator-() const {
	BigInt copy(*this);
	copy.sign = !copy.sign;
    return copy;
}



BigInt& BigInt::operator+=(const BigInt& obj) {

	BigInt copy(obj);


    if(abs_compare(copy, (*this))) {
		std::swap(digits, copy.digits);
        std::swap(sign, copy.sign);
    }

    size_t size_str = digits.size();
    size_t cpy_size = copy.digits.size();


	int carry=0;
	if(sign == copy.sign) {
		for(size_t i = 0; i < cpy_size; ++i) {

			carry += digits[size_str-1-i]-'0' + copy.digits[cpy_size-i-1]-'0';
            digits[size_str-1-i] = static_cast<char>(('0' + (carry % 10)));

			carry /= 10;
		}

		for(size_t j = cpy_size; j < size_str; ++j) {
			carry += digits[size_str-1-j]-'0';

			digits[size_str-1-j] = static_cast<char>(('0' + (carry % 10)));

			carry /= 10;
		}

		if(carry) {
			digits = static_cast<char>(carry+'0') + digits;

		}
	}
    else {
        for(int i=0; i < cpy_size; ++i) {

            if(digits[size_str-i-1]-'0' < copy.digits[cpy_size-i-1]-'0') {

                int b_index = i+1;

				while(digits[size_str-b_index-1]-'0' <= 0) {
					++b_index;
				}
                digits[size_str-b_index-1] = static_cast<char>(((digits[size_str-b_index-1]-'0')-1)+'0');


                for(int j = size_str-b_index; j < size_str-i-1; ++j) {
					digits[j] = '9';
				}

				digits[size_str-i-1] = static_cast<char>(('0' + (10-(copy.digits[cpy_size-i-1]-'0')+(digits[size_str-i-1]-'0'))));
				copy.digits[cpy_size-i-1] = 0;

			} else {
                digits[size_str-i-1] = static_cast<char>('0' + (digits[size_str-i-1]-'0') - (copy.digits[cpy_size-i-1]-'0'));
            }
        }


        if(is_zero(digits)) {
            sign = false;
        }

        while (digits.size() > 1 && digits[0] == '0') {
            digits.erase(0, 1);
        }

    }


    return *this;

}


BigInt& BigInt::operator*=(const BigInt& obj) {

	BigInt copy = obj;
	BigInt counter = (*this);

	if(copy == 0) {
		*this = 0;
		return *this;
	}

	if(copy > 0) {
		while(copy != 1) {
			(*this) += counter;
			--copy;
		}
	}
	else {
		while(copy != -1) {
            (*this) += counter;
            ++copy;
        }

	}


	(*this).sign = sign ^ obj.sign;

	return *this;
}

BigInt& BigInt::operator/=(const BigInt& obj) {

	if(obj == 0) {
		throw std::runtime_error("division by 0");
	}


	BigInt result(0);
	bool res_sign = (sign ^ obj.sign);

	BigInt abs_obj = obj;
	abs_obj.sign = 0;
	sign = 0;

	while(*this >= abs_obj) {
		++result;
		*this -= abs_obj;
	}

	*this = result;

	if(this == 0) {
		sign = 0;
	}
	else {
		sign = res_sign;
	}

	return *this;
}

BigInt& BigInt::operator-=(const BigInt& obj) {
    BigInt copy = obj;
	(*this) += (-obj);
	return (*this);
}

BigInt operator+(const BigInt& obj, const BigInt& obj1) {
	BigInt copy = obj;
	copy += obj1;
	return copy;
}

BigInt operator-(const BigInt& obj, const BigInt& obj1) {
    BigInt copy = obj;
	copy -= obj1;
    return copy;
}

BigInt operator*(const BigInt& obj, const BigInt& obj1) {
	BigInt copy = obj;
	copy *= obj1;
	return copy;
}

BigInt operator/(const BigInt& obj, const BigInt& obj1) {
	BigInt copy = obj;
	copy /= obj1;
	return copy;
}

BigInt operator%(const BigInt& obj, const BigInt& obj1) {
	BigInt copy = obj;
	copy -= (obj1*copy/obj);
	return copy;
}


BigInt BigInt::operator++(int) {
	BigInt copy = *this;
	*this += 1;
	return copy;
}

BigInt BigInt::operator--(int) {
    BigInt copy = *this;
    *this -= 1;
    return copy;
}


BigInt& BigInt::operator++() {
    *this += 1;
    return *this;
}

BigInt& BigInt::operator--() {
    *this -= 1;
    return *this;
}

char& BigInt::operator[](int x) {
	return digits[x];
}

const char& BigInt::operator[](int x) const {
	return digits[x];
}

std::ostream& operator<<(std::ostream& out, const BigInt& obj) {

	if(obj.sign == 1) {
		out << '-';
	}
	out << obj.digits;

	return out;
}

std::istream& operator>>(std::istream& in, BigInt& obj) {

	std::string str;

	in >> str;

	if(str[0] == '-') {
		obj.sign = true;
		obj.digits = str.substr(1);
	}
	else {
		obj.sign = false;
		obj.digits = str;
	}

	return in;
}

#endif
