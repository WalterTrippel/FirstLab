#ifndef NATIVE_INTERFACE_H
#define NATIVE_INTERFACE_H

#include "stack.h"

extern "C"
{

    void init();

    void push(char * data, char * handler);

    char * onTop(char * handler);

    bool isEmpty(char * handler);

    void pop(char * handler);

    char * cloneBuffer(char * handler);

}

#endif // NATIVE_INTERFACE_H
