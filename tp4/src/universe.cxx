#include "universe.hxx"
#include <math.h>
#include <random>
#include <vector>
#include <list>

Universe::Universe(unsigned int dim, double rcut, double* lcar)
                        : dim_(dim), rcut_(rcut) {
                            lcar_ = (double *) malloc(dim*sizeof(double));
                            lcar_ = lcar; 
                        }

void Universe::stromerVerlet(std::vector<Vector> &f_old){
    double t_end   = 468.5;
    double delta_t = 0.015;
    double t       = 0;
    fGravitationnal();
    while (t < t_end)
    {
        t += delta_t;
        auto f_old_it = f_old.begin();
        for (auto &particle : particles_)
        {
            for (size_t i = 0; i < particle.getDimension(); i++)
            {
                particle.setPos(i, particle.getPos(i)
                                + delta_t * (particle.getSpeed(i)
                                            + delta_t*particle.getForce(i)*0.5/particle.getMass()));
                *f_old_it = particle.getVecForce();
            }
        }
        fGravitationnal();
        f_old_it = f_old.begin();
        for (auto &particle : particles_)
        {
            for (size_t i = 0; i < particle.getDimension(); i++)
            {
                particle.setSpeed(i, particle.getSpeed(i)
                                        + 0.5*(f_old_it->getX(i)
                                                + particle.getForce(i))
                                                *delta_t/particle.getMass());   
            }
        }
    }
}

Universe::~Universe(){free(lcar_);}

void Universe::fGravitationnal(){
    for (auto it1 = this->particles_.begin(); it1 != this->particles_.end(); it1++)
    {
        double m1 = it1->getMass();
        for (auto it2 = it1+1; it2 != particles_.end(); it2++)
        {
            double m2  = it2->getMass();
            double dst = it1->getVecPos().distance(it2->getVecPos());
            for (size_t i = 0; i < it2->getDimension(); i++)
            {
                double fx = m1*m2/std::pow(dst, 3)*(it2->getPos(i)-it1->getPos(i));
                it1->setForce(i, it1->getForce(i)+fx);
                it2->setForce(i, it2->getForce(i)-fx);
            }            
        }
    }
}

double potentialLennardJones(Particle p1, Particle p2, double epsilon, double sigma, double rcut) {
    double r = p1.getVecPos().distance(p2.getVecPos());
    if (r <= rcut)
    {
        return 4*epsilon*(std::pow(sigma/r, 12)-std::pow(sigma/r, 6));
    }
    
    return 0;
}
