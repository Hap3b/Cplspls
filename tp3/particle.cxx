#include "particle.hxx"
#include <chrono>
#include <random>
#include <stdlib.h>
#include <cmath>
#include "vector.hxx"


Particle::Particle(unsigned int id, 
                Vector pos,
                Vector speed,
                Vector force,
                double mass, std::string type)
{
    id_    = id;
    pos_   = pos;
    speed_ = speed;
    force_ = force;
    mass_  = mass;
    type_  = type;
}

Particle::~Particle(){
}

void speedCollections(){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    size_t sizes[6] = {64, 128, 256, 512, 1024, 2048};

    for (size_t j = 0; j < 6; j++)
    {
        size_t count = sizes[j];
        std::cout << "Count " << count << ":\n";

        auto startList = std::chrono::steady_clock::now();
        std::list<Particle> particleList;
        for (size_t i = 0; i < count; i++)
        {
            unsigned int id = 0;
            double x, y, vx, vy, fx, fy, mass;
            std::string type = "test";
            x                = dist(mt);
            y                = dist(mt);
            vx               = dist(mt);
            vy               = dist(mt);
            fx               = dist(mt);
            fy               = dist(mt);
            mass             = dist(mt);
            vector<double> posVec;
            posVec.push_back(x); posVec.push_back(y);
            Vector pos = Vector(posVec, 2);
            vector<double> speedVec;
            speedVec.push_back(vx); speedVec.push_back(vy);
            Vector speed = Vector(speedVec, 2);
            vector<double> forceVec;
            forceVec.push_back(fx); forceVec.push_back(fy);
            Vector force = Vector(posVec, 2);             
            Particle part = Particle(id, pos, speed, force, mass, type);
            particleList.push_back(part);
        }
        auto endList = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds_list = endList-startList;
        std::cout << "  elapsed time for list: " << elapsed_seconds_list.count() << "s\n";
        
        auto startDeque = std::chrono::steady_clock::now();
        std::deque<Particle> particleDeque;
        for (size_t i = 0; i < count; i++)
        {
            unsigned int id = 0;
            double x, y, vx, vy, fx, fy, mass;
            std::string type = "test";
            x                = dist(mt);
            y                = dist(mt);
            vx               = dist(mt);
            vy               = dist(mt);
            fx               = dist(mt);
            fy               = dist(mt);
            mass             = dist(mt);
            vector<double> posVec;
            posVec.push_back(x); posVec.push_back(y);
            Vector pos = Vector(posVec, 2);
            vector<double> speedVec;
            speedVec.push_back(vx); speedVec.push_back(vy);
            Vector speed = Vector(speedVec, 2);
            vector<double> forceVec;
            forceVec.push_back(fx); forceVec.push_back(fy);
            Vector force = Vector(posVec, 2);             
            Particle part = Particle(id, pos, speed, force, mass, type);
            particleDeque.push_back(part);
        }
        auto endDeque = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds_deque = endDeque-startDeque;
        std::cout << "  elapsed time for deque: " << elapsed_seconds_deque.count() << "s\n";

        auto startVector = std::chrono::steady_clock::now();
        std::vector<Particle> particleVector;
        for (size_t i = 0; i < count; i++)
        {
            unsigned int id = 0;
            double x, y, vx, vy, fx, fy, mass;
            std::string type = "test";
            x                = dist(mt);
            y                = dist(mt);
            vx               = dist(mt);
            vy               = dist(mt);
            fx               = dist(mt);
            fy               = dist(mt);
            mass             = dist(mt);
            vector<double> posVec;
            posVec.push_back(x); posVec.push_back(y);
            Vector pos = Vector(posVec, 2);
            vector<double> speedVec;
            speedVec.push_back(vx); speedVec.push_back(vy);
            Vector speed = Vector(speedVec, 2);
            vector<double> forceVec;
            forceVec.push_back(fx); forceVec.push_back(fy);
            Vector force = Vector(posVec, 2);             
            Particle part = Particle(id, pos, speed, force, mass, type);
            particleVector.push_back(part);
        }
        auto endVector = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds_vector = endVector-startVector;
        std::cout << "  elapsed time for vector: " << elapsed_seconds_list.count() << "s\n";
    }
}

