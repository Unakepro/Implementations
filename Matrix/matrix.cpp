#include <iostream>
#include <vector>
#include <type_traits>



template<unsigned M, unsigned N, typename Field=double>
class IMatrix {
public:
    // transponent
    // rank
    // trace
    // inverted
    // invert

    virtual std::vector<Field> getRow(int row) const = 0;
    virtual std::vector<Field> getColumn(int column) const = 0;


    virtual ~IMatrix() {}
};


template<unsigned M, unsigned N, typename Field=double>
class BaseMatrix: public IMatrix<M, N, Field> {
    std::vector<Field> values;

public:    

    BaseMatrix(std::vector<Field> obj) {
        if(obj.size() != M*N) {
            throw std::logic_error("Wrong Size");
        }
        values = obj;

    }

    std::vector<Field> getRow(int row) const override {
        if(row > M) {
            throw std::logic_error("Invalid row number");
        } 

        std::vector<Field> copy;

        for(int i = (row-1)*N; i < (row-1)*N+N; ++i) {
            copy.push_back(values[i]);
        }   

        return copy;     
    }

    std::vector<Field> getColumn(int column) const override {
        if(column > N) {
            throw std::logic_error("Invalid column number");
        }

        std::vector<Field> copy;

        for(int i = column-1; i < values.size(); i += N) {
            copy.push_back(values[i]);
        }        

        return copy;
    }

    BaseMatrix<M, N, Field>& operator-=(const BaseMatrix<M, N, Field>& obj);
    BaseMatrix<M, N, Field>& operator+=(const BaseMatrix<M, N, Field>& obj);

    BaseMatrix<M, N, Field> operator-(const BaseMatrix<M, N, Field>& obj);
    BaseMatrix<M, N, Field> operator+(const BaseMatrix<M, N, Field>& obj);

};


template <unsigned M, unsigned N, typename Field=double>
class Matrix: public BaseMatrix<M, N, Field> {
public:

    Matrix(std::vector<Field> values): BaseMatrix<M, N, Field>(values) {}



    // Matrix<M, N, Field>& operator+=(const Matrix<M, N, Field>& obj);
    // Matrix<M, N, Field>& operator-=(const Matrix<M, N, Field>& obj);



    // bool operator==(const Matrix& obj);

    // template <unsigned K, unsigned P, typename OField>
    // bool operator!=(const Matrix<K, P, OField>& obj);

    // Matrix<M, N, Field>& operator[](int row) {
    //     return values[];
    // }

    // const Matrix<M, N, Field>& operator[](int i, int j) const { 
    //     return values[i*j-1];
    // }

};

template <unsigned M, typename Field>
class Matrix<M, M, Field>: public BaseMatrix<M, M, Field> {
public:

    Matrix(std::vector<Field> values): BaseMatrix<M, M, Field>(values) {}


    Matrix(): BaseMatrix<M, M, Field>(std::vector<Field>(M*M, 1)) {}



    
};

//     bool operator==(const Matrix& obj);

//     template <unsigned K, unsigned P, typename OField>
//     bool operator!=(const Matrix<K, P, OField>& obj);


//     friend std::ostream& operator<< <>(std::ostream& out, const Matrix& obj);
// };


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


// template<unsigned M, unsigned N, typename Field>
// bool Matrix<M, N, Field>::operator==(const Matrix<M, N, Field>& obj) {
//     return values==obj.values;
// }

// template<unsigned M, typename Field>
// bool Matrix<M, M, Field>::operator==(const Matrix<M, M, Field>& obj) {
//     return values==obj.values;
// }

// template<unsigned M, typename Field>
// template <unsigned K, unsigned P, typename OField>
// bool Matrix<M, M, Field>::operator!=(const Matrix<K, P, OField>& obj) {     
//     return M != K || M != P || std::is_same_v<Field, OField> == false || values != obj.values;
// }

// template<unsigned M, unsigned N, typename Field>
// template <unsigned K, unsigned P, typename OField>
// bool Matrix<M, N, Field>::operator!=(const Matrix<K, P, OField>& obj) {     
//     return M != K || N != P || std::is_same_v<Field, OField> == false || values != obj.values;
// }





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



int main() {
    std::vector<double> xs{1, 2, 3, 4, 5};

    Matrix<1, 5> a(xs);

    std::cout << a << std::endl;
    for(auto x: a.getRow(1)) {
         std::cout << x << ' ';
    }

    std::cout << '\n';

    for(auto x: a.getColumn(1)) {
        std::cout << x << '\n';
    }
    std::cout << '\n';
    
    Matrix<2, 2> b;
    
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


    // //std::cout << (a != b) << std::endl;
    return 0;
}