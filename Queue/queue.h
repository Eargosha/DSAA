#include "listik.h"
#include <cassert>

/// @brief Класс Queue есть представитель структуры данных - очередь (FIFO)
/// @tparam Type тип элементов стека
template <typename Type>
// Воспользуемся прошлым классом и сделаем наследование от двусвязного списка
class Queue : private DoublyLinkedList<Type>
{
public:

    /// @brief Конструктор по умолчанию
    Queue() {}

    /// @brief Деструктор
    ~Queue() {}

    /// @brief Добавление элемента в очередь
    /// @param element Добавляемый элемент
    /// BigO: O(1)
    void enqueue(Type element)
    {
        this->addFront(element);
    }

    /// @brief Удаление элемента из очереди, удалится первый вошедший, вернется значение по умолчанию для Type
    /// BigO: O(1)
    Type dequeue()
    {
        // Если стечек пуст
        if (this->isEmpty())
        {
            return Type(); //вернется значение по умолчанию для Type
        }
        // ИНАЧЕ МЯСО
        Type val = this->get_nodule(this->length()-1)->data;
        this->deleteBack();
        return val;
    }

    /// @brief Проверяет пуста ли очередь
    /// @return Значение true||false
    /// BigO: O(1)
    bool isEmpty() {
        bool empty = false;
        if (this->length() == 0) 
            empty = true;
        return empty; 
    }

    /// @brief Вернет размер очереди
    /// @return size_t - размер
    size_t size() {
        return this->length();
    }

    /// @brief Вернет значение конца очереди
    /// @return Type
    Type getTailData() {
        return this->get_nodule(0)->data;
    }

    /// @brief Вернет значение начала очереди
    /// @return Type
    Type getHeadData() {
        return this->get_nodule(this->size()-1)->data;
    }

    /// @brief Возращает элемент очереди, готовый к выходу из нее
    /// @return Элемент, если список пуст, то 0
    /// BigO: O(1)
    Type peek() {
        if (this->isEmpty())
        {
            return 0;
        }
        return this->get_nodule(this->length()-1)->data;
    }
};


/// @brief Функция тестирования метода enqueue
void testEnqueue() {
    Queue<int> queue;

    queue.enqueue(1);
    assert(queue.getTailData() == 1);

    queue.enqueue(2);
    assert(queue.getTailData() == 2);
    queue.enqueue(3);

    assert(queue.getHeadData() == 1);
    assert(queue.getTailData() == 3);
}

/// @brief Функция тестирования метода dequeue
void testDequeue() {
    Queue<int> queue;

    //добавляем
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    //проверяем
    queue.dequeue();
    assert(queue.size() == 2);

    assert(queue.getTailData()  == 3);

    queue.dequeue();
    assert(queue.size() == 1);
    assert(queue.getTailData()  == 3);

    assert(queue.dequeue() == 3);
    assert(queue.size() == 0);

    //проверка на ассерт пустой очереди double
    Queue<double> queueEmpty;
    assert(queueEmpty.dequeue() == 0.0);

    //проверка на ассерт пустой очереди строк
    Queue<string> queueEmpty2;
    assert(queueEmpty2.dequeue() == "");
}

/// @brief Тестирование функции peek
void testPeek() {
    Queue<int> queue;

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    assert(queue.peek() == 1);

    queue.dequeue();
    assert(queue.peek() == 2);

    queue.enqueue(123);
    assert(queue.peek() == 2);
}

/// @brief Тестик для isEmpty
void testIsEmpty() {
    Queue<int> queue;
    assert(queue.isEmpty());

    queue.enqueue(123);
    assert(!queue.isEmpty());

    queue.dequeue();
    assert(queue.isEmpty());
}



/// @brief Функция тестирования класса Stack
void testQueue() {
    testEnqueue();
    testDequeue();
    testIsEmpty();
    testPeek();
}