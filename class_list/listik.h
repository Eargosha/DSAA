/// Autor: Eargosha

#include <iostream>
#include <sstream>
#include <cassert>
#include <algorithm>

using namespace std;

/// @brief Классик Nodule есть узелок двусвязного списка
/// @tparam Type тип узла
template <typename Type>
class Nodule
{
public:
    /// Данные, сто хранятся в узелке
    Type data;
    /// Указатель на предыдущей узел в списке
    Nodule<Type> *prev;
    /// Указатель на следующий узел в списке
    Nodule<Type> *next;

    /// Конструкторы созданы методом инициализации членов класса через список инициализации конструктора в C++

    /// @brief Конструктор по умолчанию(пустенько)
    Nodule() : prev(nullptr), next(nullptr), data(Type())
    {
    }

    /// @brief Конструктор с данными и обеими указателями
    /// @param data_ - данные узла
    /// @param prev_ - указатель на предыдущий узел
    /// @param next_ - указатель на следующий узел
    Nodule(const Type &data_, Nodule<Type> *prev_, Nodule<Type> *next_)
        : data(data_), prev(prev_), next(next_)
    {
    }

    /// @brief Конструктор только с данными, указатели prev и next смотрят в null
    /// @param data_ - данные узла
    Nodule(const Type &data_) : data(data_), prev(nullptr), next(nullptr)
    {
    }

    /// @brief Конструктор копирования
    Nodule(const Nodule<Type> &other)
        : data(other.data), prev(nullptr), next(nullptr) // пока что nullptr
    {
        if (other.prev != nullptr)
        {
            // доступ через указатель, потому что хотим копировать, а не пальцем тыкать!
            prev = new Nodule(other.prev->data);
        }
        if (other.next != nullptr)
        {
            // доступ через указатель, потому что хотим копировать, а не пальцем тыкать!
            next = new Nodule(other.next->data);
        }
    }

    /// @brief Конструктор перемещения
    /// @param other То, что перемещаем
    Nodule(Nodule<Type> &&other)
        : data(other.data), prev(other.prev), next(other.next) // перемещаем указатели на пред и след узелки
    {
        // чистим чистим чистим
        other.prev = nullptr;
        other.next = nullptr;
    }

    /// @brief Оператор копирования
    /// @param other То, что копируем
    Nodule<Type> &operator=(const Nodule<Type> &other)
    {
        if (this != &other) // Проверка на самоприсваивание
        {
            // не даем памяти течь, она не жижа
            delete prev;
            delete next;

            // копируем все правильно
            data = other.data;
            if (other.prev != nullptr)
            {
                // доступ через указатель, потому что хотим копировать, а не пальцем тыкать!
                prev = new Nodule(other.prev->data);
            }
            if (other.next != nullptr)
            {
                // доступ через указатель, потому что хотим копировать, а не пальцем тыкать!
                next = new Nodule(other.next->data);
            }
        }
        return *this;
    }

    /// @brief Оператор перемещения
    Nodule<Type> &operator=(Nodule<Type> &&other)
    {
        if (this != &other) // Проверка на самоприсваивание
        {
            data = other.data;
            prev = other.prev;
            next = other.next;

            other.prev = nullptr;
            other.next = nullptr;
        }
        return *this;
    }

    /// @brief Деструктор
    ~Nodule()
    {
        /// Удаляем указатели на предыдущий и следующий узлы
        if (prev != nullptr && next != nullptr)
        {
            prev = nullptr;
            next = nullptr;
        }
    }
};

/*              Done:
    -Конструкторы правила 5
    -Методы: copy(глубоко), to_string, get_nodule

    -Поиск элемента = find = average O(n)
    -Сортировка списка = sort = average O(n)
    -Очистка списка = clearSpisok = average O(n)

    -Вставка элементика в начало = addFront = average O(1)
    -Вставка элементика в серединку = addInList = average O(n)
    -Вставка элементика в конец = addBack = average O(n)

    -Удаление элементика в начале = deleteFront = average O(1)
    -Удаление элементика в серединке = deleteInList = average O(n)
    -Удаление элементика в конце = deleteBack = average O(n)

    -Получение размера = length = average O(n)


                TO CHECK:
    -Обьединение списков (конкатенация) = concatinateLists = average O(1 || n??)
    -Исправил delelteInList
    -Спроси про комменты
    -Тест ассертами

*/

/// @brief Класс DoublyLinkedList есть двусвязный список
/// @tparam Type тип данных двусвязного списка
template <typename Type>
class DoublyLinkedList
{
private:
    // Указатель на головку списка
    Nodule<Type> *head;
    // Указатель на хвостик списка
    Nodule<Type> *tail;
    // Размерчик списка
    size_t size;

public:
    //////////////////////////////////////////5 конструкторов и там операторы есть/////////////////////////////////////

    /// @brief Конструктор по умолчанию, пустенький
    DoublyLinkedList()
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    /// @brief Создает и заполняет список значениями value
    /// @param n Размер списка
    /// @param value То, чем заполняется список
    DoublyLinkedList(size_t n, const Type &value)
    {
        for (size_t i = 0; i < n; i++)
        {
            addBack(value);
        }
    }

    /// @brief Конструктор копирования
    /// @param other То, что копируем
    DoublyLinkedList(const DoublyLinkedList &other)
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
        // Копируем элементы из другого списка.
        copyIn(other);
    }

    /// @brief Конструктор перемещения
    /// @param other То, что перемещам, собстна
    DoublyLinkedList(DoublyLinkedList &&other)
    {
        // Перемещаем элементы из другого списка.
        head = other.head;
        tail = other.tail;
        size = other.size;
        other.forget();
    }

    /// @brief Оператор присваивания, но копирует
    /// @param other Что копирует
    /// @return Сокпированное
    DoublyLinkedList &operator=(const DoublyLinkedList &other)
    {
        if (this == &other)
        {
            return *this;
        }

        // Очищаем текущий список.
        clearList();

        // Копируем элементы из другого списка.
        copyIn(other);

        return *this;
    }

    /// @brief Оператор присваивания, но перемещает
    /// @param other Что перемещает
    /// @return Перемещенное
    DoublyLinkedList &operator=(DoublyLinkedList &&other)
    {
        if (this == &other)
        {
            return *this;
        }

        // Очищаем текущий список.
        clearList();

        // Перемещаем элементы из другого списка.
        head = other.head;
        tail = other.tail;
        size = other.size;

        other.forget();

        return *this;
    }

    /// @brief Деструктор
    ~DoublyLinkedList()
    {
        // Чистим чистим чистим!
        clearList();
    }

    //////////////////////////////////////////Без категорииииииииииии/////////////////////////////////////

    /// @brief concatinateWith соединяет два списка, удаляет тот список, что присоединяли
    /// @param other тот, что присоединяют
    void concatinateWith(DoublyLinkedList<Type> other)
    {
        // Проверяем, является ли список "other" пустым
        if (other.head == nullptr)
        {
            return; // Если список "other" пуст, выходим из функции
        }

        // Если текущий список пуст, присваиваем ему значения из списка "other"
        if (head == nullptr)
        {
            head = other.head;
            tail = other.tail;
        }
        else
        {
            // Если текущий список не пуст, добавляем элементы из "other" в конец текущего списка
            tail->next = other.head; // Устанавливаем указатель на следующий элемент последнего элемента текущего списка
            other.head->prev = tail; // Устанавливаем указатель на предыдущий элемент первого элемента списка "other"
            tail = other.tail;       // Обновляем указатель на хвост текущего списка
        }

        size += other.size; // Увеличиваем размер текущего списка на размер списка "other"

        // Обнуляем указатели и размер списка "other" для предотвращения непреднамеренных изменений
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }

    //       TO CHECK:
    // -Обьединение списков (конкатенация) = concatinateLists = average O(1 || n??)
    // -Исправил delelteInList
    // -Спроси про комменты
    // -Тест ассертами

    /// @brief Глубокое копирование списка
    /// @param other То, что копируем
    void copyIn(const DoublyLinkedList<Type> &other)
    {
        // Место освободим с прохода, а то застрянет
        clearList();

        // Итерационный узелочек
        Nodule<Type> *current = other.head;
        while (current != nullptr)
        {
            addBack(current->data);
            current = current->next;
        }
    }

    /// @brief Возвращает размер списка
    /// @return Размер списка
    size_t length() const
    {
        return size;
    }

    /// @brief Выводит список в строку
    /// @return Строку с списком вида
    string to_string() const
    {
        // Создаем строковый поток, куда будем ложить содержимое списка
        stringstream spisok_stroka;
        // Ну как в питоне сделаю начало
        spisok_stroka << "[";

        // Создадим узелочек, который будет вертеть туда сюда и передадим в него голову списка
        Nodule<Type> *current = head;
        // Пока список не кончится, блин, все когда-нибудь кончаются, даже списки...
        while (current != nullptr)
        {
            // Но не будем печалиться и начнем выводить информацию!
            spisok_stroka << current->data;
            // А затем смотреть, если дальше есть обьект, то выводить разделитель, чтобы все было красиво!!!
            if (current->next != nullptr)
            {
                spisok_stroka << " ";
            }
            // А тут мы приводим наш список к концу его существования peppeDispaire
            current = current->next;
        }

        // Ну как в питоне сделаю конец (я почти то написал)
        spisok_stroka << "]";
        // преобразуем поток букавак в строку
        return spisok_stroka.str();
    }

    /// @brief Возращает узелочек по местечку его прибывания в списке по ПМЖ
    /// @param place Местечко, откуда смотрим на узелок
    /// @return Узелок класса Nodule
    Nodule<Type> *get_nodule(size_t place)
    {
        // Проверка
        if (place < 0 || place >= size)
        {
            throw out_of_range("Invalid index");
        }

        Nodule<Type> *current = head;

        for (size_t i = 0; i < place; i++)
        {
            current = current->next;
        }
        // Просматриваем и возращаем
        return current;
    }

    /// @brief Сортировка массива по возрастанию пузырьком
    void sort()
    {
        if (size <= 1)
        {
            return;
        }

        // задаем два узла для сравнения
        Nodule<Type> *current = head;
        Nodule<Type> *nextNode = nullptr;

        while (current != nullptr)
        {
            nextNode = current->next;

            while (nextNode != nullptr)
            {
                // Сравнение текущего элемента с следующим элементом
                if (current->data > nextNode->data)
                {
                    // Обмен значениями текущего и следующего элементов
                    swap(current->data, nextNode->data);
                }
                // Переходим к след узлу
                nextNode = nextNode->next;
            }
            // Также переходим к след узлу
            current = current->next;
        }
    }

    /// @brief Находит узелок с значением value
    /// @param value Вот этим значением
    /// @return Возращает узел с этим значением
    Nodule<Type> *find(Type value)
    {
        Nodule<Type> *current = head;
        while (current != nullptr)
        {
            if (current->data == value)
            {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    /// @brief Чистим, чистим списочек
    void clearList()
    {
        // Удаляем все узлы из списка.
        while (head != nullptr)
        {
            Nodule<Type> *nextNode = head->next;
            delete head;
            head = nextNode;
        }

        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    //////////////////////////////////////////Вставочки/////////////////////////////////////

    /// @brief Вставка элемента в начало
    /// @param value То, что пихаем
    void addFront(Type value)
    {
        // Создаем новый узелочек
        Nodule<Type> *newNode = new Nodule<Type>(value);
        // Если список пустенький, то новый узел становится узлом головы, хвостика там например
        if (head == nullptr)
        {
            head = tail = newNode;
        }
        // Иначе, вот он, добавляем новый узел в начало списка
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        // Увеличиваем размер, а чего не скажу 🫢
        size++;
    }

    /// @brief Вставка элемента в конец
    /// @param value То, что вставляем
    void addBack(Type value)
    {
        // Создаем то, что будем вставлять
        Nodule<Type> *newNode = new Nodule<Type>(value);

        // Если список пустой, то новый узел становится головой и хвостиком
        if (tail == nullptr)
        {
            head = tail = newNode;
        }
        else
        // Иначе! добавляем его в конец списка как и планировали
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    /// @brief Вставит ваш новый узел, содержащий value, после указанного узла node, можео считать вставкой в серединочку
    /// @param value То, что вставить нада
    /// @param node После чего вставить нада
    void addInList(Type value, Nodule<Type> *node)
    {
        // Если указанный узелок равен nullptr, кидаем его в конец списка, а то че это он
        if (node == nullptr)
        {
            addBack(value);
            return;
        }

        // Создаем тот узел, над которым эксперименты ставить будем
        Nodule<Type> *newNode = new Nodule<Type>(value);

        // Вставляем узелок после указанного
        newNode->next = node->next;
        if (node->next != nullptr)
        {
            node->next->prev = newNode;
        }
        else
        {
            tail = newNode;
        }
        node->next = newNode;
        newNode->prev = node;

        // Увеличиваем размер списка.
        size++;
    }

    //////////////////////////////////////////Удаленьица/////////////////////////////////////

    /// @brief Удаляет узел списка с его начала, вот так вот, без церемоний
    int deleteFront()
    {
        // Если список пуст, то кидаем ошибку
        if (head == nullptr)
        {
            // throw out_of_range("List is empty!");
            return 1;
        }

        // Береги голову, да да
        Nodule<Type> *temp = head;

        // Меняем голову, эх, какой же список был раньше...
        head = head->next;
        // Ну и тут кейсы просматриваем
        if (head != nullptr)
        {
            head->prev = nullptr;
        }
        else
        {
            tail = nullptr;
        }
        delete temp;
        size--;
        return 0;
    }

    /// @brief Удаляет узел с значением value из списка вашего, княже
    /// @param value То, что истребить надо
    int deleteInList(Type value)
    {
        // Нечего удалять, ты че творишь?!
        if (head == nullptr)
        {
            return 1;
        }

        // Временный узел
        Nodule<Type> *temp = this->find(value);

        // Если временный узел пуст, то его нет в списке
        if (temp != nullptr)
        {
            // Смотрим, если головка, удаляем головку
            if (temp == head)
            {
                this->deleteFront();
            }
            // Смотрим, если хвостик, удаляем хвостик
            else if (temp == tail)
            {
                this->deleteBack();
            }
            else
            {
                // Иначе удаляем указанный узел из середины списка.
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
        }
        else
        {
            throw invalid_argument("There's no this value in this list!");
        }

        return 0;
        // Уменьшаем, а то большой слишком
        size--;
    }

    /// @brief Удаляет узел списка с его конца, вот так вот, без церемоний
    int deleteBack()
    {
        // Если списочек пустенький, кричим громко ошибкой
        if (tail == nullptr)
        {
            return 1;
        }

        // Хвостик временно запоминаем
        Nodule<Type> *temp = tail;

        // Меняем хвостик, эх, какой же список был раньше...
        tail = tail->prev;
        // Просматриваем кейсы
        if (tail != nullptr)
        {
            tail->next = nullptr;
        }
        else
        {
            head = nullptr;
        }
        delete temp;
        size--;
        return 0;
    }

    /// Класс итератора для двусвязного списка.
    ///
    /// Обеспечивает доступ к элементам списка,
    /// поддерживает операции итерации (перемещение по списку).
    class Iterator
    {
    private:
        /// Указатель на текущий узел списка.
        Nodule<Type> *currentNode;

    public:
        /// Конструктор, инициализирует итератор начальным узлом.
        ///
        /// @param node Указатель на узел, с которого начинать итерацию.
        Iterator(Nodule<Type> *node) : currentNode(node) {}

        /// Возвращает ссылку на данные текущего узла.
        ///
        /// @return Ссылка на данные текущего узла.
        Type &operator*() const { return currentNode->data; }

        /// Переход к следующему узлу в списке.
        /// Может быть брошено исключение out_of_range, если итератор не имет следующего элемента
        /// @return Ссылка на текущий объект итератора.
        Iterator &operator++()
        {
            return next();
        }

        /// Возвращает ссылку на данные текущего узла.
        ///
        /// @return Ссылка на данные текущего узла.
        Type &data() const 
        {
            return currentNode->data;
        }

        /// Переход к следующему узлу в списке.
        /// Может быть брошено исключение out_of_range, если итератор не имет следующего элемента
        /// @return Ссылка на текущий объект итератора.
        Iterator &next()
        {
            /// Проверяем, существует ли следующий узел.
            if (!hasNext())
            {
                /// Если следующий узел отсутствует, вызываем исключение.
                throw std::out_of_range("Итератор вышел за пределы списка");
            }
            /// Перемещаем указатель на следующий узел.
            currentNode = currentNode->next;
            /// Возвращаем ссылку на текущий объект итератора.
            return *this;
        }

        /// Проверяет, существует ли следующий узел в списке.
        ///
        /// @return true, если следующий узел существует, иначе false.
        bool hasNext() const 
        {
            /// Возвращаем true, если currentNode не равен nullptr.
            return currentNode != nullptr;
        }

        /// Оператор сравнения, проверяет, не совпадают ли два итератора.
        ///
        /// @param other Итератор, с которым сравнивается текущий.
        /// @return true, если итераторы указывают на разные узлы, иначе false.
        bool operator!=(const Iterator &other) const
        {
            /// Возвращаем true, если currentNode не равен currentNode другого итератора.
            return currentNode != other.currentNode;
        }

        /// Сбрасывает итератор в начало списка.
        ///
        /// @param head Указатель на головной узел списка.
        void reset(Nodule<Type> *head)
        {
            currentNode = head;
        }

        /// Оператор присваивания, копирует состояние другого итератора.
        ///
        /// @param other Итератор, состояние которого нужно скопировать.
        /// @return Ссылка на текущий объект итератора.
        Iterator &operator=(const Iterator &other)
        {
            /// Проверяем, не совпадают ли итераторы по адресу в памяти.
            if (this != &other)
            {
                /// Если итераторы не совпадают, копируем состояние.
                currentNode = other.currentNode;
            }
            /// Возвращаем ссылку на текущий объект итератора.
            return *this;
        }

        /// Проверяет, находится ли итератор в конце списка (nullptr).
        ///
        /// @return true, если итератор указывает на nullptr, иначе false.
        bool EndOfList() const
        {
            return currentNode == nullptr;
        }
    };

    /// Возвращает итератор, указывающий на начало списка.
    ///
    /// @param head Указатель на головной узел списка.
    /// @return Итератор, указывающий на начало списка.
    Iterator begin() const { return Iterator(head); }

    /// Возвращает итератор, указывающий на конец списка (nullptr).
    ///
    /// @return Итератор, указывающий на конец списка.
    Iterator end() const { return Iterator(nullptr); }
};
//////////////////////////////////////////Ассерты/////////////////////////////////////

/// Тест итератора
void testListIterator()
{
    // Создаем двусвязный список с элементами 1, 2, 3
    DoublyLinkedList<int> list;
    list.addBack(1);
    list.addBack(2);
    list.addBack(3);

    // Тестируем итератор
    auto it = list.begin();

    // Проверка начального состояния
    assert(*list.begin() == 1);
    assert(it != list.end());
    assert(!it.EndOfList());

    // Переход к следующему элементу
    ++it;
    assert(*it == 2);
    assert(it != list.end());
    assert(!it.EndOfList());

    // Переход к следующему элементу
    ++it;
    assert(*it == 3);
    assert(it != list.end());
    assert(!it.EndOfList());

    // Переход к концу списка
    ++it;
    assert((it != list.end()) == false);
    assert(it.EndOfList());

    // Проверка метода reset()
    it.reset(list.get_nodule(0));
    assert(*it == 1);
    assert(it != list.end());
    assert(!it.EndOfList());

    // Проверка оператора присваивания
    auto it2 = list.end();
    it = it2;
    assert((it != list.end()) == false);
    assert(it.EndOfList());

    // Проверка оператора !=
    assert(it != list.begin());
    assert(list.begin() != list.end());

    // Проверка исключения при выходе за пределы списка
    try
    {
        ++it;
        assert(false); // Должно произойти исключение
    }
    catch (const std::out_of_range &e)
    {
        // Исключение должно быть поймано
        assert(true);
    }

    // for_each: Выводит все элементы на экран
    for_each(list.begin(), list.end(), [](int &element)
             { cout << element << " "; });

    cout << endl;
    // For по коллекции 
    for (int value : list) {
        cout << value << ' ' << endl;
    }

    // For по коллекции 
    for (auto it = list.begin(); it != list.end(); ++it) {
        cout << *it << ' ' << endl;
    }

    cout << endl;

    // // any_of: Проверяет, есть ли в списке четные числа
    // bool hasEven = std::any_of(list.begin(), list.end(), [](int element)
    //                            { return element % 2 == 0; });
    // assert(hasEven);

    // // all_of: Проверяет, являются ли все элементы списка четными
    // bool allEven = std::all_of(list.begin(), list.end(), [](int element)
    //                            { return element % 2 == 0; });
    // assert(!allEven);

    // // none_of: Проверяет, нет ли в списке четных чисел
    // bool noEven = std::none_of(list.begin(), list.end(), [](int element)
    //                            { return element % 2 == 0; });
    // assert(!noEven);

    // // // transform: Умножает все элементы списка на 2
    // // std::transform(list.begin(), list.end(), list.begin(), [](int element)
    // //                { return element * 2; });
    // // assert(*list.begin() == 2);
    // // assert(*list.begin().next() == 4);
    // // assert(*list.begin().next().next() == 6);

    // // copy_if: Копирует четные числа из списка в новый список
    // DoublyLinkedList<int> evenList;
    // std::copy_if(list.begin(), list.end(), std::back_inserter(evenList), [](int element)
    //              { return element % 2 == 0; });
    // assert(evenList.length() == 1);
    // assert(*evenList.begin() == 4);
}

/// @brief тестирует AddFront
void testAddFront()
{
    DoublyLinkedList<int> list;

    // Тестирование добавления элемента в пустой список
    list.addFront(1);
    assert(list.length() == 1);
    assert(list.get_nodule(0)->data == 1);

    // Добавляем еще элементы в список
    list.addFront(2);
    list.addFront(3);

    // Тестирование добавления элементов в начало списка
    assert(list.length() == 3);
    assert(list.get_nodule(1)->data == 2);
}

/// @brief тестирует все Delete
void testDelete()
{
    DoublyLinkedList<int> list;

    // Тестирование добавления элемента в пустой список
    assert(list.deleteBack() == 1);
    assert(list.deleteFront() == 1);
    assert(list.deleteInList(23) == 1);

    list.addFront(1);
    assert(list.length() == 1);
    assert(list.get_nodule(0)->data == 1);

    list.deleteFront();
    assert(list.length() == 0);
}

/// @brief тестирует Find
void testFind()
{
    DoublyLinkedList<int> list;

    // Добавляем элементы в список
    list.addBack(1);
    list.addBack(2);
    list.addBack(3);

    // Тестирование поиска существующего элемента
    assert(list.find(2) != nullptr);

    // Тестирование поиска несуществующего элемента
    assert(list.find(5) == nullptr);
}

/// @brief тестирует Sort
void testSort()
{
    DoublyLinkedList<int> list;

    // Тестирование сортировки пустого списка
    list.sort();
    assert(list.length() == 0);

    // Добавляем элементы в список
    list.addBack(3);
    list.addBack(1);
    list.addBack(2);

    // Тестирование сортировки списка
    list.sort();
    assert(list.find(1)->data == 1);
    assert(list.find(2)->data == 2);
    assert(list.find(3)->data == 3);
}

// Тестирование класса
void allAsertTests()
{

    // тут некоторые методы выделил
    testSort();
    testAddFront();
    testFind();
    testDelete();
}
