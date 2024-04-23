// Author: Eargosha
#include "stack.h"
#include <sstream>
#include <iostream>

using namespace std;

template <typename Type>
/// @brief StackPostFixCalculator - Постфиксный калькулятор, основанный на классе Stack
/// Возможные ошибки: деление на 0 - вернет код -2, операнд не предусмотрен калькулятором - -1 
class StackPostFixCalculator : public Stack<Type>
{
public:
    /// Вычисление значения постфиксного выражения
    Type solveThisMath(const string& input)
    {
        istringstream temp(input); // Создаем поток ввода из строки с постфиксным выражением
        string token; // Переменная для хранения текущего токена
          
        while (temp >> token) { // Цикл по каждому токену в строке
            if (isdigit(token[0])) { // Если токен является числом
                this->push(stoi(token)); // Помещаем число в стек
            } else { // Если токен является оператором
                if (this->size() < 2) { // Проверяем, достаточно ли операндов в стеке
                    cout << "Неправильно написано постфиксное выражение" << endl; // Бросаем исключение, если операндов недостаточно
                }
                  
                Type o2 = this->peek(); // Получаем второй операнд из стека
                this->pop(); // Удаляем второй операнд из стека
                  
                Type o1 = this->peek(); // Получаем первый операнд из стека
                this->pop(); // Удаляем первый операнд из стека
                  
                Type result; // Переменная для хранения результата вычисления
                  
                switch (token[0]) { // Выполняем операцию в зависимости от оператора
                    case '+':
                        result = o1 + o2;
                        break;
                    case '-':
                        result = o1 - o2;
                        break;
                    case '*':
                        result = o1 * o2;
                        break;
                    case '/':
                        if (o2 == 0) { // Проверяем деление на ноль
                            return -2; // Возвращаем -2
                        }
                        result = o1 / o2; // Выполняем деление
                        break;
                    default:
                        return -1; // Возвращаем -1 если калькулятор не предусмотрел такого операнда
                }              
                this->push(result); // Помещаем результат вычисления обратно в стек
            }
        }
          
        if (this->size() != 1) { // Проверяем, что в стеке остался только один элемент (результат вычислений)
            throw invalid_argument("Ошибка связанная со стеком!"); // Бросаем исключение, если в стеке больше одного элемента
        }
          
        Type finalResult = this->peek(); // Получаем окончательный результат из стека
        this->reset(); // Очищаем стек
          
        return finalResult; // Возвращаем окончательный результат вычислений
    }
};

/// @brief Фунция для проверки класса
void assert_calc()
{
    StackPostFixCalculator<int> calculator;
    // Постфиксное выражение: 3 4 + 2 *
    // Ожидаемый результат: (3 + 4) * 2 = 14
    assert(calculator.solveThisMath("3 4 + 2 *") == 14);

    // Постфиксное выражение: 5 2 3 * +
    // Ожидаемый результат: 5 + (2 * 3) = 11
    assert(calculator.solveThisMath("5 2 3 * +") == 11);

    // Постфиксное выражение: 8 4 / 6 -
    // Ожидаемый результат: (8 / 4) - 6 = -4
    assert(calculator.solveThisMath("8 4 / 6 -") == -4);

    // Постфиксное выражение: 1 2 3 * + 4 -
    // Ожидаемый результат: 1 + (2 * 3) - 4 = 3
    assert(calculator.solveThisMath("1 2 3 * + 4 -") == 3);

    // Если исключение не было вызвано, что является ошибкой
    assert(calculator.solveThisMath("3 0 /") == -2);

    //ОПА - DOUBLE
    StackPostFixCalculator<double> calculatorDEB;
    assert(calculatorDEB.solveThisMath("2.5 3.7 * 4.1 + 6.3 -") == 4);
}