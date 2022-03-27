#pragma once
class guardCounter
{
public:
	static guardCounter* GetSingleton()
	{
		static guardCounter singleton;
		return  std::addressof(singleton);
	}

	/*Update executes once per frame. Decrement timers for actors in guard counter.*/
	void update();

	/*Register a block, reset timer.*/
	void registerBlock();

	/*Read settings from simpleIni.*/
	void readSettings();

	/*Load all game data.*/
	void loadData();
private:
	//timer for guard counter.
	float gc_Time = 1;
	std::atomic<float> gc_Timer; 

	/*Only when having this spell would trigger guard counter.*/
	RE::SpellItem* gc_triggerSpell;
};