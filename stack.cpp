#include <iostream>
using namespace std;

class node
{
private:
    char data;
    node *next;

public:
    node() : next(nullptr) {}
    node(int inp) : data(inp), next(nullptr) {}
    node(int inp, node *below) : data(inp), next(below) {}
    char show_value()
    {
        return data;
    }
    node *show_next()
    {
        return next;
    }
};

class stack
{
private:
    node *front;
    int count;

public:
    stack() : front(nullptr), count(0) {}
    ~stack()
    {
        while (count)
            this->pop();
    }
    void insert(int d)
    {
        node *temp = new node(d, front);
        front = temp;
        count++;
    }
    char pop()
    {
        char ret = front->show_value();
        node *temp = front;
        front = front->show_next();
        delete temp;
        count--;
        return ret;
    }
};
