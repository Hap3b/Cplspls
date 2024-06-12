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
    unsigned int nbrParticles_;
    vector<Particle>& particles_;

public:
    Universe(unsigned int dim, unsigned int nbrParticles, vector<Particle> &particles);
    ~Universe();

    void stromerVerlet(vector<Vector> &f_old); /*:)*/
    void fGravitationnal();
};

#endif