void stromerVerlet(std::deque<Particle> &particles,
                    std::deque<Vector> f_old)
{
    double t_end   = 468.5;
    double delta_t = 0.015;
    double t       = 0;
    fGravitationnal(particles);
    while (t < t_end)
    {
        t += delta_t;
        auto f_old_it = f_old.begin();
        for (auto particle = particles.begin(); particle != particles.end(); particle++)
        {
            for (size_t i = 0; i < particle->getDimension(); i++)
            {
                particle->setPos(i, particle->getPos(i)
                                + delta_t * (particle->getSpeed(i)
                                            + delta_t*particle->getForce(i)*0.5/particle->getMass()));
                *f_old_it = particle->getVecForce();
            }
        }
        fGravitationnal(particles);
        f_old_it = f_old.begin();
        for (auto particle = particles.begin(); particle != particles.end(); particle++)
        {
            for (size_t i = 0; i < particle->getDimension(); i++)
            {
                particle->setSpeed(i, particle->getSpeed(i)
                                        + 0.5*(f_old_it->getX(i)
                                                + particle->getForce(i))
                                                *delta_t/particle->getMass());   
            }
        }
        std::cout << "t " << t << ":" << std::endl;
        for (auto it = particles.begin(); it != particles.end(); it++)
        {
            std::cout << "  " << it->getId() << ": " << *it->getVecPos() << std::endl;
        }
    }
}

void fGravitationnal(std::deque<Particle> &particles){
    for (auto it1 = particles.begin(); it1 != particles.end(); it1++)
    {
        double m1 = it1->getMass();
        auto it2  = it1;
        ++it2;
        for (; it2 != particles.end(); it2++)
        {
            double m2  = it2->getMass();
            double dst = it2->getVecPos()->distance(it1->getVecPos());
            for (size_t i = 0; i < it2->getDimension(); i++)
            {
                double fx  = m1*m2/std::pow(dst, 3)*(it1->getPos(i)-it2->getPos(i));
                it1->setForce(i, it1->getForce(i)+fx);
                it2->setForce(i, it2->getForce(i)-fx);
            }            
        }
    }
}

int main(){
    double mass_sun     = 1;
    double mass_earth   = 3e-6;
    double mass_jupyter = 9.55e-4;
    double mass_haley   = 1e-14;
    std::string star    = "star";
    std::string planet  = "planet";
    std::string comet   = "comet";
    std::vector<double> nul;
    nul.push_back(0); nul.push_back(0);
    Vector n0 = Vector(nul, 2);
    std::vector<double> earthPos;
    earthPos.push_back(0); earthPos.push_back(1);
    Vector ePos          = Vector(earthPos, 2);
    std::vector<double> earthSpeed;
    earthSpeed.push_back(-1); earthSpeed.push_back(0);
    Vector earthSpd      = Vector(earthSpeed, 2);
    std::vector<double> jupyterPos;
    jupyterPos.push_back(0); jupyterPos.push_back(5.36);
    Vector jpterPos      = Vector(jupyterPos, 2);
    std::vector<double> jupyterSpeed;
    jupyterSpeed.push_back(-0.425); jupyterSpeed.push_back(0);
    Vector jupyterSpd    = Vector(jupyterSpeed, 2);
    std::vector<double> halleyPos;
    halleyPos.push_back(34.75); halleyPos.push_back(0);
    Vector hPos          = Vector(halleyPos, 2);
    std::vector<double> halleySpeed;
    halleySpeed.push_back(0); halleySpeed.push_back(0.0296);
    Vector halleySpd     = Vector(halleySpeed, 2);
    Particle sun         = Particle(0, n0, n0, n0, mass_sun, star);
    Particle earth       = Particle(1, ePos, earthSpd, n0, mass_earth, planet);
    Particle jupyter     = Particle(2, jpterPos, jupyterSpd, n0, mass_jupyter, planet);
    Particle halley      = Particle(3, hPos, halleySpd, n0, mass_haley, comet);
    std::deque<Particle> *system = new std::deque<Particle>;
    system->push_back(sun); system->push_back(earth); system->push_back(jupyter); system->push_back(halley);
    std::deque<Vector> f_old;
    for (size_t i = 0; i < 4; i++)
    {
        f_old.push_back(n0);
    }
    stromerVerlet(*system, f_old);
    delete(system);
    return 0;
}

