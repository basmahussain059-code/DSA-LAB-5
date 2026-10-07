#include <iostream>
#include <string>

using namespace std;
struct CharNode {
    char data;
    CharNode* next;

    CharNode(char c) {
        data = c;
        next = NULL;
    }
};

// Character Stack
struct CharStack {
    CharNode* top;

    CharStack() {
        top = NULL;
    }

    bool isEmpty() {
        return top == NULL;
    }

    void push(char c) {
        CharNode* newNode = new CharNode(c);
        newNode->next = top;
        top = newNode;
    }

    char pop() {
        if (isEmpty()) return '\0';
        CharNode* temp = top;
        char val = temp->data;
        top = top->next;
        delete temp; // Free memory
        return val;
    }

    char peek() {
        if (isEmpty()) return '\0';
        return top->data;
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    ~CharStack() {
        clear();
    }
};

// Node for Integer Stack 
struct IntNode {
    int data;
    IntNode* next;

    IntNode(int val) {
        data = val;
        next = NULL;
    }
};

// Integer Stack
struct IntStack {
    IntNode* top;

    IntStack() {
        top = NULL;
    }

    bool isEmpty() {
        return top == NULL;
    }

    void push(int val) {
        IntNode* newNode = new IntNode(val);
        newNode->next = top;
        top = newNode;
    }

    int pop() {
        if (isEmpty()) return 0;
        IntNode* temp = top;
        int val = temp->data;
        top = top->next;
        delete temp; // Free memory
        return val;
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    ~IntStack() {
        clear();
    }
};
bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%');
}

int precedence(char op) {
    if (op == '*' || op == '/' || op == '%') return 2; // High priority
    if (op == '+' || op == '-') return 1;              // Low priority
    return 0; // for '('
}
bool infixToPostfix(string infix, string& postfix) {
    CharStack s;
    postfix = "";

    // Check for empty expression
    if (infix.length() == 0) {
        cout << ">> Error: Expression is empty!" << endl;
        return false;
    }

    int i = 0;
    while (i < infix.length()) {
        char ch = infix[i];
        //Skip spaces
        if (ch == ' ') {
            i++;
            continue;
        }
        // 2. Operands: Multi-digit numbers
        if (ch >= '0' && ch <= '9') {
            while (i < infix.length() && (infix[i] >= '0' && infix[i] <= '9')) {
                postfix += infix[i];
                i++;
            }
            postfix += " "; // Space separator so multi-digit numbers don't merge
            continue;
        }
        // 3. Opening Parenthesis
        else if (ch == '(') {
            s.push(ch);
        }

        // 4. Closing Parenthesis
        else if (ch == ')') {
            bool foundOpening = false;
            while (!s.isEmpty()) {
                if (s.peek() == '(') {
                    s.pop(); // Discard '('
                    foundOpening = true;
                    break;
                }
                postfix += s.pop();
                postfix += " ";
            }

            if (!foundOpening) {
                cout << ">> Error: Mismatched parentheses (Extra closing ')')!" << endl;
                s.clear();
                return false;
            }
        }

        // 5. Operators (+, -, *, /, %)
        else if (isOperator(ch)) {
            while (!s.isEmpty() && precedence(s.peek()) >= precedence(ch)) {
                postfix += s.pop();
                postfix += " ";
            }
            s.push(ch);
        }

        // 6. Invalid Character
        else {
            cout << ">> Error: Invalid character '" << ch << "' in expression!" << endl;
            s.clear();
            return false;
        }

        i++;
    }

    // Pop any remaining operators off the stack
    while (!s.isEmpty()) {
        if (s.peek() == '(') {
            cout << ">> Error: Mismatched parentheses (Unclosed '(')!" << endl;
            s.clear();
            return false;
        }
        postfix += s.pop();
        postfix += " ";
    }

    return true;
}
bool evaluatePostfix(string postfix, int& result) {
    IntStack s;
    int i = 0;

    while (i < postfix.length()) {
        char ch = postfix[i];

        // Skip spaces
        if (ch == ' ') {
            i++;
            continue;
        }

        // 1. Read Number
        if (ch >= '0' && ch <= '9') {
            int num = 0;
            while (i < postfix.length() && (postfix[i] >= '0' && postfix[i] <= '9')) {
                num = (num * 10) + (postfix[i] - '0');
                i++;
            }
            s.push(num);
            continue;
        }

        // 2. Process Operator
        else if (isOperator(ch)) {
            if (s.isEmpty()) {
                cout << ">> Error: Invalid postfix syntax!" << endl;
                s.clear();
                return false;
            }
            int val2 = s.pop(); // Top number

            if (s.isEmpty()) {
                cout << ">> Error: Invalid postfix syntax!" << endl;
                s.clear();
                return false;
            }
            int val1 = s.pop(); // Number underneath

            // Detect Division or Modulo by Zero
            if ((ch == '/' || ch == '%') && val2 == 0) {
                cout << ">> Error: Division or Modulo by zero!" << endl;
                s.clear();
                return false;
            }

            // Calculate (val1 comes BEFORE val2)
            if (ch == '+') s.push(val1 + val2);
            else if (ch == '-') s.push(val1 - val2);
            else if (ch == '*') s.push(val1 * val2);
            else if (ch == '/') s.push(val1 / val2);
            else if (ch == '%') s.push(val1 % val2);
        }

        i++;
    }

    if (s.isEmpty()) {
        return false;
    }

    result = s.pop();

    // Check if extra numbers were left on stack
    if (!s.isEmpty()) {
        cout << ">> Error: Invalid expression (Extra operands)!" << endl;
        s.clear();
        return false;
    }

    return true;
}
// Helper to run an expression through both steps
void processExpression(string expr) {
    cout << "\nInfix Expression  : " << expr << endl;

    string postfix = "";
    if (infixToPostfix(expr, postfix)) {
        cout << "Postfix Expression: " << postfix << endl;

        int result = 0;
        if (evaluatePostfix(postfix, result)) {
            cout << "Final Evaluation  : " << result << endl;
        }
    }
    cout << "--------------------------------------------------" << endl;
}
int main() {
    int choice;

    while (true) {
        cout << "\n================ EXPRESSION PROCESSOR ================\n";
        cout << "1. Enter Expression from User (Interactive)\n";
        cout << "2. Run All Assignment Test Cases\n";
        cout << "0. Exit\n";
        cout << "======================================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 0) {
            cout << "Exiting program. Goodbye!" << endl;
            break;
        }

        if (choice == 1) {
            cin.ignore(); // Clear newline from input buffer
            string userExpr;
            cout << "\nEnter arithmetic expression: ";
            getline(cin, userExpr);
            processExpression(userExpr);
        } 
        else if (choice == 2) {
            cout << "\n--- RUNNING REQUIRED TEST CASES ---\n";
            processExpression("2 + 3 * 4");              
            processExpression("(2 + 3) * 4");           
            processExpression("10 + 2 * 6");             
            processExpression("(10 + 2) * (6 - 3)");     
            processExpression("20 / 5 + 3");            

            cout << "\n--- RUNNING EDGE CASES ---\n";
            processExpression("((2 + 3) * (4 + 2))");     
            processExpression("10 + 2 * 3 - 4 / 2");     
            processExpression("");                      
            processExpression("(10 + 2");                
            processExpression("10 + 2)");           
            processExpression("10 / 0");                
            processExpression("20 / (5 - 5)");           
        } 
        else {
            cout << "Invalid choice! Please choose 1, 2, or 0." << endl;
        }
    }

    return 0;
}