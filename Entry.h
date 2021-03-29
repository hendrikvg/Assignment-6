#ifndef SRC_ENTRY_H_
#define SRC_ENTRY_H_

template<typename T>
class Entry {

public:
    Entry<T>(double constant);
    Entry<T>(T entryFunc);

    double calculate();

private:
    double constant;
    T entryFunction;

    bool isConstant;
};


#endif //SRC_ENTRY_H_