#include "Native_Interface.h"

char * init()
{
    wltr::Stack * _stack = new wltr::Stack();
    
    char * buffer = static_cast<char *>(static_cast<void *>(_stack));
    
    return buffer;
}

void push(Data data, size_t data_size, char *handler)
{
    wltr::Stack * _stack = static_cast<wltr::Stack *>(static_cast<void *>(handler));

    _stack->push(data, data_size);

}

Data onTop(char *handler)
{
    wltr::Stack * _stack = static_cast<wltr::Stack *>(static_cast<void *>(handler));

    return _stack->onTop();
}

size_t topSize(char *handler)
{
    wltr::Stack * _stack = static_cast<wltr::Stack *>(static_cast<void *>(handler));

    return _stack->topSize();
}

bool isEmpty(char *handler)
{
    wltr::Stack * _stack = static_cast<wltr::Stack *>(static_cast<void *>(handler));

    return _stack->isEmpty();
}

void pop(char * handler)
{
    wltr::Stack * _stack = static_cast<wltr::Stack *>(static_cast<void *>(handler));

    _stack->pop();

}

char * cloneBuffer(char *handler)
{
    wltr::Stack * _stack = static_cast<wltr::Stack *>(static_cast<void *>(handler));

    wltr::Stack * _copy = new wltr::Stack(*_stack);

    char * buffer = static_cast<char *>(static_cast<void *>(_copy));

    return buffer;
}
