#include"Program.h"
#include<thread>
#include<time.h>
#include<stdio.h>
using namespace std;
using namespace Tools;

void Log(string message)
{
    cout << message << endl;
}

class Father
{
};
class Son : public Father
{
};

static void Test1(Father f)
{
    cout << "father" << endl;
}
static void Test2(Son s)
{
    cout << "son" << endl;
}


int main()
{
    EventSystemCore core;
    core.OnLog.Add(Log);
    core.AddListener("Test", Test1);    
    core.AddListener("Test", Test2);    //错误
    //core.AddListener<Father>("Test", Test2); 编译错误

    Son s;

    core.Invoke("Test", s);             //错误
    core.Invoke<Father>("Test", s);     //正确
    return 0;
}