#include <iostream>
#include "stack.h"

using namespace std;

int main() {
    testStack();

    Stack<int> stack;

    stack.push(10);
    stack.push(20);
    stack.push(30);

    stack.pop();
    stack.pop();

    stack.push(40);

    cout << stack.to_string() << endl;

    return 0;
}