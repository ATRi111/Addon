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
        
    }
};

void Print()
{

}

int main()
{
    Comparer c1, c2;
    Action<int, int> a1;
    
    Action<int,int> a2;

    Delegate* d1 = &a1;
    Delegate* d2 = &a2;
    cout << d1->HasSameParameters(d2);
    return 0;
}