#ifndef NATIVE_INTERFACE_H
#define NATIVE_INTERFACE_H

#include "stack.h"

extern "C"
{

    char * init();

    void push(Data data, size_t data_size, char * handler);

    Data onTop(char * handler);

    size_t topSize(char * handler);

    bool isEmpty(char * handler);

    void pop(char * handler);

    char * cloneBuffer(char * handler);

}

#endif // NATIVE_INTERFACE_H
