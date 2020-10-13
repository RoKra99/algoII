#pragma once
#include <cstring>
#include <iostream>

namespace datastructures
{
    template <typename T>
    struct StackElement
    {
        StackElement<T> *prev = nullptr;
        T data;
    };

    template <class T>
    class Stack
    {
    private:
        StackElement<T> *top;
        StackElement<T> *bottom;
        std::size_t count;

    public:
        Stack()
        {
            bottom = nullptr;
            top = nullptr;
            count = 0;
        }

        size_t size() const
        {
            return count;
        }

        bool empty() const
        {
            return count == 0;
        }

        void push(const T &data)
        {
            if (empty())
            {
                top = new StackElement<T>;
                top->data = data;
                bottom = top;
            }
            else
            {
                StackElement<T> *e = new StackElement<T>;
                e->data = data;
                e->prev = top;
                top = e;
            }
            ++count;
        }

        // assumes the stack is not empty
        T pop()
        {
            StackElement<T> *e = top;
            T data = e->data;
            top = e->prev;
            delete e;
            --count;
            if (empty())
            {
                bottom = nullptr;
            }
            return data;
        }

        //assumes both Stacks are not empty
        void append(Stack<T> &other)
        {
            count += other.size();
            other.bottom->prev = top;
            top = other.top;
        }

        //assumes stack is not empty
        T getTop()
        {
            return top->data;
        }

        //assumes stack is not empty
        T preTop()
        {
            return top->prev->data;
        }

        void print()
        {
            std::cout << "Printing full stack: " << std::endl;
            StackElement<T> *e = top;
            do
            {
                std::cout << e->data.x << ", " << e->data.y << std::endl;
                e = e->prev;
            } while (e);
        }
    };
}