/// Автор: Eargosha

#include <iostream>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include "my_array.h"
using namespace std;

// тип массивчика
template <typename Type>
class MineArray
{
private:
    // поля

    // указатель на начало массива
    Type *array;

    // индекс последней свободной ячейки
    size_t indexLastElement;

    // размер массива
    size_t size;

public:
    /// @brief  Конструкторик, но без параметров, выделить память
    MineArray()
    {
        size = 0;
        indexLastElement = 0;
        array = nullptr;
    }

    /// @brief  Конструкторик, но с параметрами, даем ему вот такоооой вот размерчик
    MineArray(size_t _size, const Type &value = 0)
    {
        if (_size > 0)
        {
            size = _size;
            indexLastElement = _size;
            array = new Type[size];
            for (size_t i = 0; i < size; i++)
            {
                array[i] = value;
            }
        }
        else
            throw invalid_argument("Invalid size value " + to_string(_size));
    }

    /// @brief Перегрузка оператора [] для доступа к определенным элементам массива
    /// Средний: O(1)
    Type &operator[](size_t index)
    {
        if (index < size)
        {
            return array[index];
        }
        else
            throw invalid_argument("Invalid index value");
    }

    /// @brief Изменяет размер массива в большую сторону и меньшую
    /// @param new_size Новый размер массива, может быть меньше или больше изначального
    /// Средний: O(n)
    void resize(size_t new_size)
    {
        Type *new_array = new Type[new_size];

        // Копирование элементов из старого массива в новый
        size_t elementsToCopy = min(new_size, size);

        copy(array, array + elementsToCopy, new_array);

        delete[] array; // Освобождение вообще старого массива, в котором лежали старые значения, что потерялись в памяти

        array = new_array; // записываем новые значения в массив

        indexLastElement = new_size;
        size = new_size * 2;
    }

    /// @brief Размер|длинная массива
    /// @return Возвращает размер массива типа size_t
    /// Средний: O(1)
    size_t lenght() const
    {
        return indexLastElement;
    }

    /// @brief Добавляет элемент в массив в конец
    /// @param new_member Элемент, что нужно добавить в массив
    /// Средний: О(1) | Худший: O(n)
    void addBack(Type new_member)
    {
        if (indexLastElement < size)
        {
            array[indexLastElement] = new_member;
            indexLastElement++;
        }
        else
        {
            resize(indexLastElement);
            array[indexLastElement] = new_member;
            indexLastElement = indexLastElement + 1;
        }
    }

    /// @brief Добавление элемента в начало
    /// @param new_member то что добавляем
    /// Средний: О(n)
    void addFront(Type new_member)
    {
        // если есть место то просто работаем
        if (indexLastElement < size)
        {
            // Сдвигаем все элементы "вправо"
            copy(array, array + size - 1, array + 1);

            array[0] = new_member;
            size++;
            indexLastElement++;
        }
        // иначе начинаем увеличивать массив и работать
        else
        {
            resize(indexLastElement);
            // Сдвигаем все элементы "вправо"
            copy(array, array + size - 1, array + 1);

            array[0] = new_member;
            size++;
            indexLastElement++;
        }
    }

    /// @brief Удаляет последний элемент массива
    /// Средний: O(1)
    void deleteLast()
    {
        if (indexLastElement >= 0)
        {
            copy(array - 1, array - indexLastElement, array);
            indexLastElement -= 1;
        }
        else
        {
            throw invalid_argument("This array is already empty!");
        }
        // Если размер в четыре раза меньше емкости, уменьшаем емкость в 2 раза
        if (size <= (indexLastElement / 4))
        {
            this->resize(indexLastElement / 2);
        }
    }

    /// @brief Удаление первого элемента массива
    /// Средний: O(n)
    void deleteFirts()
    {
        if (indexLastElement >= 0) // движемся, если не пусто
        {
            copy(array + 1, array + indexLastElement, array);
            indexLastElement -= 1;
        }
        else // если массив пустой, выбрасываемся в окно
        {
            throw invalid_argument("This array is already empty!");
        }
        // Если размер в четыре раза меньше емкости, уменьшаем емкость в 2 раза
        if (size <= (indexLastElement / 4))
        {
            this->resize(indexLastElement / 2);
        }
    }

    /// @brief Ищет элемент findThis в массиве с помощью Sequatial search
    /// @param findThis То, что ищем
    /// @return Возращает индекс найденного элемента или -1, если не нашел :(
    /// Средний: O(n)
    long long search(Type findThis)
    {
        return sequential_search(array, indexLastElement, findThis);
    }

