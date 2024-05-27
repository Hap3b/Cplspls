#include "particle.hxx"
#include <set>
#include <list>
#include <deque>
#include <vector>
#include <chrono>
#include <random>
#include <stdlib.h>

Particle::Particle(unsigned int id, double x, double y, double z,
                double vx, double vy, double vz,
                double fx, double fy, double fz,
                double masse, std::string type)
{
    id_    = id;
    x_     = x;
    y_     = y;
    z_     = z;
    vx_    = vx;
    vy_    = vy;
    vz_    = vz;
    fx_    = fx;
    fy_    = fy;
    fz_    = fz;
    masse_ = masse;
    type_  = type;
}

Particle::~Particle()
{
}

int main()
{
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
            double x, y, z, vx, vy, vz, fx, fy, fz, masse;
            std::string type = "test";
            x             = dist(mt);
            y             = dist(mt);
            z             = dist(mt);
            vx            = dist(mt);
            vy            = dist(mt);
            vz            = dist(mt);
            fx            = dist(mt);
            fy            = dist(mt);
            fz            = dist(mt);
            masse         = dist(mt);
            Particle part = Particle(id, x, y, z, vx, vy, vz, fx, fy, fz, masse, type);
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
            double x, y, z, vx, vy, vz, fx, fy, fz, masse;
            std::string type = "test";
            x             = dist(mt);
            y             = dist(mt);
            z             = dist(mt);
            vx            = dist(mt);
            vy            = dist(mt);
            vz            = dist(mt);
            fx            = dist(mt);
            fy            = dist(mt);
            fz            = dist(mt);
            masse         = dist(mt);
            Particle part = Particle(id, x, y, z, vx, vy, vz, fx, fy, fz, masse, type);
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
            double x, y, z, vx, vy, vz, fx, fy, fz, masse;
            std::string type = "test";
            x             = dist(mt);
            y             = dist(mt);
            z             = dist(mt);
            vx            = dist(mt);
            vy            = dist(mt);
            vz            = dist(mt);
            fx            = dist(mt);
            fy            = dist(mt);
            fz            = dist(mt);
            masse         = dist(mt);
            Particle part = Particle(id, x, y, z, vx, vy, vz, fx, fy, fz, masse, type);
            particleVector.push_back(part);
        }
        auto endVector = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds_vector = endVector-startVector;
        std::cout << "  elapsed time for vector: " << elapsed_seconds_list.count() << "s\n";
    }
    return 0;
}

