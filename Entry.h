#ifndef SRC_ENTRY_H_
#define SRC_ENTRY_H_

template<typename F>
class Entry
{
private:
	auto value;

public:
	Entry(double);
	Entry(F & lambda);
	~Entry() {};

	double calculate();

	
};

#endif /*SRC_ENTRY_H_*/