#include "GameManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "TextManager.h"
#include "AssetManager.h"

#include "Player.h"
#include "Projectile.h"
#include "GuidedProjectile.h"

#include "ForwardEnemy.h"
#include "ReturnEnemy.h"
#include "DiagonalEnemy.h"
#include "Boss.h"

#include "Image.h"
#include "Parallax.h"

#include "Rect.h"
#include "Circle.h"

#include "RectCollider.h"
#include "CircleCollider.h"

#include "Text.h"

#include "Level.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "SDL_mixer.h"

#define FPS 60

Vector2f PLACEMENT[] = { {WIDTH + 10, 200} , {WIDTH + 10, 400 }, {WIDTH + 10, 600}, {WIDTH + 10, 800} };

GameManager* GameManager::Instance = nullptr;

GameManager* GameManager::Get()
{
	if (Instance == nullptr)
	{
		Instance = new GameManager;
	}

	return Instance;
}

void GameManager::Init(SDL_Renderer* renderer)
{
    srand(time(NULL));

    _renderer = renderer;

    Mix_VolumeMusic(60);

    _player = new Player(new Image(100, 50, _renderer, "../../src/Shoot-em-up/images/spaceship.bmp"), new RectCollider(90, 40), 1, 500, 7);
    _player->Resize(200, 75);
    _player->ResizeHitbox(150, 50);

    Entity* parallaxFloor = new Parallax(WIDTH, HEIGHT, renderer, "../../src/Shoot-em-up/images/Background/moon_floor.png", 1000);
    parallaxFloor->Resize(-1, HEIGHT);
    parallaxFloor->SetDirection(-1, 0);

    Entity* parallaxFront = new Parallax(WIDTH, HEIGHT, renderer, "../../src/Shoot-em-up/images/Background/moon_front.png", 600);
    parallaxFront->Resize(-1, HEIGHT);
    parallaxFront->SetDirection(-1, 0);

    Entity* parallaxMid = new Parallax(WIDTH, HEIGHT, renderer, "../../src/Shoot-em-up/images/Background/moon_mid.png", 400);
    parallaxMid->Resize(-1, HEIGHT);
    parallaxMid->SetDirection(-1, 0);

    Entity* parallaxBack = new Parallax(WIDTH, HEIGHT, renderer, "../../src/Shoot-em-up/images/Background/moon_back.png", 250);
    parallaxBack->Resize(-1, HEIGHT);
    parallaxBack->SetDirection(-1, 0);

    Entity* parallaxPlanet = new Parallax(WIDTH, HEIGHT, renderer, "../../src/Shoot-em-up/images/Background/moon_earth.png", 10);
    parallaxPlanet->Resize(-1, HEIGHT);
    parallaxPlanet->SetDirection(-1, 0);

    Entity* parallaxSky = new Parallax(WIDTH, HEIGHT, renderer, "../../src/Shoot-em-up/images/Background/moon_sky.png");
    parallaxSky->Resize(-1, HEIGHT);

    _parallaxes.push_back(parallaxSky);
    _parallaxes.push_back(parallaxPlanet);
    _parallaxes.push_back(parallaxBack);
    _parallaxes.push_back(parallaxMid);
    _parallaxes.push_back(parallaxFront);
    _parallaxes.push_back(parallaxFloor);

    _state = GameState::Start;
    _play = true;

    _score = 0;
}

void GameManager::Launch()
{
    while (_play)
    {
        switch (_state)
        {
        case GameState::Start:
            Start();
            break;
        case GameState::Play:
            Play();
            break;
        case GameState::GameOver:
            GameOver();
            break;
        case GameState::GameWon:
            GameWon();
            break;
        case GameState::Quit:
            _play = false;
            break;
        }
    }
}

void GameManager::AddEnemyProjectile(Projectile* projectile)
{
    _enemyProjectiles.push_back(projectile);
}

