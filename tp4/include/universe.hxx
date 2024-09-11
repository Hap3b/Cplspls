#ifndef UNIVERSE
#define UNIVERSE

#include "particle.hxx"
#include <vector>
#include "vector.hxx"

using namespace std;

class Universe
{
private:
    unsigned int dim_;
    double rcut_;
    double* lcar_;

public:
    Universe(unsigned int dim, double rcut, double* lcar);
    ~Universe();

    void stromerVerlet(vector<Vector> &f_old); /*:)*/
    void fGravitationnal();
};

#endif