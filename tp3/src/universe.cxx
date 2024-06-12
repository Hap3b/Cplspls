#include "universe.hxx"
#include <math.h>
#include <random>
#include <vector>
#include <list>

Universe::Universe(unsigned int dim, unsigned int nbrParticles, vector<Particle>& particles)
                        : dim_(dim), nbrParticles_(nbrParticles), particles_(particles) {}

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
        // std::cout << "t " << t << ":" << std::endl;
        // for (auto it = this->particles_.begin(); it != this->particles_.end(); it++)
        // {
        //     std::cout << "  " << it->getId() << ": " << *it->getVecPos() << std::endl;
        // }
    }
}

Universe::~Universe(){}

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
                double fx  = m1*m2/std::pow(dst, 3)*(it2->getPos(i)-it1->getPos(i));
                it1->setForce(i, it1->getForce(i)+fx);
                it2->setForce(i, it2->getForce(i)-fx);
            }            
        }
    }
}

int main()
{
    std::vector<double> nul(2, 0.0);
    Vector n0 = Vector(nul, 2);
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    std::vector<Particle> particles;
    std::vector<Vector> f_old;

    long unsigned int bs2 = std::pow(2, 4);
    long unsigned int nbr = std::pow(bs2, 3);
    particles.reserve(nbr);
    f_old.reserve(nbr);
    
    for (size_t i = 0; i < nbr; i++)
    {
        double x      = dist(mt);
        double y      = dist(mt);
        double vx     = dist(mt);
        double vy     = dist(mt);
        double fx     = dist(mt);
        double fy     = dist(mt);
        std::vector<double> pvc = {x, y};
        std::vector<double> vvc = {vx, vy};
        std::vector<double> fvc = {fx, fy};
        Vector pos(pvc, 2);
        Vector spd(vvc, 2);
        Vector fce(fvc, 2);
        Particle ptcl(i, pos, spd, fce, 1, "test");
        particles.push_back(ptcl);
        f_old.push_back(n0);
    }

    Universe univ_test = Universe(2, nbr, particles);
    univ_test.stromerVerlet(f_old);
    
    return 0;
}

