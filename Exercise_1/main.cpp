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

// size_t для размера массива insigned long long

int main()
{

    srand(time(0)); // Время необходимо для рандома, библиотека подключена в main

    // Ассерты
    sequential_search_assert();
    arr_is_sorted_assert();

    // Работа с созданием массива с помощью рандомайзера
    {
        // size_t size; // Переменная - размер массива
        // char check;  // Переменная - для проверки Y/N
        // int maxim;   // Переменная - для диапозона - максимальное число
        // int minim;   // Переменная - для диапозона - минимальное число

        // cout << "Enter size of array: "; // Вводим размер массива в переменную size
        // cin >> size;

        // double *a = new double[size]; // Выделяем память под динамический массив

        // cout << "Enter the maximum value in the numbers in the array: " << endl;
        // cin >> maxim; // Ввод диапозона для чисел массива - макс

        // cout << "Enter the minimum value in the numbers in the array: " << endl;
        // cin >> minim; // Ввод диапозона для чисел массива - миним

        // rand_fill_array(a, size, maxim, minim); // Заполняем массив действительными числами
        // print_array(a, size);                   // Выводим массив на экран
        // arr_is_sort(a, size) ?                  // Проверка на сортированность этого массива
        //                     cout << "Array is sorted" << endl :
        //                     cout << "Array is NOT sorted" << endl;

        // arr_is_sorted_assert();                 // assert-ом прогоняем функцию arr_is_sorted
        // delete[] a;
    }

    // Поиск элемента в маленьком массиве
    {
        // int *seqSearchArr = new int[5]{1, 2, 3, 4, 5};
        // cout << "Searching an element '4' in array..." << endl;

        // auto begin = steady_clock::now(); // начальная отметка времени
        // double key = sequential_search(seqSearchArr, 5, 4);
        // auto end = steady_clock::now(); // конечная отметка времени
        // auto elapsedNanoSeconds = duration_cast<nanoseconds>(end - begin).count(); //сколько времени заняло
        // cout << "Time elapsed(in nanoseconds): " << elapsedNanoSeconds << endl;

        // cout << "Element '4' has index: " << key << endl;
    }

    // Место работы с файлами
    {
        // string fileNameTxt = "my_txt.txt"; // Переменные - имена файлой - текстового и бинарного
        // string fileNameBin = "my_bin_file";

        // // Массив в файлы
        // array_to_file(a, size, fileNameTxt);
        // array_to_bin_file(a, size, fileNameBin);

        // // Загрузка нового массива из бинарного файла
        // double *b = new double[size]; // Выделяем память под динамический массив
        // size_t newSize = array_size_form_file(fileNameBin);
        // array_from_bin_file(b, newSize, fileNameBin);
        // cout << "A readed array from bibary: " << endl;
        // milliseconds awaitMiliseconds( 2000 );
        // this_thread::sleep_for( awaitMiliseconds );
        // print_array(b, size);                   // Выводим массив на экран
        // delete[] b;

        // // Загрузка нового массива из текстового файла
        // double *c = new double[size]; // Выделяем память под динамический массив
        // array_from_file(c, size, fileNameTxt);
        // cout << "A readed array from txt: " << endl;
        // milliseconds awaitMiliseconds( 2000 );
        // this_thread::sleep_for( awaitMiliseconds );
        // print_array(c, size);                   // Выводим массив на экран
        // delete[] c;
    }

    // Поиск в рандомном массиве, что был записан в текстовый файл
    // Также тут находятся эксперименты со временем
    {
        size_t bigSize = 10000000;
        double element = -123.0; // его там точно не существует
        string fileName = "tyzhelo.txt";

        double *a = new double[bigSize];
        rand_fill_array(a, bigSize, 100000.0, 0.0);   

        // array_to_file(a, bigSize, fileName);
        // array_from_file(a, bigSize, fileName);

        double *time = new double[5];

        double key = 0;
        for (int i = 0; i < 5; i++)
        {
            cout << i+1 << " iteration" << endl;

            auto begin = steady_clock::now();  
            //key = sequential_search(a, bigSize, element);
            (sequential_search(a, bigSize, element) == -1) ? 
                                cout << element << " was not found in this array" << endl : 
                                cout << element << " was found at the index: " << key << endl;
            auto end = steady_clock::now();

            auto elapsedSeconds = duration_cast<milliseconds>(end - begin).count();
            time[i] = elapsedSeconds;
            cout << "Time elapsed(in milliseconds): " << elapsedSeconds << endl; // сколько заняло секунд
        }
        // вычисляем среднее время итераций
        double everageTime = (time[0] + time[1] + time[2] + time[3] + time[4])/5;
        cout << endl << "Time spent (average): " << everageTime << endl;
    }

    // included Exersice_2  Определение какой элемент наиболее близок к числу x в масиве n.
    {
    // size_t n = 5;
    // size_t comparisionAll = 0;
    // string filename = "results.txt";
    // ofstream outputFile(filename);

    //     // int
    // int *arr = new int[n]{10, 20, 35, 45, 50};
    // int x = 11;  // Предположим, что нам нужно найти ближайшее число к 38

    // int closest = find_closest(arr, n, x, comparisionAll);
    // print_array(arr, n);

    // outputFile, cout << "The closest number to " << x << " in the array is " << closest 
    // << ". Comparisions at all: " << comparisionAll << endl;

    //     // double
    // double *_arr = new double[n]{10.4, 20.3, 35.3, 45.2, 43.4};
    // double _x = 38.0;  // Предположим, что нам нужно найти ближайшее число к 38

    // double _closest = find_closest(_arr, n, _x, comparisionAll);
    // print_array(_arr, n);

    // outputFile, cout << "The closest number to " << _x << " in the array is " << _closest 
    // << ". Comparisions at all: " << comparisionAll << endl;

    // outputFile.close();

    }

} // int main