#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <math.h>
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
        {
            temp.push_back(*i);
            continue;
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

int evaluate(vector<string>::iterator it, vector<string>::iterator end)
{
    stack<int> nums;
    for (auto i = it; i < end; i++)
    {
        if ((*i).size() > 1 || isdigit((*i)[0]))
            nums.push(stoi(*i));

        else
        {

            int val1 = nums.top();
            nums.pop();
            int val2 = nums.top();
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
                nums.push(val2 / val1);
                break;
            }
        }
    }
    return nums.top();
}

int main(void)
{
    string input = "-(((1+2) * (-3))^(1 + 1))";
    vector<string> v = postfix(input);
    cout << evaluate(v.begin(), v.end()) << endl;
}
