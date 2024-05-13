// Author: Eargosha

#include "queue.h"
#include <cassert>

template <typename Type>
/// <summary>
/// Класс DeQueue двусторонняя очередь, наследуется от обычной очереди
/// </summary>
class DeQueue : private Queue<Type>
{
public:
    /// @brief Добавление элемента в начало очереди F
    /// @param element Добавляемый элемент
    /// BigO: O(1)
    void pushFront(Type element)
    {
        this->enqueue(element);
    }

    /// @brief Добавление элемента в конец очереди E
    /// @param element Добавляемый элемент
    /// BigO: O(1)
    void pushBack(Type element)
    {
        this->addBack(element);
    }

    /// @brief Удаление элемента из конца очереди F
    /// @return Значение удаленного элемента, или значение по умолчанию для Type, если очередь пуста
    /// BigO: O(1)
    Type popBack()
    {
        return this->dequeue();
    }

    /// @brief Удаление элемента из начала очереди E
    /// @return Значение удаленного элемента, или значение по умолчанию для Type, если очередь пуста
    /// BigO: O(1)
    Type popFront()
    {
        // Если пусто
        if (this->isEmpty())
        {
            return Type(); // вернется значение по умолчанию для Type
        }

        Type val = this->get_nodule(0)->data;
        this->deleteFront();
        return val;
    }

    /// @brief Проверяет пуста ли очередь
    /// @return Значение true||false
    /// BigO: O(1)
    bool isEmpty()
    {
        return this->Queue<Type>::isEmpty();
    }

    /// @brief Вернет размер очереди
    /// @return size_t - размер
    size_t size() {
        return this->Queue<Type>::size();
    }

    /// @brief Очистка очереди
    /// BigO: O(n)
    void clear()
    {
        while (!this->isEmpty())
        {
            this->dequeue();
        }
    }

    /// @brief Вернет значение конца очереди
    /// @return Type
    Type getBackData() {
        return this->getTailData();
    }

    /// @brief Вернет значение начала очереди
    /// @return Type
    Type getFrontData() {
        return this->getHeadData();
    }

    string to_string() const {
        return this->to_string();
    }
};

/// @brief Функция тестирования метода pushFront
void testPushFront() {
    DeQueue<int> queue;

    queue.pushFront(1);
    assert(queue.getBackData() == 1);

    queue.pushFront(2);
    assert(queue.getBackData() == 2);
    queue.pushFront(3);

    assert(queue.getFrontData() == 1);
    assert(queue.getBackData() == 3);
}

/// @brief Функция тестирования метода pushBach
void testPushBack() {
    DeQueue<int> queue;

    queue.pushBack(1);
    assert(queue.getFrontData() == 1);

    queue.pushBack(2);
    assert(queue.getFrontData() == 2);
    queue.pushBack(3);

    assert(queue.getBackData() == 1);
    assert(queue.getFrontData() == 3);
}

/// @brief Функция тестирования метода popBack
void testPopBack() {
    DeQueue<int> queue;

    //добавляем
    queue.pushFront(1);
    queue.pushFront(2);
    queue.pushFront(3);

    //проверяем
    queue.popBack();
    assert(queue.size() == 2);

    assert(queue.getBackData()  == 3);

    queue.popBack();
    assert(queue.size() == 1);
    assert(queue.getBackData()  == 3);

    assert(queue.popBack() == 3);
    assert(queue.size() == 0);

    //проверка на ассерт пустой очереди double
    DeQueue<double> queueEmpty;
    assert(queueEmpty.popBack() == 0.0);

    //проверка на ассерт пустой очереди строк
    DeQueue<string> queueEmpty2;
    assert(queueEmpty2.popBack() == "");
}

/// @brief Функция тестирования метода popFront
void testPopFront() {
    DeQueue<int> queue;

    //добавляем
    queue.pushBack(1);
    queue.pushBack(2);
    queue.pushBack(3);

    //проверяем
    queue.popFront();
    assert(queue.size() == 2);

    assert(queue.getFrontData()  == 3);

    queue.popFront();
    assert(queue.size() == 1);
    assert(queue.getFrontData()  == 3);

    assert(queue.popFront() == 3);
    assert(queue.size() == 0);

    //проверка на ассерт пустой очереди double
    DeQueue<double> queueEmpty;
    assert(queueEmpty.popFront() == 0.0);

    //проверка на ассерт пустой очереди строк
    DeQueue<string> queueEmpty2;
    assert(queueEmpty2.popFront() == "");
}

/// @brief Тестик для isEmpty
void testIsEmptyHere() {
    DeQueue<int> queue;
    assert(queue.isEmpty());

    queue.pushFront(123);
    assert(!queue.isEmpty());

    queue.popBack();
    assert(queue.isEmpty());
}



/// @brief Функция тестирования класса Stack
void testDeQueue() {
    testPushBack();
    testPushFront();
    testPopBack();
    testPopFront();
    testIsEmptyHere();
}