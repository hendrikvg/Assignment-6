#ifndef SRC_INPUT_H
#define SRC_INPUT_H

#include "Matrix.h"

class Input
{
private:
	Matrix u;

public:
	Input(Matrix);
	Matrix getU();
};

#endif // !SRC_INPUT_H