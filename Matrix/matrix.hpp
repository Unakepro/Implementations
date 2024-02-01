#ifndef MATRIX
#define MATRIX
#include <iostream>
#include <vector>
#include <type_traits>
#include <utility>
#include <cmath>


template<unsigned M, unsigned N, typename Field=double>
class IMatrix {
public:

    virtual std::vector<Field> getRow(int) const = 0;
    virtual std::vector<Field> getColumn(int) const = 0;

    virtual typename std::vector<Field>::iterator getRowIter(int) = 0;
    virtual typename std::vector<Field>::const_iterator getConstRowIter(int) const = 0;
    virtual void swapRows(int, int) = 0;
    
    virtual Field& getRefValue(int, int) = 0;
    virtual const Field& getRefValue(int, int) const = 0;

    virtual std::vector<Field> getValues() const = 0;

    virtual ~IMatrix() {}
};


template<unsigned M, unsigned N, typename Field=double>
class BaseMatrix: public IMatrix<M, N, Field> {
protected:
    std::vector<Field> values;

public:    

    BaseMatrix(std::vector<Field> obj) {
        if(obj.size() != M*N) {
            throw std::logic_error("Wrong Size");
        }
        values = obj;

    }

    std::vector<Field> getRow(int row_index) const override {
        if(row_index >= M || row_index < 0) {
            throw std::logic_error("Invalid row number");
        } 

        std::vector<Field> copy;

        for(int i = row_index*N; i < row_index*N+N; ++i) {
            copy.push_back(values[i]);
        }   

        return copy;     
    }

    typename std::vector<Field>::iterator getRowIter(int row_index) override {
        if(row_index >= M || row_index < 0) {
            throw std::logic_error("Invalid row number");
        } 

        return values.begin()+row_index*N;     
    }

    typename std::vector<Field>::const_iterator getConstRowIter(int row_index) const override {
        if(row_index >= M || row_index < 0) {
            throw std::logic_error("Invalid row number");
        } 

        return values.begin()+row_index*N;     
    }

    Field& getRefValue(int i, int j) override {
        if(j >= N || j < 0) {
            throw std::logic_error("Invalid column number");
        }

        return *(getRowIter(i) += j);

    }

    const Field& getRefValue(int i, int j) const override {
        if(j >= N || j < 0) {
            throw std::logic_error("Invalid column number");
        }

        return *(getConstRowIter(i) += j);

    }

    std::vector<Field> getColumn(int column_index) const override {
        if(column_index >= N || column_index < 0) {
            throw std::logic_error("Invalid column number");
        }

        std::vector<Field> copy;

        for(int i = column_index; i < values.size(); i += N) {
            copy.push_back(values[i]);
        }        
        return copy;
    }

    std::vector<Field> getValues() const override {
        return values;
    }

    void swapRows(int f_row_i, int s_row_i) override {
        if(f_row_i >= M || f_row_i < 0) {
            throw std::logic_error("first row is not exist");
        }    
        if(s_row_i >= M || s_row_i < 0) {
            throw std::logic_error("second row is not exist");
        }

        for(int i = 0; i < M; ++i) {
            std::swap(values[f_row_i*N+i], values[s_row_i*N+i]);
        }

    }

    BaseMatrix<N, M, Field> transposed() {
        std::vector<Field> copy;
        for(int i = 0; i < N; ++i) {
            for(auto elem: getColumn(i)) {
                copy.push_back(elem);
            }
            std::cout << '\n';
        }

        return BaseMatrix<N, M, Field>(copy);
    }


    BaseMatrix<M, N, Field>& operator-=(const BaseMatrix<M, N, Field>& obj);
    BaseMatrix<M, N, Field>& operator+=(const BaseMatrix<M, N, Field>& obj);

    BaseMatrix<M, N, Field> operator-(const BaseMatrix<M, N, Field>& obj);
    BaseMatrix<M, N, Field> operator+(const BaseMatrix<M, N, Field>& obj);
    
    BaseMatrix<M, N, Field>& operator*=(int num);
    BaseMatrix<M, N, Field> operator*(int num);


    template <unsigned K>
    BaseMatrix<M, K, Field> operator*(const BaseMatrix<N, K, Field>& obj) const;

    template <unsigned K, unsigned P, typename OField>
    bool operator==(const BaseMatrix<K, P, OField>& obj);


    template <unsigned K, unsigned P, typename OField>
    bool operator!=(const BaseMatrix<K, P, OField>& obj);

    std::vector<Field> operator[](int j) const;
};

template <unsigned M, unsigned N, typename Field=double>
class Matrix: public BaseMatrix<M, N, Field> {
public:

    Matrix(std::vector<Field> values): BaseMatrix<M, N, Field>(values) {}
    
};

template <unsigned M, typename Field>
class Matrix<M, M, Field>: public BaseMatrix<M, M, Field> {
public:

    Matrix(std::vector<Field> values): BaseMatrix<M, M, Field>(values) {}


    Matrix(): BaseMatrix<M, M, Field>(std::vector<Field>(M*M, 1)) {}

    Field trace() {
        Field sum = Field(0);
        for(int i = 0; i < M*M; i += M+1) {
            sum += (*this).values[i];
    
        }
        return sum;
    }
    
