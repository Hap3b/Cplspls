#ifndef VECTOR
#define VECTOR

#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;

class Vector
{
private:
    vector<double> x_;
    unsigned int dim_;

public:
    Vector(vector<double> &x, unsigned int dim);
    Vector(const Vector &v);
    Vector();
    ~Vector();

    Vector operator*(double lamda) const;
    friend Vector operator*(double lamda, const Vector &v);
    Vector operator+(const Vector &v) const;
    Vector operator-(const Vector &v) const;

    Vector &operator+=(const Vector &v);
    Vector &operator-=(const Vector &v);

    bool operator==(const Vector &v) const;
    bool operator!=(const Vector &v) const;

    Vector &operator=(const Vector &v);

    friend ostream &operator<<(ostream &out, const Vector &v);

    double getX(unsigned int i) const {return x_[i];};
    unsigned int getDim() const {return dim_;};
    void setX(unsigned int i, double val) { x_[i] = val;};

    double distance(const Vector &v) const;
};

#endif