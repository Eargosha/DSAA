// Author: Eargosha
#include "stack.h"
#include <sstream>
#include <iostream>

using namespace std;

template <typename Type>
/// @brief StackPostFixCalculator - Постфиксный калькулятор, основанный на классе Stack
/// Возможные ошибки: деление на 0 - кинет ошибку runtime_error("Не дели на 0!") с завершением программы без try catch; 
///                   операнд не предусмотрен калькулятором - кинет ошибку runtime_error("Я такого не знаю") с завершением программы без try catch;
class StackPostFixCalculator : private Stack<Type>
{
public:
    /// Главный метод - решение выражения
    Type solveThisMath(const string& input)
    {
        istringstream temp(input); // Создаем поток ввода из строки с постфиксным выражением
        string token; // Переменная для хранения текущего токена
          
        while (temp >> token) { // Цикл по каждому токену в строке
            if (isdigit(token[0])) { // Если токен является числом
                this->push(stoi(token)); // Помещаем число в стек
            } else { // Если токен является оператором
                if (this->size() < 2) { // Проверяем, достаточно ли операндов в стеке
                    cout << "Неправильно написано постфиксное выражение" << endl; // Выводим ошибку о некорректности выражения
                }
                  
                Type o2 = this->pop(); // Удаляем второй операнд из стека // Получаем второй операнд из стека
                  
                Type o1 = this->pop(); // Удаляем первый операнд из стека // Получаем первый операнд из стека           
                  
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
                            throw runtime_error("Не дели на 0!");
                            return -2; // Возвращаем -2
                        }
                        result = o1 / o2; // Выполняем деление
                        break;
                    default:
                        throw runtime_error("Я такого не знаю");
                        return -1; // Возвращаем -1 если калькулятор не предусмотрел такого операнда
                }              
                this->push(result); // Помещаем результат вычисления обратно в стек
            }
        }
          
        if (this->size() != 1) { // Проверяем, что в стеке остался только один элемент (результат вычислений)
            throw invalid_argument("Ошибка связанная со стеком!"); // Бросаем исключение, если в стеке больше одного элемента
        }
          
        Type finalResult = this->peek(); // Получаем окончательный результат из стека
        this->reset();
          
        return finalResult; // Возвращаем окончательный результат вычислений
    }
};

/// @brief Функция проверки сложения +
void assert_addition() {
     StackPostFixCalculator<int> calculator;

     // Постфиксное выражение: 4 3 +
     // Ожидаемый результат: 4 + 3 = 7
     assert(calculator.solveThisMath("4 3 +") == 7);
     
     // Постфиксное выражение: 10 30 +
     // Ожидаемый результат: 10 + 30 = 40
     assert(calculator.solveThisMath("10 30 +") == 40);
     
     // Постфиксное выражение: 14 1230 +
     // Ожидаемый результат: 14 + 1230 = 1244
     assert(calculator.solveThisMath("14 1230 +") == 1244);
}

/// @brief Функция проверки вычисления -
void assert_sub() {
     StackPostFixCalculator<int> calculator;

     // Постфиксное выражение: 4 3 -
     // Ожидаемый результат: 4 - 3 = 7
     assert(calculator.solveThisMath("4 3 -") == 1);
     
     // Постфиксное выражение: 30 10 -
     // Ожидаемый результат: 30 - 10 = 40
     assert(calculator.solveThisMath("30 10 -") == 20);
     
     // Постфиксное выражение: 14 1230 +
     // Ожидаемый результат: 14 + 1230 = 1244
     assert(calculator.solveThisMath("14 1230 -") == -1216);
}

/// @brief Функция проверки умножения *
void assert_mult() {
     StackPostFixCalculator<int> calculator;

     // Постфиксное выражение: 4 3 *
     // Ожидаемый результат: 4 * 3 = 7
     assert(calculator.solveThisMath("4 3 *") == 12);
     
     // Постфиксное выражение: 30 10 *
     // Ожидаемый результат: 30 * 10 = 300
     assert(calculator.solveThisMath("30 10 *") == 300);
     
     // Постфиксное выражение: 14 1230 *
     // Ожидаемый результат: 14 * 1230 = 17220
     assert(calculator.solveThisMath("14 1230 *") == 17220);

     // Постфиксное выражение: 0 0 *
     // Ожидаемый результат: 0 * 0 = 0
     assert(calculator.solveThisMath("0 0 *") == 0);
}

/// @brief Функция проверки деления /
void assert_divis() {
     StackPostFixCalculator<int> calculator;

     // Постфиксное выражение: 12 3 /
     // Ожидаемый результат: 12 / 3 = 7
     assert(calculator.solveThisMath("12 3 /") == 4);
     
     // Постфиксное выражение: 30 10 /
     // Ожидаемый результат: 30 / 10 = 300
     assert(calculator.solveThisMath("30 10 /") == 3);
     
     // Постфиксное выражение: 14 7 /
     // Ожидаемый результат: 14 / 7 = 2
     assert(calculator.solveThisMath("14 7 /") == 2);

     // Постфиксное выражение: 0 0 /
     // Ожидаемый результат: 0 / 0 = 0
    try {
        int temp = calculator.solveThisMath("0 0 /");
    } catch(const exception &e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}

/// @brief Фунция для проверки класса
void assert_math()
{
   // assert_addition();
   // assert_sub();
    StackPostFixCalculator<int> calculator;
    // сделайть по отдельности ассерты на каждый операнд

    // Постфиксное выражение: 5 6 + 2 *
    // Ожидаемый результат: (5 + 6) * 2 = 22
    assert(calculator.solveThisMath("5 6 + 2 *") == 22);

    // Постфиксное выражение: 10 12 13 * +
    // Ожидаемый результат: 10 + (12 * 13) = 165
    assert(calculator.solveThisMath("10 12 13 * +") == 166);

    // Постфиксное выражение: 8 4 / 6 -
    // Ожидаемый результат: (8 / 4) - 6 = -4
    assert(calculator.solveThisMath("8 4 / 6 -") == -4);

    // Постфиксное выражение: 10 20 30 * + 40 -
    // Ожидаемый результат: 10 + (20 * 30) - 40 = 570
    assert(calculator.solveThisMath("10 20 30 * + 40 -") == 570);

    // Для double
    StackPostFixCalculator<double> calculatorDEB;
    assert(calculatorDEB.solveThisMath("2.5 3.7 * 4.1 + 6.3 -") == 4);
    // Если исключение не было вызвано, что является ошибкой
    try {
        int temp = calculator.solveThisMath("3 0 /");
    } catch(const exception &e) {
        cerr << "Ошибка: " << e.what() << endl;
    }

}