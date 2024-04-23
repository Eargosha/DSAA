#include <iostream>
#include "stack.h"

using namespace std;

int main() {
    testStack();

    Stack<int> stack;
    Stack<int> stack2;

    stack.push(10);
    stack.push(20);
    stack.push(30);

    
    stack2.push(10);
    stack2.push(20);
    stack2.push(30);

    stack.pop();
    cout << stack.pop() << " был удален \n";

    stack.push(40);

    cout << stack.size() << endl;
    //пустой стек
    Stack<int> stack3;
    cout << stack3.isEmpty() << endl;
    cout << stack.peek();

    return 0;
}