void GameManager::SpawnEnemy(int enemyType, float spawnX, float spawnY)
{
    Enemy* enemy;
    switch (enemyType)
    {
    case FORWARD_ENEMY:
        enemy = new ForwardEnemy(new Image(100, 50, _renderer, "../../src/Shoot-em-up/images/ForwardEnemy.png"), new RectCollider(200, 100));
        enemy->Resize(200, 50);
        enemy->ResizeHitbox(190, 45);
        break;
    case RETURN_ENEMY:
        enemy = new ReturnEnemy(new Image(100, 50, _renderer, "../../src/Shoot-em-up/images/ReturnEnemy.png"), new RectCollider(300, 200));
        enemy->Resize(300, 100);
        enemy->ResizeHitbox(290, 90);
        break;
    case DIAGONAL_ENEMY :
        enemy = new DiagonalEnemy(new Image(100, 50, _renderer, "../../src/Shoot-em-up/images/DiagonalEnemy.png"), new RectCollider(100, 50));
        enemy->Resize(75, 50);
        enemy->ResizeHitbox(70, 40);
        break;
    case BOSS:
        enemy = new Boss(new Image(100, 50, _renderer, "../../src/Shoot-em-up/images/Boss.png"), new RectCollider(100, 50));
        enemy->Resize(200, 400);
        enemy->ResizeHitbox(190, 390);
        break;
    default:
        enemy = new ForwardEnemy(new Image(100, 50, _renderer, "../../src/Shoot-em-up/images/ForwardEnemy.png"), new RectCollider(200, 100));
        enemy->Resize(200, 100);
        enemy->ResizeHitbox(190, 90);
        break;
    }

    enemy->SetPosition(spawnX, spawnY, 0, 0.5f);

    _enemies.push_back(enemy);
}

void GameManager::Start()
{
    Text title(_renderer, "../../src/Shoot-em-up/Roboto.ttf", 32, "Moon Invaders", 178, 27);
    title.SetPosition(CENTERX, 100);

    Mix_Chunk* wave = NULL;
    wave = Mix_LoadWAV("../../src/Shoot-em-up/Audio/ambient.wav");
    Mix_VolumeChunk(wave, 60);

    //TTF_SetFontSize("../../src/Shoot-em-up/Roboto.ttf", 32);

    Text howToMove(_renderer, "../../src/Shoot-em-up/Roboto.ttf", 32, "Press the arrow keys to move.", 178, 27);
    howToMove.SetPosition(CENTERX - 100, 350);

    Text howToShoot(_renderer, "../../src/Shoot-em-up/Roboto.ttf", 32, "Press the space bar to shoot.", 178, 27);
    howToShoot.SetPosition(CENTERX / 3, 550);

    Text firingMode(_renderer, "../../src/Shoot-em-up/Roboto.ttf", 32, "Press B to change the firing mode.", 178, 27);
    firingMode.SetPosition(CENTERX / 2 * 3 - 75, 550);

    Text startText(_renderer, "../../src/Shoot-em-up/Roboto.ttf", 32, "Press enter to play.", 178, 27);
    startText.SetPosition(CENTERX - 25, 750);

    for (auto& parallax : _parallaxes)
    {
        parallax->Draw(_renderer);
    }

    title.Draw(_renderer);
    startText.Draw(_renderer);
    howToMove.Draw(_renderer);
    howToShoot.Draw(_renderer);
    firingMode.Draw(_renderer);

    SDL_RenderPresent(_renderer);

    while (InputManager::Get()->IsKeyDown(SDL_SCANCODE_RETURN) == false)
    {
        InputManager::Get()->Update();

        if (Mix_PlayingMusic() == false && wave != NULL)
        {
            Mix_PlayChannel(-1, wave, 0);
        }
    }

    Mix_FadeOutChannel(-1, 750);

    Mix_FreeChunk(wave);
    
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    _state = GameState::Play;
}