    /// @brief Сортировка массива методом Merge sortik по возрастанию
    /// Средний: O(n log n)
    void sort()
    {
        // звоним функции из другого файлика, фу фуф уф
        merge_sort(array, 0, indexLastElement - 1);
    }

    /// Перезапись оператора приравнивания на оператор глубокого копирования
    /// O(n)
    MineArray &
    operator=(const MineArray<Type> &other)
    {
        if (this != &other)
        {
            if (array != nullptr)
                delete[] array; // освобождение памяти
            // копирование
            size = other.size;
            indexLastElement = other.indexLastElement;
            array = new Type[indexLastElement];
            memcpy(array, other.array, other.size * sizeof(Type));
        }
        return *this;
    }

    /// @brief Деструкторик обьектика классика
    ~MineArray()
    {
        if (array = nullptr)
        {
            delete array;
        }
        else
        {
            delete[] array;
        }
    }
};

/// @brief Тест метода Sort
void testSort()
{
    MineArray<int> arr(5);
    arr[0] = 11;
    arr[1] = 44;
    arr[2] = 22;
    arr[3] = 33;
    arr[4] = 55;

    arr.sort();

    assert(arr[0] == 11);
    assert(arr[1] == 22);
    assert(arr[2] == 33);
    assert(arr[3] == 44);
    assert(arr[4] == 55);

    // Дополнительные проверки для обработки специфических случаев
    // Проверка при сортировке массива с одним элементом
    MineArray<int> arrSingle(1);
    arrSingle[0] = 100;
    arrSingle.sort();
    assert(arrSingle[0] == 100);

    // Проверка при сортировке массива, где все элементы равны
    MineArray<int> arrEqual(3);
    arrEqual[0] = 5;
    arrEqual[1] = 5;
    arrEqual[2] = 5;
    arrEqual.sort();
    assert(arrEqual[0] == 5);
    assert(arrEqual[1] == 5);
    assert(arrEqual[2] == 5);
};

/// @brief Тест метода Searhc
void testSearch()
{
    MineArray<int> arr_int(5);
    for (size_t i = 0; i < 5; i++)
    {
        arr_int[i] = i;
    }
    assert(arr_int.search(3) == 3);  // успешный поиск элемента в массиве
    assert(arr_int.search(6) == -1); // нет элемента

    MineArray<double> arr_double(5);
    for (size_t i = 0; i < 5; i++)
    {
        arr_double[i] = i * 0.1;
    }
    assert(arr_double.search(0.1) == 1); // успешный поиск элемента в массиве

    // Дополнительные проверки для случаев, когда массив пустой
    // Проверим случай, когда элемент находится в середине массива
    MineArray<int> mid_arr_int(5);
    mid_arr_int[0] = 10;
    mid_arr_int[1] = 20;
    mid_arr_int[2] = 30;
    mid_arr_int[3] = 40;
    mid_arr_int[4] = 50;
    assert(mid_arr_int.search(30) == 2); // успешный поиск элемента в середине массива

    // Проверим случай, когда элемент находится на границе массива
    MineArray<int> border_arr_int(5);
    border_arr_int[0] = 10;
    border_arr_int[1] = 20;
    border_arr_int[2] = 30;
    border_arr_int[3] = 40;
    border_arr_int[4] = 50;
    assert(border_arr_int.search(50) == 4); // успешный поиск элемента на границе массива
};

/// @brief Тест метода Add
void testAddBackFront()
{
    MineArray<int> arr(2); // 1 2
    arr.addBack(1231);     // 3
    arr.addFront(212312);  // 4
    arr.addBack(31231230); // 5
    assert(arr.lenght() == 5);

    assert(arr[0] == 212312);
    assert(arr[3] == 1231);
    assert(arr[4] == 31231230);
    // и addFront addBack работает нормально
};

/// @brief Тест метода Resize
void testResize()
{
    MineArray<int> arr(3);
    arr.resize(6);
    assert(arr.lenght() == 6);

    arr[0] = 123;
    arr[1] = 321;
    // Проверка изменения размера на меньшее значение
    arr.resize(2);
    assert(arr.lenght() == 2);
    assert(arr[0] == 123); // Проверка, что первый элемент не изменился
    assert(arr[1] == 321); // Проверка, что второй элемент не изменился
}

/// @brief Тест метода Delete
void testDeleteBackFront()
{
    MineArray<int> arr(3);
    arr.deleteLast();
    assert(arr.lenght() == 2);
    arr.deleteFirts(); // delete from the end
    assert(arr.lenght() == 1);
}