#include<iostream>
#include <list>
#include <deque>
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
                Vector pos,
                Vector speed,
                Vector force,
                double mass, std::string type);
    ~Particle();
    double getMass()  { return this->mass_;};
    double getId()    { return this->id_;};
    double getPos(unsigned int i)   { return this->pos_.getX(i);};
    Vector* getVecPos()             { return &(this->pos_);};
    double getSpeed(unsigned int i) { return this->speed_.getX(i);};
    Vector getVecSpeed()            { return this->speed_;};
    double getForce(unsigned int i) { return this->force_.getX(i);};
    Vector getVecForce()            { return this->force_;};
    unsigned int getDimension() { return this->pos_.getDim();};
    void setPos(Vector pos)     {this->pos_ = pos;};
    void setPos(unsigned int i, double val) {this->pos_.setX(i, val);};
    void setSpeed(Vector speed) {this->speed_ = speed;};
    void setSpeed(unsigned int i, double val) {this->speed_.setX(i, val);};
    void setForce(Vector force) {this->force_ = force;};
    void setForce(unsigned int i, double val) {this->force_.setX(i, val);};
};

void fGravitationnal(std::deque<Particle> &particles);
