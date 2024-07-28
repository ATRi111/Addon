#include"Program.h"
#include<thread>
#include<time.h>
#include<stdio.h>
using namespace std;
using namespace Tools;

class Comparer
{
public:
    bool Compare(int a, int b)
    {
        return a > b;
    }
    void Test(int a, int b)
    {
        cout << a << b << endl;
    }
};

bool Handle1(string message)
{
    cout << "1:" << message << endl;
    return false;
}

bool Handle2(string message)
{
    cout << "2:" << message << endl;
    return true;
}
bool Handle3(string message)
{
    cout << "3:" << message << endl;
    return false;
}

int main()
{
    LayeredFuncList<string> LF;
    LF.Add(1, Handle1);
    LF.Add(2, Handle2);
    LF.Add(3, Handle3);

    LF.Invoke("Hello");
    return 0;
}