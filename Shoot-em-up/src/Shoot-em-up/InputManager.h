#pragma once
#include "SDL.h"

#define Down 1
#define Held 2
#define Released 3

struct Key 
{
	int lastState = 0;
	bool isKeyDown = 0;
	bool isKeyHeld = 0;
	bool isKeyUp = 0;
};

class InputManager
{
private:
	Key _keys[SDL_NUM_SCANCODES] = {};

	static InputManager* Instance;
public:
	InputManager();
	static InputManager* Get();

	void Update();

	bool IsKeyDown(SDL_Scancode scancode);
	bool IsKeyHeld(SDL_Scancode scancode);
	bool IsKeyUp(SDL_Scancode scancode);
};

