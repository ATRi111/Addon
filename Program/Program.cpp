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

void Print(string message)
{
    cout << message << endl;
}

int main()
{
    EventSystemCore core;
    core.OnLog.Add(Print);

    Comparer c1;
    core.AddListener("Test", &c1, &Comparer::Test);
    core.AddListener("Test", Print);
    core.Invoke("Test", 1, 2);
    core.RemoveListener("Test", &c1, &Comparer::Test);
    core.Invoke("Test", 1, 2.0f);

    return 0;
}