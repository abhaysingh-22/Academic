#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// ---------- NODE STRUCTURE FOR STACK ----------
struct Node {
    char data;
    Node *next;
};

// ---------- STACK IMPLEMENTATION USING LINKED LIST ----------
class Stack {
    Node *top;
public:
    Stack() { top = NULL; }

    void push(char val) {
        Node *newNode = new Node;
        newNode->data = val;
        newNode->next = top;
        top = newNode;
    }

    char pop() {
        if (isEmpty()) {
            return '\0';
        }
        Node *temp = top;
        char val = temp->data;
        top = top->next;
        delete temp;
        return val;
    }

    char peek() {
        return (isEmpty()) ? '\0' : top->data;
    }

    bool isEmpty() {
        return top == NULL;
    }

    void clear() {
        while (!isEmpty()) pop();
    }
};

// ---------- HELPER FUNCTIONS ----------
int precedence(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return -1;
}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// ---------- INFIX TO POSTFIX ----------
string infixToPostfix(string infix) {
    Stack st;
    string postfix = "";

    for (char c : infix) {
        if (c == ' ') continue;

        // Operand → directly add to output
        if (isalnum(c)) {
            postfix += c;
        }
        // '(' → push to stack
        else if (c == '(') {
            st.push(c);
        }
        // ')' → pop until '('
        else if (c == ')') {
            while (!st.isEmpty() && st.peek() != '(') {
                postfix += st.pop();
            }
            st.pop(); // remove '('
        }
        // Operator
        else if (isOperator(c)) {
            while (!st.isEmpty() && precedence(c) <= precedence(st.peek())) {
                postfix += st.pop();
            }
            st.push(c);
        }
    }

    // Pop remaining operators
    while (!st.isEmpty()) {
        postfix += st.pop();
    }

    return postfix;
}

// ---------- INFIX TO PREFIX ----------
string infixToPrefix(string infix) {
    Stack st;
    string prefix = "";

    // Reverse the infix expression
    reverse(infix.begin(), infix.end());
    for (char &c : infix) {
        if (c == '(') c = ')';
        else if (c == ')') c = '(';
    }

    // Convert reversed infix to postfix
    string revPostfix = infixToPostfix(infix);

    // Reverse the postfix to get prefix
    reverse(revPostfix.begin(), revPostfix.end());
    return revPostfix;
}

// ---------- MAIN PROGRAM ----------
int main() {
    string infix;
    int choice;

    while (true) {
        cout << "\n--- INFIX TO POSTFIX & PREFIX USING STACK (LINKED LIST) ---\n";
        cout << "1. Convert Infix to Postfix\n";
        cout << "2. Convert Infix to Prefix\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore(); // clear input buffer

        if (choice == 1) {
            cout << "Enter infix expression: ";
            getline(cin, infix);
            cout << "Postfix Expression: " << infixToPostfix(infix) << endl;
        }
        else if (choice == 2) {
            cout << "Enter infix expression: ";
            getline(cin, infix);
            cout << "Prefix Expression: " << infixToPrefix(infix) << endl;
        }
        else if (choice == 0) {
            cout << "Exiting...\n";
            break;
        }
        else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