void GameManager::IncreaseScore(int sv)
{
    if (_score >= _hscore)
    {
        _hscore = _score + sv;
        _score += sv;
    }
    else
    {
        _score += sv;
    }
}

void GameManager::Play()
{
    std::string highScore = "High Score : " + std::to_string(_hscore);

    Text highScoreText(_renderer, "../../src/Shoot-em-up/Roboto.ttf", 32, highScore.c_str(), 178, 27);
    highScoreText.SetPosition(100, 20);

    std::string scoreNb = "Score : " + std::to_string(_score);

    Text scoreText(_renderer, "../../src/Shoot-em-up/Roboto.ttf", 32, scoreNb.c_str(), 178, 27);
    scoreText.SetPosition(100, 60);

    Image projectileImage(30, 30, _renderer, "../../src/Shoot-em-up/images/shot.png");
    projectileImage.SetPosition(50, 120);

    Rect projectileImageRect(50, 50);
    projectileImageRect.SetPosition(projectileImage.GetPosition().x, projectileImage.GetPosition().y);

    _player->SetPosition((WIDTH / 3) / 2, HEIGHT / 2);

    TimeManager::Get()->SetFpsCap(FPS);

    Level level("../../src/Shoot-em-up/Levels/Level1.txt");

    Mix_Music* music = NULL;
    music = Mix_LoadMUS("../../src/Shoot-em-up/Audio/Main-Theme.mp3"); // "C:\Users\tanta\Documents\GitHub\lyo-1-amstrad-s1p6-06\Shoot-em-up\src\Shoot-em-up\Audio\Main-Theme.mp3"
    Mix_FadeInMusic(music, -1, 50);

    bool play = true;
    float currentTime = 0;

    int enemySpawn = 0;

    while (play)
    {
        InputManager::Get()->Update();
        TimeManager::Get()->StartUpdate();
        float deltaTime = TimeManager::Get()->GetDeltaTime();
        currentTime += deltaTime;
        Vector2f playerPos = _player->GetPosition();

        //EVENTS
        float dx = 0;
        float dy = 0;

        //Move Up
        if (InputManager::Get()->IsKeyDown(SDL_SCANCODE_UP) || InputManager::Get()->IsKeyHeld(SDL_SCANCODE_UP))
        {
            if (playerPos.y - _player->GetHeight() / 2 - _player->GetMoveSpeed() * deltaTime > 0)
            {
                dy -= 1;
            } 
        }
        //Move Down
        if (InputManager::Get()->IsKeyDown(SDL_SCANCODE_DOWN) || InputManager::Get()->IsKeyHeld(SDL_SCANCODE_DOWN))
        {
            if (playerPos.y + _player->GetHeight() / 2 + _player->GetMoveSpeed() * deltaTime < HEIGHT)
            {
                dy += 1;
            }
        }
        //Move Left
        if (InputManager::Get()->IsKeyDown(SDL_SCANCODE_LEFT) || InputManager::Get()->IsKeyHeld(SDL_SCANCODE_LEFT))
        {
            if (playerPos.x - _player->GetWidth() / 2 - _player->GetMoveSpeed() * deltaTime > 0)
            {
                dx -= 1;
            }
        }
        //Move Right
        if (InputManager::Get()->IsKeyDown(SDL_SCANCODE_RIGHT) || InputManager::Get()->IsKeyHeld(SDL_SCANCODE_RIGHT))
        {
            if (playerPos.x + _player->GetWidth() / 2 + _player->GetMoveSpeed() * deltaTime < WIDTH / 3)
            {
                dx += 1;
            }
        }

        //Shoot projectile
        if ((InputManager::Get()->IsKeyDown(SDL_SCANCODE_SPACE) || InputManager::Get()->IsKeyHeld(SDL_SCANCODE_SPACE)) && _player->CanShoot())
        {
            Projectile* projectile;
            switch (_player->GetShootMode())
            {
            case Normal:
                projectile = new Projectile(new Image(128, 128, _renderer, "../../src/Shoot-em-up/images/shot.png"), new RectCollider(32, 16), 1, 2000, 5);
                projectile->SetPosition(playerPos.x + _player->GetWidth() / 2, playerPos.y, 0.f, 0.5f);
                projectile->SetDirection(1, 0);
                _projectiles.push_back(projectile);
                break;
            case Guided:
                projectile = new GuidedProjectile(new Image(32, 32, _renderer, "../../src/Shoot-em-up/images/guidedProjectile.png"), new RectCollider(32, 16));
                Vector2f position = _player->GetPosition(0.5f, 0.5f);
                projectile->SetPosition(position.x + _player->GetWidth() / 2, position.y, 0.f, 0.5f);
                _guidedProjectiles.push_back(projectile);
            }

            _player->Shoot();
        }
        // Change Projectile
        else if (InputManager::Get()->IsKeyDown(SDL_SCANCODE_B))
        {
            int shootMode;
            if (_player->GetShootMode() == Normal)
            {
                shootMode = Guided;
                projectileImage.SetPath(_renderer, "../../src/Shoot-em-up/images/guidedProjectile.png");
                projectileImage.SetPosition(50, 120);
            }
            else
            {
                shootMode = Normal;
                projectileImage.SetPath(_renderer, "../../src/Shoot-em-up/images/shot.png");
                projectileImage.SetPosition(50, 120);
            }

            _player->SetShootMode(shootMode);
        }
        //Quit Game
        if (InputManager::Get()->IsKeyDown(SDL_SCANCODE_ESCAPE))
        {
            play = false;
        }

        //UPDATE

        //End of game conditions
        if (_player->GetHp() <= 0)
        {
            play = false;
            continue;
        }
        else if (level.IsCompleted() == true && _enemies.size() <= 0)
        {
            play = false;
            continue;
        }

        _player->SetDirection(dx, dy);
        _player->Update(deltaTime);

        level.Update(deltaTime);

        for (auto& parallax : _parallaxes)
        {
            parallax->Update(deltaTime);
        }

        //Projectiles Update()
        for (int i = _projectiles.size() - 1; i >= 0; --i)
        {
            //Move projectile
            Vector2f projectilePos = _projectiles[i]->GetPosition();
            _projectiles[i]->Update(deltaTime);

            //Destroy projectile if not on screen
            if (projectilePos.x > WIDTH)
            {
                delete _projectiles[i];
                _projectiles.erase(_projectiles.begin() + i);
                continue;
            }
        }

        //GuidedProjectiles
        for (int i = _guidedProjectiles.size() - 1; i >= 0; --i)
        {
            Vector2f guidedProjectilePos = _guidedProjectiles[i]->GetPosition(0.5f, 0.5f);
            
            if (_enemies.size() <= 0)
            {
                _guidedProjectiles[i]->SetDirection(1, 0);
                _guidedProjectiles[i]->Update(deltaTime);
                continue;
            }
                
            int enemyIndex = 0;                           
            GameObject* target = _enemies[enemyIndex];

            Vector2f targetPos = target->GetPosition();
            
            //Choose closest enemy to current guidedProjectile
            for (int j = 0; j < _enemies.size(); ++j)
            {
                Vector2f enemyPos = _enemies[j]->GetPosition();

                float targetDistance = Maths::GetDistance(targetPos.x, targetPos.y, guidedProjectilePos.x, guidedProjectilePos.y);
                float enemyDistance = Maths::GetDistance(enemyPos.x, enemyPos.y, guidedProjectilePos.x, guidedProjectilePos.y);

                if (enemyDistance < targetDistance)
                {
                    target = _enemies[j];
                    targetPos = target->GetPosition();
                }
            }

            if (guidedProjectilePos.x > WIDTH)
            {
                delete _guidedProjectiles[i];
                _guidedProjectiles.erase(_guidedProjectiles.begin() + i);
            }
            else
            {
                Vector2f direction;

                direction.x = targetPos.x - guidedProjectilePos.x;
                direction.y = targetPos.y - guidedProjectilePos.y;

                _guidedProjectiles[i]->SetDirection(direction.x, direction.y);
                _guidedProjectiles[i]->Update(deltaTime);

            }
        }

        //EnemiesProjectiles
        for (int i = _enemyProjectiles.size() - 1; i >= 0; --i)
        {
            _enemyProjectiles[i]->Update(deltaTime);
            Vector2f projectilePos = _enemyProjectiles[i]->GetPosition();

            if (_enemyProjectiles[i]->IsColliding(_player->GetCollider()))
            {
                _player->TakeDamage(_enemyProjectiles[i]->GetDamage());

                delete _enemyProjectiles[i];
                _enemyProjectiles.erase(_enemyProjectiles.begin() + i);
            }
            else if (projectilePos.x < 0)
            {
                delete _enemyProjectiles[i];
                _enemyProjectiles.erase(_enemyProjectiles.begin() + i);
            }
            else if (projectilePos.y > HEIGHT || projectilePos.y < 0)
            {
                delete _enemyProjectiles[i];
                _enemyProjectiles.erase(_enemyProjectiles.begin() + i);
            }
        }

        //Enemies
        for (int j = _enemies.size() - 1; j >= 0; --j)
        {
            _enemies[j]->Update(deltaTime);
            Vector2f enemyPos = _enemies[j]->GetPosition();

            //Projectiles
            for (int i = _projectiles.size() - 1; i >= 0; --i)
            {
                //Move projectile
                Vector2f projectilePos = _projectiles[i]->GetPosition();

                //Check Collision with enemy
                if (_projectiles[i]->IsColliding(_enemies[j]->GetCollider()))
                {
                    _enemies[j]->TakeDamage(_projectiles[i]->GetDamage());

                    delete _projectiles[i];
                    _projectiles.erase(_projectiles.begin() + i);
                }
            }

            //GuidedProjectiles
            for (int i = _guidedProjectiles.size() - 1; i >= 0; --i)
            {
                //Check Collision with enemy
                if (_guidedProjectiles[i]->IsColliding(_enemies[j]->GetCollider()))
                {
                    _enemies[j]->TakeDamage(_guidedProjectiles[i]->GetDamage());

                    delete _guidedProjectiles[i];
                    _guidedProjectiles.erase(_guidedProjectiles.begin() + i);
                }
            }

            if (enemyPos.x < 0 - _enemies[j]->GetWidth() / 2 || enemyPos.x > WIDTH + _enemies[j]->GetWidth() / 2)
            {
                delete _enemies[j];
                _enemies.erase(_enemies.begin() + j);
                continue;
            }
            else if (enemyPos.y < 0 - _enemies[j]->GetHeight() / 2 || enemyPos.y > HEIGHT + _enemies[j]->GetHeight() / 2)
            {
                delete _enemies[j];
                _enemies.erase(_enemies.begin() + j);
                continue;
            }

            if (_enemies[j]->IsColliding(_player->GetCollider()))
            {
                _player->TakeDamage(_enemies[j]->GetDamage());

                delete _enemies[j];
                _enemies.erase(_enemies.begin() + j);
                continue;
            }

            //Checks enemy's death
            if (_enemies[j]->GetHp() <= 0)
            {
                _enemies[j]->Die();
                delete _enemies[j];
                _enemies.erase(_enemies.begin() + j);
            }
        }

        scoreNb = "Score : " + std::to_string(_score);
        scoreText.SetText(_renderer, scoreNb.c_str());

        highScore = "High Score : " + std::to_string(_hscore);
        highScoreText.SetText(_renderer, highScore.c_str());

        //DRAW
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
        SDL_RenderClear(_renderer);

        SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

        //Draw parallax
        for (auto& parallax : _parallaxes)
        {
            parallax->Draw(_renderer);
        }

        scoreText.Draw(_renderer);
        highScoreText.Draw(_renderer);

        projectileImage.Draw(_renderer);
        projectileImageRect.Draw(_renderer);
        
        _player->Draw(_renderer);

        //Draw Projectiles
        for (auto& projectile : _projectiles)
        {
            SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
            projectile->Draw(_renderer);
        }

        // Draw GuidedProjectiles
        for (auto& guidedprojectile : _guidedProjectiles)
        {
            guidedprojectile->Draw(_renderer);
        }

        // Draw EnemyProjectiles
        for (auto& enemyProjectile : _enemyProjectiles)
        {
            enemyProjectile->Draw(_renderer);
        }

        //Draw Enemies
        for (auto& enemy : _enemies)
        {
            SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
            enemy->Draw(_renderer);
        }

        SDL_RenderPresent(_renderer);

        TimeManager::Get()->EndUpdate();
    }

    //delete all projectiles
    for (int i = _projectiles.size() - 1; i >= 0; --i)
    {
        delete _projectiles[i];
        _projectiles.erase(_projectiles.begin() + i);
    }
    //delete all GuidedProjectiles
    for (int i = _guidedProjectiles.size() - 1; i >= 0; --i)
    {
        delete _guidedProjectiles[i];
        _guidedProjectiles.erase(_guidedProjectiles.begin() + i);
    }
    //delete all enemies projectiles 
    for (int i = _enemyProjectiles.size() - 1; i >= 0; --i)
    {
        delete _enemyProjectiles[i];
        _enemyProjectiles.erase(_enemyProjectiles.begin() + i);
    }
    //delete all enemies
    for (int i = _enemies.size() - 1; i >= 0; --i)
    {
        delete _enemies[i];
        _enemies.erase(_enemies.begin() + i);
    }

    Mix_FadeOutMusic(750);

    if (_player->GetHp() <= 0)
        _state = GameState::GameOver;
    else if (level.IsCompleted())
    {
        _state = GameState::GameWon;
    }
    else
        _state = GameState::Quit;

    Mix_FreeMusic(music);

    delete _player;
}

