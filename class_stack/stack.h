#include "listik.h"
#include <cassert>

/// @brief Класс Stack есть представитель структуры данных - стека
/// @tparam Type тип элементов стека
template <typename Type>
// Воспользуемся прошлым классом и сделаем наследование от двусвязного списка
class Stack : public DoublyLinkedList<Type>
{
public:
    /// @brief Добавление элемента в вершину стека
    /// @param element Добавляемый элемент
    void push(Type element)
    {
        this->addFront(element);
    }

    /// @brief Удаление элемента из вершины стека
    void pop()
    {
        // Если стечек пуст
        if (this->length() == 0)
        {
            throw out_of_range("Stack is empty!");
            return;
        }
        // ИНАЧЕ МЯСО
        this->deleteFront();
    }
};

/// @brief Функция тестирования метода psuh
void testPush() {
    Stack<int> stack;

    stack.push(1);
    assert(stack.get_nodule(0)->data == 1);

    stack.push(2);
    assert(stack.get_nodule(0)->data == 2);
    stack.push(3);

    assert(stack.get_nodule(1)->data == 2);
    assert(stack.get_nodule(0)->data == 3);
}

/// @brief Функция тестирования метода pop
void testPop() {
    Stack<int> stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);

    stack.pop();
    assert(stack.length() == 2);
    assert(stack.get_nodule(0)->data  == 2);

    stack.pop();
    assert(stack.length() == 1);
    assert(stack.get_nodule(0)->data  == 1);

    stack.pop();
    assert(stack.length() == 0);
}

/// @brief Функция тестирования класса Stack
void testStack() {
    testPop();
    testPush();
}