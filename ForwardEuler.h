#ifndef SRC_FORWARDEULER_H
#define SRC_FORWARDEULER_H

#include "Simulator.h"
#include "Input.h"		// Input class

class ForwardEuler :
	public Simulator
{
private:
	Matrix xdot;
	Matrix x;
	Matrix u;
	Matrix y;

public:
	ForwardEuler() = default;
	ForwardEuler(StateSpace *system, double t0, double td, double tEnd);
	void integrate(Matrix& x, Input u);
	void integrate(Matrix& x, Input u, Matrix x0);
	//void integrate(Matrix& x, Input u, double t);


	

};

#endif /*SRC_FORWARDEULER_H*/