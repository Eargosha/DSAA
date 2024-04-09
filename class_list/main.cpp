/// Autor: Eargosha

#include <iostream>
#include "listik.h"

using namespace std;

int main()
{
    allAsertTests();
    DoublyLinkedList<int> list1;
    DoublyLinkedList<int> list2;
    list1.addFront(123);
    list1.addFront(123);
    list1.addFront(123);
    list2.addFront(999);
    list2.addFront(999);
    list2.addFront(999);
    list1.concatinateWith(list2);
    cout << list1.to_string() << endl;
}
