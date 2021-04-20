#ifndef SRC_COMMONINPUT_H
#define SRC_COMMONINPUT_H

#include "Matrix.h"


class CommonInput
{
protected:
	Matrix u;

public:
	CommonInput() = default;
	~CommonInput();

	virtual Matrix getU(double time) = 0;

};

#endif