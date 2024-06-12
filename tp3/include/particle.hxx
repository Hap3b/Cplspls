#ifndef PARTICLE
#define PARTICLE

#include <iostream>
#include <vector>
#include "vector.hxx"

class Particle
{
private:
    unsigned int id_;
    Vector pos_;
    Vector speed_;
    Vector force_;
    double mass_;
    std::string type_;
public:
    Particle(unsigned int id, 
                const Vector &pos,
                const Vector &speed,
                const Vector &force,
                double mass, const std::string &type);
    ~Particle();
    double getMass() const                { return mass_;};
    unsigned int getId() const            { return id_;};
    double getPos(unsigned int i) const   { return pos_.getX(i);};
    const Vector& getVecPos() const       { return pos_;};
    double getSpeed(unsigned int i) const { return speed_.getX(i);};
    const Vector& getVecSpeed() const     { return speed_;};
    double getForce(unsigned int i) const { return force_.getX(i);};
    const Vector& getVecForce() const     { return force_;};
    unsigned int getDimension() const     { return pos_.getDim();};

    void setPos(const Vector &pos)            { pos_ = pos;};
    void setPos(unsigned int i, double val)   { pos_.setX(i, val);};
    void setSpeed(const Vector &speed)        { speed_ = speed;};
    void setSpeed(unsigned int i, double val) { speed_.setX(i, val);};
    void setForce(const Vector &force)        { force_ = force;};
    void setForce(unsigned int i, double val) { force_.setX(i, val);};
};

#endif
