#include<iostream>

class Particle
{
private:
    unsigned int id_;
    double x_, y_, z_;
    double vx_, vy_, vz_;
    double fx_, fy_, fz_;
    double masse_;
    std::string type_;
public:
    Particle(unsigned int id, double x, double y, double z,
                double vx, double vy, double vz,
                double fx, double fy, double fz,
                double masse, std::string type);
    ~Particle();
};
