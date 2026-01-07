#include "Level.h"
#include "GameManager.h"
#include <iostream>
#include <fstream>

void Level::Update(float deltaTime)
{
	_currentTime += deltaTime;

	if (_currentTime > 1 * _currentLine)
	{
		if (_currentLine < _level[0].size())
		{
			ReadLevel();
		}

		_currentLine += 1;
	}
}

void Level::ReadLevel()
{
	float gapHeight = HEIGHT / _level.size();


	for (int i = _level.size() - 1; i >= 0; --i)
	{
		if (_currentLine - 1 > _level[i].size())
		{
			continue;
		}

		float currentY = gapHeight / 2 + (i * gapHeight);

		switch (_level[i][_currentLine - 1])
		{
		case 'F':
			GameManager::Get()->SpawnEnemy(FORWARD_ENEMY, WIDTH, currentY);
			break;
		case 'D':
			GameManager::Get()->SpawnEnemy(DIAGONAL_ENEMY, WIDTH, currentY);
			break;
		case 'R':
			GameManager::Get()->SpawnEnemy(RETURN_ENEMY, WIDTH, currentY);
			break;
		case 'B':
			GameManager::Get()->SpawnEnemy(BOSS, WIDTH, currentY);
		}
	}
	
}

void Level::OpenFile()
{
	std::ifstream file(_path);

	if (file.is_open()) 
	{
		std::string line;
		while (std::getline(file, line)) 
		{
			//TODO
			_level.push_back(line);
		}
	}
	else
	{
		std::cout << "File : " << _path << " not found" << std::endl;
	}

	file.close();
}

bool Level::IsCompleted()
{
	return _currentLine >= _level[0].size();
}