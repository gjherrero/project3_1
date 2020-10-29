#include <iostream>
#include <cmath>
#include <cstdlib>
#include "solarsystem.h"
#include "euler.h"
#include "verlet.h"
using namespace std;

int main(int numArguments, char **arguments)
{
    // double factor = 1;
    double timeProp = 100.0;
    // double factor = 1.2;
    // double timeProp = 1.0*2.41;
    // double factor = sqrt(2);
    // double timeProp = 1.0*4;
    // double factor = 1.6;
    // double timeProp = 1.0*4;
    int numTimesteps = 1000000;
    if(numArguments >= 2) numTimesteps = atoi(arguments[1]);
    SolarSystem solarSystem;
    // SolarSystem solarSystem2;
    // We create new bodies like this. Note that the createCelestialBody function returns a reference to the newly created body
    // This can then be used to modify properties or print properties of the body if desired
    // Use with: solarSystem.createCelestialBody( position, velocity, mass );

    // CelestialBody &sun = solarSystem.createCelestialBody(vec3(0.002841029214124732, -0.0008551488389783957, -0.0001372196345812671), vec3(3.974748627511212e-06, 5.236981821791106e-06, -9.741909867990456e-08)*365,  1.0); //Sun
    CelestialBody &sun = solarSystem.createCelestialBody(vec3(0,0,0), vec3(0,0,0),  1.0); //Sun
    // solarSystem.createCelestialBody( vec3(1, 0, 0), vec3(0, 2*M_PI, 0), 3.00e-6 );
    // solarSystem.createCelestialBody( vec3(0, 5.2, 0), vec3(0.439*2*M_PI, 0, 0), 10*1.9e27/2e30 );
    // solarSystem.createCelestialBody( vec3(1, 0, 0), vec3(0, 5, 0), 3.00e-6 );
    solarSystem.createCelestialBody( vec3(0.3075, 0, 0), vec3(0, 12.44, 0), 3.3e23/2e30 );

    // We don't need to store the reference, but just call the function without a left hand side
    // solarSystem.createCelestialBody(vec3(0.3401540875319301, -0.2044550792740463, -0.04772012105321857), vec3(0.009021681472868819, 0.02538170267716258, 0.001246034824741292)*365, (3.3e23/2e30)); //Mercury
    // solarSystem.createCelestialBody(vec3(0.5524983482189795, -0.4769264575796522, -0.03838223296316453), vec3(0.01311677229809423, 0.01521762020859779, -0.000548330058229667)*365, (4.9e24/2e30 ));
    // solarSystem.createCelestialBody(vec3(-0.1683241372257412, 0.9674441923084423, -0.0001669835242727353), vec3(-0.01721229158666166, -0.00305887886539691, 5.766702178392226e-07)*365, 3.0033e-06 );
    // solarSystem.createCelestialBody(vec3(1.358690797965978, -0.2758171771328441, -0.03917699408597988), vec3(0.003322799764204667, 0.01491641367405062, 0.0002308785778904992)*365, 3.30e-07 );
    // solarSystem.createCelestialBody(vec3(-3.726727419770284, 3.793259735061699, 0.06756056287566012), vec3(-0.00547262847071761, -0.004932423632218299, 0.000142981839482569)*365, 1.9e27/2e30);
    // solarSystem.createCelestialBody(vec3(-5.405313185983198, -8.350093624713596, 0.3603093855435262), vec3(0.004378243637136238, -0.003047908074535893, -0.0001209045910706235)*365, 5.5e26/2e30);
    // solarSystem.createCelestialBody(vec3(19.30657051495468, 5.250507992762163, -0.2306220390711898), vec3(-0.001060869194207784, 0.003611915584725741, 2.705221245633697e-05)*365, 8.8e25/2e30);
    // solarSystem.createCelestialBody(vec3(27.52968902897168, -11.84376159652895, -0.3905508179361004), vec3(0.001219338004209249, 0.002902323522768006, -8.750344055480828e-05)*365, 1.03e26/2e30);
    // solarSystem.createCelestialBody(vec3(7.400602906905451, -31.91988616953689, 1.274938896927729), vec3(0.003123860112070511, 7.897391745951373e-05, -0.0009005699193051981)*365, 1.31e22/2e30);

    
    // To get a list (a reference, not copy) of all the bodies in the solar system, we use the .bodies() function
    vector<CelestialBody> &bodies = solarSystem.bodies();

    for(int i = 0; i<bodies.size(); i++) {
        CelestialBody &body = bodies[i]; // Reference to this body
        // solarSystem2.createCelestialBody(body.position, body.velocity, body.mass);
        // cout << "The position of this object is " << body.position << " with velocity " << body.velocity << endl;
        solarSystem.writeToFile("positions.xyz");
    }
    // clock_t t0, t1,t2;
    // t0=clock();
    double dt = timeProp/(numTimesteps);
    Verlet integrator(dt);
    for(int timestep=0; timestep<numTimesteps; timestep++) {
        integrator.integrateOneStep(solarSystem);

        solarSystem.writeToFile("positions.xyz");
    }    
    // t1=clock();
    // Euler integrator2(dt);
    // for(int timestep=0; timestep<numTimesteps; timestep++) {
    //     integrator2.integrateOneStep(solarSystem2);
    //     // solarSystem2.writeToFile("positions2.xyz");
    // }  
    // t2=clock();
    // cout<<" Steps = "<<numTimesteps<<"; timeVerlet =  "<<((double)t1-(double)t0)/CLOCKS_PER_SEC<<"; timeEuler =  "<<((double)t2-(double)t1)/CLOCKS_PER_SEC<<";"<<endl;

    return 0;
}

