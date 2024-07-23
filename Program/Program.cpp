#include"Program.h"
#include<thread>
#include<time.h>
#include<stdio.h>
using namespace std;
using namespace Tools;

GameCycleBase* GameCycle;
bool finished;

static void Tick()
{
	using namespace std::literals::chrono_literals;
	while (!finished)
	{
		GameCycle->Update(0.2f);
		this_thread::sleep_for(0.2s);
	}
}

static void Print(float time)
{
	cout << clock() << endl;
}

int main()
{
	GameCycle = new GameCycleBase(); 
	ITimer::gameCycle = GameCycle;

	Metronome metronome(100.0f);
	metronome.OnTick.Add(Print);
	metronome.Start();

	thread t1(Tick);
	cin.get();
	finished = true;
	t1.join();

    return 0;
}