template <typename T>
class node
{
private:
    T data;
    node *next;

public:
    node() : next(nullptr) {}
    node(T inp) : data(inp), next(nullptr) {}
    node(T inp, node *below) : data(inp), next(below) {}
    T show_value()
    {

        return data;
    }
    node<T> *show_next()
    {
        return next;
    }
};
template <typename T>
class MyStack
{
private:
    node<T> *front;
    int count;

public:
    MyStack() : front(nullptr), count(0) {}
    ~MyStack()
    {
        while (count)
            this->pop();
    }
    void push(T d)
    {
        node<T> *temp = new node(d, front);
        front = temp;
        count++;
    }
    bool empty()
    {
        return (front == nullptr);
    }
    T top()
    {
        return front->show_value();
    }
    void pop()
    {
        if (!count)
            return ;
        node<T> *temp = front;
        front = front->show_next();
        delete temp;
        count--;
    }
};
