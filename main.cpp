#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

int operator_priority(char op)
{
    switch (op)
    {
    case '^':
        return 4;
    case '*':
    case '/':
        return 3;
    case '+':
    case '-':
        return 2;

    default:
        break;
    }
    return 0;
}

char associativity(char c)
{
    if (c == '^')
        return 'R';
    return 'L';
}
vector<string> postfix(string infix)
{
    stack<char> st;
    stack<char> paran;
    vector<string> res;
    bool valid = true;
    for (auto i = infix.begin(); i < infix.end(); i++)
    {
        if (*i == ' ')
            continue;

        string temp;
        if (*i == '-' && i == infix.begin())
            temp.push_back(*(i++));

        bool num_flag = false;
        while (*i >= '0' && *i <= '9')
        {
            temp += *i;
            i++;
            num_flag = true;
        }
        if (num_flag)
            i--;

        if (!temp.empty() && temp != "-")
            res.push_back(temp);

        else if (*i == '(')
        {
            paran.push('(');
            st.push('(');
        }
        else if (*i == ')')
        {
            if (paran.empty())
            {
                valid = false;
                break;
            }
            paran.pop();

            while (st.top() != '(')
            {
                temp.clear();
                temp += st.top();
                res.push_back(temp);
                st.pop();
            }
            st.pop();
        }
        else
        {
            while (!st.empty() && operator_priority(*i) < operator_priority(st.top()) ||
                   !st.empty() && operator_priority(*i) == operator_priority(st.top()) &&
                       associativity(*i) == 'L')
            {
                temp.clear();
                temp += st.top();
                res.push_back(temp);
                st.pop();
            }
            st.push(*i);
        }
    }
    while (!st.empty())
    {
        string temp;
        temp += st.top();
        res.push_back(temp);
        st.pop();
    }

    return res;
}

int main(void)
{
    string input = "3*1+5-9";
    auto pf = postfix(input);
}