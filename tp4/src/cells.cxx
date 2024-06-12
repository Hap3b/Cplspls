#include "cells.hxx"

Cells::Cells(unsigned int nbrParticles, vector<Particle>& particles)
            : nbrParticles_(nbrParticles), particles_(particles) {}

Cells::~Cells()
{
}