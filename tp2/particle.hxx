#include<iostream>
#include <list>
#include <deque>
#include <vector>

class Particle
{
private:
    unsigned int id_;
    double x_, y_;
    double vx_, vy_;
    double fx_, fy_;
    double mass_;
    std::string type_;
public:
    Particle(unsigned int id, 
                double x, double y,
                double vx, double vy,
                double fx, double fy,
                double mass, std::string type);
    ~Particle();
    double getMass() { return this->mass_;};
    double getId() { return this->id_;};
    double getX()  { return this->x_;};
    double getY()  { return this->y_;};
    double getVx() { return this->vx_;};
    double getVy() { return this->vy_;};
    double getFx() { return this->fx_;};
    double getFy() { return this->fy_;};
    void setX(double x)   {this->x_ = x;};
    void setY(double y)   {this->y_ = y;};
    void setVx(double vx) {this->vx_ = vx;};
    void setVy(double vy) {this->vy_ = vy;};
    void setFx(double fx) {this->fx_ = fx;};
    void setFy(double fy) {this->fy_ = fy;};
};

void fGravitationnal(std::deque<Particle> &particles);