void GameManager::GameOver()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
    SDL_RenderClear(_renderer);

    for (auto& parallax : _parallaxes)
    {
        parallax->Draw(_renderer);
    }

    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

    Text gameOverText(_renderer, "../../src/Shoot-em-up/Roboto.ttf", 32, "Game Over", 150, 38);
    gameOverText.SetPosition(CENTERX, 50);

    std::string scoreNB = "Score : " + std::to_string(_score);

    Text gameScoreText(_renderer, "../../src/Shoot-em-up/Roboto.ttf", 32, scoreNB.c_str(), 150, 38);
    gameScoreText.SetPosition(CENTERX - gameScoreText.GetWidth() / 2, 200);

    std::string highScore = "High Score : " + std::to_string(_hscore);

    Text gameHighScoreText(_renderer, "../../src/Shoot-em-up/Roboto.ttf", 32, highScore.c_str(), 150, 38);
    gameHighScoreText.SetPosition(CENTERX - gameHighScoreText.GetWidth() / 2, 240);

    Text playAgainText(_renderer, "../../src/Shoot-em-up/Roboto.ttf", 32, "Press enter to play again", 150, 38);
    playAgainText.SetPosition(CENTERX - playAgainText.GetWidth() / 2, CENTERY);

    Text exitText(_renderer, "../../src/Shoot-em-up/Roboto.ttf", 32, "Press escape to exit", 150, 38);
    exitText.SetPosition(CENTERX - exitText.GetWidth() / 2 + 25, 750);

    gameOverText.Draw(_renderer);
    gameScoreText.Draw(_renderer);
    gameHighScoreText.Draw(_renderer);
    playAgainText.Draw(_renderer);
    exitText.Draw(_renderer);

    SDL_RenderPresent(_renderer);

    bool show = true;
    
    while (show)
    {
        InputManager::Get()->Update();
        if (InputManager::Get()->IsKeyDown(SDL_SCANCODE_RETURN))
        {
            show = false;
            Init(_renderer);
        }
        else if (InputManager::Get()->IsKeyDown(SDL_SCANCODE_ESCAPE))
        {
            show = false;
            _state = GameState::Quit;
        }
    }
}

