compileRunVerlet:
	c++ -O3 -o EarthVerlet.x VerletSimple.cpp
	./EarthVerlet.x
compileRunEuler:
	c++ -O3 -o EarthEuler.x EulerSimple.cpp
	./EarthEuler.x