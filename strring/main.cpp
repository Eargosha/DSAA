#include "NewString.h"
#include <iostream>

using namespace std;

int main()
{
    testClassNewString();
    cout << "All tests passed";

    NewString str1 = "goooD!";
    NewString str2 = "goooD!";

    cout << str1 + str2 << endl;

    return 0;
}
