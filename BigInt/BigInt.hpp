#include <iostream>
#include <string>
#include <cmath>



class BigInt {
	std::string digits="0";
	bool sign=0;

public:
	BigInt(long long x): sign(std::signbit(x)) {
		x = llabs(x);
		digits = std::to_string(x);
	}	

	BigInt() = default;

	size_t size() const {
		return digits.size();
	} 

	bool get_sign() const {
		return sign;
	}

	//const std::string toString() {
	//	return sign + digits;
	//}

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

	BigInt operator-();


	char& operator[](int);
	const char& operator[](int) const;
	

	friend std::ostream& operator<<(std::ostream& out, const BigInt& obj);
	friend std::istream& operator>>(std::istream& in, BigInt& obj);
	
	explicit operator bool() {
		return *this != 0;
	}	

};
 
/*
void swap_values(int& x, int& y) {
		int tmp = x;
		x = y;
		y = tmp;
}
*/

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
	
	else if(this->sign == obj.sign) {
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


BigInt BigInt::operator-() {
	sign = sign ^ 1;
	return *this;
}

/*

BigInt& BigInt::operator+=(const BigInt& obj) {

	int len = digits.size();
	int len_obj = obj.size(); 


	int carry=0;
	if(sign == obj.sign) {
		if(len > len_obj) {
	
	
        	for(int i=0;i<len_obj;++i) {
				carry = digits[i] + obj.digits[i]+carry;
				digits[i] = carry%10;
				carry /= 10;				
   			}

			for(int i=len_obj;i<len;++i) {
				carry = digits[i] + carry;
				digits[i] = carry%10;
				carry /= 10;
			}

			if(carry != 0) {
				digits.push_back(carry);
			}
		}
		
		else {
        		for(int i=0;i<len;++i) {
					carry = digits[i] + obj.digits[i] + carry;
					digits[i] = carry%10;
					carry /= 10;
				}
			 
				for(int i=len;i<len_obj;++i) {
					carry = obj.digits[i] + carry;
					digits.push_back(carry%10);
					carry /= 10;
        		}	
				if(carry != 0) {
					digits.push_back(carry);
				} 
			}
	}
	
	else {
	
		if(*this == obj) {
			*this = 0;
			return *this;
		}

		std::vector<int> tmp;
		tmp = obj.digits;


		if(abs_compare(obj, (*this))) {
			digits.swap(tmp);			
		
			swap_values(len, len_obj);
			sign = obj.sign;	
		}	
	
				for(int i=0;i<len_obj;++i) {
	
					int x = i+1;
					while(digits[i]<tmp[i]) {
						
						if(digits[x] > 0) {	


							digits[x] = digits[x]-1;
							digits[i] += 10;

							for(int j=i+1;j<x;++j) {
								digits[j] = 9;
							}
						}
						++x;
				}
	
					digits[i] = digits[i] - tmp[i];
			}

		 
			for(int i=len-1;i>0;--i) {

						if(digits[i] == 0) {
							digits.pop_back();
						}
						
						else {
							 break;
						}
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
		throw "division by 0";
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
	-(*this) += (obj);
	return (-*this);
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



*/

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
/*
std::istream& operator>>(std::istream& in, BigInt& obj) {
	std::string str;
	
	in >> str;
	
	if(str[0] == '-') {
		obj.sign = 1;
	}
	

	for(int i=str.size()-1;i>=obj.sign;--i) {
		obj.digits.push_back(str[i] - '0');
	}

	return in;
}*/
