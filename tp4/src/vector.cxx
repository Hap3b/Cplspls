#include "vector.hxx"    

using namespace std;

Vector::Vector(vector<double> &x, unsigned int dim)
    : x_(x), dim_(dim) {
    assert(x.size()==dim);
}

Vector::Vector(const Vector &v) {
    this->x_ = v.x_;
    this->dim_ = v.dim_;
}

Vector::Vector() : dim_(0) {}

Vector::~Vector(){}

Vector Vector::operator*(double lamda) const{
    Vector result = *this;
    for (size_t i = 0; i < dim_; i++)
    {
        result.setX(i, result.getX(i)*lamda);
    }
    return result;
}

Vector Vector::operator+(const Vector &v) const{
    assert(v.dim_ == dim_);
    Vector result = *this;
    for (size_t i = 0; i < dim_; i++)
    {
        result.setX(i, result.getX(i)+v.getX(i));
    }
    return result;
}

Vector& Vector::operator=(const Vector &v){
    if (this != &v){   
        x_   = v.x_;
        dim_ = v.dim_;
    }
    return *this;
}

Vector Vector::operator-(const Vector &v) const{
    assert(v.dim_ == dim_);
    Vector result = *this;
    for (size_t i = 0; i < dim_; i++){
        result.setX(i, result.getX(i)-v.getX(i));
    }
    return result;
}

Vector& Vector::operator+=(const Vector &v){
    assert(v.getDim() == dim_);
    for (size_t i = 0; i < dim_; i++)
    {
        x_[i] += v.getX(i);
    }
    return *this;
}

Vector& Vector::operator-=(const Vector &v){
    assert(v.getDim() == dim_);
    for (size_t i = 0; i < dim_; i++)
    {
        x_[i] += v.getX(i);
    }
    return *this;
}

bool Vector::operator==(const Vector &v) const {
    if (dim_ != v.dim_)
    {
        return false;
    }
    for (size_t i = 0; i < dim_; i++)
    {
        if (v.x_[i] != x_[i])
        {
            return false;
        }
    }
    return true;
}

bool Vector::operator!=(const Vector &v) const {
    return !(*this==v);
}

ostream& operator<<(ostream &out, const Vector &v){
    out << "(";
    for (size_t i = 0; i < v.getDim()-1; i++)
    {
        out << v.getX(i) << " ; ";
    }
    out << v.getX(v.getDim()-1) << ")" << endl;
    return out;
}

Vector operator*(double lamda, const Vector &v){
    Vector result(v);
    for (size_t i = 0; i < result.getDim(); i++)
    {
        result.setX(i, result.getX(i)*lamda);
    }
    return result;
}

double Vector::distance(const Vector &v) const{
    double dst = 0;
    for (size_t i = 0; i < dim_; i++)
    {
        dst += pow(x_[i]-v.getX(i), 2);
    }
    dst = sqrt(dst);
    return dst;
}

// int main()
// {
//     vector<double> x;
//     x.push_back(1); x.push_back(2);
//     Vector test  = Vector(x, 2);
//     Vector test2 = 10*test;
//     Vector test3 = test + test2;
//     Vector test4 = test - test;
//     cout << test;
//     cout << test2;
//     cout << test3;
//     cout << test4;
//     if (test4==test)
//     {
//         cout << "true" << endl;
//     }
//     else {
//         cout << "false" << endl;
//     }
//     if (test4!=test)
//     {
//         cout << "true" << endl;
//     }
//     else {
//         cout << "false" << endl;
//     }
//     test += test2;
//     cout << test;
//     test3 -= test2;
//     cout << test3;
//     return 0;
// }

