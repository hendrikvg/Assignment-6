#ifndef SRC_SIMULATOR_H_
#define SRC_SIMULATOR_H_

#include "StateSpace.h"
class Simulator :
    public StateSpace
{
protected:
public:
    Simulator();
    //Simulator(StateSpace system);
};

#endif // !SRC_SIMULATOR_H_