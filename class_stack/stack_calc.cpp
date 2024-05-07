#include <iostream>
#include "stack_calc.h" // Подключаем ваш класс PostfixCalculator

using namespace std;

int main()
{
    StackPostFixCalculator<int> calculator; // Создаем объект калькулятора для типа int
    int result = calculator.solveThisMath( "5 6 + 2 *"); // Вычисляем результат выражения
    cout << "Answereeeeeeeeeeee: " << result << endl;

    assert_math();
    assert_addition();
    assert_sub();
    assert_mult();
    assert_divis();

    return 0;
}
