#include "Button.h"

Button::Button(Rect _rect, const GameObjects * _gameObjects, Text _normalTexture,  Text _isHoverTexture, Font _font, std::string _mouseName):GameObject(_rect, Texture("platform", "../../res/img/platform.png"), _gameObjects),
normalTexture(_normalTexture), hoverTexture(_isHoverTexture), font(_font), mouseName(_mouseName)
{
	renderer->LoadFont(_font);
	renderer->LoadTextureText(font.id, hoverTexture);
	renderer->LoadTextureText(font.id, normalTexture);
	collider= new RectCollider(rect);
}

Button::~Button(){}

void Button::Update() 
{
	if (collider->Collides(*gameObjects->at(mouseName)->GetCollider()) != Tools::CollSide::NONE)
		texture.id = hoverTexture.id;
	else
		texture.id = normalTexture.id;
}