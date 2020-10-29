#include "verlet.h"
#include "solarsystem.h"

Verlet::Verlet(double dt) :
    m_dt(dt)
{

}

void Verlet::integrateOneStep(SolarSystem &system)
{
    system.calculateForcesAndEnergy();
    m_dt2=m_dt*m_dt;

    for(CelestialBody &body : system.bodies()) {
        body.position += body.velocity*m_dt+m_dt2/2*body.force/body.mass;
        body.velocity += (m_dt/2)*body.force/body.mass;
    }    
    system.calculateForcesAndEnergy();

    for(CelestialBody &body : system.bodies()) {
        body.velocity += (m_dt/2)*body.force/body.mass;
    }
}
