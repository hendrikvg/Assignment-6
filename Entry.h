#ifndef SRC_ENTRY_H
#define SRC_ENTRY_H

#include <functional>

class Entry {

public:
    Entry(std::function<double()> entryFunc);
    Entry(double constant);
    double calculate();
    double operator-(Entry B);
    double operator-(double B);
    double operator+(Entry B);
    double operator+(double B);

private:
    double constant;
    std::function<double()> entryFunction;

    bool isConstant;
};


#endif //SRC_ENTRY_H