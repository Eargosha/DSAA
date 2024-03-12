// Autor: Иванов Егор

#include <iostream> // Библиотека cin cout
#include <cassert>  // Для assert
#include <time.h>   // Время для рандомных элементов массива
#include <fstream>  // Для работы с файлами
#include <exception>
#include <vector>
#include <chrono>
#include <thread>
#include "my_array.h" // Мой модуль

using namespace std; // Пространоство имен
using namespace std::chrono;

// long long для размера массива insigned long long

int main()
{

    srand(time(0)); // Время необходимо для рандома, библиотека подключена в main

    // Ассерты
    sequential_search_assert();
    arr_is_sorted_assert();
    binary_search_assert();
    interpolation_search_assert();
    find_closest_assert();
    selectionSortIterative_assert();
    selectionSortRecursive_assert();
    // sort_buble_test();
    // merge_sort_test();
    // quick_sort_test();
    // dyadyaShell_sort_test();

    long long sizeSmall = 6;
    int *a = new int[sizeSmall]{6, 2, 3, 4, 5, 1};
    double *b = new double[sizeSmall]{1.04, 1.05, 1.03, 1.01, 1.02, 1.06};

    merge_sort(a, 0, sizeSmall);
    print_array(a, sizeSmall);

    // Работа для построения графика времени работы сортировочных функций
    //  {
    //      size_t bigSize = 200000;

    //     int elapsedMilliSeconds1 = 0;
    //     int elapsedMilliSeconds2 = 0;

    //     for (int j = 0; bigSize < 100000000; j++) // ну пока не переполним...
    //     {
    //         int *a = new int[bigSize];
    //         cout << "size = " << bigSize << endl;
    //         rand_fill_array(a, bigSize, 1000, 1);

    //         // // померяли merge
    //         // auto begin1 = steady_clock::now();
    //         // for (int i = 0; i < 1; i++)
    //         // {
    //         //     merge_sort(a, 0, bigSize);
    //         // }
    //         // auto end1 = steady_clock::now();
    //         // elapsedMilliSeconds1 = duration_cast<milliseconds>(end1 - begin1).count();

    //         // померяли квик сорт
    //         auto begin2 = steady_clock::now();
    //         for (int i = 0; i < 1; i++)
    //         {
    //             sort_buble(a, bigSize);
    //         }
    //         auto end2 = steady_clock::now();
    //         elapsedMilliSeconds2 = duration_cast<milliseconds>(end2 - begin2).count();

    //         if (bigSize >= 10000) // если размер достиг это, то добавляем уже чуть чуть поменьше
    //             bigSize += bigSize * 0.2;
    //         else
    //             bigSize *= 10;
    //                      // сколько заняло миллисекунд n итераций/n итераций = 1 итерация //
    //         cout << "Time elapsed(in milliseconds) for merge_sort: " << elapsedMilliSeconds1 / 1 << endl;
    //         cout << "Time elapsed(in milliseconds) for quick_sort: " << elapsedMilliSeconds2 / 1 << endl;
    //     }
    // }

    // // Работа для построения графика времени работы посиковых функций
    // {
    //     size_t bigSize = 100000000;

    //     int elapsedMilliSeconds1 = 0;
    //     int elapsedMilliSeconds2 = 0;
    //     int elapsedMilliSeconds3 = 0;
    //     int element = 0;

    //     for (int j = 0; bigSize < 100000000000; j++) // ну пока не переполним...
    //     {
    //         int *a = new int[bigSize];
    //         // for (size_t t = 0; t < bigSize; t++)
    //         // {
    //         //     a[t] = t;
    //         // } // Делаем насильственно последовательным

    //         cout << "size = " << bigSize << endl;
    //         rand_fill_array(a, bigSize, 1000000, 1);

    //                         // померяли последовательно
    //         auto begin1 = steady_clock::now();
    //         for (int i = 0; i < 5; i++)
    //         {
    //             element = (int)rand() / RAND_MAX * 10000 + 1; // возможно попадется
    //             sequential_search(a, bigSize, element);
    //         }
    //         auto end1 = steady_clock::now();
    //         elapsedMilliSeconds1 = duration_cast<milliseconds>(end1 - begin1).count();

    //                        // померяли бинарный
    //         auto begin2 = steady_clock::now();
    //         for (int i = 0; i < 5; i++)
    //         {
    //             element = (int)rand() / RAND_MAX * 10000 + 1; // возможно попадется
    //             binary_search(a, bigSize, element);
    //         }
    //         auto end2 = steady_clock::now();
    //         elapsedMilliSeconds2 = duration_cast<milliseconds>(end2 - begin2).count();

    //                         // померяли интерп
    //         auto begin3 = steady_clock::now();
    //         for (int i = 0; i < 5; i++)
    //         {
    //             element = (int)rand() / RAND_MAX * 10000 + 1; // возможно попадется
    //             interpolation_search(a, bigSize, element);
    //         }
    //         auto end3 = steady_clock::now();
    //         elapsedMilliSeconds3 = duration_cast<milliseconds>(end3 - begin3).count();

    //         if (bigSize >= 1000000000) // если размер достиг это, то добавляем уже чуть чуть поменьше
    //             bigSize += bigSize * 2;
    //         else
    //             bigSize *= 10;
    //                      // сколько заняло миллисекунд n итераций/n итераций = 1 итерация //
    //         cout << "Time elapsed(in milliseconds) for Sequential Search: " << elapsedMilliSeconds1 / 5 << endl;
    //         cout << "Time elapsed(in milliseconds) for Binary Search: " << elapsedMilliSeconds2 / 5 << endl;
    //         cout << "Time elapsed(in milliseconds) for Interpolation Search: " << elapsedMilliSeconds3 / 5 << endl;
    //     }
    // }

} // int main