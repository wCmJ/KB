#include <iostream>
using namespace std;

void test_func3()
{
    throw 3;

    cout << "test func3" << endl;
}

void test_func2()
{
    cout << "test func2" << endl;
    try
    {
        test_func3();
    }
    catch (int)
    {
        cout << "catch 2" << endl;
    }
}

void test_func1()
{
    cout << "test func1" << endl;
    try
    {
        test_func2();
    }
    catch (...)
    {
        cout << "catch 1" << endl;
    }
}

int main()
{
    test_func1();
    return 0;
}
