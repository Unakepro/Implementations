#include <iostream>
#include <vector>
#include <type_traits>

template<unsigned M, unsigned N, typename Field>
class Matrix;

template<unsigned M, unsigned N, typename Field>
std::ostream& operator<<(std::ostream& out, const Matrix<M, N, Field>& obj);

template<unsigned M, typename Field>
std::ostream& operator<<(std::ostream& out, const Matrix<M, M, Field>& obj);


template <unsigned M, unsigned N, typename Field=double>
class Matrix {
public:
//std::array
//Field values[M * N];
    std::vector<Field> values;

public:
    Matrix(std::vector<Field> obj) {
        if(obj.size() != M*N) {
            throw std::runtime_error("Wrong Size");
        }
        values = obj;

    }

    std::vector<Field> getRow(int row) {
        if(row > N) {
            throw std::runtime_error("Invalid row number");
        }
        return std::vector<Field> (values.begin()+((row-1)*M), values.begin()+(((row-1)*M)+M)); 
    }

    void getColumn(int column) {
        if(column > M) {
            throw std::runtime_error("Invalid column number");
        }
        return std::vector<Field> (values.begin())
    }


    bool operator==(const Matrix& obj);

    template <unsigned K, unsigned P, typename OField>
    bool operator!=(const Matrix<K, P, OField>& obj);

    // Matrix<M, N, Field>& operator[](int row) {
    //     return values[];
    // }

    // const Matrix<M, N, Field>& operator[](int i, int j) const { 
    //     return values[i*j-1];
    // }

    friend std::ostream& operator<< <>(std::ostream& out, const Matrix& obj);
};

template <unsigned M, typename Field>
class Matrix<M, M, Field> {
public:
    std::vector<Field> values; 

public:

    Matrix(std::vector<Field> obj) {
        if(obj.size() != M*M) {
            throw std::runtime_error("Wrong Size");
        }
    }


    Matrix(): values(M*M) {
        std::fill(values.begin(), values.end(), 1); 
    }
    
    bool operator==(const Matrix& obj);

    template <unsigned K, unsigned P, typename OField>
    bool operator!=(const Matrix<K, P, OField>& obj);


    friend std::ostream& operator<< <>(std::ostream& out, const Matrix& obj);
};


template<unsigned M, unsigned N, typename Field>
std::ostream& operator<<(std::ostream& out, const Matrix<M, N, Field>& obj) {

    for(int i = 0; i < M; ++i) {
        for(int j = 0; j < N; ++j) {
            out << obj.values[j] << '\t';
        }
        out << '\n';
    }

    return out;
}

template<unsigned M, typename Field>
std::ostream& operator<<(std::ostream& out, const Matrix<M, M, Field>& obj) {

    for(int i = 0; i < M; ++i) {
        for(int j = 0; j < M; ++j) {
            out << obj.values[j] << '\t';
        }
        out << '\n';
    }

    return out;
}

template<unsigned M, unsigned N, typename Field>
bool Matrix<M, N, Field>::operator==(const Matrix<M, N, Field>& obj) {
    return values==obj.values;
}

template<unsigned M, typename Field>
bool Matrix<M, M, Field>::operator==(const Matrix<M, M, Field>& obj) {
    return values==obj.values;
}

template<unsigned M, typename Field>
template <unsigned K, unsigned P, typename OField>
bool Matrix<M, M, Field>::operator!=(const Matrix<K, P, OField>& obj) {     
    return M != K || M != P || std::is_same_v<Field, OField> == false || values != obj.values;
}

template<unsigned M, unsigned N, typename Field>
template <unsigned K, unsigned P, typename OField>
bool Matrix<M, N, Field>::operator!=(const Matrix<K, P, OField>& obj) {     
    return M != K || N != P || std::is_same_v<Field, OField> == false || values != obj.values;
}

int main() {
    std::vector<double> xs{1, 2, 3, 4, 5};

    Matrix<5, 1> a(xs);

    //std::cout << a << std::endl;
    for(auto x: a.getRow(2)) {
        std::cout << x << ' ';
    }

    Matrix<5, 5> b;

    //std::cout << (a != b) << std::endl;
    return 0;
}