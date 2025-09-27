#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    char data;
    Node *next;

    Node(char data)
    {
        this->data = data;
        this->next = nullptr;
    }
};

class Stack
{
    Node *head;
    int capacity;
    int size;

public:
    Stack(int c)
    {
        this->capacity = c;
        this->size = 0;
        this->head = nullptr;
    }

    bool isEmpty()
    {
        return this->head == NULL;
    }

    bool isFull()
    {
        return this->size == this->capacity;
    }

    void push(char data)
    {
        if (isFull())
        {
            cout << "Stack Overflow" << endl;
            return;
        }

        Node *newNode = new Node(data);
        newNode->next = head;
        head = newNode;
        size++;
    }

    char pop()
    {
        if (isEmpty())
        {
            cout << "Stack Underflow" << endl;
            return -1;
        }

        Node *temp = head;
        char poppedData = temp->data;
        head = head->next;
        delete temp;
        size--;
        return poppedData;
    }

    char gettop()
    {
        if (isEmpty())
        {
            cout << "Stack Underflow" << endl;
            return -1;
        }
        return head->data;
    }

    int prec(char op)
    {
        if (op == '+' || op == '-')
            return 1;
        if (op == '*' || op == '/')
            return 2;
        if (op == '^')
            return 3;
        return 0;
    }

    bool isOperator(char c)
    {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
    }

    string infixToPostfix(const string &infix)
    {
        string postfix = "";

        for (char c : infix)
        {
            if (isalnum(c))
            {
                postfix += c;
            }
            else if (c == '(')
            {
                push(c);
            }
            else if (c == ')')
            {
                while (!isEmpty() && gettop() != '(')
                {
                    postfix += pop();
                }
                if (!isEmpty() && gettop() == '(')
                    pop();
                else
                {
                    cout << "Mismatched parentheses\n";
                    return "";
                }
            }
            else if (isOperator(c))
            {
                while (!isEmpty() && prec(gettop()) >= prec(c) && gettop() != '(')
                {
                    postfix += pop();
                }
                push(c);
            }
        }

        while (!isEmpty())
        {
            if (gettop() == '(')
            {
                cout << "Mismatched parentheses\n";
                return "";
            }
            postfix += pop();
        }

        return postfix;
    }

    string infixToPrefix(string infix)
    {

        reverse(infix.begin(), infix.end());
        for (int i = 0; i < infix.length(); i++)
        {
            if (infix[i] == '(')
                infix[i] = ')';
            else if (infix[i] == ')')
                infix[i] = '(';
        }

        string postfix = infixToPostfix(infix);

        reverse(postfix.begin(), postfix.end());
        return postfix;
    }

    string prefixToPostfix(string &prefix)
    {
        stack<string> s;

        for (int i = prefix.length() - 1; i >= 0; i--)
        {
            char c = prefix[i];

            if (isalnum(c))
            {
                string op(1, c);
                s.push(op);
            }
            else if (isOperator(c))
            {
                if (s.size() < 2)
                {
                    cout << "Invalid prefix expression\n";
                    return "";
                }
                string op1 = s.top();
                s.pop();
                string op2 = s.top();
                s.pop();
                string combined = op1 + op2 + c;
                s.push(combined);
            }
        }

        if (s.size() != 1)
        {
            cout << "Invalid prefix expression\n";
            return "";
        }

        return s.top();
    }

    int evaluatePostfix(const string &Postfix_expression)
    {
        stack<int> s;

        for (char c : Postfix_expression)
        {
            if (isdigit(c))
            {
                s.push(c - '0');
            }
            else if (isOperator(c))
            {
                if (s.size() < 2)
                {
                    cout << "Invalid postfix expression\n";
                    return INT_MIN;
                }

                int op2 = s.top();
                s.pop();
                int op1 = s.top();
                s.pop();

                switch (c)
                {
                case '+':
                    s.push(op1 + op2);
                    break;
                case '-':
                    s.push(op1 - op2);
                    break;
                case '*':
                    s.push(op1 * op2);
                    break;
                case '/':
                    if (op2 == 0)
                    {
                        cout << "Division by zero error\n";
                        return INT_MIN;
                    }
                    s.push(op1 / op2);
                    break;
                case '^':
                    s.push(pow(op1, op2));
                    break;
                default:
                    cout << "Unsupported operator " << c << endl;
                    return INT_MIN;
                }
            }
        }

        if (s.size() != 1)
        {
            cout << "Invalid postfix expression\n";
            return INT_MIN;
        }

        return s.top();
    }

    int evaluatePrefix(const string &Prefix_expression)
    {
        stack<int> s;

        for (int i = Prefix_expression.length() - 1; i >= 0; --i)
        {
            char c = Prefix_expression[i];

            if (c == ' ')
                continue;

            if (isdigit(c))
            {
                s.push(c - '0');
            }
            else if (isOperator(c))
            {
                if (s.size() < 2)
                {
                    cout << "Invalid prefix expression\n";
                    return INT_MIN;
                }

                int op1 = s.top();
                s.pop();
                int op2 = s.top();
                s.pop();

                switch (c)
                {
                case '+':
                    s.push(op1 + op2);
                    break;
                case '-':
                    s.push(op1 - op2);
                    break;
                case '*':
                    s.push(op1 * op2);
                    break;
                case '/':
                    if (op2 == 0)
                    {
                        cout << "Division by zero error\n";
                        return INT_MIN;
                    }
                    s.push(op1 / op2);
                    break;
                case '^':
                    s.push(pow(op1, op2));
                    break;
                default:
                    cout << "Unsupported operator: " << c << endl;
                    return INT_MIN;
                }
            }
            else
            {
                cout << "Invalid character in expression: " << c << endl;
                return INT_MIN;
            }
        }

        if (s.size() != 1)
        {
            cout << "Invalid prefix expression\n";
            return INT_MIN;
        }

        return s.top();
    }
};

int main()
{
    string infix;
    cout << "Enter an infix expression: ";
    cin >> infix;

    cout << "--------------------------------" << endl;

    Stack st(100);
    string postfix = st.infixToPostfix(infix);

    if (!postfix.empty())
    {
        cout << "Postfix expression: " << postfix << endl;
        cout << "Prefix expression: " << st.infixToPrefix(infix) << endl;
        cout << "--------------------------------" << endl;

        string Postfix_expression;
        cout << "Enter an Postfix expression: ";
        cin >> Postfix_expression;

        int result = st.evaluatePostfix(Postfix_expression);
        if (result != INT_MIN)
            cout << "Postfix Evaluation Result: " << result << endl;
    }

    cout << "--------------------------------" << endl;

    string prefix;
    cout << "Enter a prefix expression: ";
    cin >> prefix;
    cout << "Prefix to Postfix: " << st.prefixToPostfix(prefix) << endl;
    cout << "--------------------------------" << endl;

    string Prefix_expression;
    cout << "Enter an Prefix expression: ";
    cin >> Prefix_expression;

    int r = st.evaluatePrefix(Prefix_expression);
    if (r != INT_MIN)
    {
        cout << "Prefix Evaluation Result: " << r << endl;
    }

    cout << "----------------------------------------*---------------" << endl;

    return 0;
}

//((a+b)*(c-d))/(e+f)
//*+a-bc/-de+-fgh
// 53+82-*