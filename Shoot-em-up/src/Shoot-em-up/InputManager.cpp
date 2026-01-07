#include "InputManager.h"
#include <iostream>

InputManager* InputManager::Instance = nullptr;

InputManager::InputManager()
{
	Instance = nullptr;
}

InputManager* InputManager::Get()
{
	if (Instance == nullptr)
	{
		Instance = new InputManager;
	}

	return Instance;
}

void InputManager::Update() {
	SDL_PumpEvents();
	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < SDL_NUM_SCANCODES; ++i) 
	{
		_keys[i].isKeyDown = false;
		_keys[i].isKeyUp = false;

		if (_keys[i].lastState == Down)
		{
			_keys[i].isKeyHeld = keyboardState[i];

			if (_keys[i].isKeyHeld)
			{
				_keys[i].lastState = Held;
			}
		}
		if (_keys[i].lastState != Held)
		{
			_keys[i].isKeyDown = keyboardState[i];

			if (_keys[i].isKeyDown)
			{
				_keys[i].lastState = Down;
			}
		}
		if ((_keys[i].lastState == Down || _keys[i].lastState == Held) && keyboardState[i] == 0)
		{
			_keys[i].isKeyUp = true;

			_keys[i].isKeyHeld = false;

			_keys[i].lastState = Released;
		}
	}
}

bool InputManager::IsKeyDown(SDL_Scancode scancode)
{
	return _keys[scancode].isKeyDown;
}

bool InputManager::IsKeyHeld(SDL_Scancode scancode)
{
	return _keys[scancode].isKeyHeld;
}

bool InputManager::IsKeyUp(SDL_Scancode scancode)
{
	return _keys[scancode].isKeyUp;
}