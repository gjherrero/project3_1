#include "solarsystem.h"
#include <iostream>
using namespace std;
double G = 4*M_PI*M_PI;
double v_light2 = 3.9873e9; //speed of light in AU/yr
SolarSystem::SolarSystem() :
    m_kineticEnergy(0),
    m_potentialEnergy(0)
{
}

CelestialBody& SolarSystem::createCelestialBody(vec3 position, vec3 velocity, double mass) {
    m_bodies.push_back( CelestialBody(position, velocity, mass) );
    return m_bodies.back(); // Return reference to the newest added celstial body
}

void SolarSystem::calculateForcesAndEnergy()
{
    m_kineticEnergy = 0;
    m_potentialEnergy = 0;
    m_angularMomentum.zeros();
    for(CelestialBody &body : m_bodies) {
        // Reset forces on all bodies
        body.force.zeros();
    }

    for(int i=0; i<numberOfBodies(); i++) {
        CelestialBody &body1 = m_bodies[i];
        for(int j=i+1; j<numberOfBodies(); j++) {
            CelestialBody &body2 = m_bodies[j];
            vec3 deltaRVector = body1.position - body2.position;
            double dr = deltaRVector.length();
            double dr2 = pow(dr,3); //change power law for exercise
            m_angularMomentum += body2.mass*body2.velocity.cross(deltaRVector);
            vec3 l = deltaRVector.cross(body2.velocity);
            double l2 = l.lengthSquared();
            double correction = (3*l2)/(dr*dr*v_light2);
            // double correction = 0;
            // Calculate the force and potential energy here
            double force = -G*body1.mass*body2.mass/dr2*(1+correction);
            body1.force+=deltaRVector*(force); 
            body2.force+=deltaRVector*(-force); 
            m_potentialEnergy += -G*body1.mass*body2.mass/dr;
        }

        m_kineticEnergy += 0.5*body1.mass*body1.velocity.lengthSquared();
    }
}

int SolarSystem::numberOfBodies() const
{
    return m_bodies.size();
}

double SolarSystem::totalEnergy() const
{
    return m_kineticEnergy + m_potentialEnergy;
}

double SolarSystem::potentialEnergy() const
{
    return m_potentialEnergy;
}

double SolarSystem::kineticEnergy() const
{
    return m_kineticEnergy;
}

void SolarSystem::writeToFile(string filename)
{
    if(!m_file.good()) {
        m_file.open(filename.c_str(), ofstream::out);
        if(!m_file.good()) {
            cout << "Error opening file " << filename << ". Aborting!" << endl;
            terminate();
        }
    }

    m_file << numberOfBodies() << endl;
    //m_file << "Comment line that needs to be here. Balle." << endl;
    for(CelestialBody &body : m_bodies) {
        m_file << body.position.x() << " " << body.position.y() << " " << body.position.z()<< "\n";
    }
    // m_file << kineticEnergy()<< " " << potentialEnergy() << " " << totalEnergy() << "\n";
    // m_file << angularMomentum()<< "\n";
}

vec3 SolarSystem::angularMomentum() const
{
    return m_angularMomentum;
}

std::vector<CelestialBody> &SolarSystem::bodies()
{
    return m_bodies;
}
