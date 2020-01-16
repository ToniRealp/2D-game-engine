#pragma once
#include "GameObject.h"
class Button :public GameObject
{
private:

	Text hoverTexture;
	Text normalTexture;
	Font font;
	std::string mouseName;

public:

	Button(Rect _rect, const GameObjects * _gameObjects, Text _normalTexture, Text _isHoverTexture, Font font,std::string _mouseName);
	~Button();

	void Update() override;

};

