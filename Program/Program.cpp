#include "Program.h"
using namespace std;
using namespace Tools;

class EventSystem
{
    static EventSystem* instance;
    EventSystem()
    {

    }
public:
    static EventSystem& Instance()
    {
        if (!instance)
            instance = new EventSystem();
        return *instance;
    }

    //arguments:current HP,max HP
    Action<int, int> AfterPlayerHPChange;
};

EventSystem* EventSystem::instance = nullptr;

class Player
{
    int HP;
    EventSystem& eventSystem;
public:
    const int maxHP = 100;
    Player()
        :HP(maxHP), eventSystem(EventSystem::Instance())
    {
        eventSystem.AfterPlayerHPChange.Invoke(HP, maxHP);
    }
    void SetHP(int HP)
    {
        if (HP != this->HP)
        {
            this->HP = HP;
            eventSystem.AfterPlayerHPChange.Invoke(HP, maxHP);
        }
    }
};

class Text
{
    EventSystem& eventSystem;
public:
    Text() 
        :eventSystem(EventSystem::Instance())
    {
        eventSystem.AfterPlayerHPChange.Add(this, &Text::AfterPlayerHPChange);
    }
    void AfterPlayerHPChange(int HP, int maxHP)
    {
        cout << HP << "/" << maxHP << endl;
    }
    ~Text()
    {
        eventSystem.AfterPlayerHPChange.Remove(this, &Text::AfterPlayerHPChange);
    }
};

int main()
{
    Player player;
    {
        Text text;
        player.SetHP(50);
    }
    player.SetHP(80);
    return 0;
}