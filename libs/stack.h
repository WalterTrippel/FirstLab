#ifndef STACK_H
#define STACK_H

#include "firstlab_global.h"
#include <iostream>

typedef void * Data;

namespace wltr
{

    class StackException : public std::exception
    {
        const char * what() const throw()
        {
            return "No such element exist!";
        }
    };

    class FIRSTLABSHARED_EXPORT Stack
    {
    public:
        Stack();
        Stack(std::initializer_list<Data> list);
        Stack(const Stack & other);
        Stack(Stack && other);

        Stack & operator = (const Stack & other);
        Stack & operator = (Stack && other);

        ~Stack();

        /** main functional */
        void clear();
        void push(Data data);
        void push(Data data, size_t data_size);
        void pop();
        bool isEmpty() const;
        Data onTop() const;
        size_t topSize() const;

    private:
        class StackImplemenation;
        StackImplemenation * pimpl;
    };

}

#endif // STACK_H
