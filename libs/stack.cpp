#include "stack.h"

namespace wltr
{

    class Stack::StackImplemenation
    {
    public:
        StackImplemenation();
        StackImplemenation(std::initializer_list<Data> list);
        StackImplemenation(const StackImplemenation & other);
        StackImplemenation(StackImplemenation && other);

        StackImplemenation & operator = (const StackImplemenation & other);
        StackImplemenation & operator = (StackImplemenation && other);

        ~StackImplemenation();

        void clear();
        void push(Data data);
        void push(Data data, size_t data_size);
        void pop();
        bool isEmpty() const;
        Data onTop() const;
        size_t topSize() const;

        struct StackNode
        {
            StackNode() = default;
            StackNode(Data data);
            StackNode(Data data, size_t data_size);
            StackNode(const StackNode & other) = default;
            StackNode(StackNode && other) = default;

            StackNode & operator = (const StackNode & other) = default;
            StackNode & operator = (StackNode && other) = default;

            ~StackNode();

            Data data;
            StackNode * next;
            size_t data_size;
        } * top;

        void copy(const StackImplemenation & other);
        void swap(StackNode *& self, StackNode * other);
    };

    Stack::StackImplemenation::StackNode::StackNode(Data data):next(nullptr), data_size(0)
    {
        this->data = data;
    }

    Stack::StackImplemenation::StackNode::StackNode(Data data, size_t data_size):next(nullptr), data_size(data_size)
    {
        this->data = data;
    }

    Stack::StackImplemenation::StackNode::~StackNode()
    {
        next = nullptr;
        data = 0;
    }

    Stack::StackImplemenation::StackImplemenation():top(nullptr)
    {

    }

    Stack::StackImplemenation::StackImplemenation(const StackImplemenation &other):top(nullptr)
    {
        copy(other);
    }

    Stack::StackImplemenation::StackImplemenation(StackImplemenation &&other):top(nullptr)
    {
        swap(top, other.top);
    }

    Stack::StackImplemenation::StackImplemenation(std::initializer_list<Data> list):top(nullptr)
    {
        for(std::initializer_list<Data>::iterator it = list.begin(); it != list.end(); ++it)
        {
            push(*it);
        }
    }

    Stack::StackImplemenation & Stack::StackImplemenation::operator =(const Stack::StackImplemenation & other)
    {
        if(this != &other)
        {
            copy(other);
        }
        return *this;
    }

    Stack::StackImplemenation & Stack::StackImplemenation::operator =(Stack::StackImplemenation && other)
    {
        swap(top, other.top);
        return *this;
    }

    Stack::StackImplemenation::~StackImplemenation()
    {
        clear();
    }

    void Stack::StackImplemenation::copy(const StackImplemenation & other)
    {
        clear();
        StackNode * p = nullptr, *q = other.top;

        while(q)
        {
            StackNode *r = nullptr;
            r = new StackNode(q->data);
            r->next = p;
            p = r;
            q = q->next;
        }

        while(p)
        {
            StackNode *r = p;
            r = p->next;
            p->next = q;
            q = p;
            p = r;
            r = nullptr;
        }

        top = q;
        q = nullptr;
    }

    void Stack::StackImplemenation::swap(StackNode *& self, StackNode * other)
    {
        if(other == nullptr)
        {
            other = self;
        }
        else
        {
            std::swap(self, other);
            swap(self->next, other->next);
        }
    }

    void Stack::StackImplemenation::clear()
    {
        while(top)
        {
            StackNode *p = top;
            top = top->next;
            delete p;
            p = nullptr;
        }
    }

    bool Stack::StackImplemenation::isEmpty() const
    {
        return top == nullptr;
    }

    void Stack::StackImplemenation::push(Data data)
    {
        StackNode *p = nullptr;
        p = new StackNode(data);
        p->next = top;
        top = p;
        p = nullptr;
    }

    void Stack::StackImplemenation::push(Data data, size_t data_size)
    {
        StackNode *p = nullptr;
        p = new StackNode(data, data_size);
        p->next = top;
        top = p;
        p = nullptr;
    }

    void Stack::StackImplemenation::pop()
    {
        StackNode *p = top;

        if(p)
        {
            top = top->next;
            delete p;
            p = nullptr;
        }
    }

    Data Stack::StackImplemenation::onTop() const
    {
        if(top)
        {
            return top->data;
        }
        else
        {
            throw StackException();
        }
    }

    size_t Stack::StackImplemenation::topSize() const
    {
        if(top)
        {
            return top->data_size;
        }
        else
        {
            throw StackException();
        }
    }

    Stack::Stack():pimpl(nullptr)
    {
        pimpl = new StackImplemenation;
    }

    Stack::Stack(const Stack &other):pimpl(nullptr)
    {
        pimpl = new StackImplemenation(*other.pimpl);
    }

    Stack::Stack(Stack &&other):pimpl(nullptr)
    {
        pimpl = new StackImplemenation;
        std::swap(pimpl, other.pimpl);
    }

    Stack::Stack(std::initializer_list<Data> list):pimpl(nullptr)
    {
        pimpl = new StackImplemenation(list);
    }

    Stack & Stack::operator =(const Stack & other)
    {
        if(this != &other)
        {
            *pimpl = *other.pimpl;
        }
        return *this;
    }

    Stack & Stack::operator =(Stack && other)
    {
        *pimpl = std::move(*other.pimpl);
        return *this;
    }

    Stack::~Stack()
    {
        clear();
        delete pimpl;
    }

    void Stack::clear()
    {
        pimpl->clear();
    }

    bool Stack::isEmpty() const
    {
        return pimpl->isEmpty();
    }

    Data Stack::onTop() const
    {
        return pimpl->onTop();
    }

    size_t Stack::topSize() const
    {
        return pimpl->topSize();
    }

    void Stack::pop()
    {
        pimpl->pop();
    }

    void Stack::push(Data data)
    {
        pimpl->push(data);
    }

    void Stack::push(Data data, size_t data_size)
    {
        pimpl->push(data, data_size);
    }
}

