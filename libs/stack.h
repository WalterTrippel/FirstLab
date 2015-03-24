#ifndef STACK_H
#define STACK_H

#include <iostream>

typedef char* Data;

namespace wltr
{

    class StackException : std::exception
    {
        const char * what() throw()
        {
            return "No such element exist!";
        }
    };

    class Stack
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
        void pop();
        bool isEmpty() const;
        Data onTop() const;

    private:
        class StackImplemenation;
        StackImplemenation * pimpl;
    };

};

#endif // STACK_H
