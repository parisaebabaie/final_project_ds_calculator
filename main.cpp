#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <iomanip>
#include "stack.h"
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
    MyStack<char> st;
    MyStack<char> paran;
    vector<string> res;
    bool valid = true;
    for (auto i = infix.begin(); i < infix.end(); i++)
    {
        if (*i == ' ')
            continue;

        string temp;
        if (*i == '-' && (i == infix.begin() || st.top() == '('))
        {
            res.push_back("0");
        }

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
    if (!valid)
    {
        res.clear();
        return res;
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

void error_dis()
{
    cout << "Error!" << endl;
}

void evaluate(vector<string>::iterator it, vector<string>::iterator end)
{
    MyStack<double> nums;
    for (auto i = it; i < end; i++)
    {
        if ((*i).size() > 1 || isdigit((*i)[0]))
            nums.push(stod(*i));

        else
        {
            if (nums.empty())
            {
                error_dis();
                return;
            }

            double val1 = nums.top();
            nums.pop();

            if (nums.empty())
            {
                error_dis();
                return;
            }
            double val2 = nums.top();
            nums.pop();

            switch ((*i)[0])
            {
            case '^':
                nums.push(pow(val2, val1));
                break;
            case '+':
                nums.push(val2 + val1);
                break;
            case '-':
                nums.push(val2 - val1);
                break;
            case '*':
                nums.push(val2 * val1);
                break;
            case '/':
                if (val1 == 0)
                {
                    error_dis();
                    return;
                }
                nums.push(val2 / val1);
                break;
            }
        }
    }
    cout << setprecision(5 + int(nums.top() / 10)) << nums.top() << endl;
}

int main(void)
{
    string input;
    cout << "Enter the infix expression: ";
    getline(cin, input);
    vector<string> v = postfix(input);
    if (v.empty())
        error_dis();
    else
        evaluate(v.begin(), v.end());
}