/// Autor: Eargosha

#include <iostream>
#include "listik.h"

#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;


void doFirstTask()
{
    // Создаем вектор чисел
    vector<int> numbers = {123, 234, 345, 456, 567, 678, 789};

    // for_each: умножаем каждый элемент вектора на 10,000 и выводим его
    cout << "Чиселки подралися и с помощью for_each поочередно, каждый умножились на 10,000. Вот, смотрите на них: " << endl;
    for_each(numbers.begin(), numbers.end(), [](int n)
             {  n = n * 10000;
                cout << n << ", "; });

    cout << endl << endl;

    // any_of: проверяем, есть ли хотя бы одно четное число, проверяет массив сначала
    bool has_even = any_of(numbers.begin(), numbers.end(), [](int n)
                           { return n % 2 != 0; });
    cout << "any_of скажет, есть ли среди них нечетные чиселки??? " << endl << (has_even ? "Да" : "Нет") << endl;

    cout << endl;

    // all_of: проверяем, все ли числа равны 123
    bool all_positive = all_of(numbers.begin(), numbers.end(), [](int n)
                               { return n == 123; });
    cout << "all_of спалит всех, что они, числа, равны числу 123?? "<< endl << (all_positive ? "Да" : "Нет") << endl;

    cout << endl; 

    // none_of: проверяем, нет ли числа равные 123
    bool no_negative = none_of(numbers.begin(), numbers.end(), [](int n)
                               { return n != 123; });
    cout << "none_of действует как и all_of, но наоборот, он скажет, числа не равны ли 123? " << endl << (no_negative ? "Да" : "Нет") << endl;

    cout << endl;
    // transform: уменьшаем каждое число в 10000 раз
    vector<int> incremented_numbers(numbers.size());
    transform(numbers.begin(), numbers.end(), incremented_numbers.begin(), [](int n)
              { return n / 10000; });

    cout << "Числа после встречи с transform и уменьшились в 10,000 раз: " << endl;
    for_each(numbers.begin(), numbers.end(), [](int n)
             { cout << n << ", "; });

    cout << endl << endl;

    // copy_if: копируем четные числа в новый вектор
    vector<int> even_numbers; 
    copy_if(numbers.begin(), numbers.end(), back_inserter(even_numbers), [](int n)
            { return n % 2 != 0; });

    cout << "copy_if скопировал нечетные чиселки в новый массивчик: " << endl;
    for_each(even_numbers.begin(), even_numbers.end(), [](int n)
             { cout << n << ", "; });

    cout << endl << endl;
}

int main()
{
    // Штуки по Linked List
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

    doFirstTask();

    testListIterator(); 

}
