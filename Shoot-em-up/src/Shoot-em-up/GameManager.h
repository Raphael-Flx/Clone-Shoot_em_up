#pragma once
#include <vector>

#define WIDTH 1600
#define HEIGHT 900

#define CENTERX WIDTH / 2
#define CENTERY HEIGHT / 2

#define FORWARD_ENEMY 0
#define RETURN_ENEMY 1
#define DIAGONAL_ENEMY 2
#define BOSS 3

class Projectile;
class Enemy;
class Entity;
class GameObject;
class Player;

struct SDL_Renderer;
class Entity;

enum class GameState
{
	Start,
	Play,
	GameOver,
	GameWon,
	Quit
};

class GameManager
{
private:
	static GameManager* Instance;

	GameState _state = GameState::Start;
	bool _play = true;

	int _score = 0;
	int _hscore = 0;

	std::vector<Projectile*> _projectiles;
	std::vector<Projectile*> _guidedProjectiles;
	std::vector<Projectile*> _enemyProjectiles;
	std::vector<Enemy*> _enemies;

	Player* _player = nullptr;

	SDL_Renderer* _renderer = nullptr;

	std::vector<Entity*> _parallaxes;

	GameManager()
	{
		Instance = nullptr;
	}

	~GameManager()
	{
		delete Instance;
	}

public:
	static GameManager* Get();

	void Init(SDL_Renderer* renderer);
	void Launch();
	void Shutdown();

	void Start();
	void Play();
	void GameOver();
	void GameWon();

	void AddEnemyProjectile(Projectile* projectile);
	void SpawnEnemy(int enemyType, float spawnX, float spawnY);

	GameObject* GetPlayer();
	SDL_Renderer* GetRenderer();

	void IncreaseScore(int sv);
};

