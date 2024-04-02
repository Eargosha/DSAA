/// Autor: Eargosha

#include <iostream>
#include "listik.h"

using namespace std;

int main()
{
DoublyLinkedList <int> listik_letel;
listik_letel.addFront(111);
listik_letel.addBack(222);
listik_letel.addInList(333, listik_letel.get_nodule(0));
//listik_letel.deleteInList(listik_letel.get_nodule(2));
//listik_letel.sort();
cout << listik_letel.to_string() << endl;
cout << listik_letel.find(111)->data << endl;
cout << listik_letel.length() << endl;

DoublyLinkedList <int> listik_letel2 = DoublyLinkedList(4, 11);
cout << listik_letel2.to_string() << endl;
}
