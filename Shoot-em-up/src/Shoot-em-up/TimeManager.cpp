#include "TimeManager.h"
#include <iostream>

TimeManager* TimeManager::Instance = nullptr;

TimeManager* TimeManager::Get()
{
	if (Instance == nullptr)
	{
		Instance = new TimeManager;
	}

	return Instance;
}

float TimeManager::GetDeltaTime()
{
	return _deltaTime;
}

void TimeManager::SetFpsCap(int fps)
{
	_fpsCap = fps;
	_targetDeltaTime = 1.f / _fpsCap;
}

void TimeManager::StartUpdate() 
{
	_startTime = SDL_GetTicks64();
}

void TimeManager::EndUpdate() 
{
	_endTime = SDL_GetTicks64();
	_deltaTime = (_endTime - _startTime) / 1000.0f;

	double diff = _targetDeltaTime - _deltaTime;

	if (diff > 0)
	{
		SDL_Delay(diff * 1000);
		_deltaTime = _targetDeltaTime;
	}
}