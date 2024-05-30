#include "particle.hxx"
#include <chrono>
#include <random>
#include <stdlib.h>
#include <cmath>

Particle::Particle(unsigned int id, 
                double x, double y,
                double vx, double vy,
                double fx, double fy,
                double mass, std::string type)
{
    id_    = id;
    x_     = x;
    y_     = y;
    vx_    = vx;
    vy_    = vy;
    fx_    = fx;
    fy_    = fy;
    mass_ = mass;
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
            x             = dist(mt);
            y             = dist(mt);
            vx            = dist(mt);
            vy            = dist(mt);
            fx            = dist(mt);
            fy            = dist(mt);
            mass         = dist(mt);
            Particle part = Particle(id, x, y, vx, vy, fx, fy, mass, type);
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
            x             = dist(mt);
            y             = dist(mt);
            vx            = dist(mt);
            vy            = dist(mt);
            fx            = dist(mt);
            fy            = dist(mt);
            mass         = dist(mt);
            Particle part = Particle(id, x, y, vx, vy, fx, fy, mass, type);
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
            x             = dist(mt);
            y             = dist(mt);
            vx            = dist(mt);
            vy            = dist(mt);
            fx            = dist(mt);
            fy            = dist(mt);
            mass         = dist(mt);
            Particle part = Particle(id, x, y, vx, vy, fx, fy, mass, type);
            particleVector.push_back(part);
        }
        auto endVector = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds_vector = endVector-startVector;
        std::cout << "  elapsed time for vector: " << elapsed_seconds_list.count() << "s\n";
    }
}

void stromerVerlet(std::deque<Particle> &particles,
                    std::deque<double> f_old_x,
                    std::deque<double> f_old_y)
{
    double t_end   = 468.5;
    double delta_t = 0.015;
    double t       = 0;
    fGravitationnal(particles);
    while (t < t_end)
    {
        t += delta_t;
        auto f_old_x_it = f_old_x.begin();
        auto f_old_y_it = f_old_y.begin();
        for (auto particle = particles.begin(); particle != particles.end(); particle++)
        {
            particle->setX(particle->getX()
                            + delta_t * (particle->getVx()
                                        + delta_t*particle->getFx()*0.5/particle->getMass()));
            particle->setY(particle->getY()
                            + delta_t * (particle->getVy()
                                        + delta_t*particle->getFy()*0.5/particle->getMass()));
            *f_old_x_it = particle->getFx();
            *f_old_y_it = particle->getFy();
        }
        fGravitationnal(particles);
        f_old_x_it = f_old_x.begin();
        f_old_y_it = f_old_y.begin();
        for (auto particle = particles.begin(); particle != particles.end(); particle++)
        {
            particle->setVx(particle->getVx()
                            + 0.5*(*f_old_x_it + particle->getFx())*delta_t/particle->getMass());
            particle->setVy(particle->getVy()
                            + 0.5*(*f_old_y_it + particle->getFy())*delta_t/particle->getMass());
        }
        std::cout << "t " << t << ":" << std::endl;
        for (auto it = particles.begin(); it != particles.end(); it++)
        {
            std::cout << "  " << it->getId() << " x: " << it->getX() << " y: " << it->getY() << std::endl;
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
            double dst = std::sqrt((it1->getX()-it2->getX())*(it1->getX()-it2->getX())
                                    +(it1->getY()-it2->getY())*(it1->getY()-it2->getY()));
            double fx  = m1*m2/std::pow(dst, 3)*(it1->getX()-it2->getX());
            double fy  = m1*m2/std::pow(dst, 3)*(it1->getY()-it2->getY());
            it1->setFx(it1->getFx()+fx);
            it2->setFx(it2->getFx()-fx);
            it1->setFy(it1->getFy()+fy);
            it2->setFy(it2->getFy()-fy);
        }
    }
}

int main(){
    double mass_sun     = 1;
    double mass_earth   = 3e-6;
    double mass_jupyter = 9.55e-4;
    double mass_haley   = 1e-14;
    Particle sun        = Particle(0, 0, 0, 0, 0, 0, 0, mass_sun, "star");
    Particle earth      = Particle(1, 0, 1, -1, 0, 0, 0, mass_earth, "planet");
    Particle jupyter    = Particle(2, 0, 5.36, -0.425, 0, 0, 0, mass_jupyter, "planet");
    Particle halley     = Particle(3, 34.75, 0, 0, 0.0296, 0, 0, mass_haley, "comet");
    std::deque<Particle> system;
    system.push_back(sun); system.push_back(earth); system.push_back(jupyter); system.push_back(halley);
    std::deque<double> f_old_x;
    std::deque<double> f_old_y;
    for (size_t i = 0; i < 4; i++)
    {
        f_old_x.push_back(0);
        f_old_y.push_back(0);
    }
    stromerVerlet(system, f_old_x, f_old_y);
    return 0;
}

