#include "../Headers/Input.h"

Input::Input()
= default;

Input::~Input()
= default;

Vec2 Input::mousePos = { 0,0 };
bool Input::isClicked = false;
bool Input::W = false;
bool Input::A = false;
bool Input::S = false;
bool Input::D = false;
bool Input::P = false;
bool Input::UP = false;
bool Input::DOWN = false;
bool Input::LEFT = false;
bool Input::RIGHT = false;
bool Input::ESC = false;
bool Input::SPACE = false;
