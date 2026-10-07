#include <iostream>
#include <string>
using namespace std;
struct Node {
    char data;
    Node* next;
    Node(char ch) {
        data = ch;
        next = NULL;
    }
};
// Stack representation using Linked Nodes
struct Stack {
    Node* topNode;

    Stack() {
        topNode = NULL;
    }
};

// 4. IsEmpty
bool isEmpty(Stack* s) {
    return s->topNode == NULL;
}

// 1. Push
void push(Stack* s, char ch) {
    Node* newNode = new Node(ch);
    newNode->next = s->topNode;
    s->topNode = newNode;
}

// 2. Pop
void pop(Stack* s) {
    if (isEmpty(s)) {
        return;
    }
    Node* temp = s->topNode;
    s->topNode = s->topNode->next;
    delete temp;
}

// 3. Top (Returns the top character without cluttering console)
char getTop(Stack* s) {
    if (isEmpty(s)) {
        return '\0';
    }
    return s->topNode->data;
}

// 6. Display Stack (Required Operation)
void displayStack(Stack* s) {
    if (isEmpty(s)) {
        cout << "Stack is empty." << endl;
        return;
    }
    cout << "Stack (Top to Bottom): ";
    Node* curr = s->topNode;
    while (curr != NULL) {
        cout << "[" << curr->data << "] ";
        curr = curr->next;
    }
    cout << endl;
}

// 7. Clear Stack
void clearStack(Stack* s) {
    while (!isEmpty(s)) {
        pop(s); // Frees node memory one by one
    }
}

// 5. Check Balance
bool checkBalancedParenthesis(const string& expression) {
    Stack* s = new Stack();

    for (int i = 0; i < expression.length(); i++) {
    char ch = expression[i]; // get the character by index
        // If opening bracket, push onto stack
        if (ch == '(' || ch == '{' || ch == '[') {
            push(s, ch);
        } 
        // If closing bracket, check for matching opening bracket
        else if (ch == ')' || ch == '}' || ch == ']') {
            // Unmatched closing bracket
            if (isEmpty(s)) {
                clearStack(s);
                delete s;
                return false; 
            }

            char topChar = getTop(s);
            // Mismatched bracket types
            if ((ch == ')' && topChar != '(') ||
                (ch == '}' && topChar != '{') ||
                (ch == ']' && topChar != '[')) {
                clearStack(s); // Free remaining nodes before exiting!
                delete s;
                return false; 
            }

            pop(s); // Matched pair, remove opening bracket
        }
    }

    bool isBalanced = isEmpty(s);

    // Free remaining nodes and stack wrapper
    clearStack(s);
    delete s;

    return isBalanced;
}

int main() {
    string testCases[] = {
        "(A+B)",
        "{A+[B*C]}",
        "(A+B]",
        "((A+B)",
        "{[()]}",
        "A+B*C",
        "([A+B])"
    };

    cout << "=== PARENTHESES BALANCE CHECKER ===" << endl << endl;

   for (int i = 0; i < 7; i++) {
    string expr = testCases[i];
    cout << "Expression: " << expr << endl;
    if (checkBalancedParenthesis(expr)) {
        cout << "Status    : Balanced" << endl;
    } else {
        cout << "Status    : Not Balanced" << endl;
    }
}

    return 0;
}