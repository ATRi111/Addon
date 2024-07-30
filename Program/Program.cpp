#include"Program.h"
#include<thread>
#include<time.h>
#include<stdio.h>
using namespace std;
using namespace Tools;

class Father
{
};

class Son : public Father
{

};

void Test1(Father f)
{
    cout << "father" << endl;
}
void Test2(Son s)
{
    cout << "son" << endl;
}

void Log(string message)
{
    cout << message << endl;
}

int main()
{
    EventSystemCore core;
    core.OnLog.Add(Log);
    core.AddListener("Test", Test1);
    core.AddListener("Test", Test2);//错误

    Son s;

    core.Invoke("Test", s);         //错误
    core.Invoke<Father>("Test", s);
    return 0;
}