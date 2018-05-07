#include "..\include\input.h"

Input *Input::instance = NULL;
Input::Input() {
	this->mustquit = false;

	for (unsigned int i = 0; i < 282; i++) {
		keys[i] = false;
		keysDown[i] = false;
		keysUp[i] = false;

		keysalreadyUp[i] = false;
		keysalreadyDown[i] = false;

		if (i < 20) {
			mouseButton[i] = false;
			mouseButtonUp[i] = false;
			mouseButtonDown[i] = false;
		}
	}
}

Input::~Input() {
	if (instance != NULL) {
		delete instance;
	}
}

Input *Input::getInstance() {
	if (Input::instance == NULL) {
		Input::instance = new Input();
	}
	return Input::instance;
}
Vector2 Input::getMouseToScreen() { return Vector2(mousePos.x, mousePos.y); }

void Input::update() {
	int x, y;
	SDL_GetMouseState(&x, &y);
	mousePos = Vector2(x, y);
	SDL_Event event;
	for (unsigned int i = 0; i < 282; i++) {
		if (keysUp[i]) {
			keysUp[i] = false;
		}
		if (keysDown[i]) {
			keysDown[i] = false;
		}
		if (i < 20) {
			if (mouseButtonUp[i]) {
				mouseButtonUp[i] = false;
			}
			if (mouseButtonDown[i]) {
				mouseButtonDown[i] = false;
			}
		}
	}
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			keysalreadyUp[event.key.keysym.scancode] = false;
			if (keysalreadyDown[event.key.keysym.scancode] == false) {
				keysDown[event.key.keysym.scancode] = true;
				keysalreadyDown[event.key.keysym.scancode] = true;
			}
			keys[event.key.keysym.scancode] = true;
			break;
		case SDL_KEYUP:
			keysalreadyDown[event.key.keysym.scancode] = false;
			if (keysalreadyUp[event.key.keysym.scancode] == false) {
				keysUp[event.key.keysym.scancode] = true;
				keysalreadyUp[event.key.keysym.scancode] = true;
			}
			keys[event.key.keysym.scancode] = false;
			break;
		case SDL_QUIT:
			mustquit = true;
			break;

		case SDL_MOUSEBUTTONDOWN:
			mouseButtonAlreadyUp[(int)event.button.button] = false;
			if (!mouseButtonAlreadyDown[(int)event.button.button]) {
				mouseButtonDown[(int)event.button.button] = true;
				mouseButtonAlreadyDown[(int)event.button.button] = true;
			}
			mouseButton[(int)event.button.button] = true;
			break;

		case SDL_MOUSEBUTTONUP:
			mouseButtonAlreadyDown[(int)event.button.button] = false;
			if (!mouseButtonAlreadyUp[(int)event.button.button]) {
				mouseButtonUp[(int)event.button.button] = true;
				mouseButtonAlreadyUp[(int)event.button.button] = true;
			}
			mouseButton[(int)event.button.button] = false;
			break;
		}
	}
}

bool Input::getKey(int keyCode) {
	return keys[SDL_GetScancodeFromKey(keyCode)];
}

bool Input::getKeyUp(int keyCode) {
	return keysUp[SDL_GetScancodeFromKey(keyCode)];
}
bool Input::getKeyDown(int keyCode) {
	return keysDown[SDL_GetScancodeFromKey(keyCode)];
}
bool Input::getMouseButton(int keyCode) { return mouseButton[keyCode]; }
bool Input::getMouseButtonDown(int keyCode) { return mouseButtonDown[keyCode]; }
bool Input::getMouseButtonUp(int keyCode) { return mouseButtonUp[keyCode]; }
