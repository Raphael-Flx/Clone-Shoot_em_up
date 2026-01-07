#pragma once
#include <vector>
#include <string>

class Level
{
private:
	std::vector<std::string> _level = {};

	float _currentTime = 0.f;
	int _currentLine = 1;

	const char* _path;

public:
	Level(const char* path) : _path(path) 
	{
		OpenFile();
	}
	~Level() {}

	void Update(float deltaTime);
	void ReadLevel();
	void OpenFile();

	bool IsCompleted();
};