void GameManager::GameWon()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
    SDL_RenderClear(_renderer);

    for (auto& parallax : _parallaxes)
    {
        parallax->Draw(_renderer);
    }

    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

    Mix_Music* music = NULL;
    music = Mix_LoadMUS("../../src/Shoot-em-up/Audio/Credits.mp3");
    Mix_FadeInMusic(music, -1, 750);

    Text gameWonText(_renderer, "../../src/Shoot-em-up/Roboto.ttf", 32, "*+* Game Won *+*", 150, 38);
    gameWonText.SetPosition(CENTERX - gameWonText.GetWidth() / 2, 50);

    Text thanksText(_renderer, "../../src/Shoot-em-up/Roboto.ttf", 32, "Thanks for playing our game !", 150, 38);
    thanksText.SetPosition(CENTERX - thanksText.GetWidth(), 220);

    Text devText(_renderer, "../../src/Shoot-em-up/Roboto.ttf", 32, "Developers : Thibaut CUIRANA, Raphaël FELIX", 150, 38);
    devText.SetPosition(CENTERX - devText.GetWidth() - 50, 300);

    std::string scoreNB = "Score : " + std::to_string(_score);

    Text gameScoreText(_renderer, "../../src/Shoot-em-up/Roboto.ttf", 32, scoreNB.c_str(), 150, 38);
    gameScoreText.SetPosition(CENTERX - gameScoreText.GetWidth() / 2, 400);

    std::string highScore = "High Score : " + std::to_string(_hscore);

    Text gameHighScoreText(_renderer, "../../src/Shoot-em-up/Roboto.ttf", 32, highScore.c_str(), 150, 38);
    gameHighScoreText.SetPosition(CENTERX - gameHighScoreText.GetWidth() / 2, 450);

    Text playAgainText(_renderer, "../../src/Shoot-em-up/Roboto.ttf", 32, "Press enter to play again", 150, 38);
    playAgainText.SetPosition(CENTERX - playAgainText.GetWidth(), 550);

    Text exitText(_renderer, "../../src/Shoot-em-up/Roboto.ttf", 32, "Press escape to exit", 150, 38);
    exitText.SetPosition(CENTERX - exitText.GetWidth() + 25, 750);

    gameWonText.Draw(_renderer);
    thanksText.Draw(_renderer);
    devText.Draw(_renderer);
    gameScoreText.Draw(_renderer);
    gameHighScoreText.Draw(_renderer);
    playAgainText.Draw(_renderer);
    exitText.Draw(_renderer);

    SDL_RenderPresent(_renderer);

    bool show = true;

    while (show)
    {
        InputManager::Get()->Update();
        if (InputManager::Get()->IsKeyDown(SDL_SCANCODE_RETURN))
        {
            show = false;
            Init(_renderer);
        }
        else if (InputManager::Get()->IsKeyDown(SDL_SCANCODE_ESCAPE))
        {
            show = false;
            _state = GameState::Quit;
        }
    }

    Mix_FreeMusic(music);
}

void GameManager::Shutdown()
{
    //delete parallax
    for (int i = _parallaxes.size() - 1; i >= 0; --i)
    {
        delete _parallaxes[i];
        _parallaxes.erase(_parallaxes.begin() + i);
    }

    Mix_CloseAudio();
}

GameObject* GameManager::GetPlayer()
{
    return _player;
}

SDL_Renderer* GameManager::GetRenderer()
{
    return _renderer;
}
