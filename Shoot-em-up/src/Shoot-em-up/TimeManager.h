#pragma once
#include <SDL.h>

class TimeManager
{
private:
	
	static TimeManager* Instance;

	Uint64 _startTime = 0;
	Uint64 _endTime = 0;
	float _deltaTime;

	int _fpsCap = 60;
	double _targetDeltaTime = .1 / _fpsCap;

	TimeManager()
	{
		Instance = nullptr;
		_deltaTime = 0;
	}
public:
	~TimeManager()
	{
		delete Instance;
		Instance = nullptr;
	}

	static TimeManager* Get();

	float GetDeltaTime();

	void SetFpsCap(int fps);

	void StartUpdate();
	void EndUpdate();
};

