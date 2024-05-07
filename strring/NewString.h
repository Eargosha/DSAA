// Author: Eargosha

#include <iostream>
#include <cassert>

/// @brief Самописный класс String
class NewString
{

private:
    /// @brief Массив символов - сама строка
    char *str;
    /// @brief Размер строки
    int size;

    /// @brief Метод копирования массива символов user_input в str обьект, куда копируем
    /// @param user_input То, что копируется в обьект
    void copy(const char *user_input)
    {
        size = 0;
        while (user_input[size] != '\0')
        {
            size++;
        }
        str = new char[size + 1];
        for (int i = 0; i < size; i++)
        {
            str[i] = user_input[i];
        }
        str[size] = '\0';
    }

public:
    /// Конструкторы ///
    /// @brief Конструктор без параметров
    NewString()
    {
        str = new char[1];
        str[0] = '\0';
        size = 0;
    }

    /// @brief Конструктор копирования
    /// @param s То, что нужно скопировать
    NewString(const char *s)
    {
        copy(s);
    }

    /// @brief Деструктор для всего этого дела
    ~NewString()
    {
        delete[] str;
    }

    /// Некоторые операторы ///
    /// @brief Доступ к строке по индексу, перегрузка оператора []. Изменение по индексу
    char &operator[](int index)
    {
        return str[index];
    }
    /// @brief Доступ к строке по индексу, перегрузка оператора []. Чтение по индексу
    char operator[](int index) const
    {
        return str[index];
    }

    /// @brief Присваивание строки, перегрузка оператора =
    /// @param user_input То, что присваиваем выбранному обьекту
    /// @return Возращает обьект типа NewString, нужно, если пользователю вздумается сделать обьект_1 = обьект_1
    NewString &operator=(const NewString &user_input)
    {
        // Если это НЕ ситуация обьект_1 = обьект_1
        if (this != &user_input)
        {
            delete[] str;
            copy(user_input.str);
        }
        // Иначе
        return *this;
    }

    /// @brief Обьединение обьекта NewString с обьектом NewString
    /// @param user_input То, с чем обьединяется обьект
    /// @return Возращает обьект типа NewString
    NewString operator+(const NewString &user_input) const
    {
        NewString temp;
        // Обьявляем результат - temp
        temp.size = size + user_input.size;
        temp.str = new char[temp.size + 1];
        int i = 0;
        // Вставляем массив сначала с первой строки
        for (; i < size; i++)
        {
            temp.str[i] = str[i];
        }
        // Теперь со второй
        for (int j = 0; j < user_input.size; j++, i++)
        {
            temp.str[i] = user_input.str[j];
        }
        temp.str[temp.size] = '\0';
        return temp;
    }

    /// NewString ввод/вывод ///
    // `friend` используется для предоставления доступа другим функциям или классам к приватным и защищенным членам класса.
    // В данном случае, операторы `<<` и `>>` перегружаются как дружественные функции класса `NewString`

    /// @brief Перегруженный оператор для ввода объекта класса NewString из потока.
    /// @param is Поток ввода.
    /// @param s Объект класса NewString, в который требуется считать строку.
    /// @return Поток ввода после считывания строки.
    friend std::istream &operator>>(std::istream &is, NewString &s)
    {
        // Считываем строку из потока до символа конца строки или конца файла
        // и сохраняем ее в буфер.
        std::string buffer;
        std::getline(is, buffer);

        // Освобождаем ресурсы предыдущей строки объекта s.
        delete[] s.str;

        // Выделяем память под новую строку в объекте s.
        s.size = buffer.size();
        s.str = new char[s.size + 1]; // +1 для символа нуль-терминатора.

        // Копируем содержимое буфера в строку объекта s.
        std::copy(buffer.begin(), buffer.end(), s.str);

        // Устанавливаем нуль-терминатор в конце строки.
        s.str[s.size] = '\0';

        return is; // Возврат потока ввода для цепочки операций ввода.
    }

    /// @brief Перегруженный оператор для вывода объекта класса NewString в поток.
    /// @param os Поток вывода.
    /// @param s Объект класса NewString, который требуется вывести.
    /// @return Поток вывода после вывода объекта.
    friend std::ostream &operator<<(std::ostream &os, const NewString &s)
    {
        for (int i = 0; i < s.size; i++)
        {
            os << s.str[i];
        }
        return os;
    }

    /// Некоторые методы ///

    /// @brief Длина строки
    /// @return Значение size_t - длина строки
    size_t count() const
    {
        return size;
    }

    /// @brief Префикс функция для подстроки (целочисленная функция от j-ого символа образца)
    /// Префиксная функция для каждого символа шаблона хранит длину наибольшего собственного префикса, который также является суффиксом.
    /// @param prefix_function Массив для хранения значений префиксной функции
    void prefixFunction(int *prefix_function) const
    {
        int m = count(); // Получаем длину строки
        if (m == 1)
        {
            prefix_function[0] = 0; // Для строки длины 1 префиксная функция равна 0
            return;
        }
        prefix_function[0] = 0; // Для первого символа префиксная функция равна 0
        int j = 0;
        for (int i = 1; i < m; i++)
        {
            while (j > 0 && str[i] != str[j])
            {
                j = prefix_function[j - 1]; // Переходим на следующий элемент префиксной функции
            }
            if (str[i] == str[j])
            {
                j++; // Увеличиваем j, если символы совпадают
            }
            prefix_function[i] = j; // Записываем значение префиксной функции для i-го символа
        }
    }

    /// @brief Функция реализует алгоритм Кнута-Морриса-Пратта (KMP) для поиска подстроки в строке, используя префиксную функцию - prefixFunction для эффективного перехода в случае несовпадения символов.
    /// @param user_input Подстрока, по которой происходит поиск
    /// @return Возращает индекс позиции в строке, где начинается найденная подстрока ИЛИ -1, если та не найдена.
    int kmpSearch(const NewString &user_input) const
    {
        int m = user_input.count(); // Длина шаблона
        int n = count();            // Длина строки

        // Обработка случая пустого шаблона
        if (m == 0)
        {
            return 0;
        }

        // Создание префиксной функции для шаблона
        int *prefix_function = new int[m];
        user_input.prefixFunction(prefix_function);

        int i = 0, j = 0;
        while (i < n)
        {
            if (str[i] == user_input[j])
            {
                i++;
                j++;
                if (j == m)
                {
                    // Шаблон найден
                    delete[] prefix_function;
                    return i - j;
                }
            }
            else
            {
                if (j != 0)
                {
                    j = prefix_function[j - 1]; // Переход к следующему элементу префиксной функции
                }
                else
                {
                    i++; // Если j == 0, то просто переходим к следующему символу в строке
                }
            }
        }

        delete[] prefix_function;
        return -1; // Шаблон не найден
    }

    /// Операторы сравнения всякие ///

    /// @brief Проверка на равенство строк
    /// @param user_input С чем сравнивать
    /// @return true - если сравнение прошло, иначе false
    bool operator==(const NewString &user_input) const
    {
        if (size != user_input.size)
        {
            return false;
        }
        for (int i = 0; i < size; i++)
        {
            if (str[i] != user_input.str[i])
            {
                return false;
            }
        }
        return true;
    }

    /// @brief Проверка на неравенство строк
    /// @param user_input С чем сравнивать
    /// @return true - если сравнение прошло, иначе false
    bool operator!=(const NewString &user_input) const
    {
        return !(*this == user_input);
    }

    /// @brief Оператор сравнения больше
    /// @param user_input С чем сравнивать
    /// @return true - если сравнение прошло, иначе false
    bool operator>(const NewString &user_input) const
    {
        int minLen = std::min(size, user_input.size);
        for (int i = 0; i < minLen; i++)
        {
            if (str[i] > user_input.str[i])
            {
                return true;
            }
            else if (str[i] < user_input.str[i])
            {
                return false;
            }
        }
        return size > user_input.size;
    }

    /// @brief Оператор сравнения меньше
    /// @param user_input С чем сравнивать
    /// @return true - если сравнение прошло, иначе false
    bool operator<(const NewString &user_input) const
    {
        int minLen = std::min(size, user_input.size);
        for (int i = 0; i < minLen; i++)
        {
            if (str[i] < user_input.str[i])
            {
                return true;
            }
            else if (str[i] > user_input.str[i])
            {
                return false;
            }
        }
        return size < user_input.size;
    }

    /// @brief Оператор сравнения больше аль равно
    /// @param user_input С чем сравнивать
    /// @return true - если сравнение прошло, иначе false
    bool operator>=(const NewString &user_input) const
    {
        return !(*this < user_input);
    }

    /// @brief Оператор сравнения меньше аль равно
    /// @param user_input С чем сравнивать
    /// @return true - если сравнение прошло, иначе false
    bool operator<=(const NewString &user_input) const
    {
        return !(*this > user_input);
    }
};

/// @brief Тестирование методов строк
void testMethods()
{
    // Тест метода length()
    NewString str1 = "goooD!";
    assert(str1.count() == 6);

    // Тест оператора []
    NewString str2 = "world";
    assert(str2[0] == 'w');
    assert(str2[4] == 'd');
    char &ref = str2[3];

    // Тест оператора =
    NewString str3;
    str3 = str1;
    assert(str3 == "goooD!");
    str3 = str2;
    assert(str3 == "world");

    // Тест оператора +
    NewString str4 = str1 + str2;
    assert(str4 == "goooD!world");
}

/// @brief Тестирование всех сравнений (какие есть)
void testComparisons()
{
    NewString str1 = "rawr~";
    NewString str2 = "sobaka";
    NewString str3 = "rawr~";
    NewString str4 = "Rawr~";
    NewString str5 = "";
    NewString str6 = "~";

    // !=
    assert(str1 != str2);
    assert(!(str1 != str3));
    assert(str1 != str4);
    assert(str5 != str6);

    // ==
    assert(str1 == str3);
    assert(!(str1 == str2));
    assert(!(str1 == str4));
    assert(str5 == "");


    // <
    assert(str1 < str2);
    assert(!(str1 < str3));
    assert(str5 < str1);

    // >
    assert(str2 > str1);
    assert(!(str1 > str3));
    assert(str1 > str5);

    // <=
    assert(str1 <= str2);
    assert(str1 <= str3);
    assert(str5 <= str1);

    // >=
    assert(str2 >= str1);
    assert(str1 >= str3);
    assert(str1 >= str5);
}

/// @brief Тестирование KMPSearch
void testKMPSearch()
{
    NewString text("This is a sample text");
    NewString pattern1("sample");
    NewString pattern2("hello");

    // Проверка для найденного шаблона
    int index1 = text.kmpSearch(pattern1);
    assert(index1 == 10); // Шаблон "goooD!" найден на позиции 10

    // Проверка для ненайденного шаблона
    int index2 = text.kmpSearch(pattern2);
    assert(index2 == -1); // Шаблон "hello" не найден

    // Проверка для пустого шаблона
    NewString emptyPattern("");
    int index3 = text.kmpSearch(emptyPattern);
    assert(index3 == 0); // Пустой шаблон найден на позиции 0

    // Проверка для текста, равного шаблону
    NewString pattern3("This is a sample text");
    int index4 = text.kmpSearch(pattern3);
    assert(index4 == 0); // Шаблон равен тексту, найден на позиции 0

    // Проверка для пустого текста
    NewString emptyText("");
    int index5 = emptyText.kmpSearch(pattern1);
    assert(index5 == -1); // В пустом тексте шаблон не найден

    // Проверка для очень длинного текста и шаблона
    NewString longText("This is a very long text to test the KMP search algorithm...");
    NewString longPattern("very long text to test");
    int index6 = longText.kmpSearch(longPattern);
    assert(index6 == 10); // Длинный шаблон найден на позиции 10
}
