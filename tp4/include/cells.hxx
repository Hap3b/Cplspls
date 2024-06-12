#ifndef CELLS
#define CELLS

#include "particle.hxx"
#include <vector>
#include "vector.hxx"

using namespace std;

class Cells
{
private:
    unsigned int nbrParticles_;
    vector<Particle>& particles_;
    vector<Cells>& neighbor_;

public:
    Cells(unsigned int nbrParticles, vector<Particle>& particles, vector<Cells>& neighbor);
    ~Cells();

};




#endif