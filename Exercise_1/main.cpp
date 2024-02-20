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
    // sosert_buble();

    // Работа для построения графика времени работы посиковых функций
    {
        long long bigSize = 1000;
        double element = 1000; // возможно попадется

        int elapsedMilliSeconds = 0;
        int elapsedMilliSeconds1 = 0;
        int elapsedMilliSeconds0 = 0;
        int elapsedMilliSeconds2 = 0;
        int elapsedMilliSeconds3 = 0;

        // сделать ссумарным 100 раз поиск элемента также для бинарного и ииии...
        for (int j = 0; bigSize < 10000000; j++)
        {

            double *a = new double[bigSize];
            for (size_t t = 0; t < bigSize; t++)
            {
                a[t] = t;
            } // Делаем насильственно последовательным

            cout << "size = " << bigSize << endl;
            for (int i = 0; i < 100; i++)
            {
                auto begin1 = steady_clock::now();
                interpolation_search(a, bigSize, element);
                auto end1 = steady_clock::now();
                elapsedMilliSeconds1 += duration_cast<milliseconds>(end1 - begin1).count(); // сумарно 100 раз

                auto begin2 = steady_clock::now();
                binary_search(a, bigSize, element);
                auto end2 = steady_clock::now();
                elapsedMilliSeconds2 += duration_cast<milliseconds>(end2 - begin2).count(); // сумарно 100 раз

                auto begin3 = steady_clock::now();
                sequential_search(a, bigSize, element);
                auto end3 = steady_clock::now();
                elapsedMilliSeconds3 += duration_cast<milliseconds>(end3 - begin3).count(); // сумарно 100 раз
            }
            bigSize *= 10;
            cout << "Time elapsed(in milliseconds) for Creating Random Array: " << elapsedMilliSeconds0 << endl; // сколько заняло секунд
            cout << "Time elapsed(in milliseconds) for Interpolation Search: " << elapsedMilliSeconds1 << endl;  // сколько заняло секунд
            cout << "Time elapsed(in milliseconds) for Binary Search: " << elapsedMilliSeconds1 << endl;         // сколько заняло секунд
            cout << "Time elapsed(in milliseconds) for Sequential Search: " << elapsedMilliSeconds1 << endl;     // сколько заняло секунд
            // bigSize *= 10;
        }

        // size_t size = 1000;
        // auto begin = steady_clock::now();
        // auto end = steady_clock::now();

        // for (size_t k = 0; k < 10000000; k++)
        // {
        //     cout << "Arr size is " << size << endl;
        //     double *arr = new double[size];
        //     rand_fill_array(arr, size, 100.0, 1.0);
        //     sort_buble(arr, size); // сортируем
        //     int time;
        //     double key = 5.24;     // ну предположим
        //     int iterations = 100;

        //     auto begin = steady_clock::now();
        //     for (size_t i = 0; i < iterations; i++) {
        //         sequential_search(arr, size, key);
        //     }
        //     auto end = steady_clock::now();
        //     time = duration_cast<milliseconds>(end-begin).count();
        //     cout << "Elapsed time in milliseconds: " << time/iterations << endl;
        //     size *= 10;

        // // поиск последовательно
        // begin = steady_clock::now();
        // for (int y = 0; y < iterations; y++)
        // {
        //     sequential_search(arr, size, key);
        // }
        // end = steady_clock::now();
        // auto elapsedMilliSeconds = duration_cast<milliseconds>(end - begin).count() / iterations;
        // cout << "Time elapsed for sequential searching an element " << key << " in array with size of " << size << " is " << elapsedMilliSeconds << " in Milliseconds " << endl;

        // cout << "================================================" << endl;
        // // поиск бинарно
        // begin = steady_clock::now();
        // for (int y = 0; y < iterations; y++)
        // {
        //     binary_search(arr, size, key);
        // }
        // end = steady_clock::now();
        // elapsedMilliSeconds = duration_cast<milliseconds>(end - begin).count() / iterations;
        // cout << "Time elapsed for binary searching an element " << key << " in array with size of " << size << " is " << elapsedMilliSeconds << " in Milliseconds " << endl;

        // cout << "================================================" << endl;
        // // поиск интерполяционно
        // begin = steady_clock::now();
        // for (int y = 0; y < iterations; y++)
        // {
        //     interpolation_search(arr, size, key);
        // }
        // end = steady_clock::now();
        // elapsedMilliSeconds = duration_cast<milliseconds>(end - begin).count() / iterations;
        // cout << "Time elapsed for binary searching an element " << key << " in array with size of " << size << " is " << elapsedMilliSeconds << " in Milliseconds " << endl;

        // size *= 10;
        // cout << "Size was multiplied by 10" << endl;
        // cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
        //}
    }

} // int main