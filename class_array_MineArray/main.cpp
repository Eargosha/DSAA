/// Автор: Eargosha

#include <iostream>
#include <cstdlib>
#include "array.h"

int main()
{
    srand(time(0)); // Время необходимо для рандома, библиотека подключена в main

    // АССЕРТИМСЯ ПО ВСЕМ ТОЧКАМ НАШЕГО СОЗНАНИЯ, Я УСТАЛ
    testSearch();
    testAddBackFront();
    testSort();
    testResize();
    testDeleteBackFront();

    // MineArray<int> b(3);
    // b[0] = 22;
    // b[1] = 33;
    // b[2] = 11;

    // b.addFront(123231);
    // b.addBack(123231);
    // b.deleteLast();
    // b.deleteFirts();

    // for (size_t i = 0; i < b.lenght(); i++)
    // {
    //     cout << b[i] << "\n";
    // }

    // cout << "gandon_meme_sound" << endl;
    // cout << b.search(11) << endl;
    // cout << "sortiiiir" << endl;

    // b.sort();
    // for (size_t i = 0; i < b.lenght(); i++)
    // {
    //     cout << b[i] << "\n";
    // }

    // b.resize(6);
    // b[5] = 777;
    // b.add_back(696969);

    // for (size_t i = 0; i < b.lenght(); i++)
    // {
    //     cout << b[i] << "\n";
    // }

    // cout << "gandon" << endl;

    // b.resize(2);
    // b[1] = 909090909;
    // b.add_back(696969);

    // for (size_t i = 0; i < b.lenght(); i++)
    // {
    //     cout << b[i] << "\n";
    // }
}
