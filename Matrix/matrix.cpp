#include <iostream>
#include <vector>
#include <type_traits>
#include <utility>
#include <cmath>


template<unsigned M, unsigned N, typename Field=double>
class IMatrix {
public:

    virtual std::vector<Field> getRow(int row) const = 0;
    virtual std::vector<Field> getColumn(int column) const = 0;

    virtual typename std::vector<Field>::iterator getRowIter(int row) = 0;
    virtual typename std::vector<Field>::const_iterator getConstRowIter(int row) const = 0;
    virtual void swapRows(int f_row, int s_row) = 0;
    
    virtual Field& getRefValue(int row, int column) = 0;
    virtual const Field& getRefValue(int row, int column) const = 0;

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

    std::vector<Field> getRow(int row) const override {
        if(row > M || row <= 0) {
            throw std::logic_error("Invalid row number");
        } 

        std::vector<Field> copy;

        for(int i = (row-1)*N; i < (row-1)*N+N; ++i) {
            copy.push_back(values[i]);
        }   

        return copy;     
    }

    typename std::vector<Field>::iterator getRowIter(int row) override {
        if(row > M || row <= 0) {
            throw std::logic_error("Invalid row number");
        } 

        return values.begin()+(row-1)*N;     
    }

    typename std::vector<Field>::const_iterator getConstRowIter(int row) const override {
        if(row > M || row <= 0) {
            throw std::logic_error("Invalid row number");
        } 

        return values.begin()+(row-1)*N;     
    }

    Field& getRefValue(int i, int j) override {
        if(j >= N || j < 0) {
            throw std::logic_error("Invalid column number");
        }

        return *(getRowIter(i+1) += j);

    }

    const Field& getRefValue(int i, int j) const override {
        if(j >= N || j < 0) {
            throw std::logic_error("Invalid column number");
        }

        return *(getConstRowIter(i+1) += j);

    }

    std::vector<Field> getColumn(int column) const override {
        if(column > N || column <= 0) {
            throw std::logic_error("Invalid column number");
        }

        std::vector<Field> copy;

        for(int i = column-1; i < values.size(); i += N) {
            copy.push_back(values[i]);
        }        
        return copy;
    }

    std::vector<Field> getValues() const override {
        return values;
    }

    void swapRows(int f_row, int s_row) override {
        if(f_row > M || f_row <= 0) {
            throw std::logic_error("first row is not exist");
        }    
        if(s_row > M || s_row <= 0) {
            throw std::logic_error("second row is not exist");
        }

        for(int i = 0; i < M; ++i) {
            std::swap(values[(f_row-1)*N+i], values[(s_row-1)*N+i]);
        }

    }

    BaseMatrix<N, M, Field> transposed() {
        std::vector<Field> copy;
        for(int i = 0; i < N; ++i) {
            for(auto elem: getColumn(i+1)) {
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
                copy.swapRows(i+1, maxRow+1);
                determinant = determinant * -1;
            }

            for(int k = i+1; k < M; ++k) {
                double c = -copy.getRow(k+1)[i] / copy.getRow(i+1)[i];
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
    
    for(int i = 1; i <= M; ++i) {
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




int main() {
    std::vector<double> xs{1, 2, 2, 3, 1, 1};

    Matrix<2, 3> a(xs);

    std::cout << a << std::endl;
    for(auto x: a.getRow(1)) {
         std::cout << x << ' ';
    }

    std::cout << '\n';

    for(auto x: a.getColumn(1)) {
        std::cout << x << '\n';
    }
    std::cout << '\n';
    
    Matrix<3, 2> b({4, 2, 3, 1, 1, 5});
    
    std::cout << b << std::endl;

    for(auto x: b.getRow(1)) {
         std::cout << x << ' ';
    }

    std::cout << '\n';

    for(auto x: b.getColumn(1)) {   
        std::cout << x << '\n';
    }
       
    std::cout << (a+a) << std::endl;
    std::cout << (a-a) << std::endl;

    std::cout << (a == a) << std::endl;
    std::cout << (a != b) << std::endl;

    std::cout << (a * 5) << std::endl;

    std::cout << a << std::endl;
    std::cout << a.getRefValue(0, 0) << std::endl;

    std::cout << (a*b) << std::endl;

    std::vector<double> sq_m{1, 1, 1, 0, 0, 2, 3, 0, 2, 1, 5, 1, 4, 0, 7, -1};
    Matrix<4, 4> c(sq_m); 

    std::cout << c.trace() << std::endl;


    std::vector<int> tr_v{1, 2, 3, 4, 5, 6};
    Matrix<2, 3, int> d(tr_v);
    
    std::cout << d.transposed() << std::endl;

    a.getRefValue(0, 0) = 0;

    std::cout << a << std::endl;

    Matrix<3, 3, int> e({-1, 2, -5, 3, 4, 1, 0, 1, 2}); 

    e *= e;

    std::cout << e << std::endl;

    std::cout << e.det() << std::endl;

}