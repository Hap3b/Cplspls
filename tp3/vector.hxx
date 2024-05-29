#include <vector>
#include <iostream> 
using namespace std;

class Vector
{
private:
    vector<double> x_;
    unsigned int dim_;
public:
    Vector(vector<double> x, unsigned int dim);
    ~Vector();
    Vector &operator*(double lamda);
    friend Vector operator*(double lamda, const Vector &v);
    Vector &operator+(const Vector &v);
    Vector &operator-(const Vector &v);
    Vector &operator+=(const Vector &v);
    Vector &operator-=(const Vector &v);
    bool operator==(const Vector &v) const;
    bool operator!=(const Vector &v) const;
    Vector &operator=(const Vector &v);
    friend ostream &operator<<(ostream &out, const Vector &v);
    double getX(unsigned int i) const {return this->x_[i];};
    unsigned int getDim() const {return this->dim_;};
    void setX(unsigned int i, double val) {this->x_[i] = val;};
};
