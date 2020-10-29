#ifndef VERLET_H
#define VERLET_H


class Verlet
{
public:
    double m_dt;
    double m_dt2;
    Verlet(double dt);
    void integrateOneStep(class SolarSystem &system);
};

#endif // VERLET_H