    double det() {
      
        double determinant = 1.0;

        std::vector<double> copy_values;

        for(Field elem: (*this).values) {
            copy_values.push_back(static_cast<double>(elem));
        }

        Matrix<M, M, double> copy(copy_values);
  
        for(int i = 0; i < M; ++i) {

            Field maxElem = abs(copy.getRefValue(i, i));
            int maxRow = i;

            for(int k = i+1; k < M; ++k) {
                if(abs(copy.getRefValue(k, i)) > maxElem) {

                    maxElem = abs(copy.getRefValue(k, i));
                    maxRow = k;
                }
            }

            if(maxRow != i) {
                copy.swapRows(i, maxRow);
                determinant = determinant * -1;
            }

            for(int k = i+1; k < M; ++k) {
                double c = -copy.getRow(k)[i] / copy.getRow(i)[i];
                for(int j = i; j < M; ++j) {
                    if(i == j) {
                        copy.getRefValue(k, j) = 0;
                    }
                    else {
                        copy.getRefValue(k, j) += c * copy.getRefValue(i, j);
                    }
                }
            }

            determinant = determinant * copy.getRefValue(i, i);

        }
        return determinant;
    }
    
    
    Matrix<M, M, Field>& operator*=(const Matrix<M, M, Field> obj);


    

};


template<unsigned M, unsigned N, typename Field>
std::ostream& operator<<(std::ostream& out, const BaseMatrix<M, N, Field>& obj) {
    
    for(int i = 0; i < M; ++i) {
        for(auto elem: obj.getRow(i)) {
            out << elem << ' ';
        }
        out << '\n';
    }
    out << std::endl;

    return out;
}


template<unsigned M, unsigned N, typename Field>
template <unsigned K, unsigned P, typename OField>
bool BaseMatrix<M, N, Field>::operator==(const BaseMatrix<K, P, OField>& obj) {
    return M == K && N == P && std::is_same_v<Field, OField> == true && (*this).getValues() == obj.getValues();
}


template<unsigned M, unsigned N, typename Field>
template <unsigned K, unsigned P, typename OField>
bool BaseMatrix<M, N, Field>::operator!=(const BaseMatrix<K, P, OField>& obj) {     
    return !(*this == obj);
}


template<unsigned M, unsigned N, typename Field>
BaseMatrix<M, N, Field>& BaseMatrix<M, N, Field>::operator+=(const BaseMatrix<M, N, Field>& obj) {

    for(int i = 0; i < values.size(); ++i) {
        values[i] += obj.values[i];
    }


    return *this;
}


template<unsigned M, unsigned N, typename Field>
BaseMatrix<M, N, Field>& BaseMatrix<M, N, Field>::operator-=(const BaseMatrix<M, N, Field>& obj) {

    for(int i = 0; i < values.size(); ++i) {
        values[i] -= obj.values[i];
    }


    return *this;
}


template<unsigned M, unsigned N, typename Field>
BaseMatrix<M, N, Field> BaseMatrix<M, N, Field>::operator+(const BaseMatrix<M, N, Field>& obj) {
    BaseMatrix<M, N, Field> copy = *this;
    copy += obj;

    return copy;
}


template<unsigned M, unsigned N, typename Field>
BaseMatrix<M, N, Field> BaseMatrix<M, N, Field>::operator-(const BaseMatrix<M, N, Field>& obj) {
    BaseMatrix<M, N, Field> copy = *this;
    copy -= obj;

    return copy;
}


template <unsigned M, unsigned N, typename Field>
BaseMatrix<M, N, Field>& BaseMatrix<M, N, Field>::operator*=(int num) {
    for(int i = 0; i < values.size(); ++i) {
        values[i] = values[i] * num;
    }
    return *this;
}

template <unsigned M, unsigned N, typename Field>
BaseMatrix<M, N, Field> BaseMatrix<M, N, Field>::operator*(int num) {
    BaseMatrix<M, N, Field> copy = *this;
    copy *= num;
    return copy;
}

template <unsigned M, unsigned N, typename Field>
template <unsigned K>
BaseMatrix<M, K, Field> BaseMatrix<M, N, Field>::operator*(const BaseMatrix<N, K, Field>& obj) const {

    std::vector<Field> copy_values; 
    for(int i = 0; i < M; ++i) {
        for(int k = 0; k < K; ++k) {
            Field sum = Field(0);
            for(int j = 0; j < N; ++j) {
                sum += (*this).getRefValue(i,j)*obj.getRefValue(j, k);

            }  
            copy_values.push_back(sum);
        } 
    }
    return BaseMatrix<M, K, Field>(copy_values);
}

template <unsigned M, typename Field>
Matrix<M, M, Field>& Matrix<M, M, Field>::operator*=(const Matrix<M, M, Field> obj) {
    for(int i = 0; i < M; ++i) {
        std::vector<Field> copy_values(M); 
        for(int k = 0; k < M; ++k) {
            Field sum = Field(0);
            for(int j = 0; j < M; ++j) {
                sum += (*this).getRefValue(i, j)* obj.getRefValue(j, k);
            }
            copy_values[k] = sum;

        }
        for(int p = 0; p < M; ++p) {
            (*this).getRefValue(i, p) = copy_values[p];
        }

    }        
    return *this;
}


#endif