#include "vector.hxx"    
#include <cassert>
using namespace std;

Vector::Vector(vector<double> x, unsigned int dim){
    assert(x.size()==dim);
    this->x_   = x;
    this->dim_ = dim;
}

Vector::~Vector(){}

Vector& Vector::operator*(double lamda){
    for (size_t i = 0; i < this->dim_; i++)
    {
        this->x_[i] *= lamda;
    }
    return *this;
}

Vector& Vector::operator+(const Vector &v){
    assert(v.dim_ == this->dim_);
    for (size_t i = 0; i < this->dim_; i++)
    {
        this->x_[i] += v.x_[i];
    }
    return *this;
}

Vector& Vector::operator=(const Vector &v){
    this->x_   = v.x_;
    this->dim_ = v.dim_;
    return *this;
}

Vector& Vector::operator-(const Vector &v){
    assert(v.dim_ == this->dim_);
    for (size_t i = 0; i < this->dim_; i++){
        this->x_[i] -= v.x_[i];
    }
    return *this;
}

Vector& Vector::operator+=(const Vector &v){
    return *this + v;
}

Vector& Vector::operator-=(const Vector &v){
    return *this - v;
}

bool Vector::operator==(const Vector &v) const {
    if (this->dim_ != v.dim_)
    {
        return false;
    }
    for (size_t i = 0; i < this->dim_; i++)
    {
        if (v.x_[i] != this->x_[i])
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

int main()
{
    vector<double> x;
    x.push_back(1); x.push_back(2);
    Vector test  = Vector(x, 2);
    Vector test2 = 10*test;
    Vector test3 = test + test2;
    Vector test4 = test - test;
    cout << test;
    cout << test2;
    cout << test3;
    cout << test4;
    if (test4==test)
    {
        cout << "true" << endl;
    }
    else {
        cout << "false" << endl;
    }
    if (test4!=test)
    {
        cout << "true" << endl;
    }
    else {
        cout << "false" << endl;
    }
    test += test2;
    cout << test;
    test3 -= test2;
    cout << test3;
    return 0;
}

