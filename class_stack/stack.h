#include "listik.h"
#include <cassert>

/// @brief Класс Stack есть представитель структуры данных - стека
/// @tparam Type тип элементов стека
template <typename Type>
// Воспользуемся прошлым классом и сделаем наследование от двусвязного списка
class Stack : private DoublyLinkedList<Type>
{
public:
    /// @brief Добавление элемента в вершину стека
    /// @param element Добавляемый элемент
    void push(Type element)
    {
        this->addFront(element);
    }

    /// @brief Удаление элемента из вершины стека
    Type pop()
    {
        // Если стечек пуст
        if (this->isEmpty())
        {
            return Type();
        }
        // ИНАЧЕ МЯСО
        Type val = this->get_nodule(0)->data;
        this->deleteFront();
        return val;
    }

    /// @brief Проверяет пустой ли стек
    /// @return Значение true||false или 1||0
    bool isEmpty() {
        bool aaa = false;
        if (this->length() == 0) 
            aaa = true;
        return aaa; 
    }

    /// @brief Возращает размер стека
    /// @return Размер стека типа Type
    size_t size() {
        return this->length();
    }

    /// @brief Возращает последний элемент стека
    /// @return Элемент, если список пуст, то 0
    Type peek() {
        if (this->isEmpty())
        {
            return Type();
        }
        return this->get_nodule(0)->data;
    }
    
    /// @brief Очищение стека
    void reset() {
        this->clearList();
    }
};

/// @brief Функция тестирования метода psuh
void testPush() {
    Stack<int> stack;

    stack.push(1);
    assert(stack.peek() == 1);

    stack.push(2);
    assert(stack.peek() == 2);
    stack.push(3);

    assert(stack.peek() == 3);
}

/// @brief Функция тестирования метода pop
void testPop() {
    Stack<int> stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);

    stack.pop();
    assert(stack.size() == 2);

    assert(stack.peek()  == 2);

    stack.pop();
    assert(stack.size() == 1);
    assert(stack.peek()  == 1);

    stack.pop();
    assert(stack.size() == 0);
}

/// @brief Тестирование функции peek
void testPeek() {
    Stack<int> stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);

    assert(stack.peek() == 3);

    stack.pop();
    assert(stack.peek() == 2);

    stack.push(123);
    assert(stack.peek() == 123);
}

/// @brief Тестик для isEmpty
void testIsEmpty() {
    Stack<int> stack;
    assert(stack.isEmpty());

    stack.push(123);
    assert(!stack.isEmpty());
}



/// @brief Функция тестирования класса Stack
void testStack() {
    testPop();
    testPush();
    testIsEmpty();
    testPeek();
}