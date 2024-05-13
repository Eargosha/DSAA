/// Autor: Eargosha

#include <iostream>
#include <sstream>
#include <cassert>

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
        if (place < 0 || place > size)
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
    void deleteFront()
    {
        // Если список пуст, то кидаем ошибку
        if (head == nullptr)
        {
            throw out_of_range("List is empty!");
            return;
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
    }

    /// @brief Удаляет узел с значением value из списка вашего, княже
    /// @param value То, что истребить надо
    void deleteInList(Type value)
    {
        // Нечего удалять, ты че творишь?!
        if (head == nullptr)
        {
            throw out_of_range("List is empty!");
            return;
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

        // Уменьшаем, а то большой слишком
        size--;
    }

    /// @brief Удаляет узел списка с его конца, вот так вот, без церемоний
    void deleteBack()
    {
        // Если списочек пустенький, кричим громко ошибкой
        if (tail == nullptr)
        {
            throw out_of_range("List is empty!");
            return;
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
    }
};
//////////////////////////////////////////Ассерты/////////////////////////////////////
// Тестирование класса

void testAddFront() {
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
    assert(list.get_nodule(2)->data == 3);
}

void testFind() {
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

void testSort() {
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


void allAsertTests()
{
                // Проверяем тут все кучей малой
    // Конструктор по умолчанию
    DoublyLinkedList<int> list1;
    assert(list1.length() == 0);

    // Конструктор, заполняющий список n элементами с значением value
    DoublyLinkedList<int> list2(5, 10);
    assert(list2.length() != 0);
    assert(list2.length() == 5);
    assert(list2.get_nodule(2)->data == 10);

    // Добавление элемента в начало списка
    list1.addFront(0);
    assert(list1.length() == 1);
    assert(list2.get_nodule(0)->data == 0);

    // Добавление элемента в конец списка
    list1.addBack(6);
    assert(list1.length() == 2);
    assert(list2.get_nodule(1)->data == 6);

    // Удаление последнего элемента из списка
    list1.deleteBack();
    assert(list1.length() == 1);

    // Удаление первого элемента из списка
    list1.deleteFront();
    assert(list1.length() == 0);

    // Вставка нового узла, содержащего data, после указанного узла node
    list1.addFront(2);
    list1.addInList(8, list1.find(2));
    assert(list1.length() == 1);
    assert(list2.get_nodule(0)->data == 2);
    assert(list2.get_nodule(1)->data == 8);

    // Склеивание двух списков
    list1.concatinateWith(list2);
    assert(list1.length() == 7);

    // Удаление указанного узла из списка
    list1.deleteInList(2);
    assert(list1.length() == 6);
    assert(list2.get_nodule(0)->data == 8);
    assert(list2.get_nodule(1)->data == 10);
                // тут некоторые методы выделил
    testSort();
    testAddFront();
    testFind();
    
